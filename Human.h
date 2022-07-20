#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "Board.h"

// clase Humano
class Human : public Player {
    public:
        // constructor
        Human(char);

        // hacer movida
        void makeMove(Board &);
};

#endif