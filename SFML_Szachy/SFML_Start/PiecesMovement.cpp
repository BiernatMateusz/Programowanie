#include "PiecesMovement.h"

PiecesMovement::PiecesMovement()
{
    makeVector2();
}

PiecesMovement::~PiecesMovement()
{

}


sf::Vector2i PiecesMovement::getMousePos1(sf::RenderWindow* window)
{
    sf::Vector2i pos;
    this->position = sf::Mouse::getPosition();
    pos = { this->position.x - window->getPosition().x,this->position.y - window->getPosition().y - 32 };

    return sf::Vector2i{ pos };
}

void PiecesMovement::GrabbingPiece(std::vector<std::vector<Figura*>> board, sf::Vector2i MousePos, bool& GrabbedPiece, Figura* &HoldedPiece)
{
    if (MousePos.x>0 and MousePos.y>0 and MousePos.x < 800 and MousePos.y < 800)
    {
        int conversedMousePosY =   - MousePos.y + 800;
        if (board[MousePos.x/100][conversedMousePosY /100]!=nullptr)
        {
          board[MousePos.x / 100][conversedMousePosY / 100]->PieceGrabbed(true);
          HoldedPiece = board[MousePos.x / 100][conversedMousePosY / 100];
          HoldedPiece->posX = MousePos.x / 100;
          HoldedPiece->posY = conversedMousePosY / 100;
        }
    }
    GrabbedPiece = 1;

}

void PiecesMovement::newPositionOfPiece(sf::Vector2i mousePos, std::vector<std::vector<Figura*>>& Plansza, Figura*& HoldedPiece, bool& WhichColorTurn, Figura& EnPaiPawn)
{
    

    if (mousePos.x > 0 && mousePos.x < 800 && mousePos.y>0 && mousePos.y < 800)
    {
        mousePos.x = mousePos.x / 100;
        mousePos.y = (-mousePos.y + 800) / 100;

        for (int vertical = 0; vertical < 8; ++vertical)
            for (int horizontal = 0; horizontal < 8; ++horizontal)
                if (Plansza[horizontal][vertical] != nullptr)
                    if (Plansza[horizontal][vertical] == HoldedPiece && Plansza[horizontal][vertical]->kolorGet() != WhichColorTurn)
                        if ((this->*EveryPieceMovement[HoldedPiece->numberOfPiece()])(Plansza, HoldedPiece,mousePos, EnPaiPawn)) 
                            if ((Plansza[mousePos.x][mousePos.y] != 0 && HoldedPiece->kolorGet() != Plansza[mousePos.x][mousePos.y]->kolorGet()) or Plansza[mousePos.x][mousePos.y] == nullptr)
                            {
                                //Remember previous position

                                std::vector < std::vector < Figura* >> PrevPlansza;
                                PrevPlansza = Plansza;
                                std::string Piece = HoldedPiece->nazwaFigury();

                                Plansza[horizontal][vertical] = nullptr;
                                Plansza[mousePos.x][mousePos.y] = HoldedPiece;


                                //PrevPos
                                sf::Vector2i mouseP;
                                mouseP.x = HoldedPiece->posX;
                                mouseP.y = HoldedPiece->posY;

                                WhichColorTurn = not WhichColorTurn; //Player turn
                                Plansza[mousePos.x][mousePos.y]->moved = true;
                                bool ColorTurn = not WhichColorTurn;


                                Plansza[mousePos.x][mousePos.y]->posX = mousePos.x;
                                Plansza[mousePos.x][mousePos.y]->posY = mousePos.y;
                                if (LookingForCheck(Plansza, ColorTurn, EnPaiPawn))
                                {
                                    Plansza = PrevPlansza;
                                    Plansza[mouseP.x][mouseP.y]->posX = mouseP.x;
                                    Plansza[mouseP.x][mouseP.y]->posY = mouseP.y;
                                    HoldedPiece->nazwaFigury() =Piece;

                                    WhichColorTurn = not WhichColorTurn; //Player turn


                                    bool ColorTurn = not WhichColorTurn;
                                }
                            }

    }
    HoldedPiece = nullptr;

}

