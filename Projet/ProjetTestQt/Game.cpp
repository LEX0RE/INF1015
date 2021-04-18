/**
* Gestion d'un jeu d'échec
* \file   Game.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#include <cppitertools/range.hpp>
#include <stdlib.h>
#include "Game.hpp"

model::Game::Game() {
	pieceMap_ = {};
	selected_ = nullptr;
	turn_ = white;
}

model::Game::~Game() {
	clearAllPieces();
}

bool model::Game::selectPiece(Piece* selected) {
	if (selected_ != selected && selected->getColor() == turn_) {
		selected_ = selected;
		emit updatePossibility(selected_->getPossibility());
		return true;
	}
	else {
		selected_ = nullptr;
		emit updatePossibility(std::list<Position>());
		return false;
	}
}

std::map<std::string, model::Piece*> model::Game::getPieceMap() const { return pieceMap_; }

bool model::Game::addPiece(const std::string specification) {
	if (specification.size() == 4) {
		PieceColor color;
		Position position;
		unsigned char type;

		if (specification[0] == 'W')
			color = white;
		else if (specification[0] == 'B')
			color = black;
		else
			return false;

		if ((specification[2] >= 'a' && specification[2] <= 'h') &&
			(specification[3] >= '1' && specification[3] <= '8'))
			position = Position(specification.substr(2, 2));
		else
			return false;

		switch (specification[1]) {
		case 'P':
			if (position.y == '1' || position.y == '8')
				return false;
			[[fallthrough]];
		case 'K': case 'Q': case 'B': case 'N': case 'R':
			type = specification[1];
			break;
		default:
			return false;
		}

		for (auto& [key, value] : pieceMap_) {
			if (value->getPosition() == position)
				return false;
		}

		return addPiece(color, type, position);
	}
	return false;
}

bool model::Game::addPiece(const PieceColor& color,
													 const unsigned char& type, 
													 const Position& position) {
	Piece* piece = nullptr;
	switch (type) {
		case 'K':
			piece = King::getInstance(color, position);
			break;
		case 'Q':
			piece = new Queen(color, position);
			break;
		case 'B':
			piece = new Bishop(color, position);
			break;
		case 'N':
			piece = new Knight(color, position);
			break;
		case 'R':
			piece = new Rook(color, position);
			break;
		case 'P':
			piece = new Pawn(color, position);
			break;
		default:
			return false;
	}
	pieceMap_[(*piece).getName()] = piece;
	return true;
}

void model::Game::removePiece(Piece* piece) {
	if (piece != nullptr) {
		pieceMap_.erase(piece->getName());
		delete piece;
	}
}

void model::Game::clearAllPieces() {
	for (auto& [key, value] : pieceMap_)
		delete value;
	pieceMap_.clear();
}

model::Piece* model::Game::getPiece(const model::Position position) const {
	for (auto& [key, value] : pieceMap_) {
		if (value->getPosition() == position)
			return value;
	}
	return nullptr;
}

bool model::Game::action(const model::Position position) {
	Piece* actionPiece = getPiece(position);

	if (selected_ != nullptr)
		return movePiece(position);
	else if (actionPiece != nullptr)
		return selectPiece(actionPiece);
	return false;
}

bool model::Game::movePiece(const Position position) {
	Position lastPosition = selected_->getPosition(), newPosition = position;
	Piece* pieceEaten = getPiece(newPosition);

	if (selected_->movePiece(position)) {
		QString mouvement = "";
		if (selected_->getName()[1] != 'P')
			mouvement += selected_->getName()[1];
		mouvement += lastPosition.name().c_str();
		if (pieceEaten != nullptr) {
			removePiece(pieceEaten);
			mouvement += "x";
		}
		else
			mouvement += "-";
		mouvement += newPosition.name().c_str();
		selectPiece(selected_);
		Piece::generatePossibility();
		if (turn_ == white)
			turn_ = black;
		else
			turn_ = white;
		emit updatePiece(pieceMap_);
		return true;
	}
	else {
		selectPiece(selected_);
		return false;
	}
}

bool model::Game::setGame(std::list<std::string> specificationPiece) {
	PieceColor color = white;
	bool valid = true;
	Piece* temporary = nullptr;
	Position position = Position("a1");
	std::string specification = "";

	for (auto piece : specificationPiece) {
		if (valid && addPiece(piece) == false)
			valid = false;
	}

	if ((pieceMap_.find("WK1") == pieceMap_.end()) || (pieceMap_.find("BK1") == pieceMap_.end()))
		valid = false;

	// TODO : Mettre dans un Doubleton
	if ((pieceMap_.find("WK2") != pieceMap_.end()) || (pieceMap_.find("BK2") != pieceMap_.end()))
		valid = false;

	if (valid == false) {
		clearAllPieces();
		return false;
	}
	Piece::generatePossibility();
	emit updatePiece(pieceMap_);
	return true;
}

void model::Game::setNewGame() {
	unsigned char color = 'W';
	std::string backline = "RNBQKBNR";
	Position position("a1");
	std::string newKey = "";
	unsigned int colorChange = 4, blackBackLine = 7, blackFrontLine = 6, 
							 whiteBackLine = 0, whiteFrontLine = 1;

	for (unsigned int y : iter::range(8)) {
		if (y == colorChange)
			color = 'B';
		for (unsigned int x : iter::range(8)) {
			newKey = "";
			position = Position((unsigned char)('a' + x), (unsigned char)('1' + y));
			if (y <= whiteFrontLine || y >= blackFrontLine) {
				newKey = color;
				if (y == whiteBackLine || y == blackBackLine)
					newKey += backline[x];
				else
					newKey += 'P';
				newKey += position.name();
				addPiece(newKey);
			}
		}
	}
	Piece::generatePossibility();
	emit updatePiece(pieceMap_);
}
