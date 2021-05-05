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

	positioning = { "WKa1", "WKa2", "BKa3" };
	EXPECT_EQ(game->setGame(positioning), true); // Le système enlève le White King de trop
	delete game;

	game = new model::Game();
	positioning = { "WKe1", "BKe8", "WKe4" };
	EXPECT_EQ(game->setGame(positioning), true); // Le système enlève le White King de trop
	delete game;

	game = new model::Game();
	positioning = { "WPh2", "BQb4", "WKe1", "BKe8" };
	EXPECT_EQ(game->setGame(positioning), true);
	delete game;
}

TEST(Game, mouvements_disponibles) {
	model::Game* game = new model::Game();
	list<string> positioning = { "WBe1", "BNf2", "BQd1", "WKf1", "BKe3", "WRa4", "BPb5", "WPb2" };
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

	expected = { model::Position("d3"), model::Position("f3") };
	obtained = game->getPieceMap()["BK1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);

	expected = { model::Position("a1"), model::Position("a2"),
							 model::Position("a3"), model::Position("a5"),
							 model::Position("a6"), model::Position("a7"),
							 model::Position("a8"), model::Position("h4"),
							 model::Position("b4"), model::Position("c4"),
							 model::Position("d4"), model::Position("e4"),
							 model::Position("f4"), model::Position("g4") };
	obtained = game->getPieceMap()["WR1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);

	expected = { model::Position("b4"), model::Position("a4")};
	obtained = game->getPieceMap()["BP1"]->getPossibility();
	expected.sort();
	obtained.sort();
	EXPECT_EQ(obtained, expected);

	expected = { model::Position("b3"), model::Position("b4")};
	obtained = game->getPieceMap()["WP1"]->getPossibility();
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

TEST(Game, ClassicGame) {
	model::Game* game = new model::Game();
	game->setNewGame();
	EXPECT_EQ(game->getPieceMap()["WP1"]->getPosition(), model::Position("a2"));
	EXPECT_EQ(game->getPieceMap()["WP2"]->getPosition(), model::Position("b2"));
	EXPECT_EQ(game->getPieceMap()["WP3"]->getPosition(), model::Position("c2"));
	EXPECT_EQ(game->getPieceMap()["WP4"]->getPosition(), model::Position("d2"));
	EXPECT_EQ(game->getPieceMap()["WP5"]->getPosition(), model::Position("e2"));
	EXPECT_EQ(game->getPieceMap()["WP6"]->getPosition(), model::Position("f2"));
	EXPECT_EQ(game->getPieceMap()["WP7"]->getPosition(), model::Position("g2"));
	EXPECT_EQ(game->getPieceMap()["WP8"]->getPosition(), model::Position("h2"));

	EXPECT_EQ(game->getPieceMap()["WR1"]->getPosition(), model::Position("a1"));
	EXPECT_EQ(game->getPieceMap()["WR2"]->getPosition(), model::Position("h1"));

	EXPECT_EQ(game->getPieceMap()["WN1"]->getPosition(), model::Position("b1"));
	EXPECT_EQ(game->getPieceMap()["WN2"]->getPosition(), model::Position("g1"));

	EXPECT_EQ(game->getPieceMap()["WB1"]->getPosition(), model::Position("c1"));
	EXPECT_EQ(game->getPieceMap()["WB2"]->getPosition(), model::Position("f1"));

	EXPECT_EQ(game->getPieceMap()["WQ1"]->getPosition(), model::Position("d1"));
	EXPECT_EQ(game->getPieceMap()["WK1"]->getPosition(), model::Position("e1"));

	EXPECT_EQ(game->getPieceMap()["BP1"]->getPosition(), model::Position("a7"));
	EXPECT_EQ(game->getPieceMap()["BP2"]->getPosition(), model::Position("b7"));
	EXPECT_EQ(game->getPieceMap()["BP3"]->getPosition(), model::Position("c7"));
	EXPECT_EQ(game->getPieceMap()["BP4"]->getPosition(), model::Position("d7"));
	EXPECT_EQ(game->getPieceMap()["BP5"]->getPosition(), model::Position("e7"));
	EXPECT_EQ(game->getPieceMap()["BP6"]->getPosition(), model::Position("f7"));
	EXPECT_EQ(game->getPieceMap()["BP7"]->getPosition(), model::Position("g7"));
	EXPECT_EQ(game->getPieceMap()["BP8"]->getPosition(), model::Position("h7"));

	EXPECT_EQ(game->getPieceMap()["BR1"]->getPosition(), model::Position("a8"));
	EXPECT_EQ(game->getPieceMap()["BR2"]->getPosition(), model::Position("h8"));

	EXPECT_EQ(game->getPieceMap()["BN1"]->getPosition(), model::Position("b8"));
	EXPECT_EQ(game->getPieceMap()["BN2"]->getPosition(), model::Position("g8"));

	EXPECT_EQ(game->getPieceMap()["BB1"]->getPosition(), model::Position("c8"));
	EXPECT_EQ(game->getPieceMap()["BB2"]->getPosition(), model::Position("f8"));

	EXPECT_EQ(game->getPieceMap()["BQ1"]->getPosition(), model::Position("d8"));
	EXPECT_EQ(game->getPieceMap()["BK1"]->getPosition(), model::Position("e8"));

	delete game;
}

TEST(Game, FischerRandomGame) {
	model::Game* game = new model::Game();
	game->setFischerRandomGame();
	EXPECT_EQ(game->getPieceMap()["WP1"]->getPosition(), model::Position("a2"));
	EXPECT_EQ(game->getPieceMap()["WP2"]->getPosition(), model::Position("b2"));
	EXPECT_EQ(game->getPieceMap()["WP3"]->getPosition(), model::Position("c2"));
	EXPECT_EQ(game->getPieceMap()["WP4"]->getPosition(), model::Position("d2"));
	EXPECT_EQ(game->getPieceMap()["WP5"]->getPosition(), model::Position("e2"));
	EXPECT_EQ(game->getPieceMap()["WP6"]->getPosition(), model::Position("f2"));
	EXPECT_EQ(game->getPieceMap()["WP7"]->getPosition(), model::Position("g2"));
	EXPECT_EQ(game->getPieceMap()["WP8"]->getPosition(), model::Position("h2"));

	EXPECT_NE(game->getPieceMap()["WR1"], nullptr);
	EXPECT_NE(game->getPieceMap()["WR2"], nullptr);

	EXPECT_NE(game->getPieceMap()["WN1"], nullptr);
	EXPECT_NE(game->getPieceMap()["WN2"], nullptr);

	EXPECT_NE(game->getPieceMap()["WB1"], nullptr);
	EXPECT_NE(game->getPieceMap()["WB2"], nullptr);

	EXPECT_NE(game->getPieceMap()["WQ1"], nullptr);
	EXPECT_NE(game->getPieceMap()["WK1"], nullptr);

	EXPECT_EQ(game->getPieceMap()["BP1"]->getPosition(), model::Position("a7"));
	EXPECT_EQ(game->getPieceMap()["BP2"]->getPosition(), model::Position("b7"));
	EXPECT_EQ(game->getPieceMap()["BP3"]->getPosition(), model::Position("c7"));
	EXPECT_EQ(game->getPieceMap()["BP4"]->getPosition(), model::Position("d7"));
	EXPECT_EQ(game->getPieceMap()["BP5"]->getPosition(), model::Position("e7"));
	EXPECT_EQ(game->getPieceMap()["BP6"]->getPosition(), model::Position("f7"));
	EXPECT_EQ(game->getPieceMap()["BP7"]->getPosition(), model::Position("g7"));
	EXPECT_EQ(game->getPieceMap()["BP8"]->getPosition(), model::Position("h7"));

	EXPECT_NE(game->getPieceMap()["BR1"], nullptr);
	EXPECT_NE(game->getPieceMap()["BR2"], nullptr);

	EXPECT_NE(game->getPieceMap()["BN1"], nullptr);
	EXPECT_NE(game->getPieceMap()["BN2"], nullptr);

	EXPECT_NE(game->getPieceMap()["BB1"], nullptr);
	EXPECT_NE(game->getPieceMap()["BB2"], nullptr);

	EXPECT_NE(game->getPieceMap()["BQ1"], nullptr);
	EXPECT_NE(game->getPieceMap()["BK1"], nullptr);

	delete game;
}

#endif
