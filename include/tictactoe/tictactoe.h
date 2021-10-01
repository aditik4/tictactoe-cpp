#pragma once

#include <string>
#include <vector>
using namespace std;
namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   * @return the state of the board as a BoardState
   */
  BoardState EvaluateBoard() const;

 private:
  /**
   * Stores the number of elements in a row needed to win in any direction
   */
  static constexpr int kNumberToWin_ = 3;

  /**
   * Stores the size of the board, as in the total number of elements
   * required to make a valid board
   */
  static const int kBoard_Size = kNumberToWin_ * kNumberToWin_;

  /**
   * Stores the character that denotes player 1's turn
   */
  static const char player_1 = 'x';

  /**
   * Stores the character that denotes player 2's turn
   */
  static const char player_2 = 'o';

  /**
   * 2d vector that stores the board contents
   */
  vector<vector<char>> board_view;

  /**
   * string that represents the board
   */
  string input_board;

  /**
   * Determines if a winner is present in the diagonal direction.
   * @param player the player's character to check for.
   * @return true if there is a win in the diagonal direction;
   *         otherwise, false.
   */
  bool IsDiagonalWinner(char player) const;

  /**
   * Determines if a win is present in the horizontal direction.
   * @param player the player's character to check for.
   * @return true if a horizontal win is present;
   *         otherwise, false.
   */
  bool IsHorizontalWinner(char player) const;

  /**
   * Determines if a win is present in the vertical direction.
   * @param player the player's character to check for.
   * @return true if a vertical win is present;
   *         otherwise, false.
   */
  bool IsVerticalWinner(char player) const;

  /**
   * Determines if a win is present in the reverse diagonal direction.
   * @param player the player's character to check for.
   * @return true if the board contains a win in the reverse diagonal direction'
   *         otherwise, false.
   */
  bool IsWinnerReverseDiagonal(char player) const;

  /**
   * Determines if the board represents an unreachable state
   * @return true if a vertical win is present;
   *         otherwise, false.
   */
  bool IsUnreachableState() const;

  /**
   * Determines whether the player has won in any direction
   * @param player the player to check if won
   * @return true if the given player has won in any direction; otherwise,
   *         false.
   */
  bool HasWon(char player) const;

};

}
