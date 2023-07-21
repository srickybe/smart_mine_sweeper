#ifndef RAND_H
#define RAND_H

#include <cstdlib>
#include <ctime>
#include <memory>
#include "IllegalArgumentException.h"

namespace util {

	template <class Real>
	class Rand {
	};

	/////////////////////////////////////////////////////////////////

	template <>
	class Rand<double> {

	private:
		static std::shared_ptr<Rand> instance;
		unsigned seed;

		Rand() {
			seed = 0;
			std::srand(seed);
		}
		
	public: 
		static Rand & getInstance() {
			if (instance != 0) {
				return *instance;
			} else {
				instance = std::shared_ptr<Rand>(new Rand());
				return *instance;
			}
		}
		
		unsigned getSeed() const {
			return seed;
		}
		
		void setSeed(unsigned seed) {
			this->seed = seed;
			
			if (this->seed < 0) {
				std::srand(std::time(0));
			} else {
				std::srand(this->seed);
			}
		}
		
		double next() const {
			return (double)(std::rand() - 1) / (double)RAND_MAX;
		}
		
		double next(double min, double max) const {
			if (max > min) {
				return min + next() * (max - min);
			} else {
				std::string message = "min";
				message.append(std::to_string(min));
				message.append("\tmax = ");
				message.append(std::to_string(max));
				throw IllegalArgumentException(message);
			}
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////

	template <>
	class Rand<float> {

	private:
		static std::shared_ptr<Rand> instance;
		unsigned seed;

		Rand() {
			seed = 0;
			std::srand(seed);
		}
		
	public: 
		static Rand & getInstance() {
			if (instance != 0) {
				return *instance;
			} else {
				instance = std::shared_ptr<Rand>(new Rand());
				return *instance;
			}
		}
		
		unsigned getSeed() const {
			return seed;
		}
		
		void setSeed(unsigned seed) {
			this->seed = seed;
			
			if (this->seed < 0) {
				std::srand(std::time(0));
			} else {
				std::srand(this->seed);
			}
		}
		
		float next() const {
			return (float)(std::rand() - 1) / (float)RAND_MAX;
		}
		
		float next(float min, float max) const {
			if (max > min) {
				return min + next() * (max - min);
			} else {
				std::string message = "min";
				message.append(std::to_string(min));
				message.append("\tmax = ");
				message.append(std::to_string(max));
				throw IllegalArgumentException(message);
			}
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////

	template <>
	class Rand<int> {
	private:
		static std::shared_ptr<Rand> instance;
		unsigned seed;

		Rand() {
			seed = 0;
			std::srand(seed);
		}
		
	public: 
		static Rand & getInstance() {
			if (instance != 0) {
				return *instance;
			} else {
				instance = std::shared_ptr<Rand>(new Rand());
				return *instance;
			}
		}
		
		unsigned getSeed() const {
			return seed;
		}
		
		void setSeed(unsigned seed) {
			this->seed = seed;
			
			if (this->seed < 0) {
				std::srand(std::time(0));
			} else {
				std::srand(this->seed);
			}
		}
		
		int next() const {
			return std::rand();
		}
		
		int next(int n) const {
			return std::rand() % n;
		}
		
		int next(int min, int max) const {
			if (max > min) {
				return min + std::rand() % (max - min);
			} else {
				std::string message = "min";
				message.append(std::to_string(min));
				message.append("\tmax = ");
				message.append(std::to_string(max));
				throw IllegalArgumentException(message);
			}
		}
	};
	
}

#endif // RAND_H