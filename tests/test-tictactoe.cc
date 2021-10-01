#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String is too short") {
    REQUIRE_THROWS_AS(Board("xxooo"), std::invalid_argument);
  }
  SECTION("String is too long") {
    REQUIRE_THROWS_AS(Board("x.......o........x...."),
                      std::invalid_argument);
  }
  SECTION("Board size big by one") {
    REQUIRE_THROWS_AS(Board("x...x...o."),
                      std::invalid_argument);
  }
  SECTION("Board size small by one") {
    REQUIRE_THROWS_AS(Board("........"),
                      std::invalid_argument);
  }
  SECTION("Empty board") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }

}

TEST_CASE("Boards with no winner") {
  SECTION("Full board with no winner") {
    REQUIRE(Board("xxoooxxxo").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Empty board") {
    REQUIRE(Board(".........").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Empty board with other characters") {
    REQUIRE(Board("kM;k+_.Lk").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Game in progress, X moved last") {
    REQUIRE(Board("xxoxo....").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Game in progress, O moved last") {
    REQUIRE(Board("xxoxoo...").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("X winners") {
  SECTION("Horizontal XWin") {
    REQUIRE(Board("XxxO.o...").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Vertical XWin") {
    REQUIRE(Board("xooxxoxox").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Diagonal XWin") {
    REQUIRE(Board("X_o.x_o.x").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Reverse Diagonal XWin") {
    REQUIRE(Board("..x.xox.o").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("X has two 3 in a rows") {
    REQUIRE(Board("xooxxoxox").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("X wins with upper case input") {
    REQUIRE(Board("XOOXXOXOX").EvaluateBoard() == BoardState::Xwins);
  }

}

TEST_CASE("O winners") {
  SECTION("Horizontal OWin") {
    REQUIRE(Board(".x.oOox.x").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Vertical OWin") {
    REQUIRE(Board(".o.XOzxoX").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Diagonal OWin") {
    REQUIRE(Board("xxO.oXozz").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Reverse Diagonal OWin") {
    REQUIRE(Board("xxoxo.o..").EvaluateBoard() == BoardState::Owins);
  }

}

TEST_CASE("Unreachable State") {
  SECTION("More Os than Xs") {
    REQUIRE(Board("O.oOxo.o.").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("One more X than O") {
    REQUIRE(Board("xoxx.....").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("X wins but O plays after") {
    REQUIRE(Board("xo.oxo..x").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("O wins but X plays after") {
    REQUIRE(Board("xo.xox.ox").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("Both win") {
    REQUIRE(Board("OoOx.oxXx").EvaluateBoard() == BoardState::UnreachableState);
  }
}