#include<iostream>
#include<conio.h>
#include "menues.h"
#include "indicesVectores.h"
#include "constantesJuego.h"
#include "admBatallas.h"
#include "admCasas.h"

using namespace std;

int seleccionDeCasa(){
    int opcion;
    cout << "---------------------------------------"               << endl;
    cout << "            Juego de Tronos            "               << endl;
    cout << "---------------------------------------"               << endl;
    cout << "          SELECCIONE LA CASA           "               << endl;
    cout << "---------------------------------------"               << endl;
    cout << "1- LANNISTER " <<endl;
    cout << "2- STARK     " <<endl;
    cout << "3- TARGARYEN"<<endl;
    cout << "4- BARATHEON " <<endl;
    cout << "---------------------------------------"               << endl;
    cin>>opcion;
    return opcion;
}

void mostrarEstadisticas(int estadisticas[], int tam){
    system("cls");
    cout << "---------------------------------------"               << endl;
    cout <<"Estadisticas de la ultima partida: "<<endl;
    cout << "---------------------------------------"               << endl;
    cout<<" batalla_cantidad_victorias ="<<estadisticas[batalla_cantidad_victorias]<<endl;
    cout<<" batalla_cantidad_derrotas  ="<<estadisticas[batalla_cantidad_derrotas]<<endl;
    cout<<" total_gastado_oro          ="<<estadisticas[total_ganado_oro]<<endl;
    cout<<" total_gastado_comida       ="<<estadisticas[total_gastado_comida]<<endl;
    cout<<" total_gastado_soldados     ="<<estadisticas[total_ganado_soldados]<<endl;
    cout<<" total_ganado_oro           ="<<estadisticas[total_ganado_oro]<<endl;
    cout<<" total_ganado_comida        ="<<estadisticas[total_ganado_oro]<<endl;
    cout<<" total_ganado_soldados      ="<<estadisticas[total_ganado_soldados]<<endl;
    cout << "---------------------------------------"  << endl;
}

void mostrarRecursosJugador(const vector<float> recursosJugador){
    cout << "> " << getNombreCasaSeleccionada(recursosJugador[casa_elegida]) << endl;
    printHabilidadesSegunCasa(recursosJugador[casa_elegida]);
    cout << "|presupuesto inicial : " << getOroInicialSegunCasa(recursosJugador[casa_elegida]) << endl;
    cout << "|oro                 : " << recursosJugador[oro] << endl;
    cout << "|comida              : " << recursosJugador[comida] << endl;
    cout << "|soldados            : " << recursosJugador[soldados] << endl;
    cout << "|activa              : " << recursosJugador[chance_hab_activa] << endl;
    cout << "---------------------------------------" << endl;
    //getche();
}

void mostrarMenuPrincipal(int casaElegida, const std::vector<float>& recursosJugador, int batalla_actual) {
    system("cls");
    cout << "---------------------------------------" << endl;
    cout << "            Juego de Tronos            " << endl;
    cout << "---------------------------------------" << endl;
    mostrarRecursosJugador(recursosJugador);
    cout << "|batallas realizadas : " << batalla_actual << endl;
    cout << "1. IR A LA BATALLA" << endl;
    cout << "2. TIENDA" << endl;
    cout << "3. SALIR" << endl;
    cout << "---------------------------------------" << endl;
    cout << "OPCION: ";
}

void mostrarNumeroDeBatalla(int batalla_actual, int duracion_guerra){
    if (batalla_actual == duracion_guerra) {
        cout << "~~ ULTIMA BATALLA ~~\n" << endl;
    }
    cout << "Batalla NRO " << batalla_actual << endl;
}

void mostrarMensajePostBatalla(bool resultado){
    if(resultado){
        cout << "Ganaste la ronda!" << endl;
    }else{
        cout << "Perdiste la ronda!" << endl;
    }
} // a definir

