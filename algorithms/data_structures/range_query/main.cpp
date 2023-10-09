#include <iostream>
#include <vector>
#include <cstdint>

#include "range_query.hpp"

int main()
{
    RangeQuery r{{1, 4, 5, 6, 7}, 8};

    std::cout << r.query(0, 8);
    return 0;
}