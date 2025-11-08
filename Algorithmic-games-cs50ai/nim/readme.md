# CS50 AI: Nim Game

This repository contains an implementation of the **Nim Game** as part of the CS50's Introduction to Artificial Intelligence with Python course. The project demonstrates the use of AI techniques to create a computer player that learns to play Nim optimally through reinforcement learning.

## About Nim

Nim is a mathematical game of strategy where two players take turns removing objects from heaps. On each turn, a player must remove at least one object, and they may remove any number of objects from a single heap. The player who takes the last object wins.

## Features

- **Reinforcement Learning**: The AI learns optimal strategies by playing games against itself.
- **Human vs AI**: Play against the trained AI.
- **Customizable Game**: Adjust the number of heaps and objects per heap.

## How It Works

The AI uses a Q-learning algorithm to improve its strategy over time. By simulating thousands of games, it learns which actions lead to winning outcomes and adjusts its policy accordingly.

## Project Structure

- `nim.py`: Main game logic and AI implementation.
- `train.py`: Script to train the AI.
- `readme.md`: Project documentation.
