// TurtleGraphics.cpp
// Definitions of member functions for class TurtleGraphics.
//
// Author: Kelvin Tay
// Version: 1.0
#include <iostream>
#include <array>
#include "TurtleGraphics.h"
using namespace std;

// Constructor
TurtleGraphics::TurtleGraphics() {

	// Initialize the whole floor to all false values.
	for (auto& row : m_Floor) {
		for (auto& col : row) {
			col = false;
		}
	}

	penPosition = STARTING_PEN_POSITION;
	direction = STARTING_DIRECTION;
	currentRow = STARTING_ROW;
	currentColumn = STARTING_COL;
}

// Processes commands in the given "commands" array argument.
void TurtleGraphics::processTurtleMoves(
	                 const array<int, TurtleGraphics::ARRAY_SIZE>& commands) {

	int rowMoveCount = 0; // The number of rows that turtle moves.
	                            // Allows for bounds checking.

	int colMoveCount = 0; // The number of columns that turtle moves.
	                            // Allows for bounds checking.

	int i = 0; // The current index in command array.

	while (commands[i] != static_cast<unsigned short>(Commands::END_OF_DATA)) {

		switch (commands[i]) {
		    case static_cast<unsigned short>(Commands::PEN_UP):
				penPosition = false;
				break;
			case static_cast<unsigned short>(Commands::PEN_DWN):
				penPosition = true;
				break;
			case static_cast<unsigned short>(Commands::TURN_RIGHT):

				switch (direction) {
				    case Directions::NORTH:
						direction = Directions::EAST;
						break;
					case Directions::EAST:
						direction = Directions::SOUTH;
						break;
					case Directions::SOUTH:
						direction = Directions::WEST;
						break;
					case Directions::WEST:
						direction = Directions::NORTH;
						break;
					default:
						cerr << "Error in TURN_RIGHT inner switch statement in "
							<< "processTurtleMoves method." << endl;
						break;
				}
				break;

			case static_cast<unsigned short>(Commands::TURN_LEFT):

				switch (direction) {
					case Directions::NORTH:
						direction = Directions::WEST;
						break;
					case Directions::EAST:
						direction = Directions::NORTH;
						break;
					case Directions::SOUTH:
						direction = Directions::EAST;
						break;
					case Directions::WEST:
						direction = Directions::SOUTH;
						break;
					default:
						cerr << "Error in TURN_LEFT inner switch statement in "
							<< "processTurtleMoves method." << endl;
						break;
				}
				break;
			case static_cast<unsigned short>(Commands::MOVE):

				switch (direction) {
				    case Directions::NORTH:

						// Check if the move is out of bounds.
						// (if it goes past the first row).
						if (currentRow - commands[i + 1] < 0) {
							rowMoveCount = currentRow;
						}
						else {
							rowMoveCount = commands[i + 1];
						}

						// Check if pen is down.
						if (penPosition) {

							for (int count = 1; count <= rowMoveCount; ++count) {
								m_Floor[currentRow][currentColumn] = true;
								currentRow--;
							}

						}
						else {
							currentRow -= rowMoveCount;
						}
						break;
					case Directions::SOUTH:

						// Check if the move is out of bounds.
						// (if it goes past the last row).
						if (currentRow + commands[i + 1] >= NROWS) {
							rowMoveCount = (NROWS - 1) - currentRow;
						}
						else {
							rowMoveCount = commands[i + 1];
						}

						if (penPosition) {

							for (int count = 1; count <= rowMoveCount; ++count) {
								m_Floor[currentRow][currentColumn] = true;
								currentRow++;
							}
						}
						else {
							currentRow += rowMoveCount;
						}
						break;
					case Directions::EAST:

						// Check if the move is out of bounds.
						// (if it goes past the last column).
						if (currentColumn + commands[i + 1] >= NCOLS) {
							colMoveCount = (NCOLS - 1) - currentColumn;
						}
						else {
							colMoveCount = commands[i + 1];
						}

						if (penPosition) {

							for (int count = 1; count <= colMoveCount; ++count) {
								m_Floor[currentRow][currentColumn] = true;
								currentColumn++;
							}
						}
						else {
							currentColumn += colMoveCount;
						}
						break;
					case Directions::WEST:

						// Check if the move is out of bounds.
						// (if it goes past the first row).
						if (currentColumn - commands[i + 1] < 0) {
							colMoveCount = currentColumn;
						}
						else {
							colMoveCount = commands[i + 1];
						}

						if (penPosition) {

							for (int count = 1; count <= colMoveCount; ++count) {
								m_Floor[currentRow][currentColumn] = true;
								currentColumn--;
							}
						}
						else {
							currentColumn -= colMoveCount;
						}
						break;
					default:
						cerr << "Error in MOVE inner switch statement in "
							<< "processTurtlesMoves method." << endl;
						break;
				}

				++i; // Allows us to go to the command after the value indicating 
				     // the number of moves.

				break;
			case static_cast<unsigned short>(Commands::DISPLAY):
				displayFloor();
				break;
			default:
				cerr << "Error in outer switch statement of processTurtleMoves "
					<< "method." << endl;
				break;
		}

		++i;
	}

}

// Private method which displays the floor on the screen.
void TurtleGraphics::displayFloor() const {

	for (const auto& row : m_Floor) {
		for (const auto& col : row) {
			if (col) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}