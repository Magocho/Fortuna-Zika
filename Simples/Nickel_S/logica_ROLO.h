#ifndef LOGICA_ROLO_H_INCLUDED
#define LOGICA_ROLO_H_INCLUDED

/* AQUI, encontra-se a funções de operação do slot */

#include <time.h>
#include <stdlib.h>
#include <assert.h>

typedef struct numero{
    int vitoria;
    int derrota;
} placar;

typedef struct slot{
    char id;
    int* rolo;
    int tamanho_do_rolo;
    int ultimo_valor;
} slot;

slot* cria_slot(int tamanho, char id);

void destroi_rolo(slot* qualquer);

void aloca_valor_no_rolo_de_slot(slot* destino, int* fila_valor, int tamanho_fila);
int simula_slot(slot* destino);
int ganhou(slot** lista_slot);

#endif // LOGICA_ROLO_H_INCLUDED
