#pragma once

#include <iostream>
#include <cmath>

namespace GridGame {

	struct Vec2 {

		float x;
		float y;

		// =========== Constructor

		Vec2(const float x, const float y)
			: x(x), y(y) {}

		Vec2(const float xy)
			: Vec2(xy, xy) {}

		Vec2()
			: Vec2(0) { }

		// ============ Methods

		float length2() {
			return x * x + y * y;
		}

		float length() {
			return std::sqrt(length2());
		}

		Vec2& normalize() {
			auto l2 = length2();
			if (l2 > 0) {
				*this /= std::sqrt(l2);
			}
			return *this;
		}

		float distance2(const Vec2& pos) {
			auto dx = x - pos.x;
			auto dy = y - pos.y;
			return dx * dx + dy * dy;
		}

		float distance(const Vec2& pos) {
			return std::sqrt(distance2(pos));
		}

		float angleAgainst(const Vec2& pos) {

			Vec2 d = (pos - *this).normalize();
			
			float angle = std::acos(d.x) * 180 / M_PI;
			if (d.y < 0)	angle = 360 - angle;
			return angle;

		}

		// ================= Operators

		bool operator == (const Vec2& p) {
			return p.x == x && p.y == y;
		}

		bool operator != (const Vec2& p) {
			return !(*this == p);
		}

		Vec2& operator+=(const Vec2& p) {
			x += p.x;
			y += p.y;
			return *this;
		}

		Vec2& operator-=(const Vec2& p) {
			x -= p.x;
			y -= p.y;
			return *this;
		}

		Vec2 operator*=(const Vec2& p) {
			x *= p.x;
			y *= p.y;
			return *this;
		}

		/// Hadamard product
		Vec2 operator/=(const Vec2& p) {
			x /= p.x;
			y /= p.y;
			return *this;
		}

		Vec2 operator*=(const float s) {
			x *= s;
			y *= s;
			return *this;
		}


		Vec2 operator+(const Vec2& p) const {
			Vec2 res(*this);
			res += p;
			return res;
		}

		Vec2 operator-(const Vec2& p) const {
			Vec2 res(*this);
			res += p;
			return res;
		}

		/// Hadamard product
		Vec2 operator*(const Vec2& p) const {
			Vec2 res(*this);
			res *= p;
			return res;
		}

		Vec2 operator/(const Vec2& p) const {
			Vec2 res(*this);
			res /= p;
			return res;
		}

		Vec2 operator+(const float s) const {
			Vec2 res(s);
			res += *this;
			return res;
		}

		Vec2 operator-(const float s) const {
			Vec2 res(s);
			res -= *this;
			return res;
		}

		Vec2 operator*(const float s) const {
			Vec2 res(*this);
			res *= s;
			return res;
		}

		friend Vec2 operator+(const float s, const Vec2& p) {
			return p + s;
		}
		friend Vec2 operator-(const float s, const Vec2& p) {
			return p - s;
		}
		friend Vec2 operator*(const float s, const Vec2& p) {
			return p * s;
		}
		friend Vec2 operator/(const float s, const Vec2& p) {
			Vec2 res(s);
			res /= p;
			return res;
		}

		// =============== Input/Output

		friend std::istream& operator >> (std::istream& is, Vec2& pos) {
			is
				>> pos.x
				>> pos.y;
			return is;
		}

		friend std::ostream& operator << (std::ostream& os, const Vec2& pos) {
			os << "[ " << pos.x << " , " << pos.y << " ]";
			return os;
		}

	};

}