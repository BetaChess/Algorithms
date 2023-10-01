#pragma once

#include <ranges>

namespace wmv
{

namespace algorithms
{

// Sorts the elements using insertion sort
template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::less>
	requires std::sortable<I, Comp>
void insertion_sort(I first, S last)
{
	auto size = std::ranges::distance(first, last);

	for (size_t i = 1; i < size; ++i)
	{
		auto key = first[i];
		int j = i - 1;
		while (j >= 0 && first[j] > key)
		{
			first[j + 1] = first[j];
			--j;
		}
		first[j + 1] = key;
	}
};

template<std::ranges::random_access_range R, class Comp = std::ranges::less>
	requires std::sortable<std::ranges::iterator_t<R>, Comp>
void insertion_sort(R& r)
{
	insertion_sort(std::ranges::begin(r), std::ranges::end(r));
}

}

}
