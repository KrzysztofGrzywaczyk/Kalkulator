#include <windows.h>
#include <assert.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <sstream>

#define PRZYCISK1 501
#define PRZYCISK2 502
#define PRZYCISK3 503
#define PRZYCISK4 504
#define PRZYCISK5 505
#define PRZYCISK6 506
#define PRZYCISK7 507
#define PRZYCISK8 508
#define PRZYCISK9 509
#define PRZYCISK0 510


#define DODAJ 511
#define WYNIK 512
#define ODEJMIJ 513
#define KASUJ 514
#define POMNOZ 515
#define PODZIEL 516



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



// lancuchy zawierajace liczby
//--------------------stringi to kontenery przechowujace napisy, musialem stworzyc dla kazdego stringa przyporzadkowana dana liczbe

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

std::string zlaczenie ("");  //nic nie znajduje sie na razie w tych stringach
std::string zlaczenie2 ("");
std::string ktora_liczba ("");
std::string ktora_liczba2 ("");

int i;    //to sa zmienne odpowiedzialne za zlaczone liczby ktore bede pozniej sie laczyc (jednak zostają)
int i2;


void lacznik (void);   //definicja funkcji
void lacznik2 (void);

int wynik=0;


void dodawanie (void);      //definicje funkcji dzialan
void odejmowanie (void);
void mnozenie (void);
void dzielenie (void);

