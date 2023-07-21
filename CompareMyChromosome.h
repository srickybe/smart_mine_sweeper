#ifndef COMPARE_MY_CHROMOSOME_H
#define COMPARE_MY_CHROMOSOME_H

namespace ai {

	class MyChromosome;
	
	class CompareMyChromosome {
	public:
		CompareMyChromosome();

		bool operator()(MyChromosome const & lhs, MyChromosome const & rhs) const;
	};
}

#endif // COMPARE_MY_CHROMOSOME_H