#ifndef SHARED_ARRAY_OF_SHARED_MINES_H
#define SHARED_ARRAY_OF_SHARED_MINES_H

#include "Mine.h"
#include <memory>
#include <vector>

namespace smrtsw {
	
	typedef std::shared_ptr<std::vector<SharedPtrMine>> SharedArrayOfSharedMines;
}

#endif // SHARED_ARRAY_OF_SHARED_MINES_H