#include<iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "indicesVectores.h"
#include "constantesJuego.h"
#include "sesionDeJuego.h"
#include "menues.h"
#include "admCasas.h"

using namespace std;

float sumarChancesSegunSoldados(int tropas){
    return (tropas%6500)*0.1f;
}

float getChanceGanarSegunRonda(int rondaActual) {
    return v_chances_ganar_ronda[rondaActual-1];
}

float getCostoComidaPorSoldado(float costoPorBatallon, int soldadosPorBatallon){
    return costoPorBatallon / soldadosPorBatallon;
}

int getComidaGastadaRonda(int cantSoldados, std::vector<float>& recursosJugador, int casaElegida){
     float costo_alimentar_soldado = getCostoComidaPorSoldado(getCostoComidaxBatallonSegunCasa(casaElegida), soldados_x_batallon);
     int auxResult =cantSoldados / costo_alimentar_soldado;
     cout << "En esta batalla gastas "  << auxResult <<" comida alimentar a tus soldados. "<< endl;
     return auxResult;
}

int getTotalPuedeAlimentar(const std::vector<float> recursosJugador){
    int casaElegida = getNumCasaElegida(recursosJugador);
    float costo_alimentar_soldado = getCostoComidaPorSoldado(getCostoComidaxBatallonSegunCasa(casaElegida), soldados_x_batallon); // distinto segun cada casa
    return static_cast<int>(recursosJugador[comida] * costo_alimentar_soldado);
}

int getTropasListas(const std::vector<float> recursosJugador){
    int soldadosComprados =  static_cast<int>(recursosJugador[soldados]);
    int puedeAlimentar = getTotalPuedeAlimentar(recursosJugador);
    if (soldadosComprados < puedeAlimentar) {
        return soldadosComprados;
    } else {
        return puedeAlimentar;
    }
}

bool seActivoChanceHab(float chance_hab){
    srand(static_cast<unsigned int>(time(0)));
    return  (static_cast<float>(rand()) / RAND_MAX) < chance_hab;
}

bool seGanoRonda(float chance_hab){
    srand(static_cast<unsigned int>(time(0)));
    return  (static_cast<float>(rand()) / RAND_MAX) < chance_hab;
}

void ejecutarActiva(std::vector<float>& recursosJugador, bool& rondaGanada, int& oroAGanar, int& tropasListas){
    int casaElegida = getNumCasaElegida(recursosJugador);
    switch (casaElegida) {
        case id_lannister :
        //Obtener 30% más de oro al ganar la batalla
        oroAGanar+= oroAGanar * 0.3;
        cout << "Obtienes un +30% de oro = " << oroAGanar << endl;
        break;
        case id_stark :
        //Tropas rinden un 20% menos en combate.
        tropasListas -= tropasListas*0.2;
        cout << "Tus tropas rinden un -20% (" << tropasListas << " soldados) " << endl;
        break;
        case id_targaryen :
        //Invocar Dragón (Automáticamente gana la batalla pero quema un 20% de las tropas enviadas).
        rondaGanada=true;
        int soldadosPerdidos = tropasListas *0.2;
        recursosJugador[soldados] -= soldadosPerdidos;
        cout << "Ganaste pero pierdes = " << soldadosPerdidos << " soldados." << endl;
        break;
    }
}

int getOroAGanar(int rondaActual, std::vector<float>& recursosJugador){
    return 10000 + (rondaActual * 5000);
}

int getTropasCaidas(int rondaActual, int combatientes_reales){
    float auxPorcentajeAPerder = 5.0f * rondaActual;
    float auxResult = (auxPorcentajeAPerder / 100.0f) * combatientes_reales;
    return static_cast<int>(auxResult);
}

