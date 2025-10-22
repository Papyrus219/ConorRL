#include "board_generator.hpp"

using namespace conor;

std::vector< std::vector<Tile> > * conor::Board_generator::assigned_board{};
std::vector< std::vector<Entities> >* conor::Board_generator::assigned_entieties{};
std::vector< std::vector<Tile> >* conor::Board_generator::Leaf::assigned_board{ conor::Board_generator::assigned_board };
std::vector< std::vector<Entities> >* conor::Board_generator::Leaf::assigned_entieties{ conor::Board_generator::assigned_entieties };
bool conor::Board_generator::Leaf::is_player{};

conor::Board_generator::Board_generator(int map_heigh_, int map_width_,std::vector<std::vector<Tile>>* board, std::vector< std::vector<Entities> > *entieties): map_heigh{map_heigh_}, map_width{map_width_}
{
    Board_generator::assigned_board = board;
    Board_generator::Leaf::assigned_board = board;
    Board_generator::assigned_entieties = entieties;
    Board_generator::Leaf::assigned_entieties = entieties;
}

conor::Board_generator::Leaf::Leaf(int x_, int y_, int width_, int heigh_): x{x_}, y{y_}, width{width_}, heigh{heigh_}
{

}

void conor::Board_generator::Generate()
{
    std::random_device rd{};
    std::mt19937 rng{rd()};
    Leaf root{0, 0, map_width, map_heigh};

    std::vector<Leaf*> leaves{};
    leaves.push_back(&root);

    bool isSplit{true};
    while(isSplit)
    {
        isSplit = false;
        for(auto leaf : leaves)
        {
            if(!leaf->left && !leaf->right && (leaf->width > max_leaf_size || leaf->heigh > max_leaf_size))
            {
                if(leaf->Split(rng))
                {
                    leaves.push_back(leaf->left);
                    leaves.push_back(leaf->right);
                    isSplit = true;
                }
            }
        }
    }
    root.Create_rooms(rng);

    root.Add_exit(leaves);

    // for(int y=0; y<100; y++)
    // {
    //     for(int x=0; x<100; x++)
    //     {
    //         switch((*assigned_board)[y][x])
    //         {
    //             case Tile::wall:
    //                 std::cout << "#";
    //                 break;
    //             case Tile::exit:
    //                 std::cout << "E";
    //             case Tile::floor:
    //                 switch((*assigned_entieties)[y][x])
    //                 {
    //                     case Entities::goblin:
    //                         std::cout << "G";
    //                         break;
    //                     case Entities::skieleton:
    //                         std::cout << "S";
    //                         break;
    //                     case Entities::player:
    //                         std::cout << "P";
    //                         break;
    //                     case Entities::none:
    //                         std::cout << ".";
    //                         break;
    //                 }
    //                 break;
    //         }
    //     }
    //     std::cout << '\n';
    // }
}

bool Board_generator::Leaf::Split(std::mt19937& rng)
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
    int split_at = distance(rng);
    if(split_heigh)
    {
        left = new Leaf{x, y, width, split_at};
        right = new Leaf(x, y + split_at, width, heigh - split_at);
    }
    else
    {
        left = new Leaf(x, y, split_at, heigh);
        right = new Leaf{x + split_at, y,width - split_at, heigh};
    }

    return true;
}

void conor::Board_generator::Leaf::Create_rooms(std::mt19937 &rng)
{
    if(left || right)
    {
        if(left) left->Create_rooms(rng);
        if(right) right->Create_rooms(rng);
        if(left && right)
            Connect_rooms(left->Get_room(), right->Get_room());
    }
    else
    {
        std::uniform_int_distribution<int> room_width_rand{3, std::max(3, width - 2)};
        std::uniform_int_distribution<int> room_heigh_rand{3, std::max(3, heigh - 2)};
        int room_width{room_width_rand(rng)};
        int room_heigh{room_heigh_rand(rng)};

        std::uniform_int_distribution<int> room_x_rand{0, std::max(0, width - room_width )};
        std::uniform_int_distribution<int> room_y_rand{0, std::max(0, heigh - room_heigh )};
        int room_x = x + room_x_rand(rng);
        int room_y = y + room_y_rand(rng);

        room = {room_x, room_y, room_width, room_heigh};
        Carve_room(room, rng);
    }
}

void conor::Board_generator::Leaf::Connect_rooms(const Room& a, const Room& b)
{
    int x1 = a.Center_x();
    int y1 = a.Center_y();
    int x2 = b.Center_x();
    int y2 = b.Center_y();
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> coin{0, 1};
    if(coin(rng))
    {
        Crave_heigh_tunnel(x1,x2,y1, rng);
        Crave_width_tunnel(y1,y2,x2, rng);
    }
    else
    {
        Crave_width_tunnel(y1, y2, x1, rng);
        Crave_heigh_tunnel(x1, x2, y2, rng);
    }
}

conor::Board_generator::Room conor::Board_generator::Leaf::Get_room()
{
        if(left || right)
        {
            if(left)
            {
                Room left_room = left->Get_room();
                if(left_room.width != 0) return left_room;
            }
            if(right)
            {
                Room right_room = right->Get_room();
                if(right_room.width != 0) return right_room;
            }
        }

        return room;
}

void conor::Board_generator::Leaf::Carve_room(const Room& room, std::mt19937 &rng)
{
    for(int y = room.y; y < room.y + room.heigh; ++y)
    {
        for(int x = room.x; x < room.x + room.width; ++x)
        {
            (*assigned_board)[y][x] = Tile::floor;

            std::uniform_int_distribution<int> gen{0,30};
            if(!gen(rng))
            {
                if(gen(rng) % 2 == 0)
                {
                    (*assigned_entieties)[y][x] = Entities::goblin;
                }
                else
                {
                    (*assigned_entieties)[y][x] = Entities::skieleton;
                }

            }
        }
    }
}

void conor::Board_generator::Leaf::Crave_heigh_tunnel(int x1, int x2, int y, std::mt19937 &rng)
{
    for(int x = std::min(x1,x2); x <= std::max(x1,x2); ++x)
    {
        (*assigned_board)[y][x] = Tile::floor;
        if(!is_player)
        {
            (*assigned_entieties)[y][x] = Entities::player;
            is_player = true;
        }

        std::uniform_int_distribution<int> gen{0,40};
        if(!gen(rng)) (*assigned_entieties)[y][x] = Entities::goblin;
    }
}

void conor::Board_generator::Leaf::Crave_width_tunnel(int y1, int y2, int x, std::mt19937 &rng)
{
    for(int y = std::min(y1,y2); y <= std::max(y1,y2); ++y)
    {
        (*assigned_board)[y][x] = Tile::floor;

        std::uniform_int_distribution<int> gen{0,40};
        if(!gen(rng)) (*assigned_entieties)[y][x] = Entities::goblin;
    }
}

void conor::Board_generator::Leaf::Add_exit(std::vector<Leaf *>& leafes)
{
    Leaf* start_leaf = leafes.front();
    Leaf* farthest_leaf = nullptr;
    int max_dist = -1;

    for(auto leaf : leafes)
    {
        int distance_x = leaf->room.Center_x() - start_leaf->room.Center_x();
        int distance_y = leaf->room.Center_y() - start_leaf->room.Center_y();
        int distance = distance_x*distance_x + distance_y*distance_y;
        if(distance > max_dist)
        {
            max_dist = distance;
            farthest_leaf = leaf;
        }
    }

    if(farthest_leaf)
    {
        int exit_x = farthest_leaf->room.Center_x();
        int exit_y = farthest_leaf->room.Center_y();
        (*assigned_board)[exit_y][exit_x] = Tile::exit;
    }
}
