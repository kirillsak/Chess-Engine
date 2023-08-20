#include "ChessBoard.h"
#include <iostream>

using namespace std;




ChessBoard::ChessBoard() {

  // one of each type of piece object is stored in array for reuse.
  pieceObjects[0] = new Pawn(WHITE, this);
  pieceObjects[1] = new Rook(WHITE, this);
  pieceObjects[2] = new Knight(WHITE, this);
  pieceObjects[3] = new Bishop(WHITE, this);
  pieceObjects[4] = new Queen(WHITE, this);
  pieceObjects[5] = new King(WHITE, this);
  pieceObjects[6] = new Pawn(BLACK, this);
  pieceObjects[7] = new Rook(BLACK, this);
  pieceObjects[8] = new Knight(BLACK, this);
  pieceObjects[9] = new Bishop(BLACK, this);
  pieceObjects[10] = new Queen(BLACK, this);
  pieceObjects[11] = new King(BLACK, this);

  // piece pointers to above are setup.
  setBoard();

  cout << "A new chess game is started!" << endl;
}


ChessBoard::~ChessBoard() {
  // deletes piece objects off heap when chessboard destructed.
  for (int i = 0; i<12; i++)
    delete pieceObjects[i];
}


void ChessBoard::setBoard() {

  // index convention is column first then row.
  // set empty board positions.
  for (int column=0; column<8; column++) {
    for (int row=0; row<8; row++)
      board[column][row] = nullptr;
  }
 
  // point rook starting positions to a rook instance.
  board[0][7] = pieceObjects[7];
  board[7][7] = pieceObjects[7];
  board[0][0] = pieceObjects[1];
  board[7][0] = pieceObjects[1];
  
  // point knight startingpositions to knight instance.
  board[1][7] = pieceObjects[8];
  board[6][7] = pieceObjects[8];
  board[1][0] = pieceObjects[2];
  board[6][0] = pieceObjects[2];
 
  // point bishop starting positions to bishop instance.
  board[2][7] = pieceObjects[9];
  board[5][7] = pieceObjects[9];
  board[2][0] = pieceObjects[3];
  board[5][0] = pieceObjects[3];

  //point queen starting positions to queen instance.
  board[3][7] = pieceObjects[10];
  board[3][0] = pieceObjects[4];

  //point king starting positions to king instance.
  board[4][7] = pieceObjects[11];
  board[4][0] = pieceObjects[5];

  // point pawn starting positions to pawn instance.
  for (int column=0; column<8; column++) {
    board[column][6] = pieceObjects[6];
    board[column][1] = pieceObjects[0];
  }
}



void ChessBoard::resetBoard() {

  // sets board to original positions.
  setBoard();

  // reset all variables board needs to know.
  whiteKingColumn = 4;
  whiteKingRow = 0;
  blackKingColumn = 4;
  blackKingRow = 7;

  blackKingInactive = true;
  whiteKingInactive = true;
  leftWhiteRookInactive = true;
  rightWhiteRookInactive = true;
  leftBlackRookInactive = true;
  rightBlackRookInactive = true;
  
  coloursTurn = WHITE;

  cout << "A new chess game is started!" << endl;
}


void ChessBoard::submitMove(const char originalPosition[],
			    const char targetPosition[]) {

  // positions are converted and stored as column and row numbers in a struct.
  Move move;
  move.originalColumn = originalPosition[0] - 'A';
  move.originalRow = originalPosition[1] - '1';
  move.targetColumn = targetPosition[0] - 'A';
  move.targetRow = targetPosition[1] - '1';

  /* run preliminary checks on the move to ensure it is the correct players 
     turn and piece in original position exist.*/
  if (!preliminaryChecks(originalPosition, move))
    return;

  
  // if move attempts to castle, go through castling process.
  if (isCastling(move)) {
    if (legalCastle(move)) {
      makeCastlingMove(move);
      castlingAdjustments(move);
      cout << "Castling move by " << coloursTurn << " with rook in position "
	   << originalPosition << " and king in position "
	   << targetPosition << endl;
      // once move is made it becomes other players turn.
      coloursTurn = !coloursTurn;
      printGameState(coloursTurn);
      return;
    }
    cout << "Illegal attempt at castle" << endl;
    return;
  }

  
  /* checks if move is valid (is one of the potential moves of the piece) 
     and legal (the associated movement on the board does not put the 
     player in check) before making the move. */
  if (board[move.originalColumn][move.originalRow]->isValid(move)
      && legalMove(move, coloursTurn)) {

    printMove(move, originalPosition, targetPosition);
    makeMove(move);
    castlingAdjustments(move);
    // once move is made it becomes other players turn.
    coloursTurn = !coloursTurn;

    // checks state of the game after move occurs.
    printGameState(coloursTurn);
  }
  
  else
    cout << coloursTurn << "'s "
	 << board[move.originalColumn][move.originalRow]->getType()
	 << " cannot move to " << targetPosition << "!" << endl;
}



