#ifndef CONOR_BOARD_GENERATOR_H
#define CONOR_BOARD_GENERATOR_H

#include "./board.hpp"
#include <iostream>
#include <random>
#include <algorithm>

namespace conor {

/**
 * @todo write docs
 */
class Board_generator
{
    Board_generator(std::vector< std::vector<Tile> > *board): assigned_board{board} {};
    void Generate();

private:
    constexpr static int min_leaf_size{10};
    constexpr static int max_leaf_size{20};

    struct Room
    {
        int x{},y{},width{},heigh{};
        int Center_x() const {return x+width/2;};
        int Center_y() const {return y+heigh/2;};
    };

    struct Leaf
    {
        int x{},y{},width{},heigh{};
        Leaf* left{};
        Leaf* right{};

        bool split(std::mt19937& rng);
    };

    std::vector< std::vector<Tile> > *assigned_board{};
};

}

#endif // CONOR_BOARD_GENERATOR_H
