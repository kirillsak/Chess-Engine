#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include "ChessBoard.h"
#include "supplementary.h"
#include <cstring>

using namespace std;

// forward declaration of ChessBoard to avoid cyclical header issues.
class ChessBoard;

class Piece {
    
public:

  /* Piece constructor.
     @param colour is the colour of piece being constructed.
     @param cboard is a pointer to the chess board object piece sit on. */
  Piece(Colour colour, ChessBoard* cboard);

  /* virtual function inherited by child classes which determines whether
     a move is valid depending on ruleset of child class. 
     @param move hold the column and row values of original 
     and target positions.*/
  virtual bool isValid(Move move) = 0;

  /* destructor for Piece object. */
  virtual ~Piece();


  /* getter function for the colour of piece. */
  Colour getPieceColour() const;

  /* getter function for the type of a piece */
  string getType() const;

  /* setter used to set type of piece when piece is constructed.
     @ type_ is the name of type of piece. */
  void setType(string type_);
 

  /* stores the chess board object on which the piece sits. */
  const ChessBoard* board_;  

protected:

  /* function that determines whether move passed in moves horizontally
     or vertically and checks if path is empty.
     @param move hold the column and row values of original 
     and target positions. */
  bool horizontalVerticalMove(Move move);
  
  /* function that determines whether move passed in moves on the diagonal
     and checks if path is empty.
     @param move hold the column and row values of original 
     and target positions. */
  bool diagonalMove(Move move);

  /* function that calculates the vertical direction of a move (up or down)
     on the chess board. 
     @param move hold the column and row values of original 
     and target positions.*/
  VerticalDirection calculateVertical(Move move);

  /* function that calculates the horizontal direction of a move (left or right)
     on the chess board. 
     @param move hold the column and row values of original 
     and target positions.*/
  HorizontalDirection calculateHorizontal(Move move);

  /* colour of piece */
  Colour pieceColour;

  /* name of type of piece */
  string type;
};


class Pawn : public Piece {
public:
  /* pawn constructor 
   @param colour is the colour of piece
   @param cboard is the chess board object associated with piece.*/
  Pawn(Colour colour, ChessBoard* cboard);
  
private:
  /* function that determines if move is valid according to rules of a pawn.
     @param move hold the column and row values of original 
     and target positions. */
  bool isValid(Move move);
};


class Knight : public Piece {
public:
  /* knight constructor 
     @param colour is the colour of piece
     @param cboard is the chess board object associated with piece.*/
  Knight(Colour colour, ChessBoard* cboard);

private:
   /* function that determines if move is valid according to rules of a knight.
     @param move hold the column and row values of original 
     and target positions. */
  bool isValid(Move move);
 
};

class Queen : public Piece {
public:
  /* queen constructor 
     @param colour is the colour of piece
     @param cboard is the chess board object associated with piece.*/
  Queen(Colour colour, ChessBoard* cboard);
 

private:
   /* function that determines if move is valid according to rules of a queen.
     @param move hold the column and row values of original 
     and target positions. */
  bool isValid(Move move);
};


class King : public Piece {
public:
  /* king constructor 
     @param colour is the colour of piece
     @param cboard is the chess board object associated with piece.*/
  King(Colour colour, ChessBoard* cboard);
 
private:
  /* function that determines if move is valid according to rules of a king.
     @param move hold the column and row values of original 
     and target positions. */
  bool isValid(Move move);
};

  

class Bishop : public Piece {
public:
  /* bishop constructor 
     @param colour is the colour of piece
     @param cboard is the chess board object associated with piece.*/
  Bishop(Colour colour, ChessBoard* cboard);

private:
   /* function that determines if move is valid according to rules of a bishop.
     @param move hold the column and row values of original 
     and target positions. */
  bool isValid(Move move);  
};



class Rook : public Piece {
public:
  /* rook constructor 
     @param colour is the colour of piece
     @param cboard is the chess board object associated with piece.*/
  Rook(Colour colour, ChessBoard* Cboard);
  
private:
   /* function that determines if move is valid according to rules of a rook.
     @param move hold the column and row values of original 
     and target positions. */
  bool isValid(Move move);
};


  

#endif
