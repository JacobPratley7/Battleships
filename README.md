# Battleships

A C based implementation of the classic game Battleships. This game involves two players and an assortment of ships. Each player is given their own set of ships (5) which will be of different variations. 

Each player will have an 8x8 board, where the y axis is referred to by letters (A-H) while the x axis is referred to by numbers (1-8). You will need to translate these coordinates for both a ship configuration board and hitboard.

Each player will have their own configuration of ships, each ship will have a vertical or horizontal configuration and the set number of spaces that they occupy.

Each player will get a chance to set up their ships prior to the game starting. Each player will need to set coordinates and an orientation for their ship. If the ship does not collide with any other ship that the player has and does not go outside of the bounds of the board, it will be accepted.

## Board

Each player has their own 'hit' board which will record the cells they have hit. The board will be presented in a terminal window as a 8x8 grid. Each cell will have a `|` on left and right side.


## Ship

There are 5 ships for each player, each ship has a location on the board and a length and orientation. The length of a ship corresponds to the number of hittable sections, once a section has been hit, it will unable to be hit again. Once a ship has been hit the program will output `We have hit the target!`. Once the ship has been destroyed, the program will output `We have sunk your ` followed by the ship name. If the shot is missed, the program will output `You have missed!`.

Example:
`We have sunk your Carrier`


There are 5 different ships and are covers a different amount of cells

* Carrier, 5 cells
* Battleship, 4 cells
* Destroyer, 3 cells
* Submarine, 2 cells
* Patrol Boat, 2 cells
  

## Player

Each player has 5 ships part of their fleet and their own hit board. Each fleet is made up of the following ships,

* Carrier
* Battleship
* Destroyer
* Submarine
* Patrol Boat

A player will have a chance to take a shot at the opponents fleet. The player will need to input the coordinates in the following format:

`[A-H] [1-8]`.

The grid will be labelled like so: 

```
  1 2 3 4 5 6 7 8
A| | | | | | | | |
B| | | | | | | | |
C| | | | | | | | |
D| | | | | | | | |
E| | | | | | | | |
F| | | | | | | | |
G| | | | | | | | |
H| | | | | | | | |
```

Coordinate placement starts from left (specified coordinate) to right for horizontal and top (specified coordinate) to bottom.

Left to right placement

```
Destroyer at C 3 H

  1 2 3 4 5 6 7 8
A| | | | | | | | |
B| | | | | | | | |
C| | |*|*|*| | | |
D| | | | | | | | |
E| | | | | | | | |
F| | | | | | | | |
G| | | | | | | | |
H| | | | | | | | |
```

Top to bottom placement

```
Destroyer at D 3 V

  1 2 3 4 5 6 7 8
A| | | | | | | | |
B| | | | | | | | |
C| | | | | | | | |
D| | |*| | | | | |
E| | |*| | | | | |
F| | |*| | | | | |
G| | | | | | | | |
H| | | | | | | | |
```

## Commands

Your program must support the following commands

* shots - Shows the shots on a grid 
* fire <A-H> <1-8> - Fires a shot at this location
* exit - Quits the game early



