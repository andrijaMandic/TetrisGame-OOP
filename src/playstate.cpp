#include "playstate.h"
#include "game.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>

// Vaš kod.


PlayState::PlayState(Game *pGame):GameState(pGame)
{

}

void PlayState::start()
{
    mBoard.clearState();
    mBoard.setSpeed(mpGame->mGameSpeed);
    mpGame->mGameScore = 0;
    mScore.restartScore();
}

void PlayState::handleEvents(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed){
        switch (event.key.code) {
        case sf::Keyboard::Left:
            mBoard.update(1,0,0,0);
            break;
        case sf::Keyboard::Right:
            mBoard.update(0,1,0,0);
            break;
        case sf::Keyboard::Up:
            mBoard.update(0,0,1,0);
            break;
        case sf::Keyboard::Space:
            mBoard.update(0,0,0,1);
            break;
        }
    }
}

void PlayState::update()
{
    if(!mBoard.isGameOver()){
        mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
        mBoard.clearNoLinesCompleted();

        mBoard.update(0,0,0,0);
        mScore.update();
        mpGame->mGameScore = mScore.getScore();

    }
    else{
        //doraditi ovo
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        mpGame->setState(GameState::Speed);
    }
}

void PlayState::render()
{

    mpGame->getWindow()->draw(mBoard);
    mpGame->getWindow()->draw(mScore);
}
