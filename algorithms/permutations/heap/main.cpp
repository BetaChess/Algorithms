#include "heap.h"

#include <iostream>
#include <vector>

int main()
{
	std::vector<int> heap = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	wmv::algorithms::make_heap(heap);
	wmv::algorithms::heap_insert(heap, 13);
	std::cout << wmv::algorithms::is_heap(heap) << std::endl;
	std::cout << wmv::algorithms::pop_heap(heap) << std::endl;

	return 0;
}