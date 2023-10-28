#include "heap.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> heap = {0, 2, 6, 9, 3, 4, 1, 8, 5, 7};
	wmv::algorithms::make_heap(heap, std::ranges::less{});
	std::cout << wmv::algorithms::is_heap(heap, std::ranges::less{}) << std::endl;
	std::cout << std::ranges::is_heap(heap, std::ranges::less{}) << std::endl;

	for (int i: heap)
		std::cout << i << " ";

	return 0;
}