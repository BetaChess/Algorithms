#pragma once

#include "../../permutations/heap/heap.h"

#include <algorithm>

namespace wmv
{

namespace algorithms
{


template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::less>
	requires std::sortable<I, Comp>
void heap_sort(I first, S last, Comp comp = Comp{})
{
	auto size = std::ranges::distance(first, last);

	wmv::algorithms::make_heap(first, last, comp);

	for (size_t i = size - 1; i > 0; --i)
	{
		std::swap(first[0], first[i]);
		wmv::algorithms::heapify(first, first + i, 0, comp);
	}

	std::ranges::reverse(first, last);
};

template<std::ranges::random_access_range R, class Comp = std::ranges::less>
	requires std::sortable<std::ranges::iterator_t<R>, Comp>
void heap_sort(R& r, Comp comp = Comp{})
{
	heap_sort(std::ranges::begin(r), std::ranges::end(r), comp);
}

}

}