bool ChessBoard::preliminaryChecks(const char originalPosition[], Move move)  {

  // disallows move to occur if game is in checkmate.
  if (inCheckMate(coloursTurn)) {
    cout << "Game has ended, no further moves can be made. Please reset board."
	 << endl;
    return false;
  }
  

  // check supplied move is a valid position.
  if ((move.originalColumn < 0) || (move.originalColumn > 7)
      || (move.targetColumn > 7) || (move.originalRow < 0)
      || (move.targetRow > 7) || (move.targetRow < 0)
      || (move.targetRow > 7) || (move.targetRow < 0)) {
    cout << "Invalid positions supplied" << endl; 
    return false;
  }
  
  // check piece exists in submitted original position.
  if (board[move.originalColumn][move.originalRow] == nullptr) {
    cout << "There is no piece at position " << originalPosition << "!" << endl;
    return false;
  }
  
  // check if submitted move corresponds to who's turn it is.
  if (board[move.originalColumn][move.originalRow]->getPieceColour()
      != coloursTurn) {
    if (board[move.originalColumn][move.originalRow]->getPieceColour()
	== BLACK) {
      cout << "It is not black's turn to move!" << endl;
    }
    else {
      cout << "It is not white's turn to move!" << endl;
    }
    return false;
  }

  return true;
}



bool ChessBoard::legalMove(Move move, Colour colour) {

  // keeps a store of piece object in target position.
  Piece* piece = board[move.targetColumn][move.targetRow];

  // prevents attacking piece from eating it's own colour.
  if (board[move.originalColumn][move.originalRow] != nullptr
      && board[move.targetColumn][move.targetRow] != nullptr) {
    if (board[move.originalColumn][move.originalRow]->getPieceColour()
	== board[move.targetColumn][move.targetRow]->getPieceColour())
      return false;
  }

  // keep track of whether the move involves a king to adjust board details.
  bool kingMove = false;
  if ((move.originalColumn == whiteKingColumn && move.originalRow
       == whiteKingRow)
      || (move.originalColumn == blackKingColumn && move.originalRow
	  == blackKingRow))
    kingMove = true;

  makeMove(move);
  
  // checks if making the move puts player in check and reverses move.
  if (inCheck(colour)) {
    reverseMove(move, piece, kingMove);
    return false;
  }
  else {
    reverseMove(move, piece, kingMove);
    return true;
  }
}




void ChessBoard::makeMove(Move move) {

  // if move is to be made and piece moving is a king, the kings position gets updated.
  if (move.originalColumn == whiteKingColumn && move.originalRow
      == whiteKingRow) {
    whiteKingColumn = move.targetColumn;
    whiteKingRow = move.targetRow;
  }

  if (move.originalColumn == blackKingColumn && move.originalRow == blackKingRow) {
    blackKingColumn = move.targetColumn;
    blackKingRow = move.targetRow;
  }

  // movement occurs here
  board[move.targetColumn][move.targetRow]
    = board[move.originalColumn][move.originalRow];
  
  board[move.originalColumn][move.originalRow] = nullptr;
 
}


