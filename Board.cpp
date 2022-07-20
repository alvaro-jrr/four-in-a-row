#include <iostream>
#include "Board.h"
#include "utils.h"
using namespace std;

// constructor
Board::Board(int modality) {
    setModality(modality);

	// asignar vacio a cada celda
	for (int row = 0; row < getHeight(); row++) {
		for (int col = 0; col < getWidth(); col++) {
			board[row][col] = EMPTY;
		}
	}
}

// destructor
Board::~Board() { };

// copiar
Board Board::copy() const {
	return *this;
}

// establecer modalidad
void Board::setModality(int modality) {
    if (modality >= 1 && modality <= 2) {
        this->modality = modality;
    }
}

// obtener modalidad
int Board::getModality() const {
    return modality;
}

// obtener alto
int Board::getHeight() const {
	return HEIGHT;
}

// obtener ancho
int Board::getWidth() const {
	return WIDTH;
}

// obtener si esta llena
bool Board::isFull() const {
	for (int col = 0; col < getWidth(); col++) {
		if (!isColumnFull(col)) return false;
	}

	return true;
}

// obtener si columna esta llena
bool Board::isColumnFull(int column) const {
	return board[0][column] != EMPTY;
}

// obtener si columna esta dentro del rango
bool Board::isColumnInRange(int column) const {
	return column >= 0 && column <= getWidth() - 1;
}

// obtener si fila esta dentro del rango
bool Board::isRowInRange(int row) const {
	return row >= 0 && row <= getHeight() - 1;
}

// obtener fila vacia
int Board::getEmptyRow(int column) const {
	int minRow = getHeight() - 1;

	while(isRowInRange(minRow)) {
		// asignar ficha en la posicion si esta vacio
		if (board[minRow][column] == EMPTY) break;

		// subir de fila
		minRow--;
	}

	return minRow;
}

// agregar ficha
bool Board::addToken(int column, char token) {
	// si esta fuera de rango
	if (!isColumnInRange(column)) {
		cerr << "Columna " << column + 1 << " esta fuera de rango debe ser (1-" << getWidth() << ")." << endl;
		return false;
	}

	// si columna esta llena retornar FALSO
	if (isColumnFull(column)) {
		cerr << "Columna " << column + 1 << " esta llena." << endl;
		return false;
	}

	// obtener espacio vacio
	int emptyRow = getEmptyRow(column);

	// agregar ficha
	board[emptyRow][column] = token;

	return true;
}

// buscar secuencias
int Board::findSequences(char token) {
	int row, col;
	int sequences = 0;

	for (row = 0; row < getHeight(); row++) {
		for (col = 0; col < getWidth(); col++) {
			// saltar paso si casilla no pertenece al jugador
			if (board[row][col] != token) continue;

			// verificar posible secuencia horizontal ( - )
			if (isColumnInRange(col + 3)) {
				if (
					board[row][col + 1] == token &&
					board[row][col + 2] == token &&
					board[row][col + 3] == token
				) {
					if (getModality() == 1) return 1;
					
					sequences++;
				}
			}
			
			// verificar posible secuencia vertical ( | )
			if (isRowInRange(row + 3)) {
				if (
					board[row + 1][col] == token &&
					board[row + 2][col] == token &&
					board[row + 3][col] == token
				) {
					if (getModality() == 1) return 1;
					
					sequences++;
				}
			}

			// verificar posible secuencia diagonal hacia la derecha ( / )
			if (isColumnInRange(col + 3) && isRowInRange(row - 3)) {
				if (
					board[row - 1][col + 1] == token &&
					board[row - 2][col + 2] == token &&
					board[row - 3][col + 3] == token
				) {
					if (getModality() == 1) return 1;
					
					sequences++;
				}
			}

			// verificar posible secuencia diagonal hacia la izquierda ( \ )
			if (isColumnInRange(col + 3) && isRowInRange(row + 3)) {
				if (
					board[row + 1][col + 1] == token &&
					board[row + 2][col + 2] == token &&
					board[row + 3][col + 3] == token
				) {
					if (getModality() == 1) return 1;
					
					sequences++;
				}
			}
		}
	}

	return sequences;
}

