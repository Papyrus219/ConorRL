#ifndef CONOR_BOARD_GENERATOR_H
#define CONOR_BOARD_GENERATOR_H

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <memory>
#include "./board.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Board_generator
{
public:
    Board_generator(int map_heigh_, int map_width_, Board *map_);
    void Set_path_to_enemies_stats(std::string path_to_enemies);
    std::vector< std::shared_ptr<Enemy>> Generate( std::shared_ptr<Player> &player);

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
        std::shared_ptr<Being> Add_exit_and_player(std::vector<Leaf*> &leafes);
        Room Get_room();

        static sf::Vector2i start_player_possition;
        static void Carve_room(const Room &room, std::mt19937 &rng);
        static void Crave_heigh_tunnel(int x1, int x2, int y, std::mt19937 &rng);
        static void Crave_width_tunnel(int y1, int y2, int x, std::mt19937 &rng);
        static Board* assigned_map;
        static bool is_player;
    };

    static Board* assigned_map;
    static std::string path_to_enemies_stats;
public:
    static sf::Vector2i* start_player_possition;

    friend class Graphics_manager;
};

}

#endif // CONOR_BOARD_GENERATOR_H
