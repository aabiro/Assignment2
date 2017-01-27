//-------------------------------------//
//-------------------------------------//
//  Aaryn Biro -- Assignment 2 - 1037  //
//-------------------------------------//
//------------TopSpin Game-------------//

#include "CDLL.h"
#include "TopSpin.h"
#include <iostream>


using namespace std;

int main()
{

	int choice;
	unsigned int numRandomMoves;

	TopSpin ts;
	//TopSpin ts(30, 6);  //Topspin(size, spinnerSize)

	cout << ts;

	cout << "How many random moves?" << endl;
	cin >> numRandomMoves;
	while ((numRandomMoves <= 0)) {
		cout << "Invalid! Please enter again..." << endl;
		cin >> numRandomMoves;
	}
	ts.randomMove(numRandomMoves);			//initiate random moves


	do {

		cout << ts;

		if (ts.isSolved() == 1) {
			cout << "Congratulations, you solved the puzzle!\n" << endl;
			break;
		}

		cout << "Please choose from the following options, enter your choice by entering the corresponding number : "
			<< endl << "1. Shift" << endl << "2. Spin" << endl << "3. Quit" << endl << endl <<"Enter:";

		cin >> choice;
		if ((choice > 3) || (0 >= choice)) {
			cout << "Invalid!" << endl;
		}

		switch (choice) {
		case 1:
			char leftOrRight;
			cout << "Which direction do you want to shift? (l/r) ";
			cin >> leftOrRight;
			while ((leftOrRight != 'l') && (leftOrRight != 'r')) {	//do the capital letter check each time..
				cout << "Invalid entry! Please choose again. ";
				cin >> leftOrRight;
			}
			if (leftOrRight == 'l')
			{
				ts.shiftleft();
			}
			else
			{
				ts.shiftright();
			}
			break;
		case 2:
			ts.spin();
			break;
		case 3:
			cout << "\n" << "Thanks for playing, come back soon.\n" << endl;
		default:
			break;
		}

	} while ((choice != 3) && (ts.isSolved() != 1));

	return 0;
}

std::ostream& operator<< (std::ostream& os, const TopSpin& ts) {
	os << std::endl << " " << "|" << " ";
	for (auto i = 1; i <= ts._spinnerSize; i++)
	{
		os << ts.board.retrieve(i) << " ";
	}
	os << "|" << " ";
	for (unsigned int i = (ts._spinnerSize + 1); i <= ts.board.size(); i++)
	{
		os << ts.board.retrieve(i) << " ";
	}
	os << std::endl << std::endl;
	return os;
}



