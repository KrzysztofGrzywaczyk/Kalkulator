#include <windows.h>
#include <assert.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <sstream>

#define PRZYCISK1
#define PRZYCISK2
#define PRZYCISK3
#define PRZYCISK4
#define PRZYCISK5
#define PRZYCISK6
#define PRZYCISK7
#define PRZYCISK8
#define PRZYCISK9
#define PRZYCISK0


#define DODAJ
#define WYNIK
#define ODEJMIJ
#define KASUJ
#define POMNOZ
#define PODZIEL



using namespace std;

LPSTR NazwaKlasy = "Klasa Okienka";
MSG Komunikat;

//Uchwyty zawierajace przyciski
HWND g_hPrzycisk1;
HWND g_hPrzycisk2;
HWND g_hPrzycisk3;
HWND g_hPrzycisk4;
HWND g_hPrzycisk5;
HWND g_hPrzycisk6;
HWND g_hPrzycisk7;
HWND g_hPrzycisk8;
HWND g_hPrzycisk9;
HWND g_hPrzycisk0;
HWND g_plus;
HWND g_minus;
HWND g_wynik;
HWND g_del;
HWND g_razy;
HWND g_przez;
HINSTANCE hInstance;
HWND hText;
HWND by;



std::string jeden1 ("1");
std::string dwa2 ("2");
std::string trzy3 ("3");
std::string cztery4 ("4");
std::string piec5 ("5");
std::string szesc6 ("6");
std::string siedem7 ("7");
std::string osiem8 ("8");
std::string dziewiec9 ("9");
std::string zero0 ("0");

std::string zlaczenie ("");
std::string zlaczenie2 ("");
std::string ktora_liczba ("");
std::string ktora_liczba2 ("");

int i;    //zmienne odpowiedzialne za zlaczone liczby
int i2;


void lacznik (void);
void lacznik2 (void);

int wynik=0;


void dodawanie (void);      //definicje funkcji dzialan
void odejmowanie (void);
void mnozenie (void);
void dzielenie (void);

//zamiana liczby na napis
template <class T>
string to_string(T obj)
{
    stringstream ss;
    ss << obj;
    return ss.str();
}


LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

    // WYPE£NIANIE STRUKTURY
    WNDCLASSEX wc;

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );

    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( NULL, "Okno odmowilo dzialania!", ":(",
        MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

    // TWORZENIE OKNA
    HWND hwnd;

    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Kalkulator", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 315, 400, NULL, NULL, hInstance, NULL );

    if( hwnd == NULL )
    {
        MessageBox( NULL, "Okno odmówilo dzoalania!", ":(", MB_ICONEXCLAMATION );
        return 1;
    }

    ShowWindow( hwnd, nCmdShow ); // Poka¿ okienko...
    UpdateWindow( hwnd );

    // Petla komunikatow
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

// OBS£UGA ZDARZEÑ
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    //utworzenie liczb potrzebnych do liczenia w kalkulatorze

    static int jeden= 1;
    static int dwa= 2;
    static int trzy= 3;
    static int cztery= 4;
    static int piec= 5;
    static int szesc= 6;
    static int siedem= 7;
    static int osiem= 8;
    static int dziewiec= 9;
    static int zero= 0;





    switch( msg )
    {
    case WM_CREATE:
        {

// okienko w ktorym wyswietlaja sie zmieniajace sie cyfry

            hText = CreateWindowEx( 0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 50, 190, 20,
            hwnd, NULL, hInstance, NULL );  //EDIT oznacza ze to pole jest edytowalne, moze sie cos w nim w kolko zmieniac dodawac itp
            SetWindowText( hText, "0" );
            by = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 65, 300, 155, 20,
            hwnd, NULL, hInstance, NULL );
            SetWindowText( by, "©Krzysztof Grzywaczyk" );
//utworzenie przyciskow odpowiadajacych danym liczbom
            g_hPrzycisk1 = CreateWindowEx( 0, "BUTTON", to_string(jeden).c_str(), WS_CHILD | WS_VISIBLE,
            50, 100, 35, 35, hwnd, (HMENU) PRZYCISK1, hInstance, NULL );

            g_hPrzycisk2 = CreateWindowEx( 0, "BUTTON", to_string(dwa).c_str(), WS_CHILD | WS_VISIBLE,
            100, 100, 35, 35, hwnd,(HMENU) PRZYCISK2, hInstance, NULL );

            g_hPrzycisk3 = CreateWindowEx( 0, "BUTTON", to_string(trzy).c_str(), WS_CHILD | WS_VISIBLE,
            150, 100, 35, 35, hwnd, (HMENU) PRZYCISK3, hInstance, NULL );

            g_hPrzycisk4 = CreateWindowEx( 0, "BUTTON", to_string(cztery).c_str(), WS_CHILD | WS_VISIBLE,
            50, 150, 35, 35, hwnd, (HMENU) PRZYCISK4, hInstance, NULL );

            g_hPrzycisk5 = CreateWindowEx( 0, "BUTTON", to_string(piec).c_str(), WS_CHILD | WS_VISIBLE,
            100, 150, 35, 35, hwnd, (HMENU) PRZYCISK5, hInstance, NULL );

            g_hPrzycisk6 = CreateWindowEx( 0, "BUTTON", to_string(szesc).c_str(), WS_CHILD | WS_VISIBLE,
            150, 150, 35, 35, hwnd, (HMENU) PRZYCISK6, hInstance, NULL );

            g_hPrzycisk7 = CreateWindowEx( 0, "BUTTON", to_string(siedem).c_str(), WS_CHILD | WS_VISIBLE,
            50, 200, 35, 35, hwnd, (HMENU) PRZYCISK7, hInstance, NULL );

            g_hPrzycisk8 = CreateWindowEx( 0, "BUTTON", to_string(osiem).c_str(), WS_CHILD | WS_VISIBLE,
            100, 200, 35, 35, hwnd, (HMENU) PRZYCISK8, hInstance, NULL );

            g_hPrzycisk9 = CreateWindowEx( 0, "BUTTON", to_string(dziewiec).c_str(), WS_CHILD | WS_VISIBLE,
            150, 200, 35, 35, hwnd, (HMENU) PRZYCISK9, hInstance, NULL );

            g_hPrzycisk0 = CreateWindowEx( 0, "BUTTON", to_string(zero).c_str(), WS_CHILD | WS_VISIBLE,
            50, 250, 35, 35, hwnd, (HMENU) PRZYCISK0, hInstance, NULL );

            //Operacje arytmetyczne
            //
            //



            //Wyzerowanie kalkulatora
            //
            //


            break;
        }




    case WM_COMMAND:
        switch (wParam)
        {
            //Przyciski

                case PRZYCISK1:
                {   if ()
                    }
                    break;
                }

                case PRZYCISK2:
                {   if ()
                    }
                    break;
                }

                case PRZYCISK3:
                {   if ()
                    }
                    break;
                }

                case PRZYCISK4:
                {   if ()
                    }
                    break;
                }

                case PRZYCISK5:
                {   if ()
                    {
                    }
                    break;
                }

                case PRZYCISK6
                {   if ()
                    }
                    break;
                }

                case PRZYCISK7
                {   if ()
                    }
                    break;
                }

                case PRZYCISK8
                {   if ()
                    }
                    break;
                }

                case PRZYCISK9
                {   if ()
                    }
                    break;
                }

                case PRZYCISK0
                {   if ()
                    }
                    break;
                }


                //Dzialania
                case DODAJ:
                    break;

                case ODEJMIJ:
                    break;

                case POMNOZ:
                    break;

                case PODZIEL:
                    break;

                //Wynik
                case WYNIK:

                    break;

                }

                //DEL - zerowanie
                case KASUJ:

                break;
                }

    return 0;
}



// Zlaczenie stringow
void lacznik (void)
{
    zlaczenie = zlaczenie + ktora_liczba;

}

void lacznik2 (void)
{
    zlaczenie2 = zlaczenie2 + ktora_liczba2;

}
