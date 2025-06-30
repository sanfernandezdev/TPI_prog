#ifndef SESIONDEJUEGO_H_INCLUDED
#define SESIONDEJUEGO_H_INCLUDED
#include <vector>
#include "admCasas.h"


void evaluarPartida(int estadisticas[], bool& perdiste, bool& ganaste);
void inicioDeJuego(int estadisticas[], int casaElegida);
// funciones relacionadas al inicio del juego ----------
void setRecursosInicialesSegunCasaElegida(int numCasa);
int getNumCasaElegida(std::vector<float> v_recursosJugador);

#endif // SESIONDEJUEGO_H_INCLUDED
