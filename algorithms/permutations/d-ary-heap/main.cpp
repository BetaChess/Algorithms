#include "daryheap.h"

#include <array>
#include <iostream>
#include <vector>


int main()
{
	std::vector<int> heap = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	wmv::algorithms::make_dheap<3>(heap);
	wmv::algorithms::dheap_insert<5>(heap, 13);

	std::cout << "Is heap: " << wmv::algorithms::is_dheap<2>(heap) << '\n';
	std::cout << "Is heap: " << wmv::algorithms::is_dheap<3>(heap) << '\n';
	std::cout << "Is heap: " << wmv::algorithms::is_dheap<4>(heap) << '\n';
	std::cout << "Is heap: " << wmv::algorithms::is_dheap<5>(heap) << '\n';
	std::cout << "Is heap: " << wmv::algorithms::is_dheap<11>(heap) << '\n';

	return 0;
}