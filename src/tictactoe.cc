#include <stdexcept>
#include <string>

#include "tictactoe/tictactoe.h"

namespace tictactoe {


using std::string;

Board::Board(const string& board) {
  if (board.empty() || board.length() != kBoard_Size) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }
  input_board = board;
  board_view =
      vector<vector<char>>(kNumberToWin_,
                           vector<char>(kNumberToWin_, '.'));
  int string_pos = 0;
  for (int i = 0; i < kNumberToWin_; i++) {
    for (int j = 0; j < kNumberToWin_; j++) {
      board_view[i][j] = putchar(tolower(input_board.at(string_pos)));
      string_pos++;
    }
  }
}

BoardState Board::EvaluateBoard() const {
  if (IsUnreachableState()) {
    return BoardState::UnreachableState;
  }

  bool player_1_isWinner = HasWon(player_1);
  bool player_2_isWinner = HasWon(player_2);
  if (player_1_isWinner && player_2_isWinner) {
    return BoardState::UnreachableState;
  } else if (player_1_isWinner) {
    return BoardState::Xwins;
  } else if (player_2_isWinner) {
    return BoardState::Owins;
  }
  return BoardState::NoWinner;
}

bool Board::IsDiagonalWinner(char player) const {
  for (int i = 0; i < kNumberToWin_; i++) {
    if (board_view[i][i] != player) {
      return false;
    }
  }
  return true;
}

bool Board::IsWinnerReverseDiagonal(char player) const {
  for (int i = 0; i < kNumberToWin_; i++) {
    if (board_view[kNumberToWin_ - i - 1][i] != player) {
      return false;
    }
  }
  return true;
}

bool Board::IsVerticalWinner(char player) const {
  for (int i = 0; i < kNumberToWin_; i++) {
    if (board_view[0][i] == player) {
      for (int j = 0; j < kNumberToWin_; j++) {
        if (board_view[j][i] != player) {
          break;
        } else if (j == kNumberToWin_ - 1) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Board::IsHorizontalWinner(char player) const {
  for (int i = 0; i < kNumberToWin_; i++) {
    if (board_view[i][0] == player) {
      for (int j = 0; j < kNumberToWin_; j++) {
        if (board_view[i][j] != player) {
          break;
        } else if (j == kNumberToWin_ - 1) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Board::IsUnreachableState() const {
  int countPlayer1 = 0;
  int countPlayer2 = 0;
  for (int i = 0; i < kNumberToWin_; i++) {
    for (int j = 0; j < kNumberToWin_; j++) {
      if (board_view[i][j] == player_1) {
        countPlayer1++;
      } if (board_view[i][j] == player_2) {
        countPlayer2++;
      }
    }
  }
  return (countPlayer1 >= (2 + countPlayer2)
          || countPlayer2 >= (1 + countPlayer1)
          || (HasWon(player_1) && countPlayer1 == countPlayer2)
          || (HasWon(player_2) && countPlayer1 == countPlayer2 + 1));
}

bool Board::HasWon(char player) const {
  return (IsHorizontalWinner(player) || IsDiagonalWinner(player)
          || IsVerticalWinner(player) || IsWinnerReverseDiagonal(player));
}
}