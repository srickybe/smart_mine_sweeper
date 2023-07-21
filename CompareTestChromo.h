#ifndef COMPARE_TEST_CHROMO_H
#define COMPARE_TEST_CHROMO_H

namespace ai {
	
	class TestChromo;
	
	struct CompareTestChromo {
		CompareTestChromo();
		bool operator() (const TestChromo & lhs, const TestChromo & rhs) const;
	};
}

#endif // COMPARE_TEST_CHROMO_H