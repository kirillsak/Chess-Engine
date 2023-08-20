chess: ChessMain.o ChessBoard.o piece.o
	g++ -Wall -g ChessMain.o ChessBoard.o piece.o -o chess


ChessMain.o: ChessMain.cpp ChessBoard.h piece.h supplementary.h
	g++ -Wall -g ChessMain.cpp -c -o ChessMain.o

ChessBoard.o: ChessBoard.cpp ChessBoard.h piece.h  supplementary.h
	g++ -Wall -g ChessBoard.cpp -c -o ChessBoard.o

piece.o: piece.cpp piece.h ChessBoard.h supplementary.h
	g++ -Wall -g piece.cpp -c -o piece.o

