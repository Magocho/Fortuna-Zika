#include "logica_ROLO.h"
#include <time.h>

/* AQUI, encontra-se a lógica das funções de operação do slot */

slot* cria_slot(int tamanho, char id){
    assert(tamanho > 0);                 // Fazer um ERRO, ao invés de matar o progama.
    slot* novo = malloc(sizeof(slot));
    novo->id = id;                      // ACHO, que nínguém colocará dois id iguais... ink ink...
    novo->tamanho_do_rolo = tamanho;
    novo->rolo = malloc(sizeof(int) * tamanho);
    novo->ultimo_valor = 0;
    return novo;
}

void destroi_rolo(slot* qualquer){
    free(qualquer->rolo);
    free(qualquer);
}

void aloca_valor_no_rolo_de_slot(slot* destino, int* fila_valor, int tamanho_fila){
    assert(tamanho_fila == destino->tamanho_do_rolo); // Aqui mudar por avisos de ERRO pelo id
    int i = 0;
    while(i < tamanho_fila){
        *(destino->rolo + i) = *(fila_valor + i);
        i++;
    }
}

int simula_slot(slot* destino){
    int chance = rand() % destino->tamanho_do_rolo;
    int resultado = *(destino->rolo + chance);
    destino->ultimo_valor = resultado;
    return resultado;
}

int ganhou(slot** lista_slot){
    int valor = 0, aux, i, j;

    for(i = 1; i < 6; i++){
        aux = 0;
        j = 0;
        while(j < 5){
            if(i == (*(lista_slot + j))->ultimo_valor)
                aux++;
            j++;
        }
        if(aux >= 3){
            switch(aux){
                case 3:
                    valor = 2;
                    break;
                case 4:
                    valor = 4;
                    break;
                case 5:
                    valor = 25;
                    break;
            }
            if(i == 5){
                switch(valor){
                    case 2:
                        valor++;
                        break;
                    case 4:
                        valor = valor + 2;
                        break;
                    case 25:
                        valor = 100;
                        break;
                }
            }
            break;
        }
    }

    return valor;
}
