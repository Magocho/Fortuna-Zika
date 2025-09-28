#include "rolo_SDL.h"
/* Aqui fica a parte gráfica e sua lógica */

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Surface* gSurface = NULL;
TTF_Font* gFonte = NULL;
SDL_Color PRETO = {0, 0, 0, 255};


bool inicio() {
	bool success = SDL_Init(SDL_INIT_VIDEO);
    if( !success ){
        SDL_Log("Initialization failed! Cuz: %s\n", SDL_GetError());
    }
    TTF_Init();
	return success;
}

bool cria_Tela(){
	const int Largura_da_tela = 1280;
	const int Altura_da_tela = 640;

	gWindow = SDL_CreateWindow("FortunaZikaA", Largura_da_tela, Altura_da_tela, 0);

    gFonte = TTF_OpenFont("LiberationMono-Regular.ttf", 24.0f);

    gRenderer = SDL_CreateRenderer(gWindow, NULL);

	return true;
}


void termina_sdl() {

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyTexture(gTexture);
    SDL_DestroySurface(gSurface);
    TTF_CloseFont(gFonte);
    TTF_Quit();
    SDL_Quit();
}

void titulo_na_tela2() {
    const char* texto = "Fortuna Zika";
    int num_letras = strlen(texto);

    SDL_Color cores[] = {
        {255, 0, 0, 255},     // Vermelho
        {255, 165, 0, 255},   // Laranja
        {255, 255, 0, 255},   // Amarelo
        {0, 128, 0, 255},     // Verde
        {0, 0, 255, 255},     // Azul
        {75, 0, 130, 255},    // Índigo
        {238, 130, 238, 255}, // Violeta
        {255, 20, 147, 255},  // Rosa forte
        {128, 0, 0, 255},     // Vinho
        {0, 0, 0, 255}        // Preto
    };

    float x = 75.0f;
    float y = 75.0f;

    for (int i = 0; i < num_letras; ++i) {
        char letra_str[2] = { texto[i], '\0' };

        SDL_Color cor = cores[i % (sizeof(cores)/sizeof(cores[0]))];

        // Renderiza letra em surface
        SDL_Surface* letra_surface = TTF_RenderText_Blended(gFonte, letra_str, 0, cor);
        if (!letra_surface) {
            SDL_Log("Erro ao renderizar letra: %s", SDL_GetError());
            continue;
        }

        // Cria textura da surface
        SDL_Texture* letra_texture = SDL_CreateTextureFromSurface(gRenderer, letra_surface);
        SDL_DestroySurface(letra_surface);
        if (!letra_texture) {
            SDL_Log("Erro ao criar textura: %s", SDL_GetError());
            continue;
        }

        SDL_FRect dst;
        SDL_GetTextureSize(letra_texture, &dst.w, &dst.h);

        dst.x = x;
        dst.y = y;

        SDL_RenderTexture(gRenderer, letra_texture, NULL, &dst);

        x += dst.w; // Move posição para próxima letra

        SDL_DestroyTexture(letra_texture);
    }
}




void titulo_na_tela1(){

    gSurface = TTF_RenderText_Blended(gFonte, "Fortuna Zika", 0, PRETO);

    gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);

    SDL_FRect distancia;
    const float escala = 1.0f;

    SDL_GetRenderOutputSize(gRenderer, 0, 0);
    SDL_SetRenderScale(gRenderer, escala, escala);
    SDL_GetTextureSize(gTexture, &distancia.w, &distancia.h);

    distancia.x = 75;
    distancia.y = 75;

    SDL_RenderTexture(gRenderer, gTexture, NULL, &distancia);
}

//**************** SÓ AGORA DESCOBRI QUE ISSO TAMBÉM TINHA QUE SER GLOBAL OU PONTEIROS...
SDL_FRect Botao_caixa;
SDL_FRect Texto_caixa;
SDL_FRect Imagem_caixa;
//**************

void botao(int eixo_x, int eixo_y, char* enunciado){

    //SDL_FRect Botao_caixa;
    //SDL_FRect Texto_caixa;

    gSurface = TTF_RenderText_Blended(gFonte, enunciado, 0,PRETO);

    gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);

    SDL_GetTextureSize(gTexture, &Texto_caixa.w, &Texto_caixa.h);

    Botao_caixa.x = eixo_x;
    Botao_caixa.y = eixo_y;
    Botao_caixa.w = Texto_caixa.w + 10;
    Botao_caixa.h = Texto_caixa.h + 10;

    Texto_caixa.x = Botao_caixa.x + (Botao_caixa.w - Texto_caixa.w) / 2.0f;
    Texto_caixa.y = Botao_caixa.y + (Botao_caixa.h - Texto_caixa.h) / 2.0f;

    SDL_SetRenderDrawColor(gRenderer, 102, 255, 102, 255);
    SDL_RenderFillRect(gRenderer, &Botao_caixa);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderRect(gRenderer, &Botao_caixa);

    SDL_RenderTexture(gRenderer, gTexture, NULL, &Texto_caixa);
}

