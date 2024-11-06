#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

//tamaño de la matriz 
#define N 5 
#define CELL_MAX ((N * N) - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i = 0; i < length ;i++) printf("................");
    printf("\n");
}

void print_board(char board[N][N])
{
    int cell = 0;

    print_sep(N);
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(N);
    }
}

char get_winner(char board[N][N])
{
    char winner = '-';
    int countX = 0;
    int countO = 0;

    //filas
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            if(board[row][column] == 'X'){
                countX++;
            }
            if(board[row][column] == 'O'){
                countO++;
            }
        }
        if(countX == N){
            winner = 'X';
        }
        else if(countO == N){
            winner = 'O';
        }
        else{
            countX = 0;
            countO = 0;
        }
    }
    //Columnas
    if(winner == '-'){
        for (int column = 0; column < N; ++column) {
            for (int row = 0; row < N; ++row) {
                if(board[row][column] == 'X'){
                    countX++;
                }
                if(board[row][column] == 'O'){
                    countO++;
                }
            }
            if(countX == N){
                winner = 'X';
            }
            else if(countO == N){
                winner = 'O';
            }
            else{
                countX = 0;
                countO = 0;
            }
        }
    }
    if(winner == '-'){
        // Diagonal principal y invertida
        for (int i = 0; i < N; i++) {
            if(board[i][i] == 'X' || board[i][N-i-1] == 'X'){
                    countX++;
            }
            if(board[i][i] == 'O' || board[i][N-i-1] == 'O'){
                countO++;
            }
        }
        if(countX == N){
            winner = 'X';
        }
        else if(countO == N){
            winner = 'O';
        }
        else{
            countX = 0;
            countO = 0;
        }
    }
    return winner;
}

bool has_free_cell(char board[N][N])
{
    bool free_cell=false;
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            if(board[row][column] == '-'){
                free_cell = true;
            }
        }
        printf("\t | \n");
        print_sep(N);
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe\n");
    // declaración de la matriz
    char board[N][N]; 

    // inicialización de la matriz con guiones
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '-';
        }
    }
    
    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn, CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / N;
            int colum = cell % N;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
