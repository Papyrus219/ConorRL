#include "board_generator.hpp"

using namespace conor;

bool Board_generator::Leaf::split(std::mt19937& rng)
{
    if( left || right) return false;

    std::uniform_int_distribution<int> coin{0,1};
    bool split_heigh = coin(rng);
    if( width > heigh && static_cast<float>(width) / heigh >= 1.25f)
        split_heigh = false;
    else if( heigh > width && static_cast<float>(heigh) / width >= 1.25f)
        split_heigh = true;

    int max = (split_heigh ? heigh : width) - min_leaf_size;
    if(max <= min_leaf_size)
        return false;

    std::uniform_int_distribution<int> distance{min_leaf_size,max};

}
