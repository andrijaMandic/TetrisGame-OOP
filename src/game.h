#pragma once
#include <SFML/Graphics.hpp>
#include "gamestate.h"

/* Klasa Game.
 *
 * Klasa ima tri stanja koja drži u polju mAllStates.
 * To su WelcomeState, PlayState i SpeedState.
 */
class Game{
    public:
        Game();
        virtual ~Game();
		void run();
        void setState(GameState::State);
        sf::RenderWindow * getWindow();

	private:
        sf::RenderWindow mWindow;
        GameState * mpGameState;
        std::array<GameState*, GameState::SIZE> mAllStates;
        float mGameSpeed;
        int   mGameScore;

        void processEvents();
        void update();
        void render();

        friend class PlayState;
        friend class SpeedState;
};