void ejecutarPasiva(std::vector<float>& recursosJugador, int rondaActual, int casaElegida, int& tropasCaidas, int& tropasListas, int& tropasAdicionales){
    switch (casaElegida) {
        case id_lannister :{
            // Tras cada batalla recuperan un 50% del oro correspondiente a los soldados caídos durante la batalla.
            float oro_a_recuperar = getValorSoldadoSegunCasa(casaElegida) * tropasCaidas * 0.5;
            recursosJugador[oro] += oro_a_recuperar;
            cout << "Gracias a tu habilidad pasiva recuperas "  << oro_a_recuperar << " de oro por el 50% del costo de " << tropasCaidas << " soldados caidos en batalla. (costo por soldado "
            << getValorSoldadoSegunCasa(casaElegida) <<")."<< endl;
        break;
        }
        case id_stark: {
          //  El porcentaje de tropas perdidas en cada batalla se reduce un (nro de ronda*1%)
          float porcentajeTropasARecuperar = 0.01f * rondaActual;
          float auxTropasRecuperar =  porcentajeTropasARecuperar * tropasListas;
          int auxTropasRecuperarInt =  static_cast<int>(auxTropasRecuperar);
          tropasCaidas += auxTropasRecuperarInt;
          recursosJugador[soldados] += auxTropasRecuperarInt;
          cout << "Gracias a tu habilidad pasiva recuperas "  << porcentajeTropasARecuperar << "% de los soldados caidos en batalla, que representan "<< auxTropasRecuperarInt <<endl;
        break;
        }

        case id_targaryen:
            //Sus tropas son un 35% más efectivas.
            tropasAdicionales += tropasListas*0.35;
            cout << "Gracias a tu habilidad pasiva tus tropas rinden un +35% " << endl;

        break;
    }
}


// cada batalla resta tropas, resta comida, ganas o perdes la batalla en si, y suma oro si ganas
bool iniciarBatalla(int& rondaActual, std::vector<float>& recursosJugador, int casaElegida, int estadisticas[]) {
    // si la ronda no se pasa del limite de rondas (ejecuta hasta la ultima inclusive)
    if (rondaActual <= maxRondas){
        bool rondaGanada = false;
        // incremento ronda y muestro mensaje con num de batalla
        rondaActual++;
        int oroAGanar=10000+(rondaActual*5000);
        int tropasAdicionales=0;
        mostrarNumeroDeBatalla(rondaActual, maxRondas);

        // obtengo los soldados que van a pelear segun comida disponible y muestro
        int auxTropasListasRonda = getTropasListas(recursosJugador);
        cout << "Combaten " <<auxTropasListasRonda << " soldados." <<endl;
        // si son 0 tropas no muestro nada y pierdo la ronda ---

        // calculo tropas caidas, muestro y resto de los recursos
        int auxTropasCaidasRonda = getTropasCaidas(rondaActual, auxTropasListasRonda);
        recursosJugador[soldados] -= auxTropasCaidasRonda; // resto las tropas que va a perder
        cout << "En la batalla pierdes " << auxTropasCaidasRonda << " soldados." <<endl;

        // calculo comida a gastar, muestro y resto
        int auxComidaGastadaRonda = getComidaGastadaRonda(auxTropasListasRonda, recursosJugador, casaElegida);
        recursosJugador[comida] -= auxComidaGastadaRonda;
        cout << "En la batalla pierdes " << auxComidaGastadaRonda << " comida." <<endl;

        // habilidad pasiva siempre se ejecuta
        ejecutarPasiva(recursosJugador, rondaActual, casaElegida, auxTropasCaidasRonda, auxTropasListasRonda, tropasAdicionales);

         // habilidad activa ejecuta si se activa segun porcentaje
        if (seActivoChanceHab(recursosJugador[chance_hab_activa])) {
            cout << "Activa: " << endl;
            ejecutarActiva(recursosJugador, rondaGanada, oroAGanar, auxTropasListasRonda);
        }
        auxTropasListasRonda+=tropasAdicionales;

        if (rondaGanada){
            estadisticas[cantidad_rondas_ganadas]++;
            recursosJugador[oro]+= oroAGanar;
            return true;
        } else {
            //no ganaste todavia, se debe evaluar y en base a eso
            float chancesDeGanar = sumarChancesSegunSoldados(auxTropasListasRonda) + getChanceGanarSegunRonda(rondaActual);
            if (seGanoRonda(chancesDeGanar)) {
                estadisticas[cantidad_rondas_ganadas]++;
                recursosJugador[oro]+= oroAGanar;
                return true;

            } else { // perdiste la ronda
                // sumarle 1 a batallas perdidas en estadisticas
            }
        system("pause");
        return false;
        }
    }
}