void botao_imagem(int eixo_x, int eixo_y, int numero) {

    switch(numero){
        case 1:
            //gTexture = IMG_LoadTexture(gRenderer, "Imagem/Final3.jpg");
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/morango.png");
            break;
        case 2:
            //gTexture = IMG_LoadTexture(gRenderer, "Imagem/chefe.png");
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/framboesa.png");
            break;
        case 3:
            //gTexture = IMG_LoadTexture(gRenderer, "Imagem/inimigo.png");
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/uva.png");
            break;
        case 4:
            //gTexture = IMG_LoadTexture(gRenderer, "Imagem/linend.png");
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/maca.png");
            break;
        case 5:
            //gTexture = IMG_LoadTexture(gRenderer, "Imagem/sarur.png");
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/estrela.png");
            break;
    }
    SDL_GetTextureSize(gTexture, &Imagem_caixa.w, &Imagem_caixa.h);

    Imagem_caixa.w = 200;
    Imagem_caixa.h = 200;

    Botao_caixa.x = eixo_x;
    Botao_caixa.y = eixo_y;
    Botao_caixa.w = Imagem_caixa.w + 10;
    Botao_caixa.h = Imagem_caixa.h + 10;

    Imagem_caixa.x = Botao_caixa.x + (Botao_caixa.w - Imagem_caixa.w) / 2.0f;
    Imagem_caixa.y = Botao_caixa.y + (Botao_caixa.h - Imagem_caixa.h) / 2.0f;

    SDL_SetRenderDrawColor(gRenderer, 245, 245, 220, 255);
    SDL_RenderFillRect(gRenderer, &Botao_caixa);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderRect(gRenderer, &Botao_caixa);

    SDL_RenderTexture(gRenderer, gTexture, NULL, &Imagem_caixa);
}

void score(int valor){
    char texto[5];
    sprintf(texto, "%d", valor);

    gSurface = TTF_RenderText_Blended(gFonte, texto, 0, PRETO);

    gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);

    SDL_FRect distancia;
    const float escala = 1.0f;

    SDL_GetRenderOutputSize(gRenderer, 0, 0);
    SDL_SetRenderScale(gRenderer, escala, escala);
    SDL_GetTextureSize(gTexture, &distancia.w, &distancia.h);

    distancia.x = 1000;
    distancia.y = 100;

    SDL_RenderTexture(gRenderer, gTexture, NULL, &distancia);
}

void loop(slot** lista_slot, int tamanho, placar* estatistica) {

	int num;
	bool tentou = false;
    bool quit = false;
    bool girar_visivel = true;
    bool ok_visivel = false;
    int j, i = 0;
    SDL_Event evento;
    SDL_zero(evento);

    while(!quit){

        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_EVENT_QUIT){
                quit = true;
            }
            else
                if(evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN && i != 0){
                    if(evento.button.button == SDL_BUTTON_LEFT){
                        float mx = evento.button.x;
                        float my = evento.button.y;

                    if (mx >= Botao_caixa.x && mx <= Botao_caixa.x + Botao_caixa.w && my >= Botao_caixa.y && my <= Botao_caixa.y + Botao_caixa.h){
                        if(girar_visivel){
                            girar_visivel = false;
                            ok_visivel = true;
                        }
                        else{
                            girar_visivel = true;
                            ok_visivel = false;
                        }
                    }
                }

        }

        SDL_SetRenderDrawColor(gRenderer, 173, 216, 230, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);

        titulo_na_tela1();

        if(!girar_visivel){
            if(tentou){
                for(j = 0; j < tamanho; j++){
                    botao_imagem((50 + 250 * j), 320, simula_slot(*(lista_slot + j)));
                }
                num = ganhou(lista_slot);
            }
            else{
                for(j = 0; j < tamanho; j++){
                    botao_imagem((50 + 250 * j), 320, (*(lista_slot + j))->ultimo_valor);
                }
            }

            if(num > 0){
                botao(600, 50, "Eh Zika mesmo!");
                if(tentou)
                    estatistica->vitoria = estatistica->vitoria + num;
            }
            tentou = false;
        }

        if(girar_visivel){
            botao(640, 100, "girar");
            i = 1;
            tentou = true;
        }

        if(ok_visivel){
            botao(760, 100, "OK");
        }

        score(estatistica->vitoria);


        SDL_RenderPresent(gRenderer);
    }
}
}
