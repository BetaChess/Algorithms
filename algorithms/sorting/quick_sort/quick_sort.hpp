#pragma once

#include "../../util/random.hpp"

#include <vector>


namespace wmv::algorithms
{

template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::less>
	requires std::sortable<I, Comp>
I partition(I first, S last, Comp comp = Comp{})
{
	auto pivot = *last;
	int64_t offset = -1;

	for (auto j = first; j < last; j++)
	{
		if (!comp(pivot, *j))
		{
			offset++;
			std::swap(*(first + offset), *j);
		}
	}

	std::swap(*(first + 1 + offset), *last);

	return first + 1 + offset;
}

template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::less>
	requires std::sortable<I, Comp>
void quick_sort(I first, S last, Comp comp = Comp{})
{
	if (first < last)
	{
		auto pivot_index = wmv::algorithms::partition(first, last, comp);
		quick_sort(first, pivot_index - 1, comp);
		quick_sort(pivot_index + 1, last, comp);
	}
}

template<std::ranges::random_access_range R, class Comp = std::ranges::less>
	requires std::sortable<std::ranges::iterator_t<R>, Comp>
void quick_sort(R &r, Comp comp = Comp{})
{
	if (std::ranges::size(r) < 2)
		return;

	quick_sort(std::ranges::begin(r), std::ranges::end(r) - 1, comp);
}

template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::less>
	requires std::sortable<I, Comp>
I randomized_partition(I first, S last, uint32_t &seed, Comp comp = Comp{})
{
	auto i = first + pcg_hash(seed) % std::distance(first, last);
	std::swap(*i, *last);
	return wmv::algorithms::partition(first, last, comp);
}

template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::less>
	requires std::sortable<I, Comp>
void randomized_quick_sort(I first, S last, uint32_t seed = 0x52616e64, Comp comp = Comp{})
{
	if (first < last)
	{
		auto pivot_index = wmv::algorithms::randomized_partition(first, last, seed, comp);
		randomized_quick_sort(first, pivot_index - 1, seed, comp);
		randomized_quick_sort(pivot_index + 1, last, seed, comp);
	}
}

template<std::ranges::random_access_range R, class Comp = std::ranges::less>
	requires std::sortable<std::ranges::iterator_t<R>, Comp>
void randomized_quick_sort(R &r, uint32_t seed = 0x52616e64, Comp comp = Comp{})
{
	if (std::ranges::size(r) < 2)
		return;

	randomized_quick_sort(std::ranges::begin(r), std::ranges::end(r) - 1, seed, comp);
}

}// namespace wmv::algorithms