void ChessBoard::reverseMove(Move move, Piece* piece, bool kingMove) {

  // if king has moved, reversing will also reverse king position details.
  if (kingMove) {
    if (move.targetColumn == whiteKingColumn && move.targetRow == whiteKingRow) {
      whiteKingColumn = move.originalColumn;
      whiteKingRow = move.originalRow;
    }
    
    if (move.targetColumn == blackKingColumn && move.targetRow == blackKingRow) {
      blackKingColumn = move.originalColumn;
      blackKingRow = move.originalRow;
    }
  }

  // move reverse occurs here
  board[move.originalColumn][move.originalRow]
    = board[move.targetColumn][move.targetRow];
  board[move.targetColumn][move.targetRow] = piece;
  
}




bool ChessBoard::inCheck(Colour colour) {

  int kingColumn;
  int kingRow;

  // used to determine which players king is checking if it is under attack.
  if(colour == WHITE){
    kingColumn = whiteKingColumn;
    kingRow = whiteKingRow;
  }
  else {
    kingColumn = blackKingColumn;
    kingRow = blackKingRow;
  }

  // position which will be attacked.
  Move kingThreatMove;
  
  // loop through each position on the board
  for (int column = 0; column < 8; column++) {
    for (int row = 0; row < 8; row++) {

      // finds piece opposite colour to king under attack.
      if (board[column][row] != nullptr && board[column][row]->getPieceColour()
	  != colour) {
	
	kingThreatMove.originalColumn = column;
	kingThreatMove.originalRow = row;
	kingThreatMove.targetColumn = kingColumn;
	kingThreatMove.targetRow = kingRow;

	// if the move onto the king is valid  player is in check.
	if (board[column][row]->isValid(kingThreatMove)) {	 
	  return true;
	}
      }
    }
  }
  /*if no opposite colour piece can validly move onto
    the kings position then not in check */
  return false;
}



bool ChessBoard::inCheckMate(Colour colour) {

  Move move;

  // loop through each position on the board.
  for (int column = 0; column < 8; column++) {
    for (int row = 0; row < 8; row++) {

      // find pieces of the same colour as player who is in check.
      if (board[column][row] != nullptr
	  && board[column][row]->getPieceColour() == colour){

	// for each piece attempt all possible moves.
	for (int targetColumn = 0; targetColumn < 8; targetColumn++) {
	  for (int targetRow = 0; targetRow < 8; targetRow++) {
	      
	    move.originalColumn = column;
	    move.originalRow = row;
	    move.targetColumn = targetColumn;
	    move.targetRow = targetRow;

	    /* if any move is both valid and puts king
	       out of check then not checkmate. */
	    if (board[column][row]->isValid(move)) {	         	       
	      if (legalMove(move, colour)) {       		  		
		return false;
	      }
	    }
	  }
	}
      }
    }
  }
  // if no possible move can be made to leave check then player is in checkmate.
  return true;
}
  




void ChessBoard::printGameState(Colour colour) {
  if (inCheck(coloursTurn)) {
    if (inCheckMate(coloursTurn)) {
      cout << coloursTurn << " is in checkmate" << endl;
    }
    else
      cout << coloursTurn << " is in check" << endl;
  }
  else
    if (inCheckMate(coloursTurn))
      cout << "Game is in stalemate" << endl;
}
    




void ChessBoard::printMove(Move move, const char originalPosition[],
			   const char targetPosition[]) const {
  
  if (board[move.targetColumn][move.targetRow] == nullptr) {
    cout << coloursTurn << "'s "
	 << board[move.originalColumn][move.originalRow]->getType()
	 << " moves from " << originalPosition << " to "
	 << targetPosition << endl;
  }
  else
    cout << coloursTurn << "'s "
	 << board[move.originalColumn][move.originalRow]->getType()
	 << " moves from " << originalPosition << " to " << targetPosition
	 << " taking " << !coloursTurn << "'s "
	 << board[move.targetColumn][move.targetRow]->getType() << endl;
}



bool ChessBoard::emptyTarget(Move move) const {

  // if target contains a piece, return it is false that position is empty.
  if (board[move.targetColumn][move.targetRow] != nullptr)
    return false;
  else
    return true;
}
  





