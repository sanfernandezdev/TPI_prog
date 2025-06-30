#ifndef BATALLAS_H_INCLUDED
#define BATALLAS_H_INCLUDED


float getChanceGanarSegunRonda(int rondaActual);
void iniciarBatalla(int& rondaActual, std::vector<float>& recursosJugador, int casaElegida, int estadisticas[], bool& rondaGanada);
bool evaluarHabActiva(const std::vector<float>& recursosJugador);
float sumarChancesSegunSoldados(int tropas);
bool seGanoRonda(float chance_hab);
void ejecutarPasiva(std::vector<float>& recursosJugador, int rondaActual, int casaElegida, int& tropasCaidas, int& tropasListas, int& tropasAdicionales, int estadisticas[]);

#endif // BATALLAS_H_INCLUDED
