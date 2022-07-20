#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "utils.h"
#include "Human.h"
using namespace std;

// constructor
Human::Human(char token) : Player(token) { }

// hacer movida
void Human::makeMove(Board &board) {
	int column;
	bool hasAddToken = false;

	// formar etiqueta para pedir columna
	string label = "Columna (";
	label += getToken();
	label += "): ";

    // ejecutar hasta que la ficha sea agregada
	while(!hasAddToken) {
		// pedir y leer columna
		column = getNumber(label);

		// intentar agregar ficha y obtener estado
		hasAddToken = board.addToken(column - 1, getToken());
		cout << endl;
	}
}