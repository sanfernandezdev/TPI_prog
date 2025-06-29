#include <iostream>
#include "menues.h"
#include "sesionDeJuego.h"
#include "indicesVectores.h"

using namespace std;

int main()
{
    int estadisticas[largo_vector_estadisticas]={};

    inicioDeJuego(estadisticas, seleccionDeCasa());

    cout<<"Elegi volver de mi sesion."<<endl;

    mostrarEstadisticas(estadisticas, largo_vector_estadisticas);
    system("pause");

}
