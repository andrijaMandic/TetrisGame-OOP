#include "gamestate.h"
#include "game.h"
#include <iostream>

// Vaš kod dolazi ovdje.

WelcomeState::WelcomeState(Game *pGame):GameState(pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }

    mText1.setFont(mFont);
    mText2.setFont(mFont);

    mText1.setCharacterSize(45);
    mText2.setCharacterSize(30);


    mText1.setString("Tetris clone by Andrija Mandic");
    mText2.setString("Press any key to continue");

    mText1.setOrigin(mText1.getLocalBounds().width/2,mText1.getLocalBounds().height/2);
    mText2.setOrigin(mText2.getLocalBounds().width/2,mText2.getLocalBounds().height/2);

    mText1.setPosition(325,200);
    mText2.setPosition(325,300);

}

void WelcomeState::handleEvents(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed){
        //bilo sto ako je stisnuto
        mpGame->setState(GameState::Playing);
    }
}

void WelcomeState::update()
{
    //nebi trebalo nista ici
}

void WelcomeState::render()
{
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
}

SpeedState::SpeedState(Game *pGame):GameState(pGame)
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }

    mText0.setFont(mFont);
    mText0.setCharacterSize(30);
    mText0.setString("Score " + std::to_string(mpGame->mGameScore));
    mText0.setOrigin(mText0.getLocalBounds().width/2,mText0.getLocalBounds().height/2);
    mText0.setPosition(325,200);

    mText1.setFont(mFont);
    mText1.setCharacterSize(30);
    mText1.setString("Current speed " + std::to_string(mpGame->mGameSpeed));
    mText1.setOrigin(mText1.getLocalBounds().width/2,mText1.getLocalBounds().height/2);
    mText1.setPosition(325,250);

    mText2.setFont(mFont);
    mText2.setCharacterSize(30);
    mText2.setString("Use keys Up and Down to change the speed");
    mText2.setOrigin(mText2.getLocalBounds().width/2,mText2.getLocalBounds().height/2);
    mText2.setPosition(325,300);

    mText3.setFont(mFont);
    mText3.setCharacterSize(50);
    mText3.setString("Enter to continue");
    mText3.setOrigin(mText3.getLocalBounds().width/2,mText3.getLocalBounds().height/2);
    mText3.setPosition(325,350);
}

void SpeedState::handleEvents(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed){
        switch (event.key.code) {
        case sf::Keyboard::Up:
            mpGame->mGameSpeed += 0.5;
            break;
        case sf::Keyboard::Down:
            if(mpGame->mGameSpeed>0.5)
                mpGame->mGameSpeed -= 0.5;
            break;
        case sf::Keyboard::Return:
            mpGame->setState(GameState::Playing);
            break;
        }
    }
}

void SpeedState::update()
{
    //mozda mozemo dodati da se brze mijenja brzina
    //dodati mClock
    //u handleEvents gledati kad je otpusena tipka, tad restartati mClock
    //ako je vrijeme vece od nekog onda dodati
    mText0.setString("Score = " + std::to_string(mpGame->mGameScore));
    mText1.setString("Current speed = " + std::to_string(mpGame->mGameSpeed));

}

void SpeedState::render()
{
    mpGame->getWindow()->draw(mText0);
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
    mpGame->getWindow()->draw(mText3);
}
