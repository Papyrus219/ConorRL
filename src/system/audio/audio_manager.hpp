#ifndef CONOR_AUDIO_MANAGER_HPP
#define CONOR_AUDIO_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "../../tools/observer.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Audio_manager: public Observer
{
public:
    Audio_manager(std::string audio_path, int enemies_amount);

    virtual void onNotify(Event event, std::shared_ptr<Being> & entity) override;

private:
    std::vector<sf::SoundBuffer> atack_sound_effects_buffers{};
    std::vector<sf::Sound> atack_sound_effects{};

    std::vector<sf::SoundBuffer> dead_sound_effects_buffers{};
    std::vector<sf::Sound> dead_sound_effects{};

    sf::Music dungeon_music{};
};

}

#endif // CONOR_AUDIO_MANAGER_HPP
