#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include "Board.h"

typedef struct {
    int bestScore;
    int bestMove;
} Minimax;

// clase Computador
class Computer : public Player {
    private:
        int level; // nivel (profundidad de procesamiento)
        char enemyToken; // ficha del enemigo
        
        // algoritmo minimax
		Minimax minimax(Board, char, char, int, int = 0, bool = true);

		// obtener la mejor movida
        int getBestMove(Board, char, char, int);

    public:
        // constructor
        Computer(char, char, int = 4);

        // establecer ficha enemiga
        void setEnemyToken(char);

        // obtener ficha enemiga
        char getEnemyToken() const;

        // establecer nivel
        void setLevel(int);

        // obtener nivel
        int getLevel() const;

        // hacer movida
        void makeMove(Board &);
};

#endif
