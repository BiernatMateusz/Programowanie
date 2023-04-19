#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;
const int frame = 120;
const float WielkoscKlocka = 40;
float timee = 0;
float timee1 = 0;

int NumerPozycji = 1;

bool pierwszy_cykl;

int RodzajKlocka = 3;
int ObrotKlocka = 0;
const int KlocekGlowny = 0;

int aktualnePrzesuniecieKlocka = 0;
int PrzesuniecieLewoPrawo = 3;

int PrzyciskGora = 0;
int spacjawcisnieta = 0;
int jedzieSzybkoWDol = 0;
int PozwolenieNaPowrotDoSpadku = 0;

int NastepneKlocki[3];

struct klocek
{
    int Klocek[4]; //obrot klocka
} s[8][4]; //pierwsza cyfra to rodzaj klocka natomiast druga to jego poszczegolne elementy

struct pozycje
{
    int PozycjaX;
    int PozycjaY;
} PozycjaKlockow[17],pozaStart[17];

struct pozycjatymczasowa
{
    int PozycjaX;
    int PozycjaY;
} PozycjaTymczasowa[4], dodatkoweNaBoku[4];



int pelne[12][22] = {}; 

int lewo = 0;
int prawo = 0;

int nowyKlocek = 0;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Learn!", sf::Style::Default);
    window.setFramerateLimit(frame);
    sf::RectangleShape kwadrat1(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::RectangleShape kwadrat2(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::RectangleShape kwadrat3(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::RectangleShape kwadrat4(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::RectangleShape kwadrat5(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::RectangleShape kwadrat6(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::RectangleShape kwadrat7(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::RectangleShape kwadrat8(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::RectangleShape napis(sf::Vector2f(WielkoscKlocka*5, WielkoscKlocka*2));
    sf::RectangleShape tlo(sf::Vector2f(WielkoscKlocka, WielkoscKlocka));
    sf::Texture t1, t2, t3, t4, t5, t6, t7, t8,napisek;
    sf::Texture Dodatek;
    t1.loadFromFile("texture/tile1.png");
    t2.loadFromFile("texture/tile2.png");
    t3.loadFromFile("texture/tile3.png");
    t4.loadFromFile("texture/tile4.png");
    t5.loadFromFile("texture/tile5.png");
    t6.loadFromFile("texture/tile6.png");
    t7.loadFromFile("texture/tile7.png");
    t8.loadFromFile("texture/tile8.png");
    Dodatek.loadFromFile("texture/tile9.png");
    napisek.loadFromFile("texture/tile10.png");

    napis.setTexture(&napisek);
    tlo.setTexture(&t1);
    sf::Clock zegar;
    sf::Clock zegar1;

    //TUTAJ MUSI BYC WYBRANY OBROT KLOCKA

    srand((unsigned)time(NULL));

    for (int i = 0; i < 2;i++) NastepneKlocki[i] = rand() % 7;


    cout << NastepneKlocki[0] << " " << NastepneKlocki[1] << " " << NastepneKlocki[2] << endl;


   //PIERWSZY OBIEG
    if (pierwszy_cykl == 0)
    {

        for (int i = 0; i < 12; i++)
            pelne[i][21] = 1;

        for (int i = 0; i < 21; i++)
        {
            pelne[0][i] = 1;
            pelne[11][i] = 1;
        }


        //kwadrat
        s[0][0].Klocek[0] = 9;
        s[0][1].Klocek[0] = 10;
        s[0][2].Klocek[0] = 13;
        s[0][3].Klocek[0] = 14;

        s[0][0].Klocek[1] = 9;
        s[0][1].Klocek[1] = 10;
        s[0][2].Klocek[1] = 13;
        s[0][3].Klocek[1] = 14;

        s[0][0].Klocek[2] = 9;
        s[0][1].Klocek[2] = 10;
        s[0][2].Klocek[2] = 13;
        s[0][3].Klocek[2] = 14;

        s[0][0].Klocek[3] = 9;
        s[0][1].Klocek[3] = 10;
        s[0][2].Klocek[3] = 13;
        s[0][3].Klocek[3] = 14;

        //kijek
        s[1][0].Klocek[0] = 2;
        s[1][1].Klocek[0] = 6;
        s[1][2].Klocek[0] = 10;
        s[1][3].Klocek[0] = 14;

        s[1][0].Klocek[1] = 9;
        s[1][1].Klocek[1] = 10;
        s[1][2].Klocek[1] = 11;
        s[1][3].Klocek[1] = 12;

        s[1][0].Klocek[2] = 2;
        s[1][1].Klocek[2] = 6;
        s[1][2].Klocek[2] = 10;
        s[1][3].Klocek[2] = 14;

        s[1][0].Klocek[3] = 9;
        s[1][1].Klocek[3] = 10;
        s[1][2].Klocek[3] = 11;
        s[1][3].Klocek[3] = 12;

        //Zielony Zygzik
        s[2][0].Klocek[0] = 6;
        s[2][1].Klocek[0] = 7;
        s[2][2].Klocek[0] = 9;
        s[2][3].Klocek[0] = 10;

        s[2][0].Klocek[1] = 6;
        s[2][1].Klocek[1] = 10;
        s[2][2].Klocek[1] = 11;
        s[2][3].Klocek[1] = 15;

        s[2][0].Klocek[2] = 6;
        s[2][1].Klocek[2] = 7;
        s[2][2].Klocek[2] = 9;
        s[2][3].Klocek[2] = 10;

        s[2][0].Klocek[3] = 6;
        s[2][1].Klocek[3] = 10;
        s[2][2].Klocek[3] = 11;
        s[2][3].Klocek[3] = 15;

        //fioletowy Zygzik
        s[3][0].Klocek[0] = 9;
        s[3][1].Klocek[0] = 10;
        s[3][2].Klocek[0] = 14;
        s[3][3].Klocek[0] = 15;

        s[3][0].Klocek[1] = 7;
        s[3][1].Klocek[1] = 10;
        s[3][2].Klocek[1] = 11;
        s[3][3].Klocek[1] = 14;

        s[3][0].Klocek[2] = 9;
        s[3][1].Klocek[2] = 10;
        s[3][2].Klocek[2] = 14;
        s[3][3].Klocek[2] = 15;

        s[3][0].Klocek[3] = 7;
        s[3][1].Klocek[3] = 10;
        s[3][2].Klocek[3] = 11;
        s[3][3].Klocek[3] = 14;

        //czerwony trojkat
        s[4][0].Klocek[0] = 14;
        s[4][1].Klocek[0] = 9;
        s[4][2].Klocek[0] = 10;
        s[4][3].Klocek[0] = 11;

        s[4][0].Klocek[1] = 6;
        s[4][1].Klocek[1] = 10;
        s[4][2].Klocek[1] = 11;
        s[4][3].Klocek[1] = 14;

        s[4][0].Klocek[2] = 9;
        s[4][1].Klocek[2] = 10;
        s[4][2].Klocek[2] = 11;
        s[4][3].Klocek[2] = 6;

        s[4][0].Klocek[3] = 6;
        s[4][1].Klocek[3] = 9;
        s[4][2].Klocek[3] = 10;
        s[4][3].Klocek[3] = 14;

        //fiolet  elka
        s[5][0].Klocek[0] = 2;
        s[5][1].Klocek[0] = 6;
        s[5][2].Klocek[0] = 10;
        s[5][3].Klocek[0] = 11;

        s[5][0].Klocek[1] = 5;
        s[5][1].Klocek[1] = 6;
        s[5][2].Klocek[1] = 7;
        s[5][3].Klocek[1] = 3;

        s[5][0].Klocek[2] = 1;
        s[5][1].Klocek[2] = 2;
        s[5][2].Klocek[2] = 6;
        s[5][3].Klocek[2] = 10;

        s[5][0].Klocek[3] = 5;
        s[5][1].Klocek[3] = 6;
        s[5][2].Klocek[3] = 7;
        s[5][3].Klocek[3] = 9;

        //zolta elka
        s[6][0].Klocek[0] = 3;
        s[6][1].Klocek[0] = 7;
        s[6][2].Klocek[0] = 10;
        s[6][3].Klocek[0] = 11;

        s[6][0].Klocek[1] = 12;
        s[6][1].Klocek[1] = 6;
        s[6][2].Klocek[1] = 7;
        s[6][3].Klocek[1] = 8;

        s[6][0].Klocek[2] = 3;
        s[6][1].Klocek[2] = 4;
        s[6][2].Klocek[2] = 7;
        s[6][3].Klocek[2] = 11;

        s[6][0].Klocek[3] = 6;
        s[6][1].Klocek[3] = 7;
        s[6][2].Klocek[3] = 8;
        s[6][3].Klocek[3] = 2;

        //Pozycje konkretnych bloczkow
        if (NumerPozycji <= 16)
            for (int j = 3; j >= 0; j--)
                for (int i = 0; i < 4; i++)
                {
                    PozycjaKlockow[NumerPozycji].PozycjaX = i * WielkoscKlocka+120;
                    PozycjaKlockow[NumerPozycji].PozycjaY = j * WielkoscKlocka;
                    pozaStart[NumerPozycji].PozycjaX = i * WielkoscKlocka + 120;
                    pozaStart[NumerPozycji].PozycjaY = j * WielkoscKlocka;

                    NumerPozycji++;
                }


        pierwszy_cykl = 1;
    } //Inicjalizacja w pierwszym obiegu


    //Aktualny klocek
    s[7][0].Klocek[KlocekGlowny] = s[NastepneKlocki[0]][0].Klocek[ObrotKlocka];
    s[7][1].Klocek[KlocekGlowny] = s[NastepneKlocki[0]][1].Klocek[ObrotKlocka];
    s[7][2].Klocek[KlocekGlowny] = s[NastepneKlocki[0]][2].Klocek[ObrotKlocka];
    s[7][3].Klocek[KlocekGlowny] = s[NastepneKlocki[0]][3].Klocek[ObrotKlocka];

    

    //cout << PozycjaKlockow[s[7][0].Klocek[KlocekGlowny]].PozycjaX<<" " << PozycjaKlockow[s[7][0].Klocek[KlocekGlowny]].PozycjaY << endl;
   // cout << PozycjaKlockow[s[7][1].Klocek[KlocekGlowny]].PozycjaX<<" " << PozycjaKlockow[s[7][1].Klocek[KlocekGlowny]].PozycjaY << endl;
   // cout << PozycjaKlockow[s[7][2].Klocek[KlocekGlowny]].PozycjaX<<" " << PozycjaKlockow[s[7][2].Klocek[KlocekGlowny]].PozycjaY << endl;
   // cout << PozycjaKlockow[s[7][3].Klocek[KlocekGlowny]].PozycjaX<<" " << PozycjaKlockow[s[7][3].Klocek[KlocekGlowny]].PozycjaY << endl;

    while (window.isOpen())
    {

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window.close();
        }
        timee = zegar.getElapsedTime().asSeconds();
        timee1 = zegar1.getElapsedTime().asSeconds();

        //Czy mozna obrócic klocek?




        //Obrot klocka - wczytanie jego aktualnej pozycji 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) and PrzyciskGora == 0)
        {
            PrzyciskGora = 1;
            NumerPozycji = 1;

            //cout << "Przesuniecie lewo prawo = " << PrzesuniecieLewoPrawo << endl;
            
            if (ObrotKlocka < 3)
                ObrotKlocka++;
            else ObrotKlocka = 0;

            for (int i = 0; i < 4; i++)
                s[7][i].Klocek[KlocekGlowny] = s[NastepneKlocki[0]][i].Klocek[ObrotKlocka];

            if (NumerPozycji <= 16)
            {
                for (int j = 3; j >= 0; j--)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        PozycjaKlockow[NumerPozycji].PozycjaX = (i * WielkoscKlocka) + PrzesuniecieLewoPrawo * WielkoscKlocka;
                        PozycjaKlockow[NumerPozycji].PozycjaY = (j * WielkoscKlocka) + aktualnePrzesuniecieKlocka * WielkoscKlocka;
                        NumerPozycji++;
                    }

                }
                
            }

            int cofnij = 0;

            for (int i = 0; i < 4; i++)
            {
                PozycjaTymczasowa[i].PozycjaX = (PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX / 40)+1;
                PozycjaTymczasowa[i].PozycjaY = PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaY / 40;
                //cout << PozycjaTymczasowa[i].PozycjaX <<" " << PozycjaTymczasowa[i].PozycjaY << endl;

                if (pelne[PozycjaTymczasowa[i].PozycjaX][PozycjaTymczasowa[i].PozycjaY])
                    cofnij = 1;

            }

            

            if (cofnij)
            {

                //cout << "Cofnieto " << endl;

                if (ObrotKlocka > 0)
                    ObrotKlocka--;
                else ObrotKlocka = 3;

                for (int i = 0; i < 4; i++)
                    s[7][i].Klocek[KlocekGlowny] = s[NastepneKlocki[0]][i].Klocek[ObrotKlocka];
            }



        }

        if (not (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)))
        {
            PrzyciskGora = 0;
        }

        
        
        
        //WCZYTANIE NOWEGO KLOCKA


        if (nowyKlocek == 0)
        {
            for (int i=0;i<4;i++)
                s[7][i].Klocek[KlocekGlowny] = s[NastepneKlocki[0]][i].Klocek[ObrotKlocka];
            nowyKlocek = 1;
            //cout << ObrotKlocka << endl;
            if (NumerPozycji <= 16)
                for (int j = 3; j >= 0; j--)
                    for (int i = 0; i < 4; i++)
                    {
                        PozycjaKlockow[NumerPozycji].PozycjaX = i * WielkoscKlocka+120;
                        PozycjaKlockow[NumerPozycji].PozycjaY = j * WielkoscKlocka;
                        NumerPozycji++;
                    }
          
        }

        //Strzalka w DOL - szybsze spadanie

        float czasDoSpadku = 0.5;
        float czasCzekania = 1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            czasDoSpadku = 0.05;
            czasCzekania = 0.2;
        }
        else if (spacjawcisnieta==0)
        { 
            czasDoSpadku = 0.5;
            czasCzekania = 1;
        }



        


        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) and spacjawcisnieta == 0 and PozwolenieNaPowrotDoSpadku==0)
        {
            
            spacjawcisnieta = 1;
            PozwolenieNaPowrotDoSpadku = 1;
            
        }

        if (not (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
            {
                spacjawcisnieta = 0;
                PozwolenieNaPowrotDoSpadku = 0;
            }

        if (spacjawcisnieta == 1 and jedzieSzybkoWDol == 0)
        {
            jedzieSzybkoWDol = 1;
            
        }

        if (jedzieSzybkoWDol)
        {
            czasDoSpadku = 0.0001;
            czasCzekania = 0.0001;
        }


        
        


        //Warunki na możliwość przesunięcia klocka w dół
        int W_Dol = 0;

        for (int i = 0; i < 4; i++)
            if (pelne[(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX / 40) + 1][(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaY / 40) + 2] )
            {
                W_Dol = 1;
                
            }

        int moznaIscDalej = 0;

        if (W_Dol == 0)
            zegar1.restart();
        else if (timee1 > czasCzekania)
        {
            zegar1.restart();
            moznaIscDalej = 1;
        }

        //cout << timee1 << endl;

        if (moznaIscDalej == 1)
        {
            
            for (int i = 0; i < 4; i++)
            {
                pelne[(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX / 40) + 1][(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaY / 40) + 1] = 1;
                
               // cout << (PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX / 40) + 1 << " " << (PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaY / 40) + 2 << endl;

            }
            NastepneKlocki[0] = NastepneKlocki[1];
            NastepneKlocki[1] = NastepneKlocki[2];
            NastepneKlocki[2] = rand()%7;

            nowyKlocek = 0;
            NumerPozycji = 1;
            aktualnePrzesuniecieKlocka = 0;
            ObrotKlocka = 0;
            PrzesuniecieLewoPrawo = 4;
            jedzieSzybkoWDol = 0;
            spacjawcisnieta = 0;

            cout << NastepneKlocki[0] << " " << NastepneKlocki[1] << " " << NastepneKlocki[2] << endl;
        }
                
        

       

        //KLOCKI W DOL
        if (timee > czasDoSpadku and W_Dol==0)
        {
            for (int i = 0; i < 4; i++)
            {
                PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaY += WielkoscKlocka;
                
                
            }
            aktualnePrzesuniecieKlocka++;
            zegar.restart();
            //nadpisanie pelnych i nowy klocek
            
        }

       

        //Warunki na możliwość przesunięcia klocka w lewo
        int W_Lewo = 0;

        for (int i = 0; i < 4; i++)
            if (pelne[(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX / 40)][(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaY / 40) + 1])
                W_Lewo = 1;

        

        //W LEWO
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) and W_Lewo==0)
        {
            if (lewo == 0)
            {
                for (int i = 0; i < 4; i++)
                {
                    PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX -= WielkoscKlocka;
                    lewo = 1;

                }
                PrzesuniecieLewoPrawo--;
            }
        }


        if  (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
            lewo = 0;

        //Warunki na możliwość przesunięcia klocka w lewo
        int W_Prawo = 0;

        for (int i = 0; i < 4; i++)
            if (pelne[(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX / 40)+2 ][(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaY / 40) + 1])
                W_Prawo = 1;

        //W PRAWO
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) and W_Prawo==0)
        {
            if (prawo == 0)
            {
                for (int i = 0; i < 4; i++)
                {
                    PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX += WielkoscKlocka;
                    prawo = 1;

                }
                PrzesuniecieLewoPrawo++;
            }
        }



        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
            prawo = 0;


        //OpuszczenieCalych linii
        int suma = 0;
        if (moznaIscDalej)
        {
            for (int i = 1; i < 21; i++)
            {
                 suma = 0;
                for (int j = 1; j < 11; j++)
                {
                    if (pelne[j][i] == 1) suma++;
                }
                if (suma == 10)
                {
                    for (int k = i; k > 0; k--)
                        for (int x = 1; x < 11; x++)
                            pelne[x][k] = pelne[x][k-1];
                }
            }

        }

        if (moznaIscDalej)
        {
            for (int i = 1; i < 21; i++)
            {
                for (int j = 1; j < 11; j++)
                {
                    cout << pelne[j][i] << " ";
                }
                cout << endl;
            }
        }

        //dodatkowe po prawej
        for (int i = 0; i < 4; i++)
        {
            int dodatekDoPrzesuniecia=0;
            int dodatekDoPrzesunieciaWX = 0;
            if ( NastepneKlocki[1]==1 or NastepneKlocki[1] == 2)
            {
                dodatekDoPrzesuniecia = 2;
            }
            else if (NastepneKlocki[1] == 5 or NastepneKlocki[1] == 6) dodatekDoPrzesuniecia = 3;

            




            if (NastepneKlocki[1] == 5 or NastepneKlocki[1] == 6)
            {
                dodatekDoPrzesunieciaWX = 1;
            }
            else if (NastepneKlocki[1] == 0) dodatekDoPrzesunieciaWX = -1;


            dodatkoweNaBoku[i].PozycjaX = pozaStart[s[NastepneKlocki[1]][i].Klocek[0]+1].PozycjaX - dodatekDoPrzesunieciaWX * (WielkoscKlocka/2);
            dodatkoweNaBoku[i].PozycjaY = pozaStart[s[NastepneKlocki[1]][i].Klocek[0]+1].PozycjaY - dodatekDoPrzesuniecia*(WielkoscKlocka/2);

            cout << dodatkoweNaBoku[i].PozycjaX << " " << dodatkoweNaBoku[i].PozycjaY << endl;

        }




        if (NastepneKlocki[0] == 0)
            kwadrat1.setTexture(&t2);
        else if (NastepneKlocki[0] == 1)
            kwadrat1.setTexture(&t3);
        else if (NastepneKlocki[0] == 2)
            kwadrat1.setTexture(&t4);
        else if (NastepneKlocki[0] == 3)
            kwadrat1.setTexture(&t5);
        else if (NastepneKlocki[0] == 4)
            kwadrat1.setTexture(&t6);
        else if (NastepneKlocki[0] == 5)
            kwadrat1.setTexture(&t7);
        else if (NastepneKlocki[0] == 6)
            kwadrat1.setTexture(&t8);


        kwadrat2.setTexture(&t8);
        kwadrat8.setTexture(&Dodatek);

        window.clear();
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 20; j++)
            {

                tlo.setPosition(i * WielkoscKlocka, j * WielkoscKlocka);
                window.draw(tlo);
            }
        
        for (int i = 0; i < 4; i++)
            {
            kwadrat1.setPosition(PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaX, (PozycjaKlockow[s[7][i].Klocek[KlocekGlowny]].PozycjaY));
            window.draw(kwadrat1);
            
            }

        for (int i=1;i<11;i++)
            for (int j=0;j<21;j++)
                if (pelne[i][j])
                {
                    kwadrat2.setPosition(i* WielkoscKlocka-WielkoscKlocka, j* WielkoscKlocka-WielkoscKlocka);
                        window.draw(kwadrat2);
                }

        //wyswietlanie tla na boczku
        napis.setPosition(12 * WielkoscKlocka - WielkoscKlocka, WielkoscKlocka - WielkoscKlocka);
        window.draw(napis);

        for (int i = 12; i < 17; i++)
            for (int j = 3; j < 8; j++)
                {
                    kwadrat8.setPosition(i * WielkoscKlocka - WielkoscKlocka, j * WielkoscKlocka - WielkoscKlocka);
                    window.draw(kwadrat8);
                }
        
        for (int i = 0; i < 4; i++)
        {   
            kwadrat2.setPosition(dodatkoweNaBoku[i].PozycjaX + 320, (dodatkoweNaBoku[i].PozycjaY + 120));

            window.draw(kwadrat2);
        }


        window.display();

    }
        
        return 0;
       
}




