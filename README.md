A Course Project in Artificial Intelligence course. Basically Mini-Max was used to code up a player for Quoridor game. The search space in Minimax Space was reduced by considering all walls placing along the shortest path. Through this , search depth of 5 was acheived for a 9X9 board. The player performed decently against some of its opponent.The Quoridor Servers contains varied boards of difffernt dimensions.

Different board_<>.cpp files contain my various experiments with various heuristics functions. The file client.cpp set communicates with the srever and sends the move and recieves the move, get the configuration of the board initially. The minimax Logic is implemented in Borad.cpp file. Board.h contains the Board class in which Board state is maintained and various functions are implemented to check for vailidity of moves.  

Usage:
	Compiling
		./compile.sh
		It compiles Board_1.cpp and client.cpp
	python ../QuoridorServers/Quoridor<board config>/TkBoard.py
	./<exec name> 127.0.0.1 12345
	./<exec anme> 127.0.0.1 12345