bool ChessBoard::pathEmpty(Move move, VerticalDirection verticalDirection,
			   HorizontalDirection horizontalDirection) const{

  int column = move.originalColumn + horizontalDirection;
  int row = move.originalRow + verticalDirection;

  /*check between original position and target if there
  exists a piece that blocks move. */
  while (column != move.targetColumn || row != move.targetRow) {
    if (board[column][row] != nullptr) 
      return false;
    
    else {
      // if empty, increment to the next position.
      column = column + horizontalDirection;
      row = row + verticalDirection;
    } 
  }
  // if all positions between original and target are empty return true.
  return true;
}







// Castling functions below.

bool ChessBoard::isCastling(Move move) const {

  if (coloursTurn == BLACK) {

    // if target is kings position and king is inactive.
    if (move.targetColumn == 4 && move.targetRow == 7 && blackKingInactive){

      // if move involves the black rooks.
      if (move.originalRow == 7) {

	// check if supplied move is a rook that also has not moved during game.
	if (move.originalColumn == 0 && leftBlackRookInactive)
	  return true;
	if (move.originalColumn == 7 && rightBlackRookInactive)
	  return true;
      }
      return false;
    }
  }
  else {
    // if target is kings position and king is inactive.
    if (move.targetColumn == 4 && move.targetRow == 0 && whiteKingInactive){

      // if move involes white rooks.
      if (move.originalRow == 0) {

	// check if suopplied move is a rook that also has not moved during game.
	if (move.originalColumn == 0 && leftWhiteRookInactive)
	  return true;
	if (move.originalColumn == 7 && rightWhiteRookInactive)
	  return true;
      }
    }
    return false;
  }
  return false;
}
  


void ChessBoard::makeCastlingMove(Move move) {

  // calculate direction of castling.
  HorizontalDirection horizontalDirection;
  if (move.originalColumn == 0)
    horizontalDirection = RIGHT;
  else
    horizontalDirection = LEFT;

  // if queen side castling/
  if (move.originalColumn == 0) {

    // assigns king and rook to their positions in case of castling.
    board[move.originalColumn + horizontalDirection*3][move.originalRow]
      = board[move.originalColumn][move.originalRow];
    
    board[move.originalColumn][move.originalRow] = nullptr;
    
    board[move.originalColumn + horizontalDirection*2][move.originalRow]
      = board[move.targetColumn][move.targetRow];
    
    board[move.targetColumn][move.targetRow] = nullptr;

    // adjust king positions.
    if (coloursTurn == BLACK)
      blackKingColumn = move.originalColumn + horizontalDirection*2;
    else
      whiteKingColumn = move.originalColumn + horizontalDirection*2;

  }
  // if not queen side castling.
  else {

    // assigns king and rook to their positions in case of castling.
    board[move.originalColumn + horizontalDirection*2][move.originalRow]
      = board[move.originalColumn][move.originalRow];
    
    board[move.originalColumn][move.originalRow] = nullptr;
    
    board[move.originalColumn + horizontalDirection][move.originalRow]
      = board[move.targetColumn][move.targetRow];
    
    board[move.targetColumn][move.targetRow] = nullptr;

    // adjust king position after move.
    if (coloursTurn == BLACK)
      blackKingColumn = move.originalColumn + horizontalDirection;
    else
      whiteKingColumn = move.originalColumn + horizontalDirection;
  } 
}


void ChessBoard::reverseCastlingMove(Move move) {

  // calculate direction of castling.
  HorizontalDirection horizontalDirection;
  if (move.originalColumn == 0)
    horizontalDirection = RIGHT;
  else
    horizontalDirection = LEFT;

  // if queen side castling.
  if (move.originalColumn == 0) {

    // place king and rook back to original positions in move.
    board[move.originalColumn][move.originalRow]
      = board[move.originalColumn + horizontalDirection*3][move.originalRow];
    
    board[move.originalColumn + horizontalDirection*3][move.originalRow]
      = nullptr;
    
    board[move.targetColumn][move.targetRow]
      =  board[move.originalColumn + horizontalDirection*2][move.originalRow];
    
    board[move.originalColumn + horizontalDirection*2][move.originalRow]
      = nullptr;
  }

  // not queen side castle reverse.
  else {
    // reverse positions of king and rook to original.
    board[move.originalColumn][move.originalRow]
      = board[move.originalColumn + horizontalDirection*2][move.originalRow];
    
    board[move.originalColumn + horizontalDirection*2][move.originalRow]
      = nullptr;
    
    board[move.targetColumn][move.targetRow]
      =  board[move.originalColumn + horizontalDirection][move.originalRow];
    
    board[move.originalColumn + horizontalDirection][move.originalRow]
      = nullptr;
  }

  // reverse position of king.
  if (coloursTurn == BLACK)
    blackKingColumn = move.targetColumn;
  else
    whiteKingColumn = move.targetColumn;
    
}

bool ChessBoard::legalCastle(Move move) {

  // castle cannot occur when player is in check.
  if (inCheck(coloursTurn))
    return false;

  // calculate direction.
  HorizontalDirection horizontalDirection;
  if (move.originalColumn == 0)
    horizontalDirection = RIGHT;
  else
    horizontalDirection = LEFT;

  // ensure path is empty between king and rook.
  if (board[move.originalColumn + horizontalDirection][move.originalRow]
      == nullptr
      && board[move.originalColumn + horizontalDirection*2][move.originalRow]
      == nullptr) {
    // if queen side castle then check extra position is empty.
    if (move.originalColumn == 0) {
      if (board[move.originalColumn + horizontalDirection*3][move.originalRow]
	  == nullptr) {
       
	makeCastlingMove(move);
     
	if (inCheck(coloursTurn)) {
	  reverseCastlingMove(move);
	  return false;
	}
	else {
	  reverseCastlingMove(move);
	  return true;
	}  
      }
    }

    // if not queen side castle, perform move and determine if in check.
    makeCastlingMove(move);
    if (inCheck(coloursTurn)) {
      reverseCastlingMove(move);
      return false;
    }
    else {
      reverseCastlingMove(move);
      return true;
    }  
  }
  
  return false;
}


void ChessBoard::castlingAdjustments(Move move) {

  // if a castling move occurs then set king activity as has moved.
  if (isCastling(move)) {
    if (coloursTurn == BLACK)
      blackKingInactive = false;
    else
      whiteKingInactive = false;
  }

  
  /* depending on original position, adjust if rooks have moved, 
     stored in chess board. */
  if (move.originalColumn == 0 && move.originalRow == 0)
    leftWhiteRookInactive = false;
  if (move.originalColumn == 7 && move.originalRow == 0)
    rightWhiteRookInactive = false;
  if (move.originalColumn == 0 && move.originalRow == 7)
    leftBlackRookInactive = false;
  if (move.originalColumn == 7 && move.originalRow == 7)
    rightBlackRookInactive = false;

  // adjust kings positions if they have moved.
  if (move.originalColumn == 4 && move.originalRow == 0)
    whiteKingInactive = false;
  if (move.originalColumn == 4 && move.originalRow == 7)
    blackKingInactive = false;
}


Colour operator!(Colour colour) {

  // returns opposite colour.
  if (colour == BLACK)
    return WHITE;
 else
   return BLACK;
}


/*
void ChessBoard::printBoard() {
  for (int i=0; i<8; i++) {
    cout << endl;
    for (int j=0; j<8; j++) {
      if (board[i][j] != nullptr) {
	if (board[i][j]->type == "Pawn")
	  cout << 'P';
	if (board[i][j]->type == "Queen")
	  cout << 'Q';
	if (board[i][j]->type == "Bishop")
	  cout << 'B';
	if (board[i][j]->type == "King")
	  cout << 'K';
	if (board[i][j]->type == "Rook")
	  cout << 'R';
	if (board[i][j]->type == "Knight")
	  cout << 'N';
      }
      else
	cout << '.';
    }
  }
}
*/


std::ostream& operator << (std::ostream& out, Colour colour) {
  if (colour == BLACK)
    out << "Black";
  else
    out << "White";
  
  return out;
}
