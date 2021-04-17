/**
* Test pour notre jeu d'échec
* \file   TestBoard.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 11 avril 2021
*/
#include "Game.hpp"
using namespace std;

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Game, initialisation) {
	Game* game = new Game();
	list<string> positioning = { "WKe8", "WKe8" };
	EXPECT_EQ(game->setGame(positioning), false);
	positioning = { "WKa1", "BKa1" };
	EXPECT_EQ(game->setGame(positioning), false);
	positioning = { "BPh8"};
	EXPECT_EQ(game->setGame(positioning), false);
	positioning = { "BPh1",  "WKe1", "BKe8" };
	EXPECT_EQ(game->setGame(positioning), false);
	positioning = { "WPh1", "BQh1", "WKe1", "BKe8" };
	EXPECT_EQ(game->setGame(positioning), false);
	positioning = { "WPh1", "BPh1", "WKe1", "BKe8" };
	EXPECT_EQ(game->setGame(positioning), false);
	positioning = { "WPh2", "BQb4", "WKe1", "BKe8" };
	EXPECT_EQ(game->setGame(positioning), true);
	delete game;
}

TEST(Game, mouvements_disponibles) {
	Game* game = new Game();
	list<string> positioning = { "WBe1", "BNf2", "BQd1", "WKf1", "BKe3" };
	game->setGame(positioning);
	list<Position> expected = {};
	list<Position> obtained = game->getPieceMap()["WB1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained , expected);
	expected = { Position("d3"), Position("e4"), Position("g4"), Position("h3"), Position("h1") };
	obtained = game->getPieceMap()["BN1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { Position("a1"), Position("a4"), Position("b1"), Position("b3"),
		           Position("c1"), Position("c2"), Position("d2"), Position("d3"), 
		           Position("d4"), Position("d5"), Position("d6"), Position("d7"), 
		           Position("d8"), Position("e1"), Position("e2"), Position("f3"), 
		           Position("g4"), Position("h5") };
	obtained = game->getPieceMap()["BQ1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { Position("g1"), Position("g2") };
	obtained = game->getPieceMap()["WK1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { Position("d3"), Position("d4"), Position("e4"), 
							 Position("f3"), Position("f4") };
	obtained = game->getPieceMap()["BK1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	delete game;
}

TEST(Game, mouvements) {
	Game* game = new Game();
	list<string> positioning = { "WKd5", "BKe4", "WQb2", "BBc5", "WNe5" };
	game->setGame(positioning);
	game->action(Position("d5"));
	EXPECT_EQ(game->action(Position("e5")), false);
	EXPECT_EQ(game->action(Position("e6")), true);
	game->action(Position("e4"));
	EXPECT_EQ(game->action(Position("d4")), false);
	EXPECT_EQ(game->action(Position("f4")), true);
	game->action(Position("b2"));
	EXPECT_EQ(game->action(Position("e5")), false);
	EXPECT_EQ(game->action(Position("f2")), true);
	game->action(Position("c5"));
	EXPECT_EQ(game->action(Position("a7")), false);
	EXPECT_EQ(game->action(Position("f2")), true);
	game->action(Position("e5"));
	EXPECT_EQ(game->action(Position("f4")), false);
	EXPECT_EQ(game->action(Position("f3")), true);
	EXPECT_EQ(game->action(Position("e5")), false);
	delete game;
}

#endif
