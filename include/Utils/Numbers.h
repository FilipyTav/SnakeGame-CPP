#pragma once

#include <cmath>
#include <cstdlib>

// Declaration
//----------------------------------------------------------------------------------
namespace numbers {
/*
 * Wraps numbers in the range [start; limit)
 *
 * See:
 * https://stackoverflow.com/questions/28313558/how-to-wrap-a-number-into-a-range
 */
template <typename T> //
T wrap_range(const T number, const T start, const T limit);
} // namespace numbers
//----------------------------------------------------------------------------------

// Definition
//----------------------------------------------------------------------------------
namespace numbers {
template <typename T> //
T wrap_range(const T number, const T start, const T limit) {

    // numberToBeWrapped = start + (numberToBeWrapped - start) % (limit - start)

    if (number < start) {
        return limit - std::abs(start - number);
    }

    return start + std::fmod(number - start, limit - start);
    // return start + (number - start) % (limit - start);
};
}; // namespace numbers
//----------------------------------------------------------------------------------
