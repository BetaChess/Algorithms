#pragma once

#include <cassert>
#include <vector>


namespace wmv::algorithms
{

void merge(std::vector<int>::iterator p, std::vector<int>::iterator q, std::vector<int>::iterator r)
{
	size_t n1 = q - p + 1;
	size_t n2 = r - q;

	std::vector<int> L(n1 + 1);
	std::vector<int> R(n2 + 1);

	for (size_t i = 0; i < n1; ++i)
	{
		L[i] = p[i];
	}
	for (size_t j = 0; j < n2; ++j)
	{
		R[j] = q[j + 1];
	}

	L[n1] = std::numeric_limits<int>::max();
	R[n2] = std::numeric_limits<int>::max();

	size_t i = 0;
	size_t j = 0;

	for (auto k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			*k = L[i++];
		}
		else
		{
			n1 - i;
			*k = R[j++];
		}
	}
}

void merge_sort(std::vector<int>::iterator p, std::vector<int>::iterator r)
{
	if (p < r)
	{
		auto q = p + (r - p) / 2;
		merge_sort(p, q);
		merge_sort(q + 1, r);
		merge(p, q, r);
	}
}

void merge_sort(std::vector<int>& v)
{
	merge_sort(v.begin(), (v.end() - 1));
}


//size_t merge(std::vector<int>::iterator p, std::vector<int>::iterator q, std::vector<int>::iterator r)
//{
//	size_t inversions = 0;
//
//	size_t n1 = q - p + 1;
//	size_t n2 = r - q;
//
//	std::vector<int> L(n1 + 1);
//	std::vector<int> R(n2 + 1);
//
//	for (size_t i = 0; i < n1; ++i)
//	{
//		L[i] = p[i];
//	}
//	for (size_t j = 0; j < n2; ++j)
//	{
//		R[j] = q[j + 1];
//	}
//
//	L[n1] = std::numeric_limits<int>::max();
//	R[n2] = std::numeric_limits<int>::max();
//
//	size_t i = 0;
//	size_t j = 0;
//
//	for (auto k = p; k <= r; k++)
//	{
//		if (L[i] <= R[j])
//		{
//			*k = L[i++];
//		}
//		else
//		{
//			inversions += n1 - i;
//			*k = R[j++];
//		}
//	}
//
//	return inversions;
//}
//
//size_t merge_sort(std::vector<int>::iterator p, std::vector<int>::iterator r)
//{
//	size_t inversions = 0;
//
//	if (p < r)
//	{
//		auto q = p + (r - p) / 2;
//		inversions += merge_sort(p, q);
//		inversions += merge_sort(q + 1, r);
//		inversions += merge(p, q, r);
//	}
//
//	return inversions;
//}


}