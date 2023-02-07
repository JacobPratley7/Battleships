#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int p1tiles[8][8] = {0};
int p2tiles[8][8] = {0};
int p1shots[8][8] = {0};
int p2shots[8][8] = {0};

int p1c_coords[5][2];
int p1b_coords[4][2];
int p1d_coords[3][2];
int p1s_coords[2][2];
int p1p_coords[2][2];

int p1c_health[5];
int p1b_health[4];
int p1d_health[3];
int p1s_health[2];
int p1p_health[2];

int *p1carrier = p1c_health;
int *p1battleship = p1b_health;
int *p1destroyer = p1d_health;
int *p1submarine = p1s_health;
int *p1patrol = p1p_health;

int p1c_dead = 0;
int p1b_dead = 0;
int p1d_dead = 0;
int p1s_dead = 0;
int p1p_dead = 0;
int p1total_dead = 0;

int p2c_coords[5][2];
int p2b_coords[4][2];
int p2d_coords[3][2];
int p2s_coords[2][2];
int p2p_coords[2][2];

int p2c_health[5];
int p2b_health[4];
int p2d_health[3];
int p2s_health[2];
int p2p_health[2];

int *p2carrier = p2c_health;
int *p2battleship = p2b_health;
int *p2destroyer = p2d_health;
int *p2submarine = p2s_health;
int *p2patrol = p2p_health;

int p2c_dead = 0;
int p2b_dead = 0;
int p2d_dead = 0;
int p2s_dead = 0;
int p2p_dead = 0;
int p2total_dead = 0;

int printed_1 = 0;
int printed_2 = 0;
int printed_3 = 0;
int printed_4 = 0;
int printed_5 = 0;
int printed_6 = 0;
int printed_7 = 0;
int printed_8 = 0;
int printed_9 = 0;
int printed_10 = 0;

int available(int player, int row, int column, int size, char direction) {
    if(player == 1) {
        if(direction == 'V') {
            for(int i = 0; i < size; i++) {
                if(p1tiles[row][column] != 0) {
                    return 0;
                } else {
                    row++;
                }
            }
            return 1;
        } else {
            for(int i = 0; i < size; i++) {
                if(p1tiles[row][column] != 0) {
                    return 0;
                } else {
                    column++;
                }
            }
            return 1;
        }
    } else {
        if(direction == 'V') {
            for(int i = 0; i < size; i++) {
                if(p2tiles[row][column] != 0) {
                    return 0;
                } else {
                    row++;
                }
            }
            return 1;
        } else {
            for(int i = 0; i < size; i++) {
                if(p2tiles[row][column] != 0) {
                    return 0;
                } else {
                    column++;
                }
            }
            return 1;
        }
    }

}

int allocate(char string[], int player, int ship[][2], int size) {
    char final[5];
    for(unsigned long i = 0; i < strlen(string); i++) {
        if(i >= 5) {
            break;
        } else {
            final[i] = string[i];
        }
    }

    if(sizeof(final) != 5) {
        printf("Invalid ship configuration\n");
        return 0;
    }
    if(final[4] != 'V' && final[4] != 'H') {
        printf("Invalid ship configuration\n");
        printf("%c\n", final[4]);
        return 0;
    }
    if(final[4] == 'V') {
        int column = final[2] - 49;
        int strow = final[0] - 65;
        if((column >= 8) || strow + size - 1 >= 8) {
            printf("Invalid ship configuration\n");
            return 0;
        } else {
            int count = 0;
            if(available(player, strow, column, size, 'V') != 1) {
                printf("Invalid ship configuration\n");
                return 0;
            } else {
                for(; count < size; count++) {
                    if(player == 1) {
                        p1tiles[strow][column] = 1;
                        ship[count][0] = strow;
                        ship[count][1] = column;
                        strow++;
                    } else {
                        p2tiles[strow][column] = 1;
                        ship[count][0] = strow;
                        ship[count][1] = column;
                        strow++;
                    }
                }
            }
            return 1;
        }
    }
    if(final[4] == 'H') {
        int column = final[2] - 49;
        int strow = final[0] - 65;
        if((strow >= 8) || column + size - 1 >= 8) {
            printf("Invalid ship configuration\n");
            return 0;
        } else {
            int count = 0;
            if(available(player, strow, column, size, 'H') != 1) {
                printf("Invalid ship configuration\n");
                return 0;
            }
            for(; count < size; count++) {
                if(player == 1) {
                    p1tiles[strow][column] = 1;
                    ship[count][0] = strow;
                    ship[count][1] = column;
                    column++;
                } else {
                    p2tiles[strow][column] = 1;
                    ship[count][0] = strow;
                    ship[count][1] = column;
                    column++;
                }
            }
            return 1;
        }

    }
    return 0;
}

