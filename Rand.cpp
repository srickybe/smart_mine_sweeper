#include "Rand.h"

namespace util {
	
	std::shared_ptr<Rand<double>> Rand<double>::instance = nullptr;
	std::shared_ptr<Rand<float>> Rand<float>::instance = nullptr;
	std::shared_ptr<Rand<int>> Rand<int>::instance = nullptr;
}

