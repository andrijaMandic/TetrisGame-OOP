#pragma once
#include <SFML/Graphics.hpp>

// Doraditi klasu ako je potrebno.

class Score : public sf::Drawable, public sf::Transformable{
public:
    Score();
    void addNoLinesCompleted(int n);
    void update();
    int  getScore() const { return mScore; }
    void restartScore(){ mScore = 0; mTotalLinesCompleted = 0;}
private:
    sf::Font mFont;
    sf::Text mScoreText;
    int mTotalLinesCompleted = 0;
    int mScore = 0;

    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};
