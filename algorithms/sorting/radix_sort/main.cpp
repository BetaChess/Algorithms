#include "radix_sort.hpp"

#include <array>
#include <iostream>
#include <vector>


int main()
{
	std::vector<uint32_t> v = {7, 5, 2, 4, 6, 6, 1, 3, 7, 3521, 35213, 543543, 777, 12345555, 122, 1566, 67222, 1467232};
	std::array<int, 9> a = {7, 5, 2, 4, 6, 6, 1, 3, 7};
	std::vector<uint32_t> out_v;
	out_v.resize(v.size());

	wmv::algorithms::radix_sort(v);
//	wmv::algorithms::heap_sort(v);
//	wmv::algorithms::heap_sort(a);

	std::cout << std::ranges::is_sorted(v) << '\n';

	for (auto i: v)
		std::cout << i << " ";
	std::cout << std::endl;
	for (auto i: a)
		std::cout << i << " ";

	return 0;
}