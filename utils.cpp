#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <cstdlib>
#include "utils.h"
using namespace std;

// desplegar opciones
void displayOptions(string options[], int size) {
    int option;

    // mostrar opcion con su numero correspondiente
    for (option = 0; option < size; option++) {
        cout << option + 1 << ") " << options[option] << endl;
    }
}

// obtener numero
int getNumber(string label) {
    int number;

    do {
        // si fallo entrada
        if (cin.fail()) {
            cin.clear(); // manejar fallo de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignorar linea
            cout << "Entrada invalida\n" << endl;
        }

        cout << label;
        cin >> number;
    } while(cin.fail());

    return number;
}

// obtener opcion
int getOption(string label, int min, int max) {
    int option;

    do {
        option = getNumber(label);
    } while(option < min || option > max);

    return option;
}

// numero aleatorio en rango
int randomInRange(int min, int max) {
    // semilla de numeros aleatorios
    srand(time(NULL));

    return min + (rand() % max);
}
