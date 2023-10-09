#pragma once

template<std::integral T>
class RangeQuery
{
public:
    constexpr RangeQuery(const std::vector<T>& integers, const T k)
    {
        data_.resize((size_t)k + 1ULL);

        for (size_t i : integers)
            data_[i]++;

        for (size_t i = 1; i < data_.size(); i++)
            data_[i] += data_[i - 1];
    }

    constexpr uint64_t query(const size_t max)
    {
        return data_[max];
    }

    constexpr uint64_t query(const size_t min, const size_t max)
    {
        if (min == 0)
            return data_[max];

        return data_[max] - data_[min - 1];
    }

private:
    std::vector<T> data_{};
};