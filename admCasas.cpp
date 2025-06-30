#include<iostream>
#include "constantesJuego.h"

using namespace std;

const int cant_casas_en_juego = 3;


const string vector_nombre_casas[cant_casas_en_juego] = {"LANNISTER", "STARK", "TARGARYEN" };

const int v_oro_inicial_segun_casa[cant_casas_en_juego] = {75000, //ORO LANNISTER
                                                            50000,  //ORO STARK
                                                            50000}; //ORO TARGARYEN

const int v_costo_batallon_segun_casa[cant_casas_en_juego] = {10000, 8500, 12500};

const float v_costo_comida_batallon_segun_casa[cant_casas_en_juego] = {5000,5000,5000};

const float v_chanceHabActiva_segun_casa[cant_casas_en_juego] = {0.15, 0.3 ,0.1};

const int v_costos_mejorar_habilidad_activa_segun_casa[cant_casas_en_juego] = {10000, 8500, 25000};

const float v_porcentaje_mejora_habilidad_activa_segun_casa[cant_casas_en_juego] = {0.05,-0.05, 0.10};

int getCostoMejorarHabilidadActivaSegunCasa(int numCasa){
    return v_costos_mejorar_habilidad_activa_segun_casa[numCasa - 1];
}

float getArticuloMejoraHabilidadActivaSegunCasa(int numCasaElegida){
    return v_porcentaje_mejora_habilidad_activa_segun_casa[numCasaElegida -1];
}

float getValorSoldadoSegunCasa(int numCasaElegida){
    return ((float)v_costo_batallon_segun_casa[numCasaElegida - 1]) / 10000;
}

int getOroInicialSegunCasa(int numCasaElegida){
    return v_oro_inicial_segun_casa[numCasaElegida - 1];
}

float getCostoComidaxBatallonSegunCasa(int numCasaElegida){
    return v_costo_comida_batallon_segun_casa[numCasaElegida - 1] ;
}

float getChanceHabActivaInicialSegunCasa(int numCasaElegida){
    return v_chanceHabActiva_segun_casa[numCasaElegida - 1];
}

string getNombreCasaSeleccionada(int numCasaElegida){
    return vector_nombre_casas[numCasaElegida - 1];
}

void printHabilidadesSegunCasa(int numCasaElegida){
    switch(numCasaElegida){
        case id_lannister:
            cout << "---------------------------------------" << endl;
            cout << "Pasiva: Tras cada batalla recuperas un +50%" << endl;
            cout << "del oro correspondiente a los soldados caidos durante la batalla." << endl;
            cout << "---------------------------------------" << endl;
            cout << "Activa: Obtenes +30% de oro al ganar la batalla" << endl;
            cout << "---------------------------------------" << endl;
            break;
        case id_stark:
            cout << "---------------------------------------" << endl;
            cout << "Pasiva: El porcentaje de tropas perdidas en" << endl;
            cout << "cada batalla se reduce un (nro de ronda*1%)." << endl;
            cout << "---------------------------------------" << endl;
            cout << "Activa: Tropas rinden un 20% menos en combate." << endl;
            cout << "---------------------------------------" << endl;
            break;
        case id_targaryen:
            cout << "---------------------------------------" << endl;
            cout << "Pasiva: Tus tropas son +35%  efectivas." << endl;
            cout << "---------------------------------------" << endl;
            cout << "Activa: Invocar Dragon (Automaticamente ganas" << endl;
            cout << "la batalla pero quema un 20% de las tropas enviadas)." << endl;
            cout << "---------------------------------------" << endl;
            break;
    }
}

