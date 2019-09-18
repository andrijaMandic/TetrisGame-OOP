#include "board.h"

// Vaš kod dolazi ovdje. Iskopirati iz zadatka Tetris.

Board::Board():mUniformDist(0,6),mRNE(r())
{
    //postavljamo praznu plocu
    clearState();

    //korekcija dimenzija, margina
    mDx = 30.0f;
    mDy = 30.0f;

    //konstruiramo mrezu
    float y = 0.0f;
    for(int i=0; i <= 20; ++i){
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(mLeftMargin, mTopMargin + y);
        line[1].position = sf::Vector2f(mLeftMargin + mWidth, mTopMargin + y);
        mHLines.push_back(line);
        y += mDy;
    }
    for(int i=0; i <= 10; ++i){
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(mLeftMargin + i * mDx, mTopMargin);
        line[1].position = sf::Vector2f(mLeftMargin + i * mDx, mTopMargin + mHeight);
        mVLines.push_back(line);
    }
    //postaviti mPiece
    spawnPiece();
}

Board::~Board()
{

}

void Board::update(bool leftPressed, bool rightPressed, bool upPressed, bool downPressed)
{
    //uvijek prvo provjerimo treba li pasti tetrimino dolje
    if(mPiece.mClock.getElapsedTime() > sf::seconds(mDt)){
        if(movePiece(mPiece.mXposition + 1, mPiece.mYposition)){


            mPiece.mClock.restart();
        }
        else{
            //palo je do kraja
            mNoLinesCompleted = clearLines();
            spawnPiece();
        }
    }
    if(leftPressed){
        movePiece(mPiece.mXposition, mPiece.mYposition - 1);
    }
    //mozemo opet if, ili else if
    //ne dopustamo istovremeno dva, po dogovoru
    else if(rightPressed){
        movePiece(mPiece.mXposition, mPiece.mYposition + 1);
    }
    else if(upPressed){
        rotatePiece();
    }
    else if(downPressed){
        //zapravo space
        while(movePiece(mPiece.mXposition + 1, mPiece.mYposition));
    }
}

void Board::spawnPiece()
{
    //postavljamo ga na sredinu gore
    mPiece.move(0,(mCols + 1) / 2);

    int tip = mUniformDist(mRNE);
    mPiece.mType = static_cast<Tetrimino::Types>(tip);
    mPiece.mRotacija = 0;
    mPiece.mClock.restart();

    if(!mGameOver){
        mGameOver = !checkSpace();
        //placePiece();

    }
    if(mGameOver){
        //ovdje sredujemo da se iscrta dio mPiecea koji je uzrokovao game over

        int y = mPiece.mYposition;

        bool flag = true;

        int k = 0;
        while(k < 3){

            flag = true;
            for(int i = k; i < 3; ++i){
                for(int j = -2; j < 2; ++j){
                    if((Tetrimino::mDijelovi[mPiece.mType][0][i+1][j+2] != 0) && (mGridContent[i-k][y+j]!=EMPTY)){
                        flag = false;
                    }
                }
            }
            if(flag){
                for(int i = k; i < 3; ++i){
                    for(int j = -2; j < 2; ++j){
                        if(Tetrimino::mDijelovi[mPiece.mType][0][i+1][j+2] != 0)
                            mGridContent[i-k][y+j] = mPiece.mType;
                    }
                }
                break;
            }
            ++k;
        }
    }
    else{
        placePiece();
    }
}

void Board::clearState()
{
    //oprez
    for(int i = 0; i < mRows; ++i)
        for(int j = 0; j < mCols; ++j)
            mGridContent[i][j] = EMPTY;

    mGameOver = false;

}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto x : mHLines)
            target.draw(x);
    for(auto x : mVLines)
            target.draw(x);

    sf::RectangleShape celija;
    celija.setSize(sf::Vector2f(28.7,28.7));
    for(int i = 0; i < mRows; ++i){
        for(int j = 0; j < mCols; ++j){
            if(mGridContent[i][j] != EMPTY){
                celija.setFillColor(Tetrimino::mColors[static_cast<Tetrimino::Types>(mGridContent[i][j])]);
                //celija.setOutlineColor(sf::Color::Red);
                celija.setOrigin(1,1);
                celija.setOutlineThickness(1);
                //celija.setPosition(mLeftMargin + i * mDx, mTopMargin + j * mDy);
                celija.setPosition(1.5 + mLeftMargin + j * mDy,2 + mTopMargin + i * mDx);

                target.draw(celija);

            }
        }
    }
}

