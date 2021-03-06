/*
Horus - A Chess Engine created for learning Game AI techniques
Copyright (C) 2016 Pranav Deshpande

This file is a part of Horus.

Horus is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

Horus is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Horus. If not, see <http://www.gnu.org/licenses/>.
*/

#include "move.hpp"

// Member function definitions
Move::Move() {
	from = to = EM;
	currPiece = capturedPiece = EM;
	promotedPiece = EM;
	isEnPassant = false;
	isCastle = false;
	castle = 0;
}

// Normal/capture moves
Move::Move(int init_pos, int final_pos, int currpiece, int capturedpiece) {
	ASSERT(isValidSquare(init_pos));
	ASSERT(isValidSquare(final_pos));
	ASSERT(init_pos != final_pos);

	from = init_pos;
	to = final_pos;
	currPiece = currpiece;
	capturedPiece = capturedpiece;
	promotedPiece = EM;
	isEnPassant = false;
	isCastle = false;
	castle = 0;
}

// Enpassant moves
Move::Move(bool isenPassant, int init_pos, int final_pos, int currpiece, int capturedpiece) {
	ASSERT(isValidSquare(init_pos));

	from = init_pos;
	to = final_pos;
	currPiece = currpiece;
	capturedPiece = capturedpiece;
	promotedPiece = EM;
	isEnPassant = isenPassant; // (True, since I am passing it)
	isCastle = false;
	castle = 0;
}

// Pawn promotion moves
Move::Move(int init_pos, int final_pos, int currpiece, int capturedpiece, int Promote) {
	ASSERT(isValidSquare(init_pos));
	ASSERT(isValidSquare(final_pos));
	ASSERT(init_pos != final_pos);
	ASSERT(isValidPromotionPiece(Promote));

	from = init_pos;
	to = final_pos;
	currPiece = currpiece;
	capturedPiece = capturedpiece;
	promotedPiece = Promote;
	isEnPassant = false;
	isCastle = false;
	castle = 0;
}

// Castling moves
Move::Move(bool iscastle, int Castle) {
	isCastle = iscastle; // which will be true only if this has been called..
	castle = Castle;
	isEnPassant = false;
	switch (castle) {
		case wOO:  from = e1; to = g1; break;
		case wOOO: from = e1; to = c1; break;
		case bOO:  from = e8; to = g8; break;
		case bOOO: from = e8; to = c8; break;
		default:   ASSERT(false);
	}
	currPiece = capturedPiece = promotedPiece = EM;
}

string Move::MoveToString() const {

	string m( squareMapping[ board120[from] ] + squareMapping[ board120[to] ] );
	if(promotedPiece != EM) {
		m += string(1, tolower( pieceChars[promotedPiece] ) );
	}
	return m;
}

bool Move::isNull() const {
	return from == EM && to == EM;
}