//Konewrsja intow na stringi
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
        MessageBox( NULL, "Okno odmowilo dzialania!", "Trudno",
        MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

    // TWORZENIE OKNA
    HWND hwnd;

    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Kalkulator", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 315, 400, NULL, NULL, hInstance, NULL );

    if( hwnd == NULL )
    {
        MessageBox( NULL, "Okno odmówilo dzoalania!", "Trudno", MB_ICONEXCLAMATION );
        return 1;
    }

    ShowWindow( hwnd, nCmdShow ); // Poka¿ okienko...
    UpdateWindow( hwnd );

    // Pêtla komunikatów
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


    static int pom = 1;
    static int zm_dodatkowa;
    static int plusik = 0;    // zmienne uzalezniajace rodzaj wykonywanej operacji
    static int minusik = 0;
    static int iloczyn = 0;
    static int iloraz = 0;
    static int koniec = 0;






    switch( msg )
    {
    case WM_CREATE:
        {

//powstawanie okienek: hText oznacza okienko w ktorym wyswietlaja sie zmieniajace sie cyfry

            hText = CreateWindowEx( 0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 50, 190, 20,
            hwnd, NULL, hInstance, NULL );  //EDIT oznacza ze to pole jest edytowalne
            SetWindowText( hText, "0" );

            by = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 65, 300, 155, 20,
            hwnd, NULL, hInstance, NULL );
            SetWindowText( by, "#Krzysztof Grzywaczyk" );
//utworzenie przyciskow odpowiadajacych danym liczbom
//zamiana int na str
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

            g_plus = CreateWindowEx( 0, "BUTTON", "+", WS_CHILD | WS_VISIBLE,
            200, 199, 40, 40, hwnd, (HMENU) DODAJ, hInstance, NULL );

            g_minus = CreateWindowEx( 0, "BUTTON", "-", WS_CHILD | WS_VISIBLE,
            200, 149, 40, 40, hwnd, (HMENU) ODEJMIJ, hInstance, NULL );

            g_razy = CreateWindowEx( 0, "BUTTON", "x", WS_CHILD | WS_VISIBLE,
            95, 245, 40, 40, hwnd, (HMENU) POMNOZ, hInstance, NULL );

            g_przez = CreateWindowEx( 0, "BUTTON", "/", WS_CHILD | WS_VISIBLE,
            145, 245, 40, 40, hwnd, (HMENU) PODZIEL, hInstance, NULL );

            //Wynik


            g_wynik = CreateWindowEx( 0, "BUTTON", "=", WS_CHILD | WS_VISIBLE,
            200, 244, 40, 40, hwnd, (HMENU) WYNIK, hInstance, NULL );


            //Wyzerowanie kalkulatora

            g_del = CreateWindowEx( 0, "BUTTON", "DEL", WS_CHILD | WS_VISIBLE,
            200, 100, 40, 40, hwnd, (HMENU) KASUJ, hInstance, NULL );

            break;
        }
    case WM_COMMAND:
        switch (wParam)
        {

                //Przyciski

                case PRZYCISK1:
                {

                    if (pom ==1) //pomocnicza -> rowna sie 1 gdy wybiera się liczby, ale jezeli +, -, /, x to zmienia sie na wartosc 2 (odróżnia  wybór liczby od działania)
                    {
                        ktora_liczba = jeden1;
                        lacznik ();  //lacznik laczy liczby w calosc np 1 i 2 tworzy 12
                        i = atoi(zlaczenie.c_str());   //zamienia stringa na inta
                    SetWindowText( hText,  to_string(i).c_str()); //wyswietla dana liczbe znowu zamieniona na tekst w hText. Tak trzeba robic zeby udawalo sie cokolwiek wyswietlac dodatkowo
                    }
                    else
                    {
                        ktora_liczba2 = jeden1;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK2:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = dwa2;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = dwa2;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK3:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = trzy3;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = trzy3;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK4:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = cztery4;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = cztery4;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK5:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = piec5;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = piec5;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK6:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = szesc6;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = szesc6;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK7:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = siedem7;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = siedem7;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK8:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = osiem8;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = osiem8;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK9:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = dziewiec9;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = dziewiec9;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                case PRZYCISK0:
                {


                    if (pom ==1)
                    {
                        ktora_liczba = zero0;
                        lacznik ();
                        i = atoi(zlaczenie.c_str());
                    SetWindowText( hText,  to_string(i).c_str());
                    }
                    else
                    {
                        ktora_liczba2 = zero0;
                        lacznik2 ();
                        i2 = atoi(zlaczenie2.c_str());
                    SetWindowText( hText,  to_string(i2).c_str());

                    }
                    break;
                }

                //Arytmetyka
                case DODAJ:
                {
                    pom = 2;  //zamienia na wyzsza pomocnicza (aby umożliwić wprowadzanie kolejnych liczb)
                    plusik = 1;
                    SetWindowText( hText, "+");  //wyswietlenie napisu

                    break;
                }


                case ODEJMIJ:
                {
                    pom = 2;
                    minusik = 1;
                    SetWindowText( hText, "-");
                    break;
                }

                case POMNOZ:
                {
                    pom = 2;
                    iloczyn = 1;
                    SetWindowText( hText, "x");
                    break;
                }

                case PODZIEL:
                {
                    pom = 2;
                    iloraz = 1;
                    SetWindowText( hText, "/");
                    break;
                }

                //Wynik
                case WYNIK:
                {
                    if (plusik ==1)  //zaleznie co jest równe 1 wykonywany jest dany if czyli dana operacja
                    {
                    dodawanie();
                    SetWindowText( hText,  to_string(wynik).c_str());
                    plusik = 0;
                    koniec = 1;

                    }
                    else if (minusik ==1)
                    {
                    odejmowanie();
                    SetWindowText( hText,  to_string(wynik).c_str());
                    minusik = 0;
                    }
                    else if (iloczyn == 1)
                    {
                    mnozenie();
                    SetWindowText( hText,  to_string(wynik).c_str());
                    iloczyn = 0;
                    }
                    else if (iloraz == 1)
                    {
                    dzielenie();
                    SetWindowText( hText,  to_string(wynik).c_str());
                    iloraz = 0;
                    }

                    break;

                }

                //DEL  //wszystko sie zeruje
                case KASUJ:
                {
                    SetWindowText( hText, "0");
                    zlaczenie = "";
                    zlaczenie2 = "";
                    ktora_liczba = "";
                    ktora_liczba2 = "";
                    pom = 1;
                    plusik = 0;
                    minusik = 0;
                break;
                }

}
break;


    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

        default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}

//Arytmetykq danych 2 liczb
void dodawanie (void)
{
    wynik = i + i2;

    }

void odejmowanie (void)
{
    wynik = i - i2;
}

void mnozenie (void)
{
    wynik = i * i2;
}

void dzielenie (void)
{
    wynik = i / i2;
}




// Zlaczenie stringow (jednak zostało...)
void lacznik (void)
{
    zlaczenie = zlaczenie + ktora_liczba;

}

void lacznik2 (void)
{
    zlaczenie2 = zlaczenie2 + ktora_liczba2;

}
