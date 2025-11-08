import sys
import copy

from crossword import *


class CrosswordCreator():

    def __init__(self, crossword):
        """
        Create new CSP crossword generate.
        """
        self.crossword = crossword
        self.domains = {
            var: self.crossword.words.copy()
            for var in self.crossword.variables
        }

    def letter_grid(self, assignment):
        """
        Return 2D array representing a given assignment.
        """
        letters = [
            [None for _ in range(self.crossword.width)]
            for _ in range(self.crossword.height)
        ]
        for variable, word in assignment.items():
            direction = variable.direction
            for k in range(len(word)):
                i = variable.i + (k if direction == Variable.DOWN else 0)
                j = variable.j + (k if direction == Variable.ACROSS else 0)
                letters[i][j] = word[k]
        return letters

    def print(self, assignment):
        """
        Print crossword assignment to the terminal.
        """
        letters = self.letter_grid(assignment)
        for i in range(self.crossword.height):
            for j in range(self.crossword.width):
                if self.crossword.structure[i][j]:
                    print(letters[i][j] or " ", end="")
                else:
                    print("█", end="")
            print()

    def save(self, assignment, filename):
        """
        Save crossword assignment to an image file.
        """
        from PIL import Image, ImageDraw, ImageFont
        cell_size = 100
        cell_border = 2
        interior_size = cell_size - 2 * cell_border
        letters = self.letter_grid(assignment)

        # Create a blank canvas
        img = Image.new(
            "RGBA",
            (self.crossword.width * cell_size,
             self.crossword.height * cell_size),
            "black"
        )
        font = ImageFont.truetype("assets/fonts/OpenSans-Regular.ttf", 80)
        draw = ImageDraw.Draw(img)

        for i in range(self.crossword.height):
            for j in range(self.crossword.width):

                rect = [
                    (j * cell_size + cell_border,
                     i * cell_size + cell_border),
                    ((j + 1) * cell_size - cell_border,
                     (i + 1) * cell_size - cell_border)
                ]
                if self.crossword.structure[i][j]:
                    draw.rectangle(rect, fill="white")
                    if letters[i][j]:
                        w, h = draw.textsize(letters[i][j], font=font)
                        draw.text(
                            (rect[0][0] + ((interior_size - w) / 2),
                             rect[0][1] + ((interior_size - h) / 2) - 10),
                            letters[i][j], fill="black", font=font
                        )

        img.save(filename)

    def solve(self):
        """
        Enforce node and arc consistency, and then solve the CSP.
        """
        self.enforce_node_consistency()
        self.ac3()
        return self.backtrack(dict())

    def enforce_node_consistency(self):
        """
        Update `self.domains` such that each variable is node-consistent.
        (Remove any values that are inconsistent with a variable's unary
         constraints; in this case, the length of the word.)
        """
        for v in self.crossword.variables:
            for x in copy.deepcopy(self.domains[v]):
                if len(x)!=v.length:
                    self.domains[v].remove(x)
                    
        #raise NotImplementedError

    def revise(self, x, y):
        """
        Make variable `x` arc consistent with variable `y`.
        To do so, remove values from `self.domains[x]` for which there is no
        possible corresponding value for `y` in `self.domains[y]`.

        Return True if a revision was made to the domain of `x`; return
        False if no revision was made.
        """
        revise=False
        i=self.crossword.overlaps[x,y]
        if i!=None:
            for l in copy.deepcopy(self.domains[x]):
                z=0
                for m in self.domains[y]:
                    if l[i[0]]==m[i[1]]:
                        z=1
                        break
                if z==0:
                    self.domains[x].remove(l)
                    revise=True
            
        return revise
        #raise NotImplementedError
    
    def count(self,x,y,word):
        count=0
        i=self.crossword.overlaps[x,y]
        if i!=None:
            for l in self.domains[x]:
                if l[i[0]]!=word[i[1]]:
                    count+=1
        return count
        

    def ac3(self, arcs=None):
        """
        Update `self.domains` such that each variable is arc consistent.
        If `arcs` is None, begin with initial list of all arcs in the problem.
        Otherwise, use `arcs` as the initial list of arcs to make consistent.

        Return True if arc consistency is enforced and no domains are empty;
        return False if one or more domains end up empty.
        """
        queue=[]
        if arcs==None:
             for i in self.crossword.overlaps:
                if self.crossword.overlaps[i]==None:
                    queue.append(i)
        
        elif arcs!=None:
            queue=arcs
        
        while len(queue)!=0:
            i=queue.pop(0)
            if self.revise(i[0],i[1]):
                if len(self.domains[i[0]])==0:
                    return False
                
                for z in self.crossword.neighbors(i[0]):
                    queue.append((z,i[0]))
        return True
                
        #raise NotImplementedError

    def assignment_complete(self, assignment):
        """
        Return True if `assignment` is complete (i.e., assigns a value to each
        crossword variable); return False otherwise.
        """
        if len(self.crossword.variables)==len(assignment):
            return True
        return False
        #raise NotImplementedError

    def consistent(self, assignment):
        """
        Return True if `assignment` is consistent (i.e., words fit in crossword
        puzzle without conflicting characters); return False otherwise.
        """
        for i in assignment:
          for j in assignment:
            if i==j:
                continue
            if self.crossword.overlaps[i,j]!=None:
                (a,b)=self.crossword.overlaps[i,j]
                if assignment[i][a]!=assignment[j][b]:
                    return False
            
            if assignment[i]==assignment[j] or j.length!=len(assignment[j]):
                return False
        return True
        #raise NotImplementedError

    def order_domain_values(self, var, assignment):
        """
        Return a list of values in the domain of `var`, in order by
        the number of values they rule out for neighboring variables.
        The first value in the list, for example, should be the one
        that rules out the fewest values among the neighbors of `var`.
        """
        lisr=[]
        least=[]
        for current in self.domains[var]:
           number=0
           for i in self.crossword.neighbors(var):
             if i not in assignment:
               number+=self.count(i,var,current)
           lisr.append([number,current])
        lisr.sort()
        for i in lisr:
            least.append(i[1])
        return least
        
                               
        
        #raise NotImplementedError

    def select_unassigned_variable(self, assignment):
        """
        Return an unassigned variable not already part of `assignment`.
        Choose the variable with the minimum number of remaining values
        in its domain. If there is a tie, choose the variable with the highest
        degree. If there is a tie, any of the tied variables are acceptable
        return values.
        """
        num=0
        minlist=[]
        for i in self.crossword.variables:
            if i not in assignment:
                num+=1
                minlist.append([len(self.domains[i]),len(self.crossword.neighbors(i)),num,i])
        Min=copy.deepcopy(min(minlist)[0])
        for j in copy.deepcopy(minlist):
            if j[0]>Min:
                 minlist.remove(j)
                       
        return max(minlist)[3]
        
                
                             
        #raise NotImplementedError

    def backtrack(self, assignment):
        """
        Using Backtracking Search, take as input a partial assignment for the
        crossword and return a complete assignment if possible to do so.

        `assignment` is a mapping from variables (keys) to words (values).

        If no assignment is possible, return None.
        """
        if self.assignment_complete(assignment):
            return assignment
        var=self.select_unassigned_variable(assignment)
        for i in copy.deepcopy(self.order_domain_values(var, assignment)):
            assignment[var]=i
            if self.consistent(assignment):
                result=self.backtrack(assignment)
                if result!=None:
                    return result
            assignment.pop(var)
        return None
        #raise NotImplementedError


def main():

    # Check usage
    if len(sys.argv) not in [3, 4]:
        sys.exit("Usage: python generate.py structure words [output]")

    # Parse command-line arguments
    structure = sys.argv[1]
    words = sys.argv[2]
    output = sys.argv[3] if len(sys.argv) == 4 else None

    # Generate crossword
    crossword = Crossword(structure, words)
    creator = CrosswordCreator(crossword)
    assignment = creator.solve()

    # Print result
    if assignment is None:
        print("No solution.")
    else:
        creator.print(assignment)
        if output:
            creator.save(assignment, output)


if __name__ == "__main__":
    main()
