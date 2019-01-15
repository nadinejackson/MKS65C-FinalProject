# MKS65C-final

### SET

Mr. Kthxbye (Raymond Wu and Nadine Jackson)
    
## Project description 
Our project is to create the game SET in the terminal with multiple players such that computers can connect to a server in order to initiate a game. Our project seeks to solve the problem where in real-life gameplay, there could be disputes over who saw a set first. As players call a valid set, the set is immediately removed from the board on all of the players’ interfaces. Our program will log in and connect players and a shared memory leaderboard for stats. At most one client will run on any one computer.

## Required libraries
No required libraries.

## How to run:
0. Open 3 terminals.
1. Compile the necessary source code by running `$ make`
2. Start a server by running `$ ./server`
3. Open a new terminal window in the current working directory. Run `$ ./client` to start a client (for the first player).
4. Open a new terminal window in the current working directory. Run `$ ./client` to start a second client (for the second player).