bool Board::checkSpace()
{
    bool flag = true;
    int x = mPiece.mXposition;
    int y = mPiece.mYposition;
    for(int i = -1; i < 3; ++i){
        for(int j = -2; j < 2; ++j){
            //poziti da ne pomijesamo redove i stupce
            if(0<=(x+i) && (x+i)<mRows && 0<=(y+j) && (y+j)<mCols){
                if((Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i+1][j+2] != 0)
                        && mGridContent[x+i][y+j] != EMPTY ){
                    flag = false;
                }
            }
            //tu smo sad izasli iz granica ploce
            else if(Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i+1][j+2] != 0){
                flag = false;
            }
        }
    }
    return flag;
}

void Board::placePiece()
{
    //pretpostavlja se da je checkSpace vratio true
    int x = mPiece.mXposition;
    int y = mPiece.mYposition;
    for(int i = -1; i < 3; ++i){
        for(int j = -2; j < 2; ++j){
            //svejedno cemo provjeriti da upada u koordinate mreze
            //da mozemo na pocetku iscrtati polovican komad
            if(0<=(x+i) && (x+i)<mRows && 0<=(y+j) && (y+j)<mCols){
                if(Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i+1][j+2] != 0){
                    //tu sad koristimo pretpostavku da ima mjesta za postavljanje
                    mGridContent[x+i][y+j] = mPiece.mType;
                }
            }
        }
    }
}

void Board::removePiece()
{
    int x = mPiece.mXposition;
    int y = mPiece.mYposition;

    //micemo ga iz logicke slike ploce
    for(int i = -1; i < 3; ++i){
        for(int j = -2; j < 2; ++j){
            //poziti da ne pomijesamo redove i stupce
            if(0<=(x+i) && (x+i)<mRows && 0<=(y+j) && (y+j)<mCols){
                if(Tetrimino::mDijelovi[mPiece.mType][mPiece.mRotacija][i+1][j+2] != 0){
                    mGridContent[x+i][y+j] = EMPTY;
                }
            }
        }
    }
}

bool Board::movePiece(int x, int y)
{
    //pamtimo staru poziciju
    int stariX = mPiece.mXposition;
    int stariY = mPiece.mYposition;

    //mijenjamo poziciju tetramina, pa provjeravamo moze li se staviti na plocu

    //prvo ga trebamo obrisati da ne dode do preklapanja
    removePiece();

    //mPiece.mXposition = x;
    //mPiece.mYposition = y;
    mPiece.move(x,y);

    if(checkSpace()){
        //moze se postaviti na novo mjesto
        //postavljamo na novu poziciju
        placePiece();
        return true;
    }
    else{
        //ne mozemo pomaknuti, treba vratiti staru poziciju
        //mPiece.mXposition = stariX;
        //mPiece.mYposition = stariY;
        mPiece.move(stariX,stariY);
        placePiece();
        return false;
    }
}

bool Board::rotatePiece()
{
    //provjerit cemo za sve tri razlicite rotacije
    //prvu po redu ostavljamo, tj prvu koja se moze izvrsiti

    removePiece();
    bool flag = false;

    for(int i = 0; (i < 3) && !flag; ++i){
        mPiece.rotate();
        if(checkSpace()){
            flag = true;
            placePiece();
        }
    }
    if(!flag){
        //cetvrta rotacija vraca na pocetnu rotaciju
        mPiece.rotate();
        placePiece();
    }
    return flag;
}

bool Board::isLineFull(int y) const
{
    bool lineFull = true;
    for(int j = 0; (j < mCols) && lineFull; ++j){
        if(mGridContent[y][j] == -1)
            lineFull = false;
    }
    return lineFull;
}

int Board::clearLines()
{
    bool flag;
    int counter = 0;
    for(int i = mRows - 1; i > -1; ){
        flag = isLineFull(i);
        if(flag){
            //nasli smo popunjen red, treba ga izbrisat
            ++counter;
            //moguca greska s indeksima u polju
            for(int j = i; j > -1; --j){
                for(int z = 0; z < mCols; ++z){
                    if(j != 0) mGridContent[j][z] = mGridContent[j-1][z];
                    else mGridContent[0][z] = EMPTY;
                }
            }
        }
        else --i;
    }
    return counter;
}








