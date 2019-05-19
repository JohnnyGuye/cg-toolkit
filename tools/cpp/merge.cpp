#include <iostream>
#include <chrono>


//============================================================
// Imported from the file: 2DGridGame/position.h
//============================================================

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

//============================================================
// Imported from the file: time/stopwatch.h
//============================================================

#define CHRONO std::chrono
#define HR_CLOCK CHRONO::high_resolution_clock

namespace Time {
	
	class Stopwatch {
	protected:
		HR_CLOCK::time_point startTime;
	
	public:

		Stopwatch( ) {
			start();
		}

		inline void start( ) {
			startTime = HR_CLOCK::now();
		}

		template<typename T>
		inline int ellapsed( ) const {
			return CHRONO::duration_cast<T>( HR_CLOCK::now() - startTime).count();
		}

		inline int milliseconds() const {
			return ellapsed<CHRONO::milliseconds>();
		}
		inline int microseconds() const {
			return ellapsed<CHRONO::microseconds>();
		}
		inline int seconds() const {
			return ellapsed<CHRONO::seconds>();
		}

		friend std::ostream& operator<<(std::ostream& os, const Stopwatch& sw) {
			auto time = sw.microseconds();
			auto micro = time % 1000;
			auto milli = (time = time / 1000) % 1000;
			auto sec = (time = time / 1000);

			os << sec << "s " << milli << "ms " << micro << "us";
			return os;
		}
	};

}

#undef CHRONO
#undef HR_CLOCK

//============================================================
// Imported from the file: main.cpp
//============================================================

int main() {

	std::cout << "It works like a charm !" << std::endl;
	return 0;

}