bool PiecesMovement::pawnMove(std::vector<std::vector<Figura*>> &Plansza, Figura* &HoldedPiece,sf::Vector2i mousePos, Figura& EnPaisPawn)
{
    //Mozliwosc ruchu jezeli:
    //
    //+++Nic nie stoi przed nim to 1 do przodu lub 2 - jezeli stoi na "swojej" 2 linii
    //+++Po ukosie jezeli bicie 
    //+++Po ukosie en paisant (bicie w przelocie)
    //+__Hetman na stale    Jezeli dojezdza do ostatniej linii to mo¿liwoœæ zmiany na 1 z 4 figur - kon goniec wieza hetman 
    bool availableMove = false;

    if (HoldedPiece->kolorGet() == 0) // bialy
    {
        if ((HoldedPiece->posY == 1 and (mousePos.y == 2 or mousePos.y == 3) or mousePos.y - HoldedPiece->posY == 1))
        {
            if (mousePos.x == HoldedPiece->posX and Plansza[mousePos.x][mousePos.y] == nullptr)
            {
                availableMove = true;
                if (mousePos.y - HoldedPiece->posY == 2)
                {
                    EnPaisPawn = *HoldedPiece;
                }
                else
                {
                    EnPaisPawn.posX = 10;
                    EnPaisPawn.posY = 10;

                }
            }
            if (HoldedPiece->posX >= 0 and HoldedPiece->posY < 8 and abs(mousePos.x - HoldedPiece->posX) == 1)
            {
                if (Plansza[mousePos.x][mousePos.y] != nullptr) {
                    if (Plansza[mousePos.x][mousePos.y]->kolorGet() == 1 and mousePos.x != HoldedPiece->posX and Plansza[mousePos.x][mousePos.y] != nullptr)
                    {
                        availableMove = true;
                    }
                }
                else if (Plansza[mousePos.x][mousePos.y] == nullptr and EnPaisPawn.posX == mousePos.x and EnPaisPawn.posY - 1 == mousePos.y)
                {
                    availableMove = true;
                    Plansza[mousePos.x][mousePos.y - 1] = nullptr;
                }
            }

        }
        if (availableMove)
            if (mousePos.y == 7)
                HoldedPiece->Nazwa = "H";
    }

    if (HoldedPiece->kolorGet() == 1) // czarny
    {
        if ((HoldedPiece->posY == 6 and (mousePos.y == 5 or mousePos.y == 4) or mousePos.y - HoldedPiece->posY == -1))
        {
            if (mousePos.x == HoldedPiece->posX and Plansza[mousePos.x][mousePos.y] == nullptr)
            {
                //std::cout << "Biore czarnego pionka z: " << HoldedPiece->posX << " " << HoldedPiece->posY << " na pozycje: " << mousePos.x << " " << mousePos.y << std::endl;
                availableMove = true;
                if (mousePos.y - HoldedPiece->posY == -2)
                {
                    EnPaisPawn = *HoldedPiece;
                }
                else
                {
                    EnPaisPawn.posX = 10;
                    EnPaisPawn.posY = 10;

                }
            }
            if (HoldedPiece->posX >= 0 and HoldedPiece->posY < 8 and abs(mousePos.x - HoldedPiece->posX) == 1)
            {
                if (Plansza[mousePos.x][mousePos.y] != nullptr)
                {
                    if (Plansza[mousePos.x][mousePos.y]->kolorGet() == 0 and mousePos.x != HoldedPiece->posX)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[mousePos.x][mousePos.y] == nullptr and EnPaisPawn.posX == mousePos.x and EnPaisPawn.posY + 1 == mousePos.y)
                    {
                        availableMove = true;
                        Plansza[mousePos.x][mousePos.y + 1] = nullptr;
                    }
                }
            }

        }
        if (availableMove)
            if (mousePos.y == 0)
                HoldedPiece->Nazwa = "H";

    }
    std::cout << "Sprawdzam pionka" << mousePos.x << " "<< mousePos.y << std::endl;
    return availableMove;
}

bool PiecesMovement::kingMove(std::vector<std::vector<Figura*>> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn)
{
    bool availableMove = false;

    //Mozliwosc ruchu jezeli:
    //
    //+++O 1 pole jezeli nie podchodzi pod szacha
    //+++Wszystko co sie kreci wokol mata do zrobienia
    //+++Roszada
    if (abs(mousePos.x - HoldedPiece->posX) == 1 or abs(mousePos.y - HoldedPiece->posY) == 1)
        if (Plansza[mousePos.x][mousePos.y] == nullptr)
        {
            availableMove = 1;
        }
        else if (Plansza[mousePos.x][mousePos.y]->kolorGet() != HoldedPiece->kolorGet())
            availableMove = 1;

    if (Plansza[7][HoldedPiece->posY] != nullptr) {
        if (HoldedPiece->moved == 0 and Plansza[7][HoldedPiece->posY]->moved == 0) //Roszada biala
        {
            if (mousePos.x - HoldedPiece->posX == 2 and Plansza[mousePos.x][mousePos.y] == nullptr and Plansza[mousePos.x - 1][mousePos.y] == nullptr)
            {
                availableMove = 1;
                if (EnPaisPawn.WhiteCheck == 0)
                {
                    Plansza[mousePos.x - 1][mousePos.y] = Plansza[7][HoldedPiece->posY];
                    Plansza[7][HoldedPiece->posY] = nullptr;
                }
            }
        }
    }
    if (Plansza[0][HoldedPiece->posY] != nullptr) {
        if (HoldedPiece->moved == 0 and Plansza[0][HoldedPiece->posY]->moved == 0) //Roszada czarna
        {
            if (mousePos.x - HoldedPiece->posX == -2 and Plansza[mousePos.x][mousePos.y] == nullptr and Plansza[mousePos.x - 1][mousePos.y] == nullptr and Plansza[mousePos.x + 1][mousePos.y] == nullptr)
            {
                availableMove = 1;
                if (EnPaisPawn.BlackCheck == 0)
                {
                    Plansza[mousePos.x + 1][mousePos.y] = Plansza[0][HoldedPiece->posY];
                    Plansza[0][HoldedPiece->posY] = nullptr;
                }
            }
        }
    }

    std::cout << "Sprawdzam krola" << std::endl;
    return availableMove;
}

