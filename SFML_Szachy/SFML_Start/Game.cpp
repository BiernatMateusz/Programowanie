#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 800), "Chess_game");
    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initChessBoard()
{
    this->chessBoard = new ChessBoard;

}

Game::Game()
{
    this->initWindow();
    this->initChessBoard();
}

Game::~Game()
{
	delete this->window;
    delete this->chessBoard;
}

void Game::updateSfEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        
        this->MousePosition = chessBoard->piecesMov->getMousePos1(window);

        if (chessBoard->OneOfPiecesGrabbed==0)
        {
            chessBoard->piecesMov->GrabbingPiece(chessBoard->Plansza, MousePosition, chessBoard->OneOfPiecesGrabbed,chessBoard->HoldedPiece);
        }
    }
    else 
    { 
        chessBoard->notGrabbed();

        if (chessBoard->HoldedPiece != nullptr)
        {
        chessBoard->piecesMov->newPositionOfPiece(MousePosition, chessBoard->Plansza, chessBoard->HoldedPiece, chessBoard->WhichColorTurn,chessBoard->EnPaisPawn); 
        //PRZENOSZONY PIONEK POWINIEN MIEC GRAFIKE "NA WIERZCHU"

        }
    }

    

}

void Game::update()
{
    this->updateSfEvents();

    
}

void Game::render()
{
    this->window->clear();


    //Render items

    chessBoard->renderBoard(window);
    chessBoard->renderPieces(window, this->MousePosition);
    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();

    }    
}


