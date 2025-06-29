#ifndef BATALLAS_H_INCLUDED
#define BATALLAS_H_INCLUDED


float getChanceGanarSegunRonda(int rondaActual);
bool iniciarBatalla(int& rondaActual, std::vector<float>& recursosJugador, int casaElegida, int estadisticas[]);
bool evaluarHabActiva(const std::vector<float>& recursosJugador);
float sumarChancesSegunSoldados(int tropas);
bool seGanoRonda(float chance_hab);

#endif // BATALLAS_H_INCLUDED
