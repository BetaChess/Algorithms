#include "insertion_sort.h"

#include <iostream>
#include <vector>
#include <array>


int main()
{
	std::vector<int> v = { 7, 5, 2, 4, 6, 6, 1, 3, 7 };
	std::array<int, 9> a = { 7, 5, 2, 4, 6, 6, 1, 3, 7 };

	wmv::algorithms::insertion_sort(v);
	wmv::algorithms::insertion_sort(a);

	for (auto i : v)
		std::cout << i << " ";
	std::cout << std::endl;
	for (auto i : a)
		std::cout << i << " ";

	return 0;
}