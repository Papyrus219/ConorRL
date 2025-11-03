#include "audio_manager.hpp"
#include "../../enemies/enemy.hpp"
#include <iostream>

using namespace conor;

conor::Audio_manager::Audio_manager(std::string audio_path, int enemies_amount)
{

    atack_sound_effects_buffers.reserve(enemies_amount+1);
    atack_sound_effects.reserve(enemies_amount+1);
    for(int i=0;i<enemies_amount+1;i++)
    {
        atack_sound_effects_buffers.emplace_back();
        if(!atack_sound_effects_buffers[i].loadFromFile(audio_path + "sound effects/atack/atack" + std::to_string(i+1) + ".wav") )
            std::cerr << "Kurwa mać...\n";
        atack_sound_effects.emplace_back( atack_sound_effects_buffers[i] );
        atack_sound_effects[i].setBuffer( atack_sound_effects_buffers[i] );

        atack_sound_effects[i].setVolume(100);
    }

    dead_sound_effects_buffers.reserve(enemies_amount);
    dead_sound_effects.reserve(enemies_amount);
    for(int i=0;i<enemies_amount;i++)
    {
        dead_sound_effects_buffers.emplace_back();
        if(!dead_sound_effects_buffers[i].loadFromFile(audio_path + "sound effects/death/death" + std::to_string(i+1) + ".wav") )
            std::cerr << "Kurwa mać...\n";

        dead_sound_effects.emplace_back(dead_sound_effects_buffers[i]);
        dead_sound_effects[i].setBuffer( dead_sound_effects_buffers[i] );

        dead_sound_effects[i].setVolume(100);
    }

    dungeon_music.openFromFile(audio_path + "music/dungeon.wav");
    dungeon_music.setVolume(70);
}

void conor::Audio_manager::onNotify(Event event, std::shared_ptr<Being>& entity)
{
    switch(event)
    {
        case Event::Game_started:
            dungeon_music.play();
            dungeon_music.setLooping(true);
            break;
        case Event::Enemy_attack:
        {
            switch(entity->species)
            {
                case Enemy::Species::goblin:
                    atack_sound_effects[0].play();
                    break;
                case Enemy::Species::skieleton:
                    atack_sound_effects[1].play();
                    break;
                default:
                    break;
            }
            break;
        }
        case Event::Enemy_killed:
            switch(entity->species)
            {
                case Enemy::Species::goblin:
                    dead_sound_effects[0].play();
                    break;
                case Enemy::Species::skieleton:
                    dead_sound_effects[1].play();
                    break;
                default:
                    dead_sound_effects[0].play();
                    break;
            }
            break;
        case Event::Player_atack:
        {
            atack_sound_effects[2].play();
            break;
        }
        default:
            break;
    }
}
