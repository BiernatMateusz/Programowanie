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
        
        this->MousePosition = chessBoard->piecesMove()->getMousePos1(window);

        if (chessBoard->OneOfPiecesGrabbedF() == 0)
        {
            chessBoard->piecesMove()->GrabbingPiece(chessBoard->Plansza, MousePosition, chessBoard->OneOfPiecesGrabbedF(), chessBoard->HoldedPieceFF());
        }
    }
    else 
    { 
        chessBoard->notGrabbed();

        if (chessBoard->HoldedPieceFF() != nullptr)
        {
        chessBoard->piecesMove()->newPositionOfPiece(MousePosition, chessBoard->Plansza, chessBoard->HoldedPieceFF(), chessBoard->WhichColorTurnF(), chessBoard->EnPaisPawn);
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

