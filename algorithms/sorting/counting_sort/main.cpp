#include "counting_sort.hpp"

#include <array>
#include <iostream>
#include <vector>
#include <cstdint>


int main()
{
	std::vector<uint32_t> v = {7, 5, 2, 4, 6, 6, 1, 3, 7};
	std::array<int, 9> a = {7, 5, 2, 4, 6, 6, 1, 3, 7};
	std::array<int, 9> b;

	std::vector<uint32_t> out_v;
	out_v.resize(v.size());
	wmv::algorithms::counting_sort(v, out_v, 8u);
	wmv::algorithms::counting_sort(a, b, 8u);
//	wmv::algorithms::heap_sort(v);
//	wmv::algorithms::heap_sort(a);

	for (auto i: out_v)
		std::cout << i << " ";
	std::cout << std::endl;
	for (auto i: b)
		std::cout << i << " ";

	return 0;
}