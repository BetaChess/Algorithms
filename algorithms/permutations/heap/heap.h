#pragma once

#include "../../container_concepts.h"

#include <cassert>
#include <limits>
#include <iterator>

using size_t = std::size_t;


namespace wmv::algorithms
{

// Returns the index of the parent of a heap object with index i
constexpr size_t heap_parent_index(size_t i)
{
	return (i - 1) / 2;
}

// Returns the index of the jth child of a heap object with index i
size_t heap_child_index(size_t i, size_t j)
{
	assert(j < 2);
	return 2 * i + j + 1;
}

// Returns true if the ith element has a child jth child
template<std::random_access_iterator I, std::sentinel_for<I> S>
bool heap_child_exists(const I it, S last, size_t i, size_t j)
{
	assert(j < 2);
	return heap_child_index(i, j) < std::ranges::distance(it, last);
}
// Returns true if the ith element has a child jth child
template<std::ranges::random_access_range R>
bool heap_child_exists(const R& range, size_t i, size_t j)
{
	return heap_child_exists(std::ranges::begin(range), std::ranges::end(range), i, j);
}

// Returns true if the range is a heap
template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::greater>
bool is_heap(const I it, S end, Comp comp = Comp{})
{
	auto size = std::ranges::distance(it, end);
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < 2; ++j)
		{
			if (heap_child_exists(it, end, i, j) && comp(it[heap_child_index(i, j)], it[i]))
			{
				return false;
			}
		}
	}
	return true;
}
// Returns true if the range is a heap
template<std::ranges::random_access_range R, class Comp = std::ranges::greater>
bool is_heap(const R& range, Comp comp = Comp{})
{
	return is_heap(std::ranges::begin(range), std::ranges::end(range), comp);
}

// Places the ith element at its correct location, assuming the sub heaps are actually heaps.
template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::greater>
	requires std::sortable<I, Comp>
void heapify(I it, S end, size_t i, Comp comp = Comp{})
{
	// Find the max of itself and its children
	size_t max = i;
	for (size_t j = 0; j < 2; ++j)
	{
		if (heap_child_exists<I, S>(it, end, i, j) && comp(it[heap_child_index(i, j)], it[max]))
		{
			max = heap_child_index(i, j);
		}
	}

	if (max != i)
	{
		std::ranges::iter_swap(it + i, it + max);
		heapify(it, end, max);
	}
}
// Places the ith element at its correct location, assuming the sub heaps are actually heaps.
template<std::ranges::random_access_range R, class Comp = std::ranges::greater>
	requires std::sortable<std::ranges::iterator_t<R>, Comp>
void heapify(R& range, size_t i, Comp comp = Comp{})
{
	heapify(std::ranges::begin(range), std::ranges::end(range), i, comp);
}

// Pops the head of the heap, reforms heap structure, then returns the value of the original head.
template<std::ranges::random_access_range R, class Comp = std::ranges::greater>
	requires std::sortable<std::ranges::iterator_t<R>, Comp> && is_popable<R>
auto pop_heap(R& range, Comp comp = Comp{})
{
    auto head = range[0];
	range[0] = range[std::ranges::size(range) - 1];
	range.pop_back();
	heapify(range, 0, comp);
	return head;
}

// Changes the key of the ith element, assuming the heap is actually a heap.
template<std::random_access_iterator I, class Comp = std::ranges::greater>
	requires std::sortable<I, Comp>
void heap_change_key(I it, size_t i, auto key, Comp comp = Comp{})
{
	assert(!comp(it[i], key));

	it[i] = key;
	while (i > 0 && comp(it[i], it[heap_parent_index(i)]))
	{
		std::swap(it[i], it[heap_parent_index(i)]);
		i = heap_parent_index(i);
	}
}
// Changes the key of the ith element, assuming the heap is actually a heap.
template<std::ranges::random_access_range R, class Comp = std::ranges::greater>
	requires std::sortable<std::ranges::iterator_t<R>, Comp>
void heap_change_key(R& range, size_t i, auto key, Comp comp = Comp{})
{
	heap_change_key(std::ranges::begin(range), i, key, comp);
}

// Inserts a key into the heap, assuming the heap is actually a heap.
template<std::ranges::random_access_range R, typename U, class Comp = std::ranges::greater>
	requires std::sortable<std::ranges::iterator_t<R>, Comp> && is_pushable<R, U>
void heap_insert(R& range, U key, Comp comp = Comp{}, U keyDefault = std::numeric_limits<int>::min())
{
	range.push_back(keyDefault);
	// Get size
	size_t size = std::ranges::size(range);
	heap_change_key(range, size - 1, key, comp);
}

// Builds a heap in a range
template<std::random_access_iterator I, std::sentinel_for<I> S, class Comp = std::ranges::greater>
	requires std::sortable<I, Comp>
void make_heap(I it, S end, Comp comp = Comp{})
{
	size_t size = std::ranges::distance(it, end);
	for (size_t i = size / 2 - 1; i != (size_t)-1; i--)
	{
		heapify<I, S, Comp>(it, end, i, comp);
	}
}
// Builds a heap in a range
template<std::ranges::random_access_range R, class Comp = std::ranges::greater>
	requires std::sortable<std::ranges::iterator_t<R>, Comp>
void make_heap(R& range, Comp comp = Comp{})
{
	make_heap(std::ranges::begin(range), std::ranges::end(range), comp);
}

}



