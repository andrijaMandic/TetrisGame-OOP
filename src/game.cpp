#include "game.h"
#include "playstate.h"

#include <iostream>

Game::Game() : mWindow(sf::VideoMode(650,750), "Tetris"), mGameSpeed(3.0f),
               mGameScore(0)
{
    // Inicijalizacija stanja dolazi ovdje
    //for(std::size_t i = 0; i < GameState::SIZE; ++i){
    //    mAllStates[i] = new GameState(this);
    //}

    mAllStates[GameState::Welcome] = new WelcomeState(this);
    mAllStates[GameState::Playing] = new PlayState(this);
    mAllStates[GameState::Speed] = new SpeedState(this);

    //na pocetku je WelcomeState
    //mpGameState = mAllStates[0];
    setState(GameState::Welcome);
}

Game::~Game()
{
   // Eventualna dealokacija  
    for(std::size_t i = 0; i< GameState::SIZE; ++i){
        delete mAllStates[i];
    }
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::setState(GameState::State st)
{
    mpGameState = mAllStates[st];
    mpGameState->start();
}

sf::RenderWindow * Game::getWindow()
{
    return &mWindow;
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
            mWindow.close();
        }
        else if(event.type ==sf::Event::Resized){
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        }
        else {
            mpGameState->handleEvents(event);
		}
    }
}

void Game::update()
{
    mpGameState->update();
}

void Game::render()
{
     mWindow.clear();
     mpGameState->render();
     mWindow.display();
}
