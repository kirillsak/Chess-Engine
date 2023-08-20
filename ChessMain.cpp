#include"ChessBoard.h"

#include<iostream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	cout << '\n';
	  cout << "===========================" << endl;
  
    
cb.submitMove("D7", "D6");
	cout << '\n';

    
    cb.submitMove("D4", "H6");
    cout << '\n';
    
    cb.submitMove("D2", "D4");
    cout << '\n';
	
    cb.submitMove("F8", "B4");
    cout << '\n'; 

    cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

      
	cb.submitMove("E2", "E4");
	//	cb.printBoard();
	cb.submitMove("E7", "E6");
	//cb.printBoard();
	cout << '\n';

	cb.submitMove("D2", "D4");
	//	cb.printBoard();
	cb.submitMove("D7", "D5");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("B1", "C3");
	//	cb.printBoard();
	cb.submitMove("F8", "B4");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("F1", "D3");
	//	cb.printBoard();
	cb.submitMove("B4", "C3");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("B2", "C3");
	//	cb.printBoard();
	cb.submitMove("H7", "H6");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("C1", "A3");
	//	cb.printBoard();
	cb.submitMove("B8", "D7");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("D1", "E2");
	//	cb.printBoard();
	cb.submitMove("D5", "E4");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("D3", "E4");
	//	cb.printBoard();
	cb.submitMove("G8", "F6");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("E4", "D3");
	//	cb.printBoard();
	cb.submitMove("B7", "B6");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("E2", "E6");
	//	cb.printBoard();
	cb.submitMove("F7", "E6");
	//	cb.printBoard();
	cout << '\n';

	cb.submitMove("D3", "G6");
	//	cb.printBoard();

				 
	cout << '\n';
	
	return 0;
}
