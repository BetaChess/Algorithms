#pragma once

#include "../../util/random.hpp"

#include <vector>


namespace wmv::algorithms
{

std::vector<int>::iterator partition(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	auto pivot = *last;
	int64_t offset = -1;

	for (auto j = first; j < last; j++)
	{
		if (*j <= pivot)
		{
			offset++;
			std::swap(*(first + offset), *j);
		}
	}

	std::swap(*(first + 1 + offset), *last);

	return first + 1 + offset;
}

void quick_sort(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	if (first < last)
	{
		auto pivot_index = partition(first, last);
		quick_sort(first, pivot_index - 1);
		quick_sort(pivot_index + 1, last);
	}
}

void quick_sort(std::vector<int> &v)
{
	if (v.size() < 2) [[unlikely]]
		return;

	quick_sort(v.begin(), v.end() - 1);
}

std::vector<int>::iterator
randomized_partition(std::vector<int>::iterator first, std::vector<int>::iterator last, uint32_t &seed)
{
	auto i = first + pcg_hash(seed) % std::distance(first, last);
	std::swap(*i, *last);
	return partition(first, last);
}

void randomized_quick_sort(std::vector<int>::iterator first, std::vector<int>::iterator last, uint32_t seed = 0x52616e64)
{
	if (first < last)
	{
		auto pivot_index = randomized_partition(first, last, seed);
		randomized_quick_sort(first, pivot_index - 1, seed);
		randomized_quick_sort(pivot_index + 1, last, seed);
	}
}

void randomized_quick_sort(std::vector<int> &v, uint32_t seed = 0x52616e64)
{
	if (v.size() < 2) [[unlikely]]
		return;

	randomized_quick_sort(v.begin(), v.end() - 1, seed);
}

}// namespace wmv::algorithms