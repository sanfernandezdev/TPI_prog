#ifndef CONSTANTESJUEGO_H_INCLUDED
#define CONSTANTESJUEGO_H_INCLUDED

    //constantes config juego
    const int maxRondas = 10;
    const int vidasTotales = 4;
    const int soldados_x_batallon = 10000;
    const float v_chances_ganar_ronda[maxRondas] = {
        0.50, // Ronda 1
        0.45, // Ronda 2
        0.40, // Ronda 3
        0.35, // Ronda 4
        0.30, // Ronda 5
        0.25, // Ronda 6
        0.20, // Ronda 7
        0.15, // Ronda 8
        0.10, // Ronda 9
        0.10  // Ronda 10
    };

    // menu principal
    const int idx_opcion_menu_batalla = 1;
    const int idx_opcion_menu_tienda  = 2;
    const int idx_opcion_menu_volver  = 3;

    // ID casas
    const int id_lannister = 1;
    const int id_stark  = 2;
    const int id_targaryen = 3;

    // tienda
    const int articulo_soldados= 1000;
    const int articulo_comida = 10000; // UNIDADES DE COMIDA
    const int valor_x_comida = 500;

    const int idx_opcion_tienda_soldados = 1;
    const int idx_opcion_tienda_comida = 2;
    const int idx_opcion_tienda_mejora_activa = 3;
    const int idx_opcion_tienda_volver = 4;



#endif // CONSTANTESJUEGO_H_INCLUDED
