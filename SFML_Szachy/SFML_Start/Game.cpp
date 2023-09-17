<<<<<<< HEAD
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


=======
#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 800), "Gierka");
    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initSzachownica()
{
    this->szachownica = new Szachownica;
    std::cout << "Mamy nowa szachownice: " << szachownica << std::endl;
}

Game::Game()
{
    this->initWindow();
    this->initSzachownica();
}

Game::~Game()
{
	delete this->window;
    delete this->szachownica;
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
        
        this->MousePosition = szachownica->piecesMov->getMousePos1(window);

        if (szachownica->OneOfPiecesGrabbed==0)
        {
            szachownica->piecesMov->GrabbingPiece(szachownica->Plansza, MousePosition, szachownica->OneOfPiecesGrabbed,szachownica->HoldedPiece);
        }
    }
    else 
    { 
        szachownica->OneOfPiecesGrabbed = 0; 
        szachownica->notGrabbed();

        if (szachownica->HoldedPiece != nullptr)
        {
        szachownica->piecesMov->newPositionOfPiece(MousePosition, szachownica->Plansza, szachownica->HoldedPiece, szachownica->WhichColorTurn,szachownica->EnPaisPawn); 
        //+++CO JEZELI POZA PLANSZA 
        //+++SPRAWDZIC CZY JEST MOZLIWOSC PRZESTAWIENIA TAM FIGURY
        //ZASADY!!
        //PRZENOSZONY PIONEK POWINIEN MIEC GRAFIKE "NA WIERZCHU"
        //+++Klikniecie pionka omija ruch gracza

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

    szachownica->renderBoard(window);
    szachownica->renderPieces(window, this->MousePosition);
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


>>>>>>> 62aa2c46b80bd51f4099328a85205c0098f2123f
