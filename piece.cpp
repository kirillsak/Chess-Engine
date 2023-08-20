#include "piece.h"
#include <iostream>

Piece::Piece(Colour colour, ChessBoard* cboard) {
  board_ = cboard;
  pieceColour = colour;
}

Piece::~Piece() {
}

Knight::Knight(Colour colour, ChessBoard* cboard) : Piece(colour, cboard){
  setType("Knight");
}

Bishop::Bishop(Colour colour, ChessBoard* cboard) : Piece(colour, cboard){
  setType("Bishop");
}

Rook::Rook(Colour colour, ChessBoard* cboard) : Piece(colour, cboard){
  setType("Rook");
}

Queen::Queen(Colour colour, ChessBoard* cboard) : Piece(colour, cboard){
  setType("Queen");
}

King::King(Colour colour, ChessBoard* cboard) : Piece(colour, cboard) {
  setType("King");
}

Pawn::Pawn(Colour colour, ChessBoard* cboard) : Piece(colour, cboard) {
  setType("Pawn");
}

Colour Piece::getPieceColour() const{
  return pieceColour;
}

string Piece::getType() const {
  return type;
}

void Piece::setType(string type_) {
  type = type_;
}

bool Pawn::isValid(Move move) {
  
  // calculates direction of pawn moves.
  VerticalDirection verticalDirection;
  if (getPieceColour() == BLACK)
    verticalDirection = DOWN;
  else
    verticalDirection = UP;
  HorizontalDirection horizontalDirection = NOT_HORIZONTAL;

  // standard pawn move forward.
  if (move.originalColumn == move.targetColumn
      && move.targetRow == move.originalRow + verticalDirection
      && board_->emptyTarget(move)) {
      return true;
    }
 
  // pawn kill (diagonal move).
   if ((move.originalColumn - verticalDirection == move.targetColumn
	&& move.originalRow + verticalDirection == move.targetRow) 
      || (move.originalColumn + verticalDirection == move.targetColumn
	  && move.originalRow + verticalDirection == move.targetRow)) {
     // if diagonal pawn target is empty, cannot do move.
     if (board_->emptyTarget(move))
       return false;
     else 
	 return true;
   }
  
  

   // case where pawn in starting position and path is empty.
   if ((move.originalRow == 6 && getPieceColour() == BLACK)
       || (move.originalRow == 1 && getPieceColour() == WHITE)) {
    if (move.originalColumn == move.targetColumn
	&& move.targetRow == move.originalRow + verticalDirection*2
	&& board_->pathEmpty(move, verticalDirection, horizontalDirection)
	&& board_->emptyTarget(move))
      return true;
    else
      return false;
  }
  return false;
}


bool King::isValid(Move move) {

  // king can move 1 unit around its column and row.
  VerticalDirection verticalDirection = calculateVertical(move);
  HorizontalDirection horizontalDirection = calculateHorizontal(move);
  
  if (move.targetRow == move.originalRow + verticalDirection
      && move.targetColumn == move.originalColumn + horizontalDirection)
    return true;
  else
    return false;  
}


bool Queen::isValid(Move move) {

  // checks if move is on the diagonal.
  if (diagonalMove(move))
    return true;

  // checks if move is straight vertically or horizontally.
  if (horizontalVerticalMove(move))
    return true;

  return false;
}


bool Rook::isValid(Move move) {

  // checks if move is straight horizontally or vertically.
  if (horizontalVerticalMove(move))
    return true;
  else
    return false;
  
}


bool Bishop::isValid(Move move) {

  // checks if move is on the diagonal.
  if (diagonalMove(move))
    return true;
  else
    return false;
}

bool Knight::isValid(Move move) {

  // knight moves in L shape. 1 and 2 are the respective possible columns/ rows.
  if ((move.targetColumn == move.originalColumn + 1
       || move.targetColumn == move.originalColumn -1)
      && (move.targetRow == move.originalRow + 2
	  || move.targetRow == move.originalRow -2))
    return true;

  if ((move.targetColumn == move.originalColumn + 2
       || move.targetColumn == move.originalColumn -2)
      && (move.targetRow == move.originalRow + 1
	  || move.targetRow == move.originalRow -1))
    return true;

  return false;
}

bool Piece::horizontalVerticalMove(Move move) {

  // in the case that neither column or row are the same, move is diagonal.
  if (move.originalColumn != move.targetColumn
      && move.originalRow != move.targetRow)
    return false;

  VerticalDirection verticalDirection = calculateVertical(move);
  HorizontalDirection horizontalDirection = calculateHorizontal(move);  

   int column = move.originalColumn + horizontalDirection;
   int row = move.originalRow + verticalDirection;

   /* loop through board in appropirate horizontal or 
      vertical direction to see if piece is on that path. */
   // 8, -1 ensure loop doesn't go off the board.
   while ((column < 8) && (column > -1) && (row < 8) && (row > -1)) {
     if (column == move.targetColumn && row == move.targetRow) {

       // if move is on this path, check if path there is empty.
       if (board_->pathEmpty(move, verticalDirection, horizontalDirection))
	 return true;
       else
	 return false;
     }
     column = column + horizontalDirection;
     row = row + verticalDirection;
   }
   return false;
}


bool Piece::diagonalMove(Move move) {

  // in the case that move is not on diagonal.
  if (move.originalColumn == move.targetColumn
      || move.originalRow == move.targetRow)
    return false;

  VerticalDirection verticalDirection = calculateVertical(move);
  HorizontalDirection horizontalDirection = calculateHorizontal(move);
  
  int column = move.originalColumn + horizontalDirection;
  int row = move.originalRow + verticalDirection;

  /* loop through board in appropirate diagonal direction 
     to see if piece is on that path. */
  // 8, -1 ensure loop doesn't go off the board.
  while ((column < 8) && (column > -1) && (row < 8) && (row > -1)){
    if (row == move.targetRow && column  == move.targetColumn) {

      // if move is on path, check if path there is empty.
      if (board_->pathEmpty(move, verticalDirection, horizontalDirection))
	return true;
      else
	return false;
    }
    column = column + horizontalDirection;
    row = row + verticalDirection;
  }
  return false;
}



VerticalDirection Piece::calculateVertical(Move move) {

  VerticalDirection direction;
  /* if orginal row and orignal column are the same
     there is no direction of movements. */
  if (move.originalRow == move.targetRow)
    direction = NOT_VERTICAL;
   
  else if (move.originalRow > move.targetRow) 
    direction = DOWN;
   
  else
    direction = UP;

  return direction;
}



HorizontalDirection Piece::calculateHorizontal(Move move) {

  HorizontalDirection horizontalDirection;

  /* if orginal row and orignal column are the same
     there is no direction of movements. */
  if (move.targetColumn == move.originalColumn)
    horizontalDirection = NOT_HORIZONTAL;
  
  else if (move.targetColumn > move.originalColumn)
    horizontalDirection = RIGHT;
  
  else
    horizontalDirection = LEFT;

  return horizontalDirection;
}
