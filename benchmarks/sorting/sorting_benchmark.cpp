//#pragma comment(linker, "/6000000")

#include <benchmark/benchmark.h>

#include <chrono>
#include <iostream>
#include <sstream>

#include <util/random.hpp>
#include <sorting/heap_sort.hpp>
#include <sorting/insertion_sort.hpp>
#include <sorting/merge_sort.hpp>
#include <sorting/quick_sort.hpp>
#include <sorting/radix_sort.hpp>
#include <sorting/counting_sort.hpp>

// Naming standard:
// BM_<algorithm>_<input_distribution>_<element_type>
//
// Note: element_type could for example be "unique", meaning each elemt in the range is unique.
//       It could also be "repeated", meaning there are duplicates in the range, or "random", meaning the range is randomly generated (with a seed).

// Functions to generate random lists in a fair way

#define STARTSEED 6942069


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
		std::swap(v[i], v[pcg_random(seed, 0, v.size() - 1)]);
}

/// SORTING BENCHMARK MACROS

#define STANDARDPARAMS RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime()
#define SLOWPARAMS RangeMultiplier(2)->Range(0, 1 << 15)->UseManualTime()

#define SORTED_UNIQUE(NAME, SORTINGFUNCTION, BENCHMARKPARAMS)                                              \
	static void NAME(benchmark::State &state)                                                              \
	{                                                                                                      \
		state.SetLabel((std::stringstream{} << state.range(0)).str());                                     \
		std::vector<int32_t> l;                                                                            \
		populateVector_sequential(l, 0, state.range(0));                                                   \
		for (auto _: state)                                                                                \
		{                                                                                                  \
			auto start = std::chrono::high_resolution_clock::now();                                        \
			SORTINGFUNCTION(l);                                                                            \
			auto end = std::chrono::high_resolution_clock::now();                                          \
			auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start); \
			state.SetIterationTime(elapsed_seconds.count());                                               \
		}                                                                                                  \
	}                                                                                                      \
	BENCHMARK(NAME)->BENCHMARKPARAMS;

#define REVERSESORTED_UNIQUE(NAME, SORTINGFUNCTION, BENCHMARKPARAMS)                                       \
	static void NAME(benchmark::State &state)                                                              \
	{                                                                                                      \
		state.SetLabel((std::stringstream{} << state.range(0)).str());                                     \
		std::vector<int32_t> l;                                                                            \
		populateVector_sequential(l, 0, state.range(0));                                                   \
		for (auto _: state)                                                                                \
		{                                                                                                  \
			std::reverse(l.begin(), l.end());                                                              \
			auto start = std::chrono::high_resolution_clock::now();                                        \
			SORTINGFUNCTION(l);                                                                            \
			auto end = std::chrono::high_resolution_clock::now();                                          \
			auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start); \
			state.SetIterationTime(elapsed_seconds.count());                                               \
		}                                                                                                  \
	}                                                                                                      \
	BENCHMARK(NAME)->BENCHMARKPARAMS;

#define RANDOM_UNIQUE(NAME, SORTINGFUNCTION, BENCHMARKPARAMS)                                              \
	static void NAME(benchmark::State &state)                                                              \
	{                                                                                                      \
		state.SetLabel((std::stringstream{} << state.range(0)).str());                                     \
		uint32_t seed = STARTSEED;                                                                         \
		std::vector<int32_t> l;                                                                            \
		l.resize(state.range(0));                                                                          \
		for (auto _: state)                                                                                \
		{                                                                                                  \
			for (size_t i = 0; i < l.size(); i++)                                                          \
				l[i] = pcg_random(seed, 0, l.size() - 1);                                                  \
			auto start = std::chrono::high_resolution_clock::now();                                        \
			SORTINGFUNCTION(l);                                                                            \
			auto end = std::chrono::high_resolution_clock::now();                                          \
			auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start); \
			state.SetIterationTime(elapsed_seconds.count());                                               \
		}                                                                                                  \
	}                                                                                                      \
	BENCHMARK(NAME)->BENCHMARKPARAMS;


// STD::SORT BENCHMARKS
SORTED_UNIQUE(BM_StdSort_Sorted_Unique, std::ranges::sort, STANDARDPARAMS);

REVERSESORTED_UNIQUE(BM_StdSort_ReverseSorted_Unique, std::ranges::sort, STANDARDPARAMS);

RANDOM_UNIQUE(BM_StdSort_Random_Unique, std::ranges::sort, STANDARDPARAMS);


// INSERTION SORT BENCHMARKS
SORTED_UNIQUE(BM_InsertionSort_Sorted_Unique, wmv::algorithms::insertion_sort, STANDARDPARAMS);

REVERSESORTED_UNIQUE(BM_InsertionSort_ReverseSorted_Unique, wmv::algorithms::insertion_sort, SLOWPARAMS);

RANDOM_UNIQUE(BM_InsertionSort_Random_Unique, wmv::algorithms::insertion_sort, SLOWPARAMS);


// HEAP SORT BENCHMARKS
SORTED_UNIQUE(BM_HeapSort_Sorted_Unique, wmv::algorithms::heap_sort, STANDARDPARAMS);

REVERSESORTED_UNIQUE(BM_HeapSort_ReverseSorted_Unique, wmv::algorithms::heap_sort, STANDARDPARAMS);

RANDOM_UNIQUE(BM_HeapSort_Random_Unique, wmv::algorithms::heap_sort, STANDARDPARAMS);


// MERGE SORT BENCHMARKS
SORTED_UNIQUE(BM_MergeSort_Sorted_Unique, wmv::algorithms::merge_sort, STANDARDPARAMS);

REVERSESORTED_UNIQUE(BM_MergeSort_ReverseSorted_Unique, wmv::algorithms::merge_sort, STANDARDPARAMS);

RANDOM_UNIQUE(BM_MergeSort_Random_Unique, wmv::algorithms::merge_sort, STANDARDPARAMS);


// QUICK SORT BENCHMARKS
SORTED_UNIQUE(BM_QuickSort_Sorted_Unique, wmv::algorithms::quick_sort, SLOWPARAMS);

REVERSESORTED_UNIQUE(BM_QuickSort_ReverseSorted_Unique, wmv::algorithms::quick_sort, SLOWPARAMS);

RANDOM_UNIQUE(BM_QuickSort_Random_Unique, wmv::algorithms::quick_sort, STANDARDPARAMS);

// RANDOMIZED QUICK SORT
SORTED_UNIQUE(BM_RandomizedQuickSort_Sorted_Unique, wmv::algorithms::randomized_quick_sort, STANDARDPARAMS);

REVERSESORTED_UNIQUE(BM_RandomizedQuickSort_ReverseSorted_Unique, wmv::algorithms::randomized_quick_sort,
					 STANDARDPARAMS);

RANDOM_UNIQUE(BM_RandomizedQuickSort_Random_Unique, wmv::algorithms::randomized_quick_sort, STANDARDPARAMS);

// RADIX SORT
SORTED_UNIQUE(BM_RadixSort_Sorted_Unique, wmv::algorithms::radix_sort, STANDARDPARAMS);

REVERSESORTED_UNIQUE(BM_RadixSort_ReverseSorted_Unique, wmv::algorithms::radix_sort,
					 STANDARDPARAMS);

RANDOM_UNIQUE(BM_RadixSort_Random_Unique, wmv::algorithms::radix_sort, STANDARDPARAMS);


BENCHMARK_MAIN();