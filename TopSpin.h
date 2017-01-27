#pragma once
#include "CDLL.h"
#include <iostream>

class TopSpinADT {
public:

	// shifts the pieces 1 to the left   
	virtual void shiftleft() = 0;
	//shifts the pieces 1 to the right   
	virtual void shiftright() = 0;
	//reverses the pieces in the spin mechanism   
	virtual void spin() = 0;
	//checks to see if the puzzle is solved 
	virtual bool isSolved() = 0;
	virtual ~TopSpinADT() {}


};

class TopSpin : public TopSpinADT
{
private:

	int _size;
	int _spinnerSize;

public:

	TopSpin();
	TopSpin(int x, int y);
	~TopSpin() {}
	CircularDoublyLinkedList<int> board;
	CircularDoublyLinkedList<int>::Iterator iterator;
	void randomMove(unsigned int x);
	void shiftleft() override;
	void shiftright() override;
	void spin() override;
	bool isSolved() override;


	friend std::ostream& operator<< (std::ostream& os, const TopSpin& ts);		//declare ostream overload

};

