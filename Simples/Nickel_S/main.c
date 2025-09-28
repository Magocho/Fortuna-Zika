#include <stdio.h>
#include <stdlib.h>
#include "logica_ROLO.h"
#include "rolo_SDL.h"



int main(){
    placar* estatistica = malloc(sizeof(placar));
    estatistica->derrota = 0;
    estatistica->vitoria = 0;
    srand(time(NULL));
    int fila1[5] = {1, 2, 3, 4, 5 }; // TRANSFORMAR ISSO EM UM TXT...
    int fila2[4][6] = {
        {1, 2, 2, 3, 4, 5},
        {1, 2, 3, 4, 5, 3},
        {1, 2, 3, 4, 5, 4},
        {1, 2, 3, 4, 5, 1}
    };
    slot* MaqZika[5];

    //***********************************************
    MaqZika[0] = cria_slot(5, 'A');                     // Automatizar isso depois
    MaqZika[1] = cria_slot(6, 'B');
    MaqZika[2] = cria_slot(6, 'C');
    MaqZika[3] = cria_slot(6, 'C');
    MaqZika[4] = cria_slot(6, 'C');
    aloca_valor_no_rolo_de_slot(MaqZika[0], fila1, 5);   // Isso também
    aloca_valor_no_rolo_de_slot(MaqZika[1], fila2[0], 6);
    aloca_valor_no_rolo_de_slot(MaqZika[2], fila2[1], 6);
    aloca_valor_no_rolo_de_slot(MaqZika[3], fila2[2], 6);
    aloca_valor_no_rolo_de_slot(MaqZika[4], fila2[3], 6);
    //***********************************************
    printf("Hello world! %d\n", simula_slot(MaqZika[0]));

    inicio();
    cria_Tela();
    loop(MaqZika, 5, estatistica);
    termina_sdl();

    return 0;
}