bool PiecesMovement::queenMove(std::vector<std::vector<Figura*>> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn)
{   
    bool availableMove = false;

    //Mozliwosc ruchu jezeli:
    //
    //+++Jak wieza i jak goniec razem wziete
    if (abs(mousePos.x - HoldedPiece->posX) == abs(mousePos.y - HoldedPiece->posY))
    {
        if (mousePos.x - HoldedPiece->posX == mousePos.y - HoldedPiece->posY and mousePos.y - HoldedPiece->posY > 0) //up right
        {
            std::cout << "Sprawdzam: " << mousePos.x - HoldedPiece->posX << " i " << mousePos.y - HoldedPiece->posY << std::endl;

            for (int SquareX = HoldedPiece->posX + 1, SquareY = HoldedPiece->posY + 1; SquareX < mousePos.x + 1; ++SquareX, ++SquareY)
            {
                if (SquareX < 8 and SquareY < 8 and SquareX >= 0 and SquareY >= 0)
                    if (Plansza[SquareX][SquareY] == nullptr)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[SquareX][SquareY]->kolorGet() != HoldedPiece->kolorGet())
                    {
                        availableMove = true;
                    }
                    else
                    {
                        SquareX = 10;
                        availableMove = false;
                    }

            }
        }

        if (HoldedPiece->posX - mousePos.x == mousePos.y - HoldedPiece->posY and mousePos.y - HoldedPiece->posY > 0) //up left
        {

            std::cout << "Sprawdzam: " << HoldedPiece->posX - 1 << " i " << mousePos.x << std::endl;

            for (int SquareX = HoldedPiece->posX - 1, SquareY = HoldedPiece->posY + 1; SquareX >= mousePos.x; --SquareX, ++SquareY)
            {
                if (SquareX < 8 and SquareY < 8 and SquareX >= 0 and SquareY >= 0)
                    if (Plansza[SquareX][SquareY] == nullptr)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[SquareX][SquareY]->kolorGet() != HoldedPiece->kolorGet())
                    {
                        availableMove = true;
                    }
                    else
                    {
                        SquareX = 0;
                        availableMove = false;
                    }

            }
        }

        if (HoldedPiece->posX - mousePos.x == HoldedPiece->posY - mousePos.y and mousePos.y - HoldedPiece->posY < 0) //down left
        {

            std::cout << "Sprawdzam3: " << HoldedPiece->posX - 1 << " i " << mousePos.y << std::endl;

            for (int SquareX = HoldedPiece->posX - 1, SquareY = HoldedPiece->posY - 1; SquareX >= mousePos.x; --SquareX, --SquareY)
            {
                if (SquareX < 8 and SquareY < 8 and SquareX >= 0 and SquareY >= 0)
                    if (Plansza[SquareX][SquareY] == nullptr)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[SquareX][SquareY]->kolorGet() != HoldedPiece->kolorGet())
                    {
                        availableMove = true;
                    }
                    else
                    {
                        SquareX = 0;
                        availableMove = false;
                    }

            }
        }

        if (mousePos.x - HoldedPiece->posX == HoldedPiece->posY - mousePos.y and mousePos.y - HoldedPiece->posY < 0) //down right
        {
            std::cout << "Sprawdzam4: " << mousePos.x - HoldedPiece->posX << " i " << mousePos.y - HoldedPiece->posY << std::endl;

            for (int SquareX = HoldedPiece->posX + 1, SquareY = HoldedPiece->posY - 1; SquareX < mousePos.x + 1; ++SquareX, --SquareY)
            {
                if (SquareX < 8 and SquareY < 8 and SquareX >= 0 and SquareY >= 0)
                    if (Plansza[SquareX][SquareY] == nullptr)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[SquareX][SquareY]->kolorGet() != HoldedPiece->kolorGet())
                    {
                        availableMove = true;
                    }
                    else
                    {
                        SquareX = 10;
                        availableMove = false;
                    }

            }
        }

    }

    else if (mousePos.x == HoldedPiece->posX or mousePos.y == HoldedPiece->posY)
    {
        if (mousePos.x == HoldedPiece->posX && mousePos.y > HoldedPiece->posY) // up movement
        {
            for (int Square = HoldedPiece->posY; Square < mousePos.y; ++Square)
            {
                if ((Plansza[mousePos.x][Square + 1] == nullptr) or (mousePos.y == Square + 1 && Plansza[mousePos.x][Square + 1] != nullptr and Plansza[mousePos.x][Square + 1]->kolorGet() != HoldedPiece->kolorGet()))
                {
                    availableMove = true;
                }
                else
                {
                    availableMove = false;
                    Square = mousePos.y + 1;
                }

            }
        }

        if (mousePos.x == HoldedPiece->posX && mousePos.y < HoldedPiece->posY) // down movement
        {
            for (int Square = HoldedPiece->posY; Square > mousePos.y; --Square)
            {
                if ((Plansza[mousePos.x][Square - 1] == nullptr) or (mousePos.y == Square - 1 && Plansza[mousePos.x][Square - 1] != nullptr and Plansza[mousePos.x][Square - 1]->kolorGet() != HoldedPiece->kolorGet()))
                {
                    availableMove = true;
                }
                else
                {
                    availableMove = false;
                    Square = mousePos.y - 1;
                }

            }
        }

        if (mousePos.y == HoldedPiece->posY && mousePos.x > HoldedPiece->posX) // right movement
        {
            for (int Square = HoldedPiece->posX; Square < mousePos.x; ++Square)
            {
                if ((Plansza[Square + 1][mousePos.y] == nullptr) or (mousePos.x == Square + 1 && Plansza[Square + 1][mousePos.y] != nullptr and Plansza[Square + 1][mousePos.y]->kolorGet() != HoldedPiece->kolorGet()))
                {
                    availableMove = true;
                }
                else
                {
                    availableMove = false;
                    Square = mousePos.x + 1;
                }

            }
        }

        if (mousePos.y == HoldedPiece->posY && mousePos.x < HoldedPiece->posX) // left movement
        {
            for (int Square = HoldedPiece->posX; Square > mousePos.x; --Square)
            {
                if ((Plansza[Square - 1][mousePos.y] == nullptr) or (mousePos.x == Square - 1 && Plansza[Square - 1][mousePos.y] != nullptr and Plansza[Square - 1][mousePos.y]->kolorGet() != HoldedPiece->kolorGet()))
                {
                    availableMove = true;
                }
                else
                {
                    availableMove = false;
                    Square = mousePos.x - 1;
                }

            }
        }

    }

    std::cout << "Sprawdzam hetmana" << std::endl;
    return availableMove;
}

bool PiecesMovement::knightMove(std::vector<std::vector<Figura*>> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn)
{   
    bool availableMove = false;

   
    //Mozliwosc ruchu jezeli:
    //
    //+++Po L - 2 kwadraty w któr¹œ strone i nastepie 1 w prostopad³ym kierunku
    if ((abs(mousePos.x - HoldedPiece->posX) == 2 and abs(mousePos.y - HoldedPiece->posY) == 1) or (abs(mousePos.x - HoldedPiece->posX) == 1 and abs(mousePos.y - HoldedPiece->posY) == 2))
        availableMove = true;

    std::cout << "Sprawdzam skoczka" << std::endl;
    return availableMove;
}

