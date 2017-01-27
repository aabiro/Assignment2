#include "TopSpin.h"
#include "CDLL.h"
#include <stdlib.h>

TopSpin::TopSpin() :_size(20), _spinnerSize(4) {
	for (unsigned int i = _size; i >= 1; i--)
	{
		board.addHead(i);
	}
}


TopSpin::TopSpin(int x, int y) : _size(x), _spinnerSize(y) {
	for (unsigned int i = _size; i >= 1; i--)
	{
		board.addHead(i);
	}
}

void TopSpin::spin() {
	auto * container = new int[_spinnerSize];
	CircularDoublyLinkedList<int>::Iterator it1 = board.begin();
	for (auto i = 0; i < _spinnerSize; i++) {
		container[i] = it1.getValue();	//fill container with values
		++it1;
	}
	for (auto i = 0; i<_spinnerSize; i++) {
		--it1;							//point back to m_head
	}
	auto * reverseContainer = new int[_spinnerSize];
	for (auto i = 0, j = (_spinnerSize - 1); i < _spinnerSize; i++, j--) {
		reverseContainer[j] = container[i];		//reverse array
	}
	for (auto i = 0; i<_spinnerSize; i++) {
		it1.setValue(reverseContainer[i]);		//set reverse values
		++it1;
	}
	delete[] container;
	delete[] reverseContainer;
}

void TopSpin::randomMove(unsigned int x) {
	unsigned int numMoves;
	for (unsigned int k = 0; k < x; k++) {
		numMoves = 1 + (rand() % 19);
		for (auto i = 0; i < 1; i++) {
			board.shiftLeftParameter(numMoves);
			spin();
		}
	}
}


void TopSpin::shiftleft() {
	board.shiftLeft();
}

void TopSpin::shiftright() {
	board.shiftRight();
}

bool TopSpin::isSolved() {
	CircularDoublyLinkedList<int>::Iterator it1 = board.begin();
	auto count = 1;
	while (it1.getValue() != 1)
	{
		++it1;
		count++;
	}
	for (auto i = 1; i < _size; i++)
	{
		if (i != it1.getValue())
			return false;
		++it1;
	}
	for (auto i = 0; i < count; i++)
	{
		--it1;
	}
	for (auto i = 0; i < _size; i++) {
		--it1;							//point back to m_head
	}
	return true;
}
