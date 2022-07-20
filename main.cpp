#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "utils.h"
using namespace std;

// declaracion de funciones
void handleWinner(Board, Player *, Player *);
void handleMatch(Board, Player *, Player *);
void handleGame();

int main(int argc, char** argv) {
    // opciones
    string options[] = {
        "Iniciar Partida",
        "Salir"
    };

    int optionsLength = 2;

    // estado del programa
    bool shouldContinue = true;

    while(shouldContinue) {
        cout << "----- Cuatro en Linea -----\n" << endl;

        // mostrar opciones
        displayOptions(options, optionsLength);
        cout << endl;

        // pedir y leer opcion
        int option = getOption("Opcion: ", 1, optionsLength);
        cout << endl;

        // ejecutar accion de acuerdo a opcion elegida
        if (option == 1) {
        	handleGame();
		} else if (option == 2) {
			shouldContinue = false;
		} else {
			cout << "Opcion invalida" << endl;
		}

        cout << endl;
    }

    return 0;
}

// controlar ganador
void handleWinner(Board board, Player *P1, Player *P2) {
    // buscar secuencias para cada jugador
    int firstPlayerScore = board.findSequences(P1->getToken());
    int secondPlayerScore = board.findSequences(P2->getToken());

    // establecer puntuaciones
    P1->setScore(firstPlayerScore);
    P2->setScore(secondPlayerScore);

    // determinar resultado
    if (P1->getScore() > P2->getScore()) {
        cout << "Ganador es Jugador 1 (" << P1->getToken() << ")" << endl;
        cout << "Puntaje: " << P1->getScore() << endl;
    } else if (P1->getScore() < P2->getScore()) {
        cout << "Ganador es Jugador 2 (" << P2->getToken() << ")" << endl;
        cout << "Puntaje: " << P2->getScore() << endl;
    } else {
        cout << "Empate" << endl;
    }
}

// controlar partida
void handleMatch(Board board, Player *P1, Player *P2) {
    // obtener jugador a iniciar partida
    int playerToStart = randomInRange(1, 2);

    // establecer ficha de turno actual
    char currentTokenTurn = playerToStart == 1
        ? P1->getToken()
        : P2->getToken();

    // mostrar jugador a iniciar partida
    cout << "> Primer Turno es Jugador " << playerToStart
        << " (" << currentTokenTurn << ")\n" << endl;

    // jugar hasta que partida no haya terminado
    while(!board.isGameOver(P1->getToken(), P2->getToken())) {
        // mostrar estado del tablero
		board.display();
		cout << endl;

        // determinar jugador del turno
        if (currentTokenTurn == P1->getToken()) {
            P1->makeMove(board);

            // asignar ficha del proximo turno
            currentTokenTurn = P2->getToken();
        } else {
            P2->makeMove(board);

            // asignar ficha del proximo turno
            currentTokenTurn = P1->getToken();
        }
    }

    // mostrar estado final del tablero
    board.display();
    cout << endl;

    // determinar ganador
    handleWinner(board, P1, P2);
}

// controlar juego
void handleGame() {
    // modalidades
    string modalities[] = {
        "Ganador por primer 4 en Linea",
        "Ganador por secuencias de 4 en Linea"
    };

    int modalitiesLength = 2;

    // tipos de partida
    string matchTypes[] = {
        "Humano vs Humano",
        "Humano vs Computadora",
        "Computadora vs Computadora"
    };

    int matchTypesLength = 3;

    // mostrar modalidades
    cout << "> Modalidades\n" << endl;
    displayOptions(modalities, modalitiesLength);
    cout << endl;

    // pedir y leer modalidad
    int modality = getOption("Modalidad: ", 1, modalitiesLength);
    cout << endl;

    // mostrar tipos de partida
    cout << "> Tipos de Partida\n" << endl;
    displayOptions(matchTypes, matchTypesLength);
    cout << endl;

    // pedir y leer tipo de partida
    int matchType = getOption("Tipo de Partida: ", 1, matchTypesLength);
    cout << endl;

    // crear elementos
    Board board(modality);
    Player *P1, *P2;

    // fichas de jugadores
    char firstPlayerToken = 'X';
    char secondPlayerToken = 'O';

    // asignar jugadores de acuerdo a tipo de partida
    switch(matchType) {
        case 1:
            P1 = new Human(firstPlayerToken);
            P2 = new Human(secondPlayerToken);
            break;

        case 2:
            P1 = new Human(firstPlayerToken);
            P2 = new Computer(secondPlayerToken, firstPlayerToken);
            break;

        case 3:
            P1 = new Computer(firstPlayerToken, secondPlayerToken);
            P2 = new Computer(secondPlayerToken, firstPlayerToken);
            break;

        default:
            cout << "Opcion invalida" << endl;
    }

    // iniciar partida
    handleMatch(board, P1, P2);

    // destruir objetos
    delete P1;
    delete P2;
}