bool PiecesMovement::bishopMove(std::vector<std::vector<Figura*>> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn)
{   
    bool availableMove = false;

    //Mozliwosc ruchu jezeli:
    //
    //++Po skosie do najblizszej swojej figury - lub do najblizszej figury wroga zbijajac j¹
    if (abs(mousePos.x - HoldedPiece->posX) == abs(mousePos.y - HoldedPiece->posY))
    {
        if (mousePos.x - HoldedPiece->posX == mousePos.y - HoldedPiece->posY and mousePos.y - HoldedPiece->posY > 0) //up right
        {
            std::cout << "Sprawdzam: " << mousePos.x - HoldedPiece->posX << " i " << mousePos.y - HoldedPiece->posY << std::endl;
            
            for (int SquareX = HoldedPiece->posX+1, SquareY = HoldedPiece->posY+1; SquareX < mousePos.x+1; ++SquareX, ++SquareY)
            {
                if (SquareX < 8 and SquareY < 8 and SquareX>=0 and SquareY>=0)
                    if (Plansza[SquareX][SquareY]==nullptr)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[SquareX][SquareY]->kolorGet() != HoldedPiece->kolorGet())
                    {
                        availableMove = true;
                    }
                    else    
                    {
                        SquareX = 10;
                        availableMove = false;
                    }

            }
        }

        if (HoldedPiece->posX - mousePos.x == mousePos.y - HoldedPiece->posY and mousePos.y - HoldedPiece->posY > 0) //up left
        {

            std::cout << "Sprawdzam: " << HoldedPiece->posX - 1 << " i " << mousePos.x << std::endl;

            for (int SquareX = HoldedPiece->posX -1, SquareY = HoldedPiece->posY + 1; SquareX >= mousePos.x ; --SquareX, ++SquareY)
            {
                if (SquareX < 8 and SquareY < 8 and SquareX>=0 and SquareY>=0)
                    if (Plansza[SquareX][SquareY] == nullptr)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[SquareX][SquareY]->kolorGet() != HoldedPiece->kolorGet())
                    {
                        availableMove = true;
                    }
                    else
                    {
                        SquareX = 0;
                        availableMove = false;
                    }

            }
        }

        if (HoldedPiece->posX - mousePos.x ==  HoldedPiece->posY - mousePos.y and mousePos.y - HoldedPiece->posY < 0) //down left
        {

            std::cout << "Sprawdzam3: " << HoldedPiece->posX - 1 << " i " << mousePos.y << std::endl;

            for (int SquareX = HoldedPiece->posX - 1, SquareY = HoldedPiece->posY - 1; SquareX >= mousePos.x; --SquareX, --SquareY)
            {
                if (SquareX < 8 and SquareY < 8 and SquareX >= 0 and SquareY >= 0)
                    if (Plansza[SquareX][SquareY] == nullptr)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[SquareX][SquareY]->kolorGet() != HoldedPiece->kolorGet())
                    {
                        availableMove = true;
                    }
                    else
                    {
                        SquareX = 0;
                        availableMove = false;
                    }

            }
        }

        if (mousePos.x - HoldedPiece->posX == HoldedPiece->posY - mousePos.y and mousePos.y - HoldedPiece->posY < 0) //down right
        {
            std::cout << "Sprawdzam4: " << mousePos.x - HoldedPiece->posX << " i " << mousePos.y - HoldedPiece->posY << std::endl;

            for (int SquareX = HoldedPiece->posX + 1, SquareY = HoldedPiece->posY - 1; SquareX < mousePos.x + 1; ++SquareX, --SquareY)
            {
                if (SquareX < 8 and SquareY < 8 and SquareX >= 0 and SquareY >= 0)
                    if (Plansza[SquareX][SquareY] == nullptr)
                    {
                        availableMove = true;
                    }
                    else if (Plansza[SquareX][SquareY]->kolorGet() != HoldedPiece->kolorGet())
                    {
                        availableMove = true;
                    }
                    else
                    {
                        SquareX = 10;
                        availableMove = false;
                    }

            }
        }

    }

    std::cout << "Sprawdzam gonca" << std::endl;
    return availableMove;
}

