#include <benchmark/benchmark.h>

#include <chrono>
#include <sstream>

#include "../../algorithms/sorting/insertion_sort/insertion_sort.h"
#include "../../algorithms/sorting/heap_sort/heap_sort.h"
#include "../../algorithms/sorting/merge_sort/merge_sort.hpp"

// Naming standard:
// BM_<algorithm>_<input_distribution>_<element_type>
// 
// Note: element_type could for example be "unique", meaning each elemt in the range is unique.
//       It could also be "repeated", meaning there are duplicates in the range, or "random", meaning the range is randomly generated (with a seed).

// Functions to generate random lists in a fair way

#define STARTSEED 6942069


uint32_t pcg_hash(uint32_t x)
{
	x = x * 747796405u + 2891336453u;
	uint32_t word = ((x >> ((x >> 28u) + 4u)) ^ x) * 277803737u;
	return (word >> 22) ^ word;
}

float pcg_random(uint32_t& seed)
{
	seed = pcg_hash(seed);
	return float(seed) / float(std::numeric_limits<uint32_t>::max());
}

uint32_t pcg_random(uint32_t& seed, uint32_t min, uint32_t max)
{
	return min + uint32_t(pcg_random(seed) * float(max - min));
}

void populateVector_sequential(std::vector<int32_t>& v, int32_t min, int32_t max)
{
	v.resize(max - min + 1);
	for (int32_t i = min; i <= max; i++)
		v[i - min] = i;
}

void shuffleVector_random(std::vector<int32_t>& v, uint32_t& seed)
{
	for (size_t i = 0; i < v.size(); i++)
		std::swap(v[i], v[pcg_random(seed, 0, v.size() - 1)]);
}

// Generates a list of sequential numbers (positive and negative) in a random order
// The randomness is seeded, so shuffling an instance will yield the same result as on a seperate instance.
// The list is initially sorted!

// STD::SORT BENCHMARKS
static void BM_StdSort_Sorted_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		benchmark::DoNotOptimize(l);
		benchmark::ClobberMemory();

		auto start = std::chrono::high_resolution_clock::now();
		std::sort(l.begin(), l.end());
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	} 
}
BENCHMARK(BM_StdSort_Sorted_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();

static void BM_StdSort_ReverseSorted_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		std::reverse(l.begin(), l.end());

		auto start = std::chrono::high_resolution_clock::now();
		std::sort(l.begin(), l.end());
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_StdSort_ReverseSorted_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();

static void BM_StdSort_Random_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	uint32_t seed = STARTSEED;
	
	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));
		shuffleVector_random(l, seed);

		auto start = std::chrono::high_resolution_clock::now();
		std::sort(l.begin(), l.end());
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_StdSort_Random_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();



// INSERTION SORT BENCHMARKS
static void BM_InsertionSort_Sorted_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::insertion_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_InsertionSort_Sorted_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();

static void BM_InsertionSort_ReverseSorted_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		std::reverse(l.begin(), l.end());

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::insertion_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_InsertionSort_ReverseSorted_Unique)->RangeMultiplier(2)->Range(0, 1 << 14)->UseManualTime();

static void BM_InsertionSort_Random_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	uint32_t seed = STARTSEED;

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		shuffleVector_random(l, seed);

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::insertion_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_InsertionSort_Random_Unique)->RangeMultiplier(2)->Range(0, 1 << 14)->UseManualTime();;


// HEAP SORT BENCHMARKS
static void BM_HeapSort_Sorted_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::heap_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_HeapSort_Sorted_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();

static void BM_HeapSort_ReverseSorted_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		std::reverse(l.begin(), l.end());

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::heap_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_HeapSort_ReverseSorted_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();

static void BM_HeapSort_Random_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	uint32_t seed = STARTSEED;


	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));
		shuffleVector_random(l, seed);

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::heap_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_HeapSort_Random_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();


// MERGE SORT BENCHMARKS
static void BM_MergeSort_Sorted_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::merge_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_MergeSort_Sorted_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();

static void BM_MergeSort_ReverseSorted_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));

		std::reverse(l.begin(), l.end());

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::merge_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_MergeSort_ReverseSorted_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();

static void BM_MergeSort_Random_Unique(benchmark::State& state)
{
    state.SetLabel((std::stringstream{} << state.range(0)).str());

	uint32_t seed = STARTSEED;

	for (auto _ : state)
	{
		std::vector<int32_t> l;
		populateVector_sequential(l, 0, state.range(0));
		shuffleVector_random(l, seed);

		auto start = std::chrono::high_resolution_clock::now();
		wmv::algorithms::merge_sort(l);
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		state.SetIterationTime(elapsed_seconds.count());
	}
}
BENCHMARK(BM_MergeSort_Random_Unique)->RangeMultiplier(2)->Range(0, 1 << 17)->DenseRange(1 << 18, 1 << 22, 500000)->DenseRange(1 << 22, 1 << 26, 1000000)->UseManualTime();




BENCHMARK_MAIN();