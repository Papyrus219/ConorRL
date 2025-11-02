#include "logic_manager.hpp"
#include "../resorces/resorces_manager.hpp"
#include "../graphics/graphics_manager.hpp"
#include <SFML/Graphics.hpp>

using namespace conor;

void conor::Logic_manager::Loop()
{
    while(renderer->window.isOpen())
    {
        Events();

        renderer->Render();
    }
}

void conor::Logic_manager::Events()
{
    while(const std::optional event = renderer->window.pollEvent() )
    {
        if (event->is<sf::Event::Closed>())
        {
            renderer->window.close();
        }
        else if (auto key_pressed = event->getIf<sf::Event::KeyPressed>())
        {
            sf::Keyboard::Key key = key_pressed->code;
            input_handler->Handle_input(key,game_state);
        }
    }
}

void conor::Logic_manager::onNotify(Event event, std::shared_ptr<Being>& entity)
{
    switch(event)
    {
        case Event::Game_started:
            game_state = Game_state::gameplay;
            break;
        default:
            break;
    }
}
