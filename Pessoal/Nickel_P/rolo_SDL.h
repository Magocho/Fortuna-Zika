#ifndef ROLO_SDL_H_INCLUDED
#define ROLO_SDL_H_INCLUDED

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include<stdio.h>
#include <string.h>
#include "logica_ROLO.h"

typedef struct para_o_personagem{
    SDL_FRect dimensao;
    int contador;
} Ppersonagem;

bool inicio();
bool cria_Tela();
void termina_sdl();
void desenha_todos_estados();
void texto_na_tela();
void loop(slot** lista_slot, int tamanho, placar* score);



#endif // ROLO_SDL_H_INCLUDED