bool PiecesMovement::rookMove(std::vector<std::vector<Figura*>> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn)
{   
    bool availableMove = false;

    //Mozliwosc ruchu jezeli:
    //
    //+++Po liniach do najblizszej swojej figury - lub do najblizszej figury wroga zbijajac j¹
    //+++Roszada
    if (mousePos.x == HoldedPiece->posX or mousePos.y == HoldedPiece->posY)
    {
        if (mousePos.x == HoldedPiece->posX && mousePos.y > HoldedPiece->posY) // up movement
        {
            for (int Square = HoldedPiece->posY; Square < mousePos.y; ++Square)
            {
                if ((Plansza[mousePos.x][Square + 1] == nullptr) or (mousePos.y == Square+1 && Plansza[mousePos.x][Square + 1] != nullptr and Plansza[mousePos.x][Square + 1]->kolorGet() != HoldedPiece->kolorGet()))
                {
                    availableMove = true;
                }
                else
                {
                    availableMove = false;
                    Square = mousePos.y+1; 
                }

            }
        }

        if (mousePos.x == HoldedPiece->posX && mousePos.y < HoldedPiece->posY) // down movement
        {
            for (int Square = HoldedPiece->posY; Square > mousePos.y; --Square)
            {
                if ((Plansza[mousePos.x][Square-1] == nullptr) or (mousePos.y == Square-1 && Plansza[mousePos.x][Square-1] != nullptr and Plansza[mousePos.x][Square-1]->kolorGet() != HoldedPiece->kolorGet()))
                {
                    availableMove = true;
                }
                else
                {
                    availableMove = false;
                    Square = mousePos.y -1 ;
                }

            }
        }

        if (mousePos.y == HoldedPiece->posY && mousePos.x > HoldedPiece->posX) // right movement
        {
            for (int Square = HoldedPiece->posX; Square < mousePos.x; ++Square)
            {
                if ((Plansza[Square+1][mousePos.y] == nullptr) or (mousePos.x == Square + 1 && Plansza[Square+1][mousePos.y] != nullptr and Plansza[Square+1][mousePos.y]->kolorGet() != HoldedPiece->kolorGet()))
                {
                    availableMove = true;
                }
                else
                {
                    availableMove = false;
                    Square = mousePos.x + 1;
                }

            }
        }

        if (mousePos.y == HoldedPiece->posY && mousePos.x < HoldedPiece->posX) // left movement
        {
            for (int Square = HoldedPiece->posX; Square > mousePos.x; --Square)
            {
                if ((Plansza[Square - 1][mousePos.y] == nullptr) or (mousePos.x == Square - 1 && Plansza[Square-1][mousePos.y] != nullptr and Plansza[Square-1][mousePos.y]->kolorGet() != HoldedPiece->kolorGet()))
                {
                    availableMove = true;
                }
                else
                {
                    availableMove = false;
                    Square = mousePos.x - 1;
                }

            }
        }
       
    }

    std::cout << "Sprawdzam wieze" << std::endl;
    return availableMove;
}

void PiecesMovement::makeVector2()
{
    this->EveryPieceMovement.push_back(&PiecesMovement::pawnMove);       // [0]
    this->EveryPieceMovement.push_back(&PiecesMovement::kingMove);       // [1]
    this->EveryPieceMovement.push_back(&PiecesMovement::queenMove);      // [2]
    this->EveryPieceMovement.push_back(&PiecesMovement::knightMove);     // [3]
    this->EveryPieceMovement.push_back(&PiecesMovement::bishopMove);     // [4]
    this->EveryPieceMovement.push_back(&PiecesMovement::rookMove);       // [5]
}

bool PiecesMovement::LookingForCheck(std::vector<std::vector<Figura*>>& Plansza, bool& WhichColorTurn, Figura& EnPaiPawn)
{
    
    bool legalMove = true;
    //Lets imagine that king is looking for:
    //Rooks on lines
    //Bishop on diagonal
    //Queen on both
    //Pawn on diagonal -1 / +1
    //Knight on L
    //King on close square

    //If something is true then move in unavailable -> move must be undone
    Figura WhiteK, BlackK;

    for (int vertically=0;vertically<8;++vertically)
        for (int horizontally=0;horizontally<8;++horizontally)
            if (Plansza[horizontally][vertically]!=nullptr)
                if (Plansza[horizontally][vertically]->nazwaFigury()=="K")
                    if (Plansza[horizontally][vertically]->kolorGet() == 0)
                    {
                        WhiteK = *Plansza[horizontally][vertically];
                        //std::cout << " Bialy krolewicz: " << Plansza[horizontally][vertically]->posX << " " << Plansza[horizontally][vertically]->posY << std::endl;
                    }
                    else
                    {
                        BlackK = *Plansza[horizontally][vertically];
                        //std::cout << " Czarny krolewicz: " << Plansza[horizontally][vertically]->posX << " " << Plansza[horizontally][vertically]->posY << std::endl;
                    }


    std::cout <<" Bialy krolewicz: " << WhiteK.posX << " " << WhiteK.posY << std::endl;
    std::cout << " Czarny krolewicz: " << BlackK.posX << " " << BlackK.posY << std::endl;


    //King cant face each other
    
    if ((abs(WhiteK.posX - BlackK.posX) == 1 and abs(WhiteK.posY - BlackK.posY) == 1) or (abs(WhiteK.posX - BlackK.posX) == 0 and abs(WhiteK.posY - BlackK.posY) == 1) or (abs(WhiteK.posX - BlackK.posX) == 1 and abs(WhiteK.posY - BlackK.posY) == 0))
    {
        legalMove = false;
        std::cout << "Nielegal" << std::endl;
    }

    //Facing pawn
    if (WhichColorTurn == 1) //Black pawn check
    {
        if (WhiteK.posX + 1 < 8)
        {
            if (WhiteK.posX - 1 >= 0 and WhiteK.posX + 1 < 8)
            {
                if (Plansza[WhiteK.posX - 1][WhiteK.posY + 1] != nullptr)
                {
                    if ((Plansza[WhiteK.posX - 1][WhiteK.posY + 1]->nazwaFigury() == "P" and Plansza[WhiteK.posX - 1][WhiteK.posY + 1]->kolorGet() == 1))
                    {
                        legalMove = false;
                        std::cout << "Nielegal" << std::endl;
                    }
                }
                else if (Plansza[WhiteK.posX + 1][WhiteK.posY + 1] != nullptr)
                {
                    if ((Plansza[WhiteK.posX + 1][WhiteK.posY + 1]->nazwaFigury() == "P" and Plansza[WhiteK.posX + 1][WhiteK.posY + 1]->kolorGet() == 1))
                    {
                        legalMove = false;
                        std::cout << "Nielegal" << std::endl;
                    }
                }
            }
        }
    }
    //White pawn check
    if (WhichColorTurn == 0 ) 
    {
        if (BlackK.posY - 1 >= 0)
        {
            if (BlackK.posX - 1 >= 0 and BlackK.posX + 1 < 8)
            {
                if (Plansza[BlackK.posX - 1][BlackK.posY - 1] != nullptr)
                {
                    if ((Plansza[BlackK.posX - 1][BlackK.posY - 1]->nazwaFigury() == "P" and Plansza[BlackK.posX - 1][BlackK.posY - 1]->kolorGet() == 0))
                    {
                        legalMove = false;
                        std::cout << "Nielegal" << std::endl;
                    }
                }
                else if (Plansza[BlackK.posX + 1][BlackK.posY - 1] != nullptr)
                {
                    if ((Plansza[BlackK.posX + 1][BlackK.posY - 1]->nazwaFigury() == "P" and Plansza[BlackK.posX + 1][BlackK.posY - 1]->kolorGet() == 0))
                    {
                        legalMove = false;
                        std::cout << "Nielegal" << std::endl;
                    }
                }
            }
        }
    }
    //Black horse check
    if (WhichColorTurn == 1) 
    {
            if (WhiteK.posX > 0 and WhiteK.posX < 8 and WhiteK.posY > 1 and WhiteK.posY < 8)
            if (Plansza[WhiteK.posX-1][WhiteK.posY-2]!=nullptr)
            {
                if ((Plansza[WhiteK.posX - 1][WhiteK.posY -2]->nazwaFigury() == "S" and Plansza[WhiteK.posX - 1][WhiteK.posY -2]->kolorGet() == 1))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
            if (WhiteK.posX > 1 and WhiteK.posX < 8 and WhiteK.posY > 0 and WhiteK.posY < 8)
            if (Plansza[WhiteK.posX - 2][WhiteK.posY - 1] != nullptr)
            {
                if ((Plansza[WhiteK.posX - 2][WhiteK.posY - 1]->nazwaFigury() == "S" and Plansza[WhiteK.posX - 2][WhiteK.posY - 1]->kolorGet() == 1))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
            if (WhiteK.posX > 0 and WhiteK.posX < 8 and WhiteK.posY >=0 and WhiteK.posY < 6)
            if (Plansza[WhiteK.posX - 1][WhiteK.posY + 2] != nullptr)
            {
                if ((Plansza[WhiteK.posX - 1][WhiteK.posY + 2]->nazwaFigury() == "S" and Plansza[WhiteK.posX - 1][WhiteK.posY + 2]->kolorGet() == 1))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
            if (WhiteK.posX >= 0 and WhiteK.posX < 6 and WhiteK.posY > 0 and WhiteK.posY < 8)
            if (Plansza[WhiteK.posX + 2][WhiteK.posY - 1] != nullptr)
            {
                if ((Plansza[WhiteK.posX + 2][WhiteK.posY - 1]->nazwaFigury() == "S" and Plansza[WhiteK.posX + 2][WhiteK.posY - 1]->kolorGet() == 1))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
            if (WhiteK.posX >= 0 and WhiteK.posX < 7 and WhiteK.posY > 1 and WhiteK.posY < 8)
            if (Plansza[WhiteK.posX + 1][WhiteK.posY - 2] != nullptr)
            {
                if ((Plansza[WhiteK.posX + 1][WhiteK.posY - 2]->nazwaFigury() == "S" and Plansza[WhiteK.posX + 1][WhiteK.posY - 2]->kolorGet() == 1))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
            if (WhiteK.posX > 1 and WhiteK.posX < 8 and WhiteK.posY >= 0 and WhiteK.posY < 7)
            if (Plansza[WhiteK.posX - 2][WhiteK.posY + 1] != nullptr)
            {
                if ((Plansza[WhiteK.posX - 2][WhiteK.posY + 1]->nazwaFigury() == "S" and Plansza[WhiteK.posX - 2][WhiteK.posY + 1]->kolorGet() == 1))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
            if (WhiteK.posX >= 0 and WhiteK.posX < 7 and WhiteK.posY >= 0 and WhiteK.posY < 6)
            if (Plansza[WhiteK.posX + 1][WhiteK.posY + 2] != nullptr)
            {
                if ((Plansza[WhiteK.posX + 1][WhiteK.posY + 2]->nazwaFigury() == "S" and Plansza[WhiteK.posX + 1][WhiteK.posY + 2]->kolorGet() == 1))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
            if (WhiteK.posX >= 0 and WhiteK.posX < 6 and WhiteK.posY >= 0 and WhiteK.posY < 7)
            if (Plansza[WhiteK.posX + 2][WhiteK.posY + 1] != nullptr)
            {
                if ((Plansza[WhiteK.posX + 2][WhiteK.posY + 1]->nazwaFigury() == "S" and Plansza[WhiteK.posX + 2][WhiteK.posY + 1]->kolorGet() == 1))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }


        
    }
    //White horse check
    if (WhichColorTurn == 0) 
    {
        if (BlackK.posX > 0 and BlackK.posX < 8 and BlackK.posY > 1 and BlackK.posY < 8)
            if (Plansza[BlackK.posX - 1][BlackK.posY - 2] != nullptr)
            {
                if ((Plansza[BlackK.posX - 1][BlackK.posY - 2]->nazwaFigury() == "S" and Plansza[BlackK.posX - 1][BlackK.posY - 2]->kolorGet() == 0))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
        if (BlackK.posX > 1 and BlackK.posX < 8 and BlackK.posY > 0 and BlackK.posY < 8)
            if (Plansza[BlackK.posX - 2][BlackK.posY - 1] != nullptr)
            {
                if ((Plansza[BlackK.posX - 2][BlackK.posY - 1]->nazwaFigury() == "S" and Plansza[BlackK.posX - 2][BlackK.posY - 1]->kolorGet() == 0))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
        if (BlackK.posX > 0 and BlackK.posX < 8 and BlackK.posY >= 0 and BlackK.posY < 6)
            if (Plansza[BlackK.posX - 1][BlackK.posY + 2] != nullptr)
            {
                if ((Plansza[BlackK.posX - 1][BlackK.posY + 2]->nazwaFigury() == "S" and Plansza[BlackK.posX - 1][BlackK.posY + 2]->kolorGet() == 0))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
        if (BlackK.posX >= 0 and BlackK.posX < 6 and BlackK.posY > 0 and BlackK.posY < 8)
            if (Plansza[BlackK.posX + 2][BlackK.posY - 1] != nullptr)
            {
                if ((Plansza[BlackK.posX + 2][BlackK.posY - 1]->nazwaFigury() == "S" and Plansza[BlackK.posX + 2][BlackK.posY - 1]->kolorGet() == 0))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
        if (BlackK.posX >= 0 and BlackK.posX < 7 and BlackK.posY > 1 and BlackK.posY < 8)
            if (Plansza[BlackK.posX + 1][BlackK.posY - 2] != nullptr)
            {
                if ((Plansza[BlackK.posX + 1][BlackK.posY - 2]->nazwaFigury() == "S" and Plansza[BlackK.posX + 1][BlackK.posY - 2]->kolorGet() == 0))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
        if (BlackK.posX > 1 and BlackK.posX < 8 and BlackK.posY >= 0 and BlackK.posY < 7)
            if (Plansza[BlackK.posX - 2][BlackK.posY + 1] != nullptr)
            {
                if ((Plansza[BlackK.posX - 2][BlackK.posY + 1]->nazwaFigury() == "S" and Plansza[BlackK.posX - 2][BlackK.posY + 1]->kolorGet() == 0))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
        if (BlackK.posX >= 0 and BlackK.posX < 7 and BlackK.posY >= 0 and BlackK.posY < 6)
            if (Plansza[BlackK.posX + 1][BlackK.posY + 2] != nullptr)
            {
                if ((Plansza[BlackK.posX + 1][BlackK.posY + 2]->nazwaFigury() == "S" and Plansza[BlackK.posX + 1][BlackK.posY + 2]->kolorGet() == 0))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }
        if (BlackK.posX >= 0 and BlackK.posX < 6 and BlackK.posY >= 0 and BlackK.posY < 7)
            if (Plansza[BlackK.posX + 2][BlackK.posY + 1] != nullptr)
            {
                if ((Plansza[BlackK.posX + 2][BlackK.posY + 1]->nazwaFigury() == "S" and Plansza[BlackK.posX + 2][BlackK.posY + 1]->kolorGet() == 0))
                {
                    legalMove = false;
                    std::cout << "Nielegal" << std::endl;
                }
            }



    }
    
    //Black rook/queen (rook like) check
    
    if (WhichColorTurn==1)
    {
        //UP
        for (int Square = WhiteK.posY+1; Square < 8; ++Square)
        {
            if (Plansza[WhiteK.posX][Square] != nullptr)
            {
                //std::cout << "Sprawdzam nr:  " << Square << std::endl;
                
                if (Plansza[WhiteK.posX][Square]->kolorGet() == 1 and (Plansza[WhiteK.posX][Square]->nazwaFigury() == "W" or (Plansza[WhiteK.posX][Square]->nazwaFigury() == "H")))
                {
                    //std::cout << "Widze czarnego:  " << Plansza[WhiteK.posX][Square]->posX << "  " << Plansza[WhiteK.posX][Square]->posY <<" figura to: " << Plansza[WhiteK.posX][Square]->nazwaFigury()  << std::endl;
                    legalMove = false;
                }
                break;
            }
        }
        //DOWN
        for (int Square = WhiteK.posY - 1; Square >=0; --Square)
        {
            if (Plansza[WhiteK.posX][Square] != nullptr)
            {
                //std::cout << "Sprawdzam nr:  " << Square << std::endl;

                if (Plansza[WhiteK.posX][Square]->kolorGet() == 1 and (Plansza[WhiteK.posX][Square]->nazwaFigury() == "W" or (Plansza[WhiteK.posX][Square]->nazwaFigury() == "H")))
                {
                    //std::cout << "Widze czarnego:  " << Plansza[WhiteK.posX][Square]->posX << "  " << Plansza[WhiteK.posX][Square]->posY << " figura to: " << Plansza[WhiteK.posX][Square]->nazwaFigury() << std::endl;
                    legalMove = false;
                }
                break;
            }
        }
        //LEFT
        for (int Square = WhiteK.posX - 1; Square >= 0; --Square)
        {
            if (Plansza[Square][WhiteK.posY] != nullptr)
            {
                std::cout << "Sprawdzam lewo nr:  " << Square << std::endl;

                if (Plansza[Square][WhiteK.posY]->kolorGet() == 1 and (Plansza[Square][WhiteK.posY]->nazwaFigury() == "W" or (Plansza[Square][WhiteK.posY]->nazwaFigury() == "H")))
                {
                    std::cout << "Widze czarnego:  " << Plansza[Square][WhiteK.posY]->posX << "  " << Plansza[Square][WhiteK.posY]->posY << " figura to: " << Plansza[Square][WhiteK.posY]->nazwaFigury() << std::endl;
                    legalMove = false;
                }
                break;
            }
        }
        //RIGHT
        for (int Square = WhiteK.posX + 1; Square < 8; ++Square)
        {
            if (Plansza[Square][WhiteK.posY] != nullptr)
            {
                std::cout << "Sprawdzam prawo nr:  " << Square << std::endl;

                if (Plansza[Square][WhiteK.posY]->kolorGet() == 1 and (Plansza[Square][WhiteK.posY]->nazwaFigury() == "W" or (Plansza[Square][WhiteK.posY]->nazwaFigury() == "H")))
                {
                    std::cout << "Widze czarnego:  " << Plansza[Square][WhiteK.posY]->posX << "  " << Plansza[Square][WhiteK.posY]->posY << " figura to: " << Plansza[Square][WhiteK.posY]->nazwaFigury() << std::endl;
                    legalMove = false;
                }
                break;
            }
        }

    }

    //White rook/queen (rook like) check

    if (WhichColorTurn == 0)
    {
        //UP
        for (int Square = BlackK.posY + 1; Square < 8; ++Square)
        {
            if (Plansza[BlackK.posX][Square] != nullptr)
            {

                if (Plansza[BlackK.posX][Square]->kolorGet() == 0 and (Plansza[BlackK.posX][Square]->nazwaFigury() == "W" or (Plansza[BlackK.posX][Square]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }
        }
        //DOWN
        for (int Square = BlackK.posY - 1; Square >= 0; --Square)
        {
            if (Plansza[BlackK.posX][Square] != nullptr)
            {
               if (Plansza[BlackK.posX][Square]->kolorGet() == 0 and (Plansza[BlackK.posX][Square]->nazwaFigury() == "W" or (Plansza[BlackK.posX][Square]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }
        }
        //LEFT
        for (int Square = BlackK.posX - 1; Square >= 0; --Square)
        {
            if (Plansza[Square][BlackK.posY] != nullptr)
            {
                if (Plansza[Square][BlackK.posY]->kolorGet() == 0 and (Plansza[Square][BlackK.posY]->nazwaFigury() == "W" or (Plansza[Square][BlackK.posY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }
        }
        //RIGHT
        for (int Square = BlackK.posX + 1; Square < 8; ++Square)
        {
            if (Plansza[Square][BlackK.posY] != nullptr)
            {
                if (Plansza[Square][BlackK.posY]->kolorGet() == 0 and (Plansza[Square][BlackK.posY]->nazwaFigury() == "W" or (Plansza[Square][BlackK.posY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }
        }

    }

    //Black bishop/quenn (bishop like) check

    if (WhichColorTurn == 1)
    {
        for (int SquareX = WhiteK.posX+1, SquareY = WhiteK.posY+1; SquareX < 8 and SquareY < 8; ++SquareX, ++SquareY)
        {
            if (Plansza[SquareX][SquareY] != nullptr)
            {
                if (Plansza[SquareX][SquareY]->kolorGet() == 1 and (Plansza[SquareX][SquareY]->nazwaFigury() == "G" or (Plansza[SquareX][SquareY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }
            
        }

        for (int SquareX = WhiteK.posX + 1, SquareY = WhiteK.posY - 1; SquareX < 8 and SquareY >= 0; ++SquareX, --SquareY)
        {
            if (Plansza[SquareX][SquareY] != nullptr)
            {
                if (Plansza[SquareX][SquareY]->kolorGet() == 1 and (Plansza[SquareX][SquareY]->nazwaFigury() == "G" or (Plansza[SquareX][SquareY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }

        }

        for (int SquareX = WhiteK.posX - 1, SquareY = WhiteK.posY - 1; SquareX >=0 and SquareY >= 0; --SquareX, --SquareY)
        {
            if (Plansza[SquareX][SquareY] != nullptr)
            {
                if (Plansza[SquareX][SquareY]->kolorGet() == 1 and (Plansza[SquareX][SquareY]->nazwaFigury() == "G" or (Plansza[SquareX][SquareY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }

        }

        for (int SquareX = WhiteK.posX - 1, SquareY = WhiteK.posY + 1; SquareX >= 0 and SquareY < 8; --SquareX, ++SquareY)
        {
            if (Plansza[SquareX][SquareY] != nullptr)
            {
                if (Plansza[SquareX][SquareY]->kolorGet() == 1 and (Plansza[SquareX][SquareY]->nazwaFigury() == "G" or (Plansza[SquareX][SquareY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }

        }
    }

    //White bishop/quenn (bishop like) check

    if (WhichColorTurn == 0)
    {
        for (int SquareX = BlackK.posX + 1, SquareY = BlackK.posY + 1; SquareX < 8 and SquareY < 8; ++SquareX, ++SquareY)
        {
            if (Plansza[SquareX][SquareY] != nullptr)
            {
                if (Plansza[SquareX][SquareY]->kolorGet() == 0 and (Plansza[SquareX][SquareY]->nazwaFigury() == "G" or (Plansza[SquareX][SquareY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }

        }

        for (int SquareX = BlackK.posX + 1, SquareY = BlackK.posY - 1; SquareX < 8 and SquareY >= 0; ++SquareX, --SquareY)
        {
            if (Plansza[SquareX][SquareY] != nullptr)
            {
                if (Plansza[SquareX][SquareY]->kolorGet() == 0 and (Plansza[SquareX][SquareY]->nazwaFigury() == "G" or (Plansza[SquareX][SquareY]->nazwaFigury() == "H")))
                {
                   legalMove = false;
                }
                break;
            }

        }

        for (int SquareX = BlackK.posX - 1, SquareY = BlackK.posY - 1; SquareX >= 0 and SquareY >= 0; --SquareX, --SquareY)
        {
            if (Plansza[SquareX][SquareY] != nullptr)
            {
                if (Plansza[SquareX][SquareY]->kolorGet() == 0 and (Plansza[SquareX][SquareY]->nazwaFigury() == "G" or (Plansza[SquareX][SquareY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }

        }

        for (int SquareX = BlackK.posX - 1, SquareY = BlackK.posY + 1; SquareX >= 0 and SquareY < 8; --SquareX, ++SquareY)
        {
            if (Plansza[SquareX][SquareY] != nullptr)
            {
                if (Plansza[SquareX][SquareY]->kolorGet() == 0 and (Plansza[SquareX][SquareY]->nazwaFigury() == "G" or (Plansza[SquareX][SquareY]->nazwaFigury() == "H")))
                {
                    legalMove = false;
                }
                break;
            }

        }
    }
    


    return !(legalMove);

}
