/**
* Test pour notre jeu d'échec
* \file   TestBoard.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 11 avril 2021
*/
#include "View/BoardView.hpp"
using namespace std;

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST
/*
TEST(BoardView, initialisation) {
	BoardView* board = new BoardView();
	list<string> positioning = { "WKe8", "WKe8" };
	EXPECT_EQ(board->setGame(positioning), false);
	positioning = { "WKa1", "BKa1" };
	EXPECT_EQ(board->setGame(positioning), false);
	positioning = { "BPh8"};
	EXPECT_EQ(board->setGame(positioning), false);
	positioning = { "BPh1",  "WKe1", "BKe8" };
	EXPECT_EQ(board->setGame(positioning), false);
	positioning = { "WPh1", "BQh1", "WKe1", "BKe8" };
	EXPECT_EQ(board->setGame(positioning), false);
	positioning = { "WPh1", "BPh1", "WKe1", "BKe8" };
	EXPECT_EQ(board->setGame(positioning), false);
	positioning = { "WPh2", "BQb4", "WKe1", "BKe8" };
	EXPECT_EQ(board->setGame(positioning), true);
	delete board;
}

TEST(BoardView, mouvements_disponibles) {
	BoardView* board = new BoardView();
	list<string> positioning = { "WBf1", "BNf2", "BQd1", "WKe1", "BKe3" };
	board->setGame(positioning);
	list<Position> expected = { Position("a6"), Position("b5"), Position("c4"), Position("d3"), 
		                          Position("e2"), Position("g2"), Position("h3") };
	list<Position> obtained = board->getPieceMap()["WB1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained , expected);
	expected = { Position("d3"), Position("e4"), Position("g4"), Position("h3"), Position("h1") };
	obtained = board->getPieceMap()["BN1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { Position("a1"), Position("a4"), Position("b1"), Position("b3"),
		           Position("c1"), Position("c2"), Position("d2"), Position("d3"), 
		           Position("d4"), Position("d5"), Position("d6"), Position("d7"), 
		           Position("d8"), Position("e1"), Position("e2"), Position("f3"), 
		           Position("g4"), Position("h5") };
	obtained = board->getPieceMap()["BQ1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { Position("d1"), Position("d2"), Position("e2"), Position("f2") };
	obtained = board->getPieceMap()["WK1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { Position("d2"), Position("d3"), Position("d4"), Position("e2"), 
		           Position("e4"), Position("f3"), Position("f4") };
	obtained = board->getPieceMap()["BK1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	delete board;
}

TEST(BoardView, mouvements) {
	BoardView* board = new BoardView();
	list<string> positioning = { "WKd5", "BKe4", "WQb2", "BBc5", "WNe5" };
	board->setGame(positioning);
	board->selectPiece(board->getPieceMap()["WK1"]);
	EXPECT_EQ(board->movePiece(Position("e5")), false);
	EXPECT_EQ(board->movePiece(Position("e6")), true);
	board->selectPiece(board->getPieceMap()["BK1"]);
	EXPECT_EQ(board->movePiece(Position("d4")), false);
	EXPECT_EQ(board->movePiece(Position("f4")), true);
	board->selectPiece(board->getPieceMap()["WQ1"]);
	EXPECT_EQ(board->movePiece(Position("e5")), false);
	EXPECT_EQ(board->movePiece(Position("f2")), true);
	board->selectPiece(board->getPieceMap()["BB1"]);
	EXPECT_EQ(board->movePiece(Position("a7")), false);
	EXPECT_EQ(board->movePiece(Position("f2")), true);
	board->selectPiece(board->getPieceMap()["WN1"]);
	EXPECT_EQ(board->movePiece(Position("f4")), false);
	EXPECT_EQ(board->movePiece(Position("f3")), true);
	delete board;
}
*/
#endif
