#ifndef ADMCASAS_H_INCLUDED
#define ADMCASAS_H_INCLUDED
#include <string>
using std::string;

// get valores iniciales segun casa
int getOroInicialSegunCasa(int numCasa);
float getChanceHabActivaInicialSegunCasa(int numCasa);
// obtener valores de tienda segun casa
float getValorSoldadoSegunCasa(int numCasa);
float getCostoComidaxBatallonSegunCasa(int numCasa);
// get string del nombre
string getNombreCasaSeleccionada(int numCasa);
// referido a habilidades
int getCostoMejorarHabilidadPasivaSegunCasa(int numCasa);
int getCostoMejorarHabilidadActivaSegunCasa(int numCasa);
float getArticuloMejoraHabilidadActivaSegunCasa(int numCasa);
// print info pasiva/activa segun casa
void printHabilidadesSegunCasa(int numCasaElegida);


#endif // CASAS_H_INCLUDED
