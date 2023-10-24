#pragma once

#include "container_concepts.h"

#include <cassert>
#include <functional>
#include <limits>
#include <vector>



namespace wmv::algorithms
{

// Returns the index of the parent of v[i]
template<size_t d>
size_t parent_index(const std::vector<int> &v, size_t i)
{
	assert(i > 0);
	return (i - 1) / d;
}

// Returns the parent of v[i]
template<size_t d>
int &parent(std::vector<int> &v, size_t i)
{
	return v[parent_index<d>(v, i)];
}

// Returns the parent of v[i]
template<size_t d>
const int &parent(const std::vector<int> &v, size_t i)
{
	return v[parent_index<d>(v, i)];
}


// Returns the index of the jth child of v[i]
template<size_t d>
size_t child_index(const std::vector<int> &v, size_t i, size_t j)
{
	assert(j < d);
	return d * i + j + 1;
}

// Returns the jth child of v[i]
template<size_t d>
int &child(std::vector<int> &v, size_t i, size_t j)
{
	assert(j < d);
	return v[child_index<d>(v, i, j)];
}

// Returns the jth child of v[i]
template<size_t d>
const int &child(const std::vector<int> &v, size_t i, size_t j)
{
	assert(j < d);
	return v[child_index<d>(v, i, j)];
}

// Returns true if the jth child of v[i] exists
template<size_t d>
bool child_exists(const std::vector<int> &v, size_t i, size_t j)
{
	return child_index<d>(v, i, j) < v.size();
}

// Returns true if the vector is a d-ary heap
template<size_t d, class Compare = std::greater<>>
bool is_dheap(const std::vector<int> &v, Compare comp = std::greater<>{})
{
	for (size_t i = 1; i < v.size(); ++i)
	{
		int p_value = parent<d>(v, i);
		int c_value = v[i];
		if (comp(c_value, p_value))
		{
			return false;
		}
	}
	return true;
}

// Places the ith element at it's correct location, assuming the sub heaps are actually heaps.
template<size_t d, class Compare = std::greater<>>
void dheapify(std::vector<int> &v, size_t i, Compare comp = std::greater<>{})
{
	// Find the max of itself and its children
	int max = i;
	for (size_t j = 0; j < d; j++)
	{
		if (child_exists<d>(v, i, j) && comp(child<d>(v, i, j), v[max]))
		{
			max = child_index<d>(v, i, j);
		}
	}

	if (max != i)
	{
		std::swap(v[i], v[max]);
		dheapify<d>(v, max, comp);
	}
}

// Pops the head of the d-ary heap, reforms heap structure, then returns the value of the original head.
template<size_t d, class Compare = std::greater<>>
int pop_dheap(std::vector<int> &v, Compare comp = std::greater<>{})
{
	assert(v.size() > 0);
	int retValue = v[0];
	v[0] = v.back();
	v.pop_back();
	dheapify<d>(v, 0, comp);
	return retValue;
}

// Changes the key of the ith element to key (comp(v[i], key) must be false)
template<size_t d, class Compare = std::greater<>>
void dheap_change_key(std::vector<int> &v, size_t i, int key, Compare comp = std::greater<>{})
{
	assert(!comp(v[i], key));

	v[i] = key;
	while (i > 0 && comp(v[i], parent<d>(v, i)))
	{
		std::swap(v[i], parent<d>(v, i));
		i = parent_index<d>(v, i);
	}
}

// Inserts are key into the d-ary heap
template<
		size_t d,
		typename T,
		typename U,
		U keyDefault = std::numeric_limits<U>::min(),
		class Compare = std::greater<>>
	requires is_pushable<T, U>
void dheap_insert(T v, U key, Compare comp = std::greater<>{})
{
	v.push_back(keyDefault);
	dheap_change_key<d>(v, v.size() - 1, key, comp);
}

// Builds a d-ary heap in a range
template<size_t d, class Compare = std::greater<>>
void make_dheap(std::vector<int> &v, Compare comp = std::greater<>{})
{
	for (size_t i = v.size() / d - 1; i != (size_t) -1; i--)
	{
		dheapify<d>(v, i, comp);
	}
}

} // namespace wmv::algorithms


