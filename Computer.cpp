#include <iostream>
#include <limits>
#include "Player.h"
#include "Board.h"
#include "utils.h"
#include "Computer.h"
using namespace std;

// constructor
Computer::Computer(char token, char enemyToken, int level) : Player(token) {
	setEnemyToken(enemyToken);
	setLevel(level);
}
// establecer ficha enemiga
void Computer::setEnemyToken(char enemyToken) {
	this->enemyToken = enemyToken;
}

// obtener ficha enemiga
char Computer::getEnemyToken() const {
	return enemyToken;
}

// establecer nivel
void Computer::setLevel(int level) {
	if (level > 0) {
		this->level = level;
	}
}

// obtener nivel
int Computer::getLevel() const {
	return level;
}

// algoritmo minimax
Minimax Computer::minimax(
	Board board,
	char maxPlayer,
	char minPlayer,
	int maxDepth,
	int currentDepth,
	bool isMaximizingPlayer
) {
	// almacenar resultados del minimax (puntuacion, movida)
	Minimax state;

	// verificar si ha acabado la recursion
	if (board.isGameOver(maxPlayer, minPlayer) || currentDepth == maxDepth) {
		state.bestScore = board.evaluate(maxPlayer);
		return state;
	}

    // almacenar mejor movida y mejor puntaje
	int bestMove;
	int bestScore;

	// jugador actual
	char currentPlayer = isMaximizingPlayer ? maxPlayer : minPlayer;

	// establecer mejor puntuacion inicial
	if (isMaximizingPlayer) {
		bestScore = numeric_limits<int>::min();
	} else {
		bestScore = numeric_limits<int>::max();
	}

	// pasar por cada movida posible
	for (int col = 0; col < board.getWidth(); col++) {
		// saltar paso si la columna esta llena
		if (board.isColumnFull(col)) continue;

		// simular movida
		Board tempBoard = board.copy();
		tempBoard.addToken(col, currentPlayer);

		// recursion
		Minimax recursionState = minimax(
            tempBoard,
            maxPlayer,
            minPlayer,
            maxDepth,
            currentDepth + 1,
            !isMaximizingPlayer
        );

		// puntuacion actual
		int currentScore = recursionState.bestScore;

		// actualiza la mejor puntuacion
		if (isMaximizingPlayer) {
			if (currentScore > bestScore) {
				bestScore = currentScore;
				bestMove = col;
			}
		} else {
			if (currentScore < bestScore) {
				bestScore = currentScore;
				bestMove = col;
			}
		}
	}

	// actualizar valores
	state.bestScore = bestScore;
	state.bestMove = bestMove;

    // estado del minimax
	return state;
}

// obtener la mejor movida
int Computer::getBestMove(
	Board board,
	char maxPlayer,
	char minPlayer,
	int maxDepth
) {
    // obtener resultado del minimax
	Minimax result = minimax(board, maxPlayer, minPlayer, maxDepth);

	// devolver mejor movida
	return result.bestMove;
}

// hacer movida
void Computer::makeMove(Board &board) {
	int bestMove = getBestMove(board, getToken(), getEnemyToken(), getLevel());
	
	// agregar mejor movida
	board.addToken(bestMove, getToken());

	// mostrar columna elegida
	cout << "Columna (" << getToken() << "): " << bestMove + 1 << "\n" << endl;
}
