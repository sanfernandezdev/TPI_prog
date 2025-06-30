#include<iostream>
#include <vector>
#include <limits>
#include <iomanip>

#include "sesionDeJuego.h"
#include "admCasas.h"
#include "admBatallas.h"
#include "menues.h"
#include "indicesVectores.h"
#include "constantesJuego.h"

using namespace std;


int getNumCasaElegida(std::vector<float> v_recursosJugador){
    return v_recursosJugador[casa_elegida];
}

void setRecursosInicialesJugador(int numCasaElegida, std::vector<float>& v_recursosJugador) {
    v_recursosJugador[oro] = getOroInicialSegunCasa(numCasaElegida); // oro del jugador
    v_recursosJugador[comida] = 0; //  comida del jugador
    v_recursosJugador[soldados] = 0; //  soldados del jugador
    v_recursosJugador[chance_hab_activa] = getChanceHabActivaInicialSegunCasa(numCasaElegida); // % de activacion de la habilidad activa del jugador
    v_recursosJugador[casa_elegida] = numCasaElegida; // id de la casa elegida
    v_recursosJugador[comida_x_batallon] = getCostoComidaxBatallonSegunCasa(numCasaElegida);
}

void evaluarPartida(int estadisticas[], bool& perdiste, bool& ganaste){
        perdiste = estadisticas[cantidad_rondas_perdidas]>=4;
        ganaste = estadisticas[cantidad_rondas_ganadas] >= 3;//cambiar
}

void inicioDeJuego(int estadisticas[], int casaElegida) {

    /// Variables del juego
    vector<float> recursosJugador(largo_vector_recursos);
    int rondaActual = 0;
    /// variables de menu principal
    int cin_opcion_menu;

    // inicializacion de los recursos del jugador
    setRecursosInicialesJugador(casaElegida, recursosJugador);

    // menu principal
    cout << "CASA SELECCIONADA: " << getNombreCasaSeleccionada(casaElegida)<<endl;
    system("pause");
    bool perdiste=false;
    bool ganaste=false;
    while(!perdiste && !ganaste) { //mientras Perdiste==false
        mostrarMenuPrincipal(casaElegida, recursosJugador, rondaActual);
        cin >> cin_opcion_menu;
        switch(cin_opcion_menu) {
            case idx_opcion_menu_batalla:
                menuBatalla(casaElegida, recursosJugador, rondaActual, estadisticas);
                system("pause");
                evaluarPartida(estadisticas, perdiste, ganaste);
                break;
            case idx_opcion_menu_tienda:
                menuTienda(recursosJugador, casaElegida, estadisticas);
                break;
            case idx_opcion_menu_volver:
                return;
        }
    }
    if(ganaste){
        cout << "Ganaste el juego." << endl;
        system("pause");
    }
    if(perdiste){
        cout << "Perdiste el juego." << endl;
        system("pause");
    }
}
