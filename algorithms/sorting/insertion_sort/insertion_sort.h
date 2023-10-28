#pragma once

#include <ranges>
#include <cstdint>


namespace wmv::algorithms
{

// Sorts the elements using insertion sort
template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::less>
	requires std::sortable<I, Comp>
void insertion_sort(I first, S last, Comp comp = Comp{})
{
	auto size = std::ranges::distance(first, last);

	for (int64_t i = 1; i < size; ++i)
	{
		auto key = first[i];
		int64_t j = i - 1;
		while (j >= 0 && comp(key, first[j]))
		{
			first[j + 1] = first[j];
			--j;
		}
		first[j + 1] = key;
	}
};

template<std::ranges::random_access_range R, class Comp = std::ranges::less>
	requires std::sortable<std::ranges::iterator_t<R>, Comp>
void insertion_sort(R &r, Comp comp = Comp{})
{
	if (std::ranges::size(r) < 2)
		return;

	insertion_sort(std::ranges::begin(r), std::ranges::end(r), comp);
}

} // namespace wmv::algorithms


