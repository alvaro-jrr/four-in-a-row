#include <iostream>
#include "Player.h"
using namespace std;

// constructor sin parametros
Player::Player() { }

// constructor
Player::Player(char token) {
	this->token = token;
	score = 0;
}

// obtener ficha
char Player::getToken() const {
	return token;
}

// obtener puntuacion
int Player::getScore() const {
	return score;
}

// establecer puntuacion
void Player::setScore(int score) {
	if (score > 0) {
		this->score = score;
	}
}
