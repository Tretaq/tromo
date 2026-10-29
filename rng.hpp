#include <random>
inline int randInt(std::mt19937& rng, int lo, int hi)
{
    return std::uniform_int_distribution<int>(lo,hi)(rng);
}
