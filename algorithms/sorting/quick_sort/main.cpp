
#include <iostream>
#include <vector>

#include "quick_sort.hpp"


int main()
{
	// Random vector of integers
	std::vector<int> v{10, 1, 5, 2, 4, 3, 6, 7, 8, 9};
	std::vector<int> v2{10, 1, 5, 2, 4, 3, 6, 7, 8, 9};

	// Sort the vector
	wmv::algorithms::quick_sort(v.begin(), v.end() - 1);
	wmv::algorithms::randomized_quick_sort(v2.begin(), v2.end() - 1);

	for (auto i: v)
	{
		std::cout << i << " ";
	}
	for (auto i: v2)
	{
		std::cout << i << " ";
	}

	return 0;
}
