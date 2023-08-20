#ifndef SUPPLEMENTARY_H
#define SUPPLEMENTARY_H

// enum for possible colours of chess.
enum Colour {WHITE, BLACK};

// overloaded ! that returns the opposite colour.
Colour operator!(Colour colour);

// overloaded output operator for colour.
std::ostream& operator << (std::ostream& out, Colour colour);

// enum storing the possible directions a piece moves in vertically.
enum VerticalDirection {DOWN = -1 ,NOT_VERTICAL = 0, UP = 1};

// enum storing the possible directions a piece moves in horizontally.
enum HorizontalDirection {LEFT = -1,  NOT_HORIZONTAL = 0, RIGHT = 1};

// struct holding information about a potential move.
struct Move {
  int originalColumn;
  int originalRow;
  int targetColumn;
  int targetRow;
};


#endif
