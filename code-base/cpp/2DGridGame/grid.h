#include <iostream>
#include "position.h"

namespace GridGame {
	
	// Turning clockwise from right
	enum Directions {
		RIGHT, DOWN, LEFT, UP
	};
	constexpr auto EAST = RIGHT,
		SOUTH = DOWN, 
		WEST = LEFT, 
		NORTH = UP;

	struct BaseCell {

	};

	struct BasePositionedCell : BaseCell {
		Position pos = Position( -1 );
	};

	struct BaseNeighboroodCell : BasePositionedCell {
		BaseNeighboroodCell* neighbours[4]{ nullptr, nullptr, nullptr, nullptr };

		BaseNeighboroodCell* right() {	return neighbours[RIGHT];	}
		BaseNeighboroodCell* down() {	return neighbours[DOWN];	}
		BaseNeighboroodCell* left() {	return neighbours[LEFT];	}
		BaseNeighboroodCell* up() {		return neighbours[UP];		}

	};

	struct DynamicGrid {

	};
}