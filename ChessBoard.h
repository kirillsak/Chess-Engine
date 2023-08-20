#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "piece.h"
#include <iostream>
#include "supplementary.h"
#include <string>

// forward declaration to avoid cyclical header file issue.
class Piece;

using namespace std;

// correspond to rows and columns of chess board.
const int NUMBER_RANKS = 8;
const int NUMBER_FILES = 8;

class ChessBoard{

public:

  /* constructor for the chess board, calls functions to set up pieces 
     and pointers to those pieces. */
  ChessBoard();

  /* destructor for the chess board */
  ~ChessBoard();

  /* function that takes in the move player wants to make on the chess board.
     @param originalPosition holds location of piece that player wants to move.
     @param targetPosition holds location of where the player 
     wants to move the piece.
  */
  void submitMove(const char originalPosition[], const char targetPosition[]);

  /* function that checks if target position supplied by 
     player contains a piece or is empty.
     @param move hold the column and row values of original and target positions */
  bool emptyTarget(Move move) const;

  /* function that checks if target location of a pawn contains a piece to kill.
      @param move holds the column and row values of original and target positions.
      @param verticalDirection determines whether the piece is 
       moving up or down on the board. */
  bool pawnKill(Move move, VerticalDirection verticalDirection) const;

  /* function that checks if the positions between the position of piece
     that wants to move and the target position are empty.
      @param move holds the column and row values of original and target positions.
      @param verticalDirection determines whether the piece is
       moving up or down on the board.
      @param horizontalDirection determines whether the piece is 
       moving left or right on the board. */
  bool pathEmpty(Move move, VerticalDirection verticalDirection,
		 HorizontalDirection horizontalDirection) const;

  /* function that puts all the chess pieces to their original positions on the board
     and sets up all the original board information. */
  void resetBoard();
  

  /* function that checks if move is legal according to the state of the game 
       @param move holds the column and row values of original and target positions.
       @param colour passes in the colour of who's turn it is */
  bool legalMove(Move move, Colour colour);

  
  void printBoard();

  
  

private:

  /* function that sets up appropirate Piece pointers and nullptr's
     to represent a chess board.
   */
  void setBoard();

  /* function that prints whether game is in check, checkmate or stalemate.
     @param colour is the colour of who's turn it currently is. */
  void printGameState(Colour colour);

  /* function that prints the move that occurs or is attempted by player.
     @param move hold the column and row values of original and target positions.
     @param originalPosition holds location of piece that player wants to move.
     @param targetPosition holds location of where the player 
     wants to move the piece. */
  void printMove(Move move, const char originalPosition[],
		 const char targetPosition[]) const;

  /* function that runs initial checks when a move is submitted,
     checking if it is the correct players turn, if a piece actually 
     exists in original position etc.
     @param originalPosition holds location of piece that player wants to move.
     @param move hold the column and row values of original 
      and target positions. */
  bool preliminaryChecks(const char originalPosition[], Move move);

  /* function that determines whether the player who's colour
     is passed in is in check.
     @param colour is the colour for which player
      you wish to determine is in check. */
  bool inCheck(Colour colour);

  /* function that determines whether the player who's colour
     is passed in is in checkmate.
     @param colour is the colour for which player
     you wish to determine is in checkmate. */
  bool inCheckMate(Colour colour);

  /* function that makes a move on the chess board.
     @param move hold the column and row values of original 
     and target positions. */
  void makeMove(Move move);

  /* function that reverses a move that was made,
     adjusting other details such king position
      @param move hold the column and row values of original 
      and target positions.
      @param piece holds the piece object that was stored in target position.
      @param kingMove is a bool that determines whether move involves a king. */
  void reverseMove(Move move, Piece* piece, bool kingMove);

  /* represents the chess board as an array of Piece pointers. */
  Piece* board[NUMBER_RANKS][NUMBER_FILES];

  /* array which stores the possible chess board piece objects. */
  Piece* pieceObjects[12];

  /* when a board is intially constructed, it is white players turn. */
  Colour coloursTurn = WHITE;

  // stores king locations.
  int whiteKingColumn = 4;
  int whiteKingRow = 0;
  int blackKingColumn = 4;
  int blackKingRow = 7;

  
  /* function that determines if a move attempts to castle. 
     @param move hold the column and row values of original 
     and target positions. */
  bool isCastling(Move move) const;

  /* function that checks if castling move is legal according to state of
     the board.
     @param move hold the column and row values of original 
     and target positions. */
  bool legalCastle(Move move);

  /* function that makes a castling move and adjusts board details accordingly.
     @param move hold the column and row values of original 
     and target positions. */
  void makeCastlingMove(Move move);

  /* function that reverses castling move and adjust board details accordingly.
     @param move hold the column and row values of original 
     and target positions. */
  void reverseCastlingMove(Move move);

  /* function that checks if a move affects any castling related details that
     the chess board class stores, adjusting them.
     @param move hold the column and row values of original 
     and target positions. */
  void castlingAdjustments(Move move);

  // details relevant to castling.
  bool blackKingInactive = true;
  bool whiteKingInactive = true;
  bool leftWhiteRookInactive = true;
  bool rightWhiteRookInactive = true;
  bool leftBlackRookInactive = true;
  bool rightBlackRookInactive = true;
  
 
  
};

#endif
