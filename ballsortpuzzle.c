#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ballsortpuzzle.h"
 
void generator(const int rows, const int columns, char field[rows][columns])
{
    int spaceCol1 = rand() % columns;
    int spaceCol2 = rand() % columns;
    while (spaceCol1 == spaceCol2) {
        spaceCol2 = rand() % columns;
    }
 
    for (int i = 0; i < rows; i++) {
        field[i][spaceCol1] = ' ';
        field[i][spaceCol2] = ' ';
    }
 
    char symbols[10] = {'*', '+', '^', '@', '&', '#', '$', '%', '-', '='};
    int countArr[10];
    for (int i = 0; i < 10; i++) {
        countArr[i] = 0;
    }
 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j == spaceCol1 || j == spaceCol2) {
                continue;
            }
            int index = rand() % (columns - 2);
            if (countArr[index] < rows) {
                countArr[index]++;
                field[i][j] = symbols[index];
            } else {
                while (1) {
                    index = rand() % (columns - 2);
                    if (countArr[index] < rows) {
                        countArr[index]++;
                        field[i][j] = symbols[index];
                        break;
                    }
                }
            }
        }
    }
}
 
void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)
{
    
    if (x == y || x > columns || y > columns || x < 1 || y < 1) {
        
        printf("Error");
    } else {
        int indexX = -1;
        char tmp = '\0';
        for (int i = 0; i < rows; i++) {
            if (field[i][x-1] != ' ') {
                //printf("(%c)", field[i][x-1]);
                tmp = field[i][x-1];
                indexX = i;
                break;
            }
        }
        if (tmp == '\0') {
            printf("Column is empty\n");
        } else {
            if (field[rows-1][y-1] == ' ') {
                field[rows-1][y-1] = tmp;
                field[indexX][x-1] = ' ';
            } else {
                for (int i = 0; i < rows; i++) {
                    if (i == 0 && field[i][y-1] != ' ') {
                        printf("Column is full\n");
                        break;
                    }
                    if (field[i][y-1] == tmp) {
                        field[i-1][y-1] = tmp;
                        field[indexX][x-1] = ' ';
                    } else if (field[i][y-1] != ' ') {
                        //printf("[%c-%c]", tmp, field[i][y-1]);
                        printf("Symbols are not the same\n");
                        break;
                    }
                }
            }
        }
    }
}

bool check(const int rows, const int columns, char field[rows][columns])
{
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < rows - 1; i++) {
            if (field[i][j] != field[i+1][j]) {
                return false;
            }
        }
    }
    return true;
}

void game_field(const int rows, const int columns, char field[rows][columns])
{
    
    
    for (int i = 0; i < rows; i++) {
        printf("%d  |", i + 1);
        for (int j = 0; j < columns; j++) {
            
            printf(" %c |", field[i][j]);

        }
        
        printf("\n");
    }
    printf("   ");
        for (int j = 0; j < columns; j++) {
            printf(" ---");
        }
        printf("\n    ");
        for (int j = 0; j < columns; j++) {
            printf(" %d  ", j + 1);
        }
 printf("\n");

}

void ball_sort_puzzle ()
{
    srand(time(NULL));
    
    int rows, cols;
    
    printf("Enter rows: ");
    scanf("%d", &rows);
    printf("Enter cols: ");
    scanf("%d", &cols);
    char field[rows][cols];
 
    generator(rows, cols, field);
    
    int x = 0, y = 0;
    
    while (!check(rows, cols, field)) {
       
        game_field(rows, cols, field);
         printf("Choose a column:\n");
        scanf("%d", &x);
        printf("Put there:\n");
        scanf("%d", &y);
        down_possible(rows, cols, field, x, y);
        

    }
 
    
    printf("Congratulations, you won!\n");
}