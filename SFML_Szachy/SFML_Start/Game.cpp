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


