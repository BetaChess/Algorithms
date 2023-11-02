#pragma once

#include <ranges>
#include <cstdint>
#include <cstring>


namespace wmv::algorithms
{

template<std::ranges::random_access_range R>
R& counting_sort(std::ranges::random_access_range auto &r, R &out_range, std::unsigned_integral auto k)
{
	const size_t size = static_cast<size_t>(k) + static_cast<size_t>(1u);
	auto *C = new decltype(k)[size];

	std::memset(C, 0, sizeof(decltype(k)) * size);

	for (size_t i = 0; i < std::ranges::size(r); i++)
		C[r[i]]++;

	for (size_t i = 1; i < size; i++)
		C[i] += C[i - 1];

	for (size_t i = std::ranges::size(r) - 1; i != static_cast<size_t>(-1); i--)
	{
		size_t j = r[i];
		C[j]--;
		out_range[C[j]] = r[i];
	}

	delete[] C;

	return out_range;
}

template<std::ranges::random_access_range R>
R& _r_counting_sort(std::ranges::random_access_range auto &r, R &out_range, std::integral auto place)
{
//	const size_t size = static_cast<size_t>(k) + static_cast<size_t>(1u);
//	auto *C = new decltype(k)[size];
//	auto mask = 0xff << digit;
	decltype(place) C[10];

	std::memset(C, 0, sizeof(C));

	for (size_t i = 0; i < std::ranges::size(r); i++)
		C[(r[i] / place) % 10]++;

	for (size_t i = 1; i < 10; i++)
		C[i] += C[i - 1];

	for (size_t i = std::ranges::size(r) - 1; i != static_cast<size_t>(-1); i--)
	{
		size_t j = (r[i] / place) % 10;
		C[j]--;
		out_range[C[j]] = r[i];
	}

	return out_range;
}

}// namespace wmv::algorithms
