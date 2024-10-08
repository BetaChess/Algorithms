#pragma once

#include <cstdint>

constexpr uint32_t pcg_hash(uint32_t x)
{
	x = x * 747796405u + 2891336453u;
	uint32_t word = ((x >> ((x >> 28u) + 4u)) ^ x) * 277803737u;
	return (word >> 22) ^ word;
}