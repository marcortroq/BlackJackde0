#include <iostream>
#include <windows.h>        // para windows


using namespace std;

//DEFINIR MAZO
    int mazo[4][12];
    string cardSuit[4] = {"DIAMANTES", "PICAS", "TREBOLES", "CORAZONES" };
    
//VARIABLES GENERALES    
    int selectSuit;
    int cart;
    bool choose;
    int puntuacion;
    int pause = 2000;

//VARIABLES JUGADOR

    string jugador = "Jugador1";
    int cuentaJugador;
    int valorAs;
    bool choseAs = false;
    int eleccion;
    bool checksel = false;

//VARIABLES CRUPPIER

    string crupier = "Crupier";
    int cuentaCrupier;

    void selectCards() {
        choose = false; 

        //ELEGIMOS LA CARTA

        while (!choose){
            //SELECIONA UN PALO
            selectSuit = rand() % 4;
            //SELECCIONAR UNA CARTA
            cart = rand() % 12;

            //COMPROBAMOS QUE NO ESTA COGIDA LA CARTA Y LA QUITAMOS DEL MAZO
            if (mazo[selectSuit][cart] == 0)
            {
                cout << (cart + 1) << " " << cardSuit[selectSuit] << " ";
                mazo[selectSuit][cart] = 1;
                choose = true;
            }
            else {
                choose = false;
            }
        }


    }

    int valueCards(int& cuentaCard, string& name) {
        //ASIGNAMOS EL VALOR A LAS CARTAS

        //VALOR DE LA CARTA DEL 1 AL 9
        if ((cart >= 1) && (cart <= 9)) {
            puntuacion = (cart + 1);
        }
        //VALOR DE LAS FIGURAS
        else if (cart >= 10) {
            puntuacion = 10;
        }
        //VALORES DEL AS
        if (cart == 0) {
            //ELECCION DEL VALOR AS PARA JUGADOR
            if (name == jugador){
                cout << "\nQue valor le asignas al AS [1/11]";
                while (!choseAs)
                {
                    cin >> valorAs;
                    if (valorAs == 1) {
                        puntuacion = 1;
                        choseAs = true;
                    }
                    else if (valorAs == 11) {
                        puntuacion = 11;
                        choseAs = true;
                    }
                }
                valorAs = 0;
            //ELECCION DEL VALOR AS PARA CRUPIER
            } else if (name == crupier)
                if ((cart + 11) <= 21){
                    puntuacion = 11;
                } else {
                    puntuacion = 1;
                }
        choseAs = false;
        }

        cuentaCard = cuentaCard + puntuacion;

        return cuentaCard;
    }

    void jugardorSelection() {
        while (!checksel) {
            if (cuentaJugador == 21)
            {
                //CASO DE OBTENER UN BLACKJACK
                cout << "El jugador ha obtenido un blackjack, pasa automaticamente el turno al cruppier para intentar empatar\n";
                checksel = true;
                break;
            }
            else if (cuentaJugador > 21) {
                //SI SE PASA LA PUNTUACION DE 21
                cout << "\nEl " << jugador << " ha sobrepasado 21 de puntuacion\n";
                break;
            }
            else {
                //PREGUNTAMOS SI QUIERE SEGUIR ROBANDO
                cout << jugador << " quieres robar una carta o plantarte? [1 ROBAR /2 PLANTARSE]\n";
                cin >> eleccion;

                if (eleccion == 2) {
                    cout << "El jugador no roba mas cartas";
                    cout << "\nLa puntuacion final del " << jugador << " es: " << cuentaJugador << "\n";
                    checksel = true;

                }
                else if (eleccion == 1) {
                    cout << "El crupier reparte otra carta al " << jugador << "\n";
                    Sleep(pause);
                    selectCards();
                    valueCards(cuentaJugador, jugador);
                    cout << "\nLa puntuacion del " << jugador << " es: " << cuentaJugador << "\n";
                }
                else {
                    cout << "ERROR: Introduce una eleccion valida [1/2]\n";
                }
            }
            
        }
        
    }

    void crupierSelection() {
        //FUNCION PARA SABER SI EL CRUPPIER SIGUE ROBANDO O NO
        while (cuentaCrupier <= cuentaJugador && cuentaJugador <= 21){
            Sleep(pause);
            cout << "El crupier reparte otra carta al " << crupier << "\n";
            Sleep(pause);
            selectCards();
            valueCards(cuentaCrupier, crupier);
            cout << "\nLa puntuacion del " << crupier << " es: " << cuentaCrupier << "\n\n";
       
        }
        
    }
    void checkWin() {
        //QUIEN GANA LA PARTIDA

        if (cuentaCrupier == 21 && cuentaJugador != 21) {
            cout << "El crupier ha obtenido un blackjack el " << crupier << " gana la partida\n";
        }
        else if (cuentaCrupier != 21 && cuentaJugador == 21) {
            cout << "El jugador ha obtenido un blackjack el " << jugador << " gana la partida\n";
        }
        else if (cuentaCrupier == 21 && cuentaJugador == 21) {
            cout << "El jugador y el cruppier ha obtenido un blackjack es un empate\n";
        }
        else if (cuentaJugador > cuentaCrupier && cuentaJugador < 21 && cuentaCrupier < 21) {
            cout << "El " << jugador << " Gana la partida\n";
        }
        else if (cuentaJugador < 21 && cuentaCrupier > 21) {
            cout << "El " << jugador << " Gana la partida\n";
        }
        else if (cuentaJugador < cuentaCrupier && cuentaCrupier < 21 && cuentaJugador < 21) {
            cout << "El " << crupier << " Gana la partida\n";
        }
    }


void main()
{
    srand(time(NULL));
    cout << "El crupier reparte dos cartas al " << jugador << "\n";
    Sleep(pause);
    selectCards();
    valueCards(cuentaJugador, jugador);
    selectCards();
    valueCards(cuentaJugador, jugador);
    cout << "\nLa puntuacion del " << jugador << " es: " << cuentaJugador <<"\n";
    cout << "\nEl crupier reparte una carta al " << crupier << "\n";
    Sleep(pause);
    selectCards();
    valueCards(cuentaCrupier, crupier);
    cout << "\nLa puntuacion del " << crupier << " es: " << cuentaCrupier << "\n\n";
    jugardorSelection();
    cout << "\nEl crupier reparte la segunda carta al " << crupier << "\n";
    Sleep(pause);
    selectCards();
    valueCards(cuentaCrupier, crupier);
    cout << "\nLa puntuacion del " << crupier << " es: " << cuentaCrupier << "\n\n";
    crupierSelection();
    checkWin();
    
}