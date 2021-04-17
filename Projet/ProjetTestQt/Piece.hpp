#pragma once
/**
* Librairie pour la gestion d'une pièce d'un jeu d'échec
* \file   Piece.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#include <list>
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()
#include <cppitertools/range.hpp>

// Image au lien suivant : https://pixabay.com/fr/vectors/d-%C3%A9checs-pi%C3%A8ces-ensemble-symboles-26774/

namespace model {

	enum PieceColor { white, black };

	enum AddMoveState { stop, add };

	struct Position {
		unsigned char x, y;
		Position() = default;
		Position(unsigned char x, unsigned char y);
		Position(std::string name);

		std::string name();
		bool operator==(Position autre) const;
		bool operator<(Position autre) const;
	};

	class Piece : public QObject {
		Q_OBJECT

	public:
		Piece(const PieceColor& color, const unsigned char& type, const Position& position);
		~Piece();

		std::string getName() const;
		Position getPosition() const;
		PieceColor getColor() const;

		static void generatePossibility();
		std::list<Position> getPossibility();

		void cancelMove();
		bool movePiece(const Position& position);

	protected:
		PieceColor color_;
		Position position_, lastPosition_;
		std::list<Position> possibility_;
		std::string name_;
		static std::map<std::string, Piece*> allPieces_;

		virtual void checkPossibility() = 0;

		void removeCheckSelfPossibility();
		bool isKingAlive() const;
		bool isDoingCheck();
		bool isRemovingCheck(const Position& position);
		AddMoveState addMove(const Position& position);
		void addDirection(int iterateX, int iterateY, iter::impl::Range<int> range);
		bool atAlly(const Position& position) const;
		bool atEnemy(const Position& position) const;
	};

	class King : public Piece {
		Q_OBJECT

	public:
		static King* getInstance(const PieceColor& color, const Position& position);
		~King();
	private:
		static std::list<King*> instanceList_;
		King(const PieceColor& color, const Position& position);
		void checkPossibility() override;
	};

	class Queen : public Piece {
		Q_OBJECT

	public:
		Queen(const PieceColor& color, const Position& position);
	private:
		void checkPossibility() override;
	};

	class Knight : public Piece {
		Q_OBJECT

	public:
		Knight(const PieceColor& color, const Position& position);
	private:
		void checkPossibility() override;
	};

	class Bishop : public Piece {
		Q_OBJECT

	public:
		Bishop(const PieceColor& color, const Position& position);
	private:
		void checkPossibility() override;
	};

	class Rook : public Piece {
		Q_OBJECT

	public:
		Rook(const PieceColor& color, const Position& position);
	private:
		void checkPossibility() override;
	};

	class Pawn : public Piece {
		Q_OBJECT

	public:
		Pawn(const PieceColor& color, const Position& position);
	private:
		void checkPossibility() override;
	};
}