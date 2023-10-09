#include <iostream>

#include "merge_sort.hpp"


int main()
{
	// Random vector of integers
	std::vector<int> v{ 10, 1, 5, 2, 4, 3, 6, 7, 8, 9 };

	// Sort the vector
	//std::cout << "inversions: " << wmv::algorithms::merge_sort(v.begin(), (v.end() - 1)) << '\n';
	for (auto i : v)
	{
		std::cout << i << " ";
	}

	return 0;
}