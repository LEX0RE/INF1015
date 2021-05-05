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
	model::Game* game = new model::Game();
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
	positioning = { "WKe1", "BKe8", "WKe4" };
	EXPECT_EQ(game->setGame(positioning), true);
	delete game;
	game = new model::Game();
	positioning = { "WPh2", "BQb4", "WKe1", "BKe8" };
	EXPECT_EQ(game->setGame(positioning), true);
	delete game;
}

TEST(Game, mouvements_disponibles) {
	model::Game* game = new model::Game();
	list<string> positioning = { "WBe1", "BNf2", "BQd1", "WKf1", "BKe3" };
	game->setGame(positioning);
	list<model::Position> expected = {};
	list<model::Position> obtained = game->getPieceMap()["WB1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained , expected);
	expected = { model::Position("d3"), model::Position("e4"), 
							 model::Position("g4"), model::Position("h3"), 
							 model::Position("h1") };
	obtained = game->getPieceMap()["BN1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { model::Position("a1"), model::Position("a4"), model::Position("b1"), model::Position("b3"),
		           model::Position("c1"), model::Position("c2"), model::Position("d2"), model::Position("d3"), 
		           model::Position("d4"), model::Position("d5"), model::Position("d6"), model::Position("d7"), 
		           model::Position("d8"), model::Position("e1"), model::Position("e2"), model::Position("f3"), 
		           model::Position("g4"), model::Position("h5") };
	obtained = game->getPieceMap()["BQ1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { model::Position("g1"), model::Position("g2") };
	obtained = game->getPieceMap()["WK1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	expected = { model::Position("d3"), model::Position("d4"), model::Position("e4"), 
							 model::Position("f3"), model::Position("f4") };
	obtained = game->getPieceMap()["BK1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);
	delete game;
}

TEST(Game, mouvements) {
	model::Game* game = new model::Game();
	list<string> positioning = { "WKd5", "BKe4", "WQb2", "BBc5", "WNe5" };
	game->setGame(positioning);
	game->action(model::Position("d5"));
	EXPECT_EQ(game->action(model::Position("e5")), false);
	game->action(model::Position("d5"));
	EXPECT_EQ(game->action(model::Position("e6")), true);
	game->action(model::Position("e4"));
	EXPECT_EQ(game->action(model::Position("d4")), false);
	game->action(model::Position("e4"));
	EXPECT_EQ(game->action(model::Position("f4")), true);
	game->action(model::Position("b2"));
	EXPECT_EQ(game->action(model::Position("e5")), false);
	game->action(model::Position("b2"));
	EXPECT_EQ(game->action(model::Position("f2")), true);
	game->action(model::Position("c5"));
	EXPECT_EQ(game->action(model::Position("a7")), false);
	game->action(model::Position("c5"));
	EXPECT_EQ(game->action(model::Position("f2")), true);
	game->action(model::Position("e5"));
	EXPECT_EQ(game->action(model::Position("f4")), false);
	game->action(model::Position("e5"));
	EXPECT_EQ(game->action(model::Position("f3")), true);
	game->action(model::Position("e5"));
	EXPECT_EQ(game->action(model::Position("e5")), false);
	delete game;
}

#endif
