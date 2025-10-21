#include "board_generator.hpp"

using namespace conor;

std::vector< std::vector<Tile> > * conor::Board_generator::assigned_board{};
std::vector< std::vector<Tile> >* conor::Board_generator::Leaf::assigned_board{ conor::Board_generator::assigned_board };

conor::Board_generator::Board_generator(int map_heigh_, int map_width_,std::vector<std::vector<Tile>>* board): map_heigh{map_heigh_}, map_width{map_width_}
{
    Board_generator::assigned_board = board;
    Board_generator::Leaf::assigned_board = board;
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
    for(int y=0; y<100; y++)
    {
        for(int x=0; x<100; x++)
        {
            std::cout << ((*assigned_board)[y][x] == Tile::wall ? '#' : '.');
        }
        std::cout << '\n';
    }
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
        Carve_room(room);
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
        Crave_heigh_tunnel(x1,x2,y1);
        Crave_width_tunnel(y1,y2,x2);
    }
    else
    {
        Crave_width_tunnel(y1, y2, x1);
        Crave_heigh_tunnel(x1, x2, y2);
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

void conor::Board_generator::Leaf::Carve_room(const Room& room)
{
    for(int y = room.y; y < room.y + room.heigh; ++y)
    {
        for(int x = room.x; x < room.x + room.width; ++x)
        {
            (*assigned_board)[y][x] = Tile::floor;
        }
    }
}

void conor::Board_generator::Leaf::Crave_heigh_tunnel(int x1, int x2, int y)
{
    for(int x = std::min(x1,x2); x <= std::max(x1,x2); ++x)
        (*assigned_board)[y][x] = Tile::floor;
}

void conor::Board_generator::Leaf::Crave_width_tunnel(int y1, int y2, int x)
{
    for(int y = std::min(y1,y2); y <= std::max(y1,y2); ++y)
        (*assigned_board)[y][x] = Tile::floor;
}
