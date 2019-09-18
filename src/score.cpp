#include "score.h"
#include <iostream>

// Vaša implementacija (mala izmjena prema prvoj verziji)

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
    mScoreText.setFont(mFont);
    mScoreText.setCharacterSize(40);
    mScoreText.setString("Score: " + std::to_string(mScore));
    mScoreText.setPosition(440,200);
}

void Score::addNoLinesCompleted(int n)
{
    mTotalLinesCompleted += n;
    //paziti na update mScore
}

void Score::update()
{
    mScore = mTotalLinesCompleted * 10;
    mScoreText.setString("Score: " + std::to_string(mScore));

}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mScoreText);
}
