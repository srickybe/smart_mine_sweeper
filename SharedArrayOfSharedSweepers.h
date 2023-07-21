#ifndef SHARED_ARRAY_OF_SHARED_SWEEPERS_H
#define SHARED_ARRAY_OF_SHARED_SWEEPERS_H

#include "SmartMineSweeper.h"
#include <memory>
#include <vector>

namespace smrtsw {
	
	typedef std::shared_ptr<std::vector<SharedPtrSmartMineSweeper>> SharedArrayOfSharedSweepers;
}

#endif // SHARED_ARRAY_OF_SHARED_SWEEPERS_H