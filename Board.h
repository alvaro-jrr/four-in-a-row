#ifndef BOARD_H
#define BOARD_H

// clase Tablero
class Board {
	private:
		enum { HEIGHT = 6, WIDTH = 7, EMPTY = ' ' }; // constantes
		char board[HEIGHT][WIDTH]; // tablero
		int modality; // numero de modalidad

	public:
		// constructor
		Board(int = 1);

		// destructor
		~Board();

        // retornar copia
		Board copy() const;

		// establecer modalidad
		void setModality(int);

		// obtener modalidad
		int getModality() const;

		// obtener alto
		int getHeight() const;

		// obtener ancho
		int getWidth() const;

		// obtener si esta llena
		bool isFull() const;

		// obtener si columna esta llena
		bool isColumnFull(int) const;

		// obtener si columna esta dentro del rango
		bool isColumnInRange(int) const;

		// obtener si fila esta dentro del rango
		bool isRowInRange(int) const;

		// obtener fila vacia
		int getEmptyRow(int) const;

		// agregar ficha
		bool addToken(int, char);

		// buscar secuencias
		int findSequences(char);

		// obtener puntuacion
        int getScore(char *, char);

		// evaluar ficha en el tablero
		int evaluate(char);

        // obtener si juego se ha acabado
        bool isGameOver(char, char);

		// mostrar
		void display() const;
};

#endif
