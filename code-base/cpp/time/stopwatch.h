#include <chrono>

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