#ifndef CONOR_BOARD_GENERATOR_H
#define CONOR_BOARD_GENERATOR_H

#include "./board.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <random>
#include <algorithm>

namespace conor {

/**
 * @todo write docs
 */
class Board_generator
{
public:
    Board_generator(int map_heigh_, int map_width_, std::vector< std::vector<Tile> > *board, std::vector< std::vector<Entities> > *entities);
    void Generate();

private:
    const int map_heigh{};
    const int map_width{};
    const static int min_leaf_size{10};
    const static int max_leaf_size{20};

    struct Room
    {
        int x{},y{},width{},heigh{};
        int Center_x() const {return x+width/2;};
        int Center_y() const {return y+heigh/2;};
    };

    struct Leaf
    {
        Leaf(int x_, int y_, int width_, int heigh_);
        int x{},y{},width{},heigh{};
        Leaf* left{};
        Leaf* right{};
        Room room{};

        bool Split(std::mt19937& rng);
        void Create_rooms(std::mt19937 &rng);
        void Connect_rooms(const Room& a, const Room& b);
        void Add_exit(std::vector<Leaf*> &leafes);
        Room Get_room();

        static sf::Vector2i start_player_possition;
        static void Carve_room(const Room &room, std::mt19937 &rng);
        static void Crave_heigh_tunnel(int x1, int x2, int y, std::mt19937 &rng);
        static void Crave_width_tunnel(int y1, int y2, int x, std::mt19937 &rng);
        static std::vector< std::vector<Tile> > *assigned_board;
        static std::vector< std::vector<Entities> > *assigned_entieties;
        static bool is_player;
    };


    static std::vector< std::vector<Tile> > *assigned_board;
    static std::vector< std::vector<Entities> > *assigned_entieties;
public:
        static sf::Vector2i* start_player_possition;
};

}

#endif // CONOR_BOARD_GENERATOR_H
