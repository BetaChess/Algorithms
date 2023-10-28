#include <gtest/gtest.h>

#include <algorithm>
#include <ranges>

#include "../algorithms/sorting/heap_sort/heap_sort.h"
#include "../algorithms/sorting/insertion_sort/insertion_sort.h"
#include "../algorithms/sorting/merge_sort/merge_sort.hpp"
#include "../algorithms/sorting/quick_sort/quick_sort.hpp"
#include "../algorithms/util/random.hpp"


float pcg_random(uint32_t &seed)
{
	seed = pcg_hash(seed);
	return float(seed) / float(std::numeric_limits<uint32_t>::max());
}

uint32_t pcg_random(uint32_t &seed, uint32_t min, uint32_t max)
{
	return min + uint32_t(pcg_random(seed) * float(max - min));
}

void populateVector_sequential(std::vector<int32_t> &v, int32_t min, int32_t max)
{
	v.resize(max - min + 1);
	for (int32_t i = min; i <= max; i++)
		v[i - min] = i;
}

void shuffleVector_random(std::vector<int32_t> &v, uint32_t &seed)
{
	for (size_t i = 0; i < v.size(); i++)
		std::swap(v[i], v[pcg_random(seed, 0U, static_cast<uint32_t>(v.size() - 1ULL))]);
}

#define MIN -5
#define MAX 10000


TEST(Sorting, Insertion)
{
	std::vector<int32_t> l;
	populateVector_sequential(l, MIN, MAX);
	uint32_t seed = 54325342;
	shuffleVector_random(l, seed);

	EXPECT_FALSE(std::ranges::is_sorted(l));
	wmv::algorithms::insertion_sort(l);
	EXPECT_TRUE(std::ranges::is_sorted(l));

	shuffleVector_random(l, seed);
	EXPECT_FALSE(std::ranges::is_sorted(l, std::ranges::greater{}));
	wmv::algorithms::insertion_sort(l, std::ranges::greater{});
	EXPECT_TRUE(std::ranges::is_sorted(l, std::ranges::greater{}));
}

TEST(Sorting, Heap)
{
	std::vector<int32_t> l;
	populateVector_sequential(l, MIN, MAX);
	uint32_t seed = 54325342;
	shuffleVector_random(l, seed);

	EXPECT_FALSE(std::ranges::is_sorted(l));
	wmv::algorithms::heap_sort(l);
	EXPECT_TRUE(std::ranges::is_sorted(l));

	shuffleVector_random(l, seed);
	EXPECT_FALSE(std::ranges::is_sorted(l, std::ranges::greater{}));
	wmv::algorithms::heap_sort(l, std::ranges::greater{});
	EXPECT_TRUE(std::ranges::is_sorted(l, std::ranges::greater{}));
}

TEST(Sorting, Merge)
{
	std::vector<int32_t> l;
	populateVector_sequential(l, MIN, MAX);
	uint32_t seed = 54325342;
	shuffleVector_random(l, seed);

	EXPECT_FALSE(std::ranges::is_sorted(l));
	wmv::algorithms::merge_sort(l);
	EXPECT_TRUE(std::ranges::is_sorted(l));

	// TODO: IMPLEMENT MERGE SORT PROPERLY
//	shuffleVector_random(l, seed);
//	EXPECT_FALSE(std::ranges::is_sorted(l, std::ranges::greater{}));
//	wmv::algorithms::merge_sort(l, std::ranges::greater{});
//	EXPECT_TRUE(std::ranges::is_sorted(l, std::ranges::greater{}));
}

TEST(Sorting, Quick)
{
	std::vector<int32_t> l;
	populateVector_sequential(l, MIN, MAX);
	uint32_t seed = 54325342;
	shuffleVector_random(l, seed);

	EXPECT_FALSE(std::ranges::is_sorted(l));
	wmv::algorithms::quick_sort(l);
	EXPECT_TRUE(std::ranges::is_sorted(l));

	shuffleVector_random(l, seed);
	EXPECT_FALSE(std::ranges::is_sorted(l, std::ranges::greater{}));
	wmv::algorithms::quick_sort(l, std::ranges::greater{});
	EXPECT_TRUE(std::ranges::is_sorted(l, std::ranges::greater{}));
}

TEST(Sorting, RandomizedQuick)
{
	std::vector<int32_t> l;
	populateVector_sequential(l, MIN, MAX);
	uint32_t seed = 54325342;
	shuffleVector_random(l, seed);

	EXPECT_FALSE(std::ranges::is_sorted(l));
	wmv::algorithms::randomized_quick_sort(l);
	EXPECT_TRUE(std::ranges::is_sorted(l));

	shuffleVector_random(l, seed);
	EXPECT_FALSE(std::ranges::is_sorted(l, std::ranges::greater{}));
	wmv::algorithms::randomized_quick_sort(l, 0x52616e64, std::ranges::greater{});
	EXPECT_TRUE(std::ranges::is_sorted(l, std::ranges::greater{}));
}

TEST(Sorting, ALLEQUAL)
{
#define NUMSORTFUNCTIONS 5
	std::vector<int32_t> l[NUMSORTFUNCTIONS];
	for (int i = 0; i < NUMSORTFUNCTIONS; i++)
	{
		populateVector_sequential(l[i], MIN, MAX);
		uint32_t seed = 54325342;
		shuffleVector_random(l[i], seed);
	}

	wmv::algorithms::insertion_sort(l[0]);
	wmv::algorithms::heap_sort(l[1]);
	wmv::algorithms::merge_sort(l[2]);
	wmv::algorithms::quick_sort(l[3]);
	wmv::algorithms::randomized_quick_sort(l[4]);

	for (size_t i = 0; i < l[0].size(); i++)
	{
		EXPECT_EQ(l[0][i], l[1][i]);
		EXPECT_EQ(l[0][i], l[2][i]);
		EXPECT_EQ(l[0][i], l[3][i]);
		EXPECT_EQ(l[0][i], l[4][i]);
	}
}
