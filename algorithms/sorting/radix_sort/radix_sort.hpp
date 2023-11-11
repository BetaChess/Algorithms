#pragma once

#include <algorithm>
#include "../counting_sort/counting_sort.hpp"

namespace wmv::algorithms
{

template<std::ranges::random_access_range R>
void radix_sort(R &r)
{
	if (std::ranges::size(r) < 2)
		return;
	
	typedef typename std::remove_reference_t<typename std::remove_reference_t<decltype(r)>::value_type> range_elem_type;
	auto* aux = new range_elem_type[std::ranges::size(r)];
	std::span s{aux, std::ranges::size(r)};

	range_elem_type max = std::ranges::max(r);

	for (range_elem_type place = 1; 0 < max / place; place *= RADIX_BASE)
	{
		_r_counting_sort(r, s, place);
		if (0 < max / place)
			_r_counting_sort(s, r, place *= RADIX_BASE);
		else
		{
			for (size_t j = 0; j < std::ranges::size(r); j++)
				r[j] = s[j];
			return;
		}
	}

//	for (uint64_t i = 0; i < sizeof(*aux) + 1; i += 2)
//	{
//		counting_sort(r, s, static_cast<uint8_t>(i));
//		counting_sort(s, r, static_cast<uint8_t>(i + 1));
//	}

//	delete[] aux;
}

}// namespace wmv::algorithms