void removeLine(char line[]) {
    int len = strlen(line);
    for(int i = 0; i < len; i++) {
        if(line[i] == '\n') {
            line[i] = 0;
            break;
        }
    }
}

//hello there
void setup1() {
    printf("Player 1, please set up your ships (y, x, orientation)\n");
    while(1) {
        char input[7];
        printf("Carrier: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 1, p1c_coords, 5) == 1) {
            break;
        }
    }
    while(1) {
        char input[7];
        printf("Battleship: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 1, p1b_coords, 4) == 1) {
            break;
        }
    }
    while(1) {
        char input[7];
        printf("Destroyer: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 1, p1d_coords, 3) == 1) {
            break;
        }
    }
    while(1) {
        char input[7];
        printf("Submarine: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 1, p1s_coords, 2) == 1) {
            break;
        }
    }
    while(1) {
        char input[7];
        printf("Patrol Boat: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 1, p1p_coords, 2) == 1) {
            break;
        }
    }
    printf("\n");
    printf("\n");
    return;
}

void setup2() {
    printf("Player 2, please set up your ships (y, x, orientation)\n");
    while(1) {
        char input[7];
        printf("Carrier: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 2, p2c_coords, 5) == 1) {
            break;
        }
    }
    while(1) {
        char input[7];
        printf("Battleship: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 2, p2b_coords, 4) == 1) {
            break;
        }
    }
    while(1) {
        char input[7];
        printf("Destroyer: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 2, p2d_coords, 3) == 1) {
            break;
        }
    }
    while(1) {
        char input[7];
        printf("Submarine: ");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 2, p2s_coords, 2) == 1) {
            break;
        }
    }
    while(1) {
        char input[7];
        printf("Patrol Boat: \n");
        fgets(input, 7, stdin);
        removeLine(input);
        if(allocate(input, 2, p2p_coords, 2) == 1) {
            break;
        }
    }
    printf("All boats set up, Player 1 can now strike.\n");
    printf("\n");
    return;
}

void draw(int tiles[8][8], int shots[8][8]) {
    printf("\n");
    printf("%s\n", "  1 2 3 4 5 6 7 8");
    for(int i = 0; i < 8; i++) {
        printf("%c", i + 65);
        for(int j = 0; j < 8; j++) {
            if(shots[i][j] == 0) {
                printf("%s", "| ");
            } else if(shots[i][j] == 1 && (tiles[i][j] == 1 || tiles[i][j] == 2)) {
                printf("%s", "|X");
            } else {
                printf("%s", "|0");
            }
        }
        printf("%s\n", "|");
    }
    printf("\n");
}

int checkShip(int  *ship, int dead, int total, int size) {
    for(int i = 0; i < size; i++) {
        if(*(ship + i) != 1) {
            return 0;
        }
    }
    //printf("dead");
    dead = 1;
    total++;

    return 1;
}

void hit1(int row, int column, int size, int ship_id) {
    if(ship_id == 1) {
        for(int i = 0; i < size; i++) {
            if(p1c_coords[i][0] == row && p1c_coords[i][1] == column) {
                p1c_health[i] = 1;
                return;
            }
        }
    } else if (ship_id == 2) {
        for(int i = 0; i < size; i++) {
            if(p1b_coords[i][0] == row && p1b_coords[i][1] == column) {
                p1b_health[i] = 1;
                return;
            }
        }
    } else if(ship_id == 3) {
        for(int i = 0; i < size; i++) {
            if(p1d_coords[i][0] == row && p1d_coords[i][1] == column) {
                p1d_health[i] = 1;
                return;
            }
        }
    } else if(ship_id == 4) {
        for(int i = 0; i < size; i++) {
            if(p1s_coords[i][0] == row && p1s_coords[i][1] == column) {
                p1s_health[i] = 1;
                return;
            }
        }
    } else {
        for(int i = 0; i < size; i++) {
            if(p1p_coords[i][0] == row && p1p_coords[i][1] == column) {
                p1p_health[i] = 1;
                return;
            }
        }
    }
}

void hit2(int row, int column, int size, int ship_id) {
    if(ship_id == 1) {
        for(int i = 0; i < size; i++) {
            if(p2c_coords[i][0] == row && p2c_coords[i][1] == column) {
                p2c_health[i] = 1;
                return;
            }
        }
        return;
    } else if (ship_id == 2) {
        for(int i = 0; i < size; i++) {
            if(p2b_coords[i][0] == row && p2b_coords[i][1] == column) {
                p2b_health[i] = 1;
                return;
            }
        }
        return;
    } else if(ship_id == 3) {
        for(int i = 0; i < size; i++) {
            if(p2d_coords[i][0] == row && p2d_coords[i][1] == column) {
                p2d_health[i] = 1;
                return;
            }
        }
        return;
    } else if(ship_id == 4) {
        for(int i = 0; i < size; i++) {
            if(p2s_coords[i][0] == row && p2s_coords[i][1] == column) {
                p2s_health[i] = 1;
                return;
            }
        }
        return;
    } else {
        for(int i = 0; i < size; i++) {
            if(p2p_coords[i][0] == row && p2p_coords[i][1] == column) {
                p2p_health[i] = 1;
                return;
            }
        }
        return;
    }
}

int sunk(int pnum) {
    if(pnum == 1) {
        int sank = checkShip(p1carrier, p1c_dead, p1total_dead, 5);
        if(sank == 1 && printed_1 == 0) {
            printf("\n");
            printf("We have sunk your Carrier!\n");
            printed_1 = 1;
            return 1;
        }
        int sank2 = checkShip(p1battleship, p1b_dead, p1total_dead, 4);
        if(sank2 == 1 && printed_2 == 0) {
            printf("\n");
            printf("We have sunk your Battleship!\n");
            printed_2 = 1;
            return 1;
        }
        int sank3 = checkShip(p1destroyer, p1d_dead, p1total_dead, 3);
        if(sank3 == 1 && printed_3 == 0) {
            printf("\n");
            printf("We have sunk your Destroyer!\n");
            printed_3 = 1;
            return 1;
        }
        int sank4 = checkShip(p1submarine, p1s_dead, p1total_dead, 2);
        if(sank4 == 1 && printed_4 == 0) {
            printf("\n");
            printf("We have sunk your Submarine!\n");
            printed_4 = 1;
            return 1;
        }
        int sank5 = checkShip(p1patrol, p1p_dead, p1total_dead, 2);
        if(sank5 == 1 && printed_5 == 0) {
            printf("\n");
            printf("We have sunk your Patrol Boat!\n");
            printed_5 = 1;
            return 1;
        }
        return 0;
    } else {
        int sank6 = checkShip(p2carrier, p2c_dead, p2total_dead, 5);
        if(sank6 == 1 && printed_6 == 0) {
            printf("\n");
            printf("We have sunk your Carrier!\n");
            printed_6 = 1;
            return 1;
        }
        int sank7 = checkShip(p2battleship, p2b_dead, p2total_dead, 4);
        if(sank7 == 1 && printed_7 == 0) {
            printf("\n");
            printf("We have sunk your Battleship!\n");
            printed_7 = 1;
            return 1;
        }
        int sank8 = checkShip(p2destroyer, p2d_dead, p2total_dead, 3);
        if(sank8 == 1 && printed_8 == 0) {
            printf("\n");
            printf("We have sunk your Destroyer!\n");
            printed_8 = 1;
            return 1;
        }
        int sank9 = checkShip(p2submarine, p2s_dead, p2total_dead, 2);
        if(sank9 == 1 && printed_9 == 0) {
            printf("\n");
            printf("We have sunk your Submarine!\n");
            printed_9 = 1;
            return 1;
        }
        int sank10 = checkShip(p2patrol, p2p_dead, p2total_dead, 2);
        if(sank10 == 1 && printed_10 == 0) {
            printf("\n");
            printf("We have sunk your Patrol Boat!\n");
            printed_10 = 1;
            return 1;
        }
        return 0;
    }
}

int fire(int tiles[8][8], int shots[8][8], int row, int column, int next) {
    if(row >= 8 || row < 0) {
        printf("Invalid coordinates\n");
        return 0;
    }
    if(column >= 8 || column < 0) {
        printf("Invalid coordinates\n");
        return 0;
    }
    if(shots[row][column] == 1) {
        printf("You have already fired at this location\n");
        //printf("\n");
        return 0;
    }
    if(shots[row][column] == 0 && tiles[row][column] == 0) {
        shots[row][column] = 1;
        printf("\n");
        printf("You have missed!\n");
        printf("\n");
        printf("%s %d%s", "Player", next, "'s turn\n");
        printf("\n");
        return 1;
    }
    if(shots[row][column] == 0 && tiles[row][column] == 1) {
        shots[row][column] = 1;
        tiles[row][column] = 2;
        if(next == 2) {
            hit2(row, column, 5, 1);
            hit2(row, column, 4, 2);
            hit2(row, column, 3, 3);
            hit2(row, column, 2, 4);
            hit2(row, column, 2, 5);
        } else {
            hit1(row, column, 5, 1);
            hit1(row, column, 4, 2);
            hit1(row, column, 3, 3);
            hit1(row, column, 2, 4);
            hit1(row, column, 2, 5);
        }
        if(sunk(next) != 1) {
            printf("\n");
            printf("We have hit the target!\n");
        }
        if(checkPlayer1() != 1 && checkPlayer2() != 1) {
            printf("\n");
            printf("%s %d%s", "Player", next, "'s turn\n");
            printf("\n");
        }
        // printf("\n");
        // printf("%s %d%s", "Player", next, "'s turn\n");
        // printf("\n");
        return 1;
    }
    return 0;
}
int checkPlayer1() {
    
    int sank = checkShip(p2carrier, p2c_dead, p2total_dead, 5);
    int sank2 = checkShip(p2battleship, p2b_dead, p2total_dead, 4);
    int sank3 = checkShip(p2destroyer, p2d_dead, p2total_dead, 3);
    int sank4 = checkShip(p2submarine, p2s_dead, p2total_dead, 2);
    int sank5 = checkShip(p2patrol, p2p_dead, p2total_dead, 2);
    if(sank == 1 && sank2 == 1 && sank3 == 1 && sank4 == 1 && sank5 == 1) {
        return 1;
    } else {
        return 0;
    }
}

int checkPlayer2() {
    int sank = checkShip(p1carrier, p1c_dead, p1total_dead, 5);
    int sank2 = checkShip(p1battleship, p1b_dead, p1total_dead, 4);
    int sank3 = checkShip(p1destroyer, p1d_dead, p1total_dead, 3);
    int sank4 = checkShip(p1submarine, p1s_dead, p1total_dead, 2);
    int sank5 = checkShip(p1patrol, p1p_dead, p1total_dead, 2);
    if(sank == 1 && sank2 == 1 && sank3 == 1 && sank4 == 1 && sank5 == 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    setup1();
    setup2();
    int player_count = 0;
    while(1) {
        if(checkPlayer1() == 1) {
            printf("\n");
            printf("Player 1 wins!\n");
            break;
        }
        if(checkPlayer2() == 1) {
            printf("\n");
            printf("Player 2 wins!\n");
            break;
        }
        if(player_count % 2 == 0) {
            // printf("\n");
            // printf("%s %d%s", "Player", 1, "'s turn\n");
            // printf("\n");
            char command[12];
            fgets(command, 12, stdin);
            removeLine(command);
            if(strstr(command, "fire") != NULL) {
                if(strlen(command) != 8) {
                    printf("Invalid coordinates\n");
                } else {
                    int y_axis = command[5] - 65;
                    int x_axis = command[7] - 49;
                    if(fire(p2tiles, p1shots, y_axis, x_axis, 2) == 1){
                        player_count++;
                    }
                }  
            } else if(strstr(command, "shots") != NULL ) {
                if(strlen(command) == 5) {
                    draw(p2tiles, p1shots);
                } else {
                    printf("Invalid command\n");
                }
            } else if(strstr(command, "exit") != NULL) {
                if(strlen(command) == 4) {
                    break;
                }
            } else {
                printf("Invalid command\n");
            }
        } else {
            // printf("\n");
            // printf("%s %d%s", "Player", 2, "'s turn\n");
            // printf("\n");
            char command[12];
            fgets(command, 12, stdin);
            removeLine(command);
            if(strstr(command, "fire") != NULL) {
                if(strlen(command) != 8) {
                    printf("Invalid command\n");
                } else {
                    int y_axis = command[5] - 65;
                    int x_axis = command[7] - 49;
                    if(fire(p1tiles, p2shots, y_axis, x_axis, 1) == 1){
                        player_count++;
                    }
                }
            } else if(strstr(command, "shots") != NULL ) {
                if(strlen(command) == 5) {
                    draw(p1tiles, p2shots);
                } else {
                    printf("Invalid command\n");
                }
            } else if(strstr(command, "exit") != NULL) {
                if(strlen(command) == 4) {
                    break;
                }
            } else {
                printf("Invalid command\n");
            }
        }
    }
    return 0;
}

//hello