# Conway's game of life - Plan

## Rules of the game

Universe consists of an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, _live_ or _dead_.

Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically or diagonally adjacent.

**Time step transitions**

1. Any live cell with _fewer than two live neighbours_ dies, as if by underpopulation.
2. Any live cell with _two or three live neighbours_ lives on to the next generation.
3. Any live cell with _more than three live neighbours_ dies, as if by overpopulation.
4. Any dead cell with _exactly three live neighbours_ becomes a live cells, as if by reproduction

## High level overview of data structures

- grid of cells (booleans)

## Display requirements

- size of grid (for basic implementation)
- random seed

## interactivity requirements

- [x] user should be able to pause the simulation 
- [x] user should be able to reset the grid
- [x] user should be able to erase (fill cells with 0s)
- [x] user should be able to fill cells (fill cells with 1s)
- [ ] user should be able to set the size of the simulation 
- [ ] user should be able to play the simulation and watch it progress

## Directory structure

- static
    - index.html (main display for page)
    - index.js (contains functions for user interactivity)
        - initSim() initialize the display board and the boardState global variable
        - update() update the display board based on the boardState global variable
 
    - target
        - life.js
        - life.wasm
- src
    - life.cpp
        - clear_cell(int x, int y) given the coordinates of a cell, change its contents to a 0
        - fill_cell(int x, int y) given the coordinates of a cell, change its contents to a 1
        - step() advances the simulation by one step, returns array of cell locations to change
        - resetSim()
- run (script that sets up test server)
- kill_srv (script that kills server using process id stored in pid file)


