#include "path_finder.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace conor;

conor::Path_finder::Path_finder(Board* board,std::vector<Enemy*> &enemies ): assign_board{board}, assign_enemies{&enemies}
{
    distans.resize(board->dungeon_map.size(), std::vector<int>(board->dungeon_map[0].size(),-1) );
}

void conor::Path_finder::Set_board(Board* board)
{
    assign_board = board;
    distans.resize(board->dungeon_map.size(), std::vector<int>(board->dungeon_map[0].size(),-1) );
}

void conor::Path_finder::Set_enemies(std::vector<Enemy *> &enemies)
{
    assign_enemies = &enemies;
}


void conor::Path_finder::Update_distances(Player* player)
{
    distans.clear();
    distans.resize(assign_board->dungeon_map.size(), std::vector<int>(assign_board->dungeon_map[0].size(),-1) );
    std::pair<int,int> moves[4]{ {0,1},{0,-1},{1,0},{-1,0} };
    std::queue<std::pair<int,int>> queue;
    int player_y = player->possition.y;
    int player_x = player->possition.x;

    queue.push( {player_y,player_x} );

    while(!queue.empty())
    {
        auto [x,y] = queue.front();
        for(int i=0;i<4;i++)
        {
            int mov_y{y + moves[i].first};
            int mov_x{x + moves[i].second};

            if(mov_y >= assign_board->dungeon_map.size() || mov_y < 0) continue;
            if(mov_x >= assign_board->dungeon_map[0].size() || mov_x < 0) continue;

            if(distans[mov_y][mov_x] == -1)
            {
                queue.push( {mov_y,mov_x} );
                distans[mov_y][mov_x] = distans[y][x]+1;
            }

            distans[mov_y][mov_x] = std::min( distans[mov_y][mov_x], distans[y][x]+1 );
        }

        queue.pop();
    }
}

void conor::Path_finder::Move_enemies()
{
    std::pair<int,int> moves[4] = { {0,1},{0,-1},{1,0},{-1,0} };

    for (auto &enemy : *assign_enemies)
    {
        int y = enemy->possition.y;
        int x = enemy->possition.x;
        int min_dis = -1;

        for (int i = 0; i < 4; i++)
        {
            int mov_y = y + moves[i].first;
            int mov_x = x + moves[i].second;

            if (mov_y < 0 || mov_y >= assign_board->dungeon_map.size()) continue;
            if (mov_x < 0 || mov_x >= assign_board->dungeon_map[mov_y].size()) continue;
            if(assign_board->dungeon_map[mov_y][mov_x] != Tile::floor) continue;
            if(assign_board->entities_map[mov_y][mov_x]) continue;

            if (min_dis == -1 || distans[y + moves[min_dis].first][x + moves[min_dis].second] > distans[mov_y][mov_x])
            {
                min_dis = i;
            }
        }

        if (min_dis == -1) continue;

        int new_y = y + moves[min_dis].first;
        int new_x = x + moves[min_dis].second;

        assign_board->entities_map[new_y][new_x] = enemy;
        assign_board->entities_map[y][x] = nullptr;

        enemy->possition = {new_y, new_x};
    }
}

void conor::Path_finder::onNotify(Event event, Being* entity)
{
    switch(event)
    {
        case Event::Player_moved:
            Update_distances( static_cast<Player*>(entity) );
            Move_enemies();
            break;
    }
}
