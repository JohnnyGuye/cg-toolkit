#include <iostream>

namespace GridGame {

	struct Position {

		int x;
		int y;

		// =========== Constructor

		Position(const int x, const int y)
		: x(x), y(y) {}

		Position(const int xy)
		: Position(xy, xy) {}

		Position() 
		: Position(0) { }

		// ============ Methods

		unsigned int distance(const Position& pos) {
			auto dx = x - pos.x;
			auto dy = y - pos.y;
			return std::abs(dx) + std::abs(dy);
		}

		// ================= Operators

		bool operator == (const Position& p) {
			return p.x == x && p.y == y;
		}

		bool operator != (const Position& p) {
			return !(*this == p);
		}

		Position& operator+=(const Position& p) {
			x += p.x;
			y += p.y;
			return *this;
		}

		Position& operator-=(const Position& p) {
			x -= p.x;
			y -= p.y;
			return *this;
		}

		Position operator*=(const int s) {
			x *= s;
			y *= s;
			return *this;
		}

		Position operator+(const Position& p) const {
			Position res(*this);
			res += p;
			return res;
		}

		Position operator-(const Position& p) const {
			Position res(*this);
			res += p;
			return res;
		}
		Position operator+(const int s) const {
			Position res(s);
			res += *this;
			return res;
		}

		Position operator-(const int s) const {
			Position res(s);
			res -= *this;
			return res;
		}

		Position operator*(const int s) const {
			Position res(*this);
			res *= s;
			return res;
		}

		friend Position operator+(const int s, const Position& p) {
			return p + s;
		}
		friend Position operator-(const int s, const Position& p) {
			return p - s;
		}
		friend Position operator*(const int s, const Position& p) {
			return p * s;
		}

		// =============== Input/Output

		friend std::istream& operator >> (std::istream& is, Position& pos) {
			is
				>> pos.x
				>> pos.y;
			return is;
		}

		friend std::ostream& operator << (std::ostream& os, const Position& pos) {
			os << "[ " << pos.x << " , " << pos.y << " ]";
			return os;
		}

	};

}