// obtener puntuacion
int Board::getScore(char *window, char token) {
	int score = 0;
	int tokenCount = 0;
	int emptyCount = 0;
	int enemyCount = 0;

	// contar apariciones de ficha, vacio y ficha enemiga
	for (int i = 0; i < 4; i++) {
		if (window[i] == token) tokenCount++;
		if (window[i] == EMPTY) emptyCount++;
		if (window[i] != token && window[i] != EMPTY) enemyCount++;
	}

	// mejor puntuacion si gana
	if (tokenCount == 4) score += 100;

    // si hay 3 fichas propias y 1 es vacio
	if (tokenCount == 3 && emptyCount == 1) score += 5;

    // si hay 2 fichas propias y 2 vacios
	if (tokenCount == 2 && emptyCount == 2) score += 2;

    // si hay 2 fichas enemigas y 2 vacios
	if (enemyCount == 2 && emptyCount == 2) score -= 2;

    // si hay 3 fichas enemigas y 1 vacio
	if (enemyCount == 3 && emptyCount == 1) score -= 5;

    // peor puntuacion si pierde
	if (enemyCount == 4) score -= 100;

	return score;
}

// obtener ficha en el tablero
int Board::evaluate(char token) {
	int score = 0;
	char window[4];

	// puntuacion central
	for (int row = 0; row < getHeight() - 3; row++) {
		int centerColumn = getWidth() / 2;
		int tokenCount = 0;

		for (int i = 0; i < 4; i++) {
			if (board[row + i][centerColumn] == token) tokenCount++;
		}
		
		score += tokenCount * 3;
	}

	// puntuacion horizontal
	for (int row = 0; row < getHeight(); row++) {
		for (int col = 0; col < getWidth() - 3; col++) {
			for (int i = 0; i < 4; i++) {
				// ir a siguiente columna de la misma fila
				window[i] = board[row][col + i];
			}

			score += getScore(window, token);
		}
	}

	// puntuacion vertical
	for (int col = 0; col < getWidth(); col++) {
		for (int row = 0; row < getHeight() - 3; row++) {
			for (int i = 0; i < 4; i++) {
				// ir a siguiente fila de la misma columna
				window[i] = board[row + i][col];
			}

			score += getScore(window, token);
		}
	}

	// puntuacion diagonal positiva ( / )
	for (int row = 0; row < getHeight() - 3; row++) {
		for (int col = 0; col < getWidth() - 3; col++) {
			for (int i = 0; i < 4; i++) {
				// subir una fila e ir a siguiente columna
				window[i] = board[row + 3 - i][col + i];
			}

			score += getScore(window, token);
		}
	}

	// puntuacion diagonal negativa ( \ )
	for (int row = 0; row < getHeight() - 3; row++) {
		for (int col = 0; col < getWidth() - 3; col++) {
			for (int i = 0; i < 4; i++) {
				// bajar una fila e ir a siguiente columna
				window[i] = board[row + i][col + i];
			}

			score += getScore(window, token);
		}
	}

	return score;
}

// obtener si juego se ha acabado
bool Board::isGameOver(char tokenA, char tokenB) {
    // cuando modalidad es ganador por primer 4 en linea
    if (getModality() == 1) {
        return findSequences(tokenA) > 0 || findSequences(tokenB) > 0 || isFull();
    }

	return isFull();
}

// mostrar
void Board::display() const {
	int row, col;

	// mostrar tablero
	for (row = 0; row < getHeight(); row++) {
		cout << "|";

		for (col = 0; col < getWidth(); col++) {
			cout << " " << board[row][col] << " ";
		}

		cout << "|" << endl;
	}

	cout << endl;

	// mostrar numeros de columna
	for (col = 0; col < getWidth(); col++) {
		cout << "  " << col + 1;
	}

	cout << endl;
}