void mostrarRecursosPreBatalla(const std::vector<float>& recursosJugador) {
    cout << "Soldados: " << recursosJugador[soldados] << endl;
    cout << "Comida: " << recursosJugador[comida] << endl;
    cout << "Probabilidad de activa: " << recursosJugador[chance_hab_activa] << endl;
    cout << endl;
}
void menuBatalla(int casaElegida, std::vector<float>& recursosJugador, int& rondaActual, int estadisticas[]){
    int cin_batalla_deseas_continuar;
    if (rondaActual > maxRondas) {
        cout << "No hay mas batallas por luchar, puedes descansar!" << endl;
        system("pause");
        return;
    }
    mostrarRecursosPreBatalla(recursosJugador);
    cout << "Deseas continuar a la batalla? 1(SI) / 2(NO)\nopcion: ";
    cin >> cin_batalla_deseas_continuar;
    if (cin_batalla_deseas_continuar == 2){
        cout << "Volviendo al menu anterior..."<<endl;
        system("pause");
        return;
    } else {
        system("cls");
        // LOGICA DE BATALLA
        bool resultadoBatalla;
        resultadoBatalla= iniciarBatalla(rondaActual, recursosJugador, casaElegida, estadisticas);
        mostrarMensajePostBatalla(resultadoBatalla);
    }
}

void menuTienda(vector<float>& recursosJugador, int casaElegida, int estadisticas[]) {

    const float articulo_mejora_activa = getArticuloMejoraHabilidadActivaSegunCasa(casaElegida);
    const float valor_x_articulo_soldado = getValorSoldadoSegunCasa(casaElegida) * articulo_soldados;
    const int valor_x_mejora_activa = getCostoMejorarHabilidadActivaSegunCasa(casaElegida);

    int cin_opcion_tienda = 0;

    //refactorizar(pendiente)
    while (true) {
        if (cin_opcion_tienda == idx_opcion_tienda_volver) break;
        system("cls");
        mostrarRecursosJugador(recursosJugador);
        cout << "TIENDA" << endl;
        cout << "---------------------------------------" << endl;
        cout << "1. Soldados          $" << valor_x_articulo_soldado << " x por " << articulo_soldados << " soldados" << endl;
        cout << "2. Comida            $" << valor_x_comida << " x " << articulo_comida << " unidades." << endl;
        cout << "3. Mejorar activa    $" << valor_x_mejora_activa << " x +" << articulo_mejora_activa << endl;
        cout << "4. Volver al menu principal" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Opcion: ";
        cin >> cin_opcion_tienda;
        system("cls");

        switch (cin_opcion_tienda) {
            case idx_opcion_tienda_soldados:
                if (recursosJugador[oro] >= valor_x_articulo_soldado) {
                    recursosJugador[soldados] += articulo_soldados;
                    recursosJugador[oro] -= valor_x_articulo_soldado;
                    estadisticas[total_gastado_oro] += valor_x_articulo_soldado;
                } else {
                    cout << "No tienes oro suficiente!" << endl;
                    system("pause");
                }
                break;
            case idx_opcion_tienda_comida:
                if (recursosJugador[oro] >= valor_x_comida) {
                    recursosJugador[comida] += articulo_comida;
                    recursosJugador[oro] -= valor_x_comida;
                    estadisticas[total_gastado_comida] += valor_x_comida;
                } else {
                    cout << "No tienes oro suficiente!" << endl;
                    system("pause");
                }
                break;
            case idx_opcion_tienda_mejora_activa:
                if (recursosJugador[oro] >= valor_x_mejora_activa) {
                    recursosJugador[chance_hab_activa] += articulo_mejora_activa;
                    recursosJugador[oro] -= valor_x_mejora_activa;
                } else {
                    cout << "No tienes oro suficiente!" << endl;
                    system("pause");
                }
                break;
            case idx_opcion_tienda_volver:
                break;
        }}
    }
