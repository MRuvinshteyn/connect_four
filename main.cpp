#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;

char board[6][7];
char comp_char = 'O', play_char = 'X';

void setupBoard(){
	for (int row = 0; row < 6; row++)
		for (int col = 0; col < 7; col++)
			board[row][col] = '-';
}

void printBoard(){
	for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++)
			cout << "| " << board[row][col] << " |";
		cout << endl;
	}
}

int checkBoard(){
	char curr, first, second, third;

	//checks for horizontal win
	for (int row = 0; row < 6; row++)
		for (int col = 0; col < 4; col++){
			curr = board[row][col];
			first = board[row][col + 1];
			second = board[row][col + 2];
			third = board[row][col + 3];
			if (curr != '-' && curr == first && first == second && second == third){
				if (curr == comp_char) return -1;
				else return 1;
			}
		}

	//checks for vertical win
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 7; col++){
			curr = board[row][col];
			first = board[row + 1][col];
			second = board[row + 2][col];
			third = board[row + 3][col];
			if (curr != '-' && curr == first && first == second && second == third){
				if (curr == comp_char) return -1;
				else return 1;
			}
		}

	//check for diagonal win
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 4; col++){
			curr = board[row][col];
			first = board[row + 1][col + 1];
			second = board[row + 2][col + 2];
			third = board[row + 3][col + 3];
			if (curr != '-' && curr == first && first == second && second == third){
				if (curr == comp_char) return -1;
				else return 1;
			}
		}

	//check for other diagonal win
	for (int row = 0; row < 3; row++)
		for (int col = 3; col < 7; col++){
			curr = board[row][col];
			first = board[row + 1][col - 1];
			second = board[row + 2][col - 2];
			third = board[row + 3][col - 3];
			if (curr != '-' && curr == first && first == second && second == third){
				if (curr == comp_char) return -1;
				else return 1;
			}
		}

	return 0;
}

void playerMove(){
	int col;
	cout << "Please enter column number: ";
	cin >> col;
	while (0 > col || col > 6 || board[0][col] != '-'){
		if (0 > col || col > 6){
			cout << "Please enter a column within range: ";
			cin >> col;
		}
		else{
			cout << "Column is full, please try again: ";
			cin >> col;
		}
	}
	for (int row = 0; row < 6; row++){
		if (row == 5 && board[5][col] == '-')
			board[5][col] = play_char;
		else if (board[row][col] == '-' && board[row + 1][col] != '-')
			board[row][col] = play_char;
	}
}

void cpuMove(){
	int col = rand() % 7;
	while (board[0][col] != '-')
		col = rand() % 7;
	for (int row = 0; row < 6; row++){
		if (row == 5 && board[5][col] == '-')
			board[5][col] = comp_char;
		else if (board[row][col] == '-' && board[row + 1][col] != '-')
			board[row][col] = comp_char;
	}
}

bool checkFull(){
	for (int row = 0; row < 6; row++)
		for (int col = 0; col < 7; col++)
			if (board[row][col] == '-') return false;
	return true;
}

int main(){
	int winner = 0;
	setupBoard();
	
	cout << "Type in your desired character: ";
	cin >> play_char;
	while (play_char == '-'){
		cout << "Please enter a different character: ";
		cin >> play_char;
	}
	if (comp_char == play_char)
		comp_char = 'X';
	
	while (true){
		printBoard();
		playerMove();
		if (checkBoard() == 1){
			printBoard();
			cout << "You Win!" << endl;
			break;
		}
		cpuMove();
		if (checkBoard() == -1){
			printBoard();
			cout << "You Lose!" << endl;
			break;
		}
		if (checkFull()){
			printBoard();
			cout << "Draw!" << endl;
			break;
		}
	}

	return 0;
}