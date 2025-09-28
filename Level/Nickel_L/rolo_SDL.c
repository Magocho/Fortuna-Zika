#include "rolo_SDL.h"
/* Aqui fica a parte gráfica e sua lógica */

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Surface* gSurface = NULL;
TTF_Font* gFonte = NULL;
SDL_Color PRETO = {0, 0, 0, 255};
SDL_Color VERDE = {102, 255, 102, 255};
SDL_Color BRANCO = {255, 255, 255, 255};
SDL_Color VERM_ESC = {200, 30, 30, 255};
SDL_Color LARANJA = {255, 165, 0, 255};
SDL_Color AMARELO = {255, 255, 0, 255};

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

void botao(int eixo_x, int eixo_y, char* enunciado, SDL_FRect* Botao_caixa, SDL_FRect* Texto_caixa, SDL_Color cor_meio){

    gSurface = TTF_RenderText_Blended(gFonte, enunciado, 0,PRETO);

    gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);

    SDL_GetTextureSize(gTexture, &Texto_caixa->w, &Texto_caixa->h);

    Botao_caixa->x = eixo_x;
    Botao_caixa->y = eixo_y;
    Botao_caixa->w = Texto_caixa->w + 10;
    Botao_caixa->h = Texto_caixa->h + 10;

    Texto_caixa->x = Botao_caixa->x + (Botao_caixa->w - Texto_caixa->w) / 2.0f;
    Texto_caixa->y = Botao_caixa->y + (Botao_caixa->h - Texto_caixa->h) / 2.0f;

    SDL_SetRenderDrawColor(gRenderer, cor_meio.r, cor_meio.g, cor_meio.b, cor_meio.a);
    SDL_RenderFillRect(gRenderer, Botao_caixa);

    SDL_SetRenderDrawColor(gRenderer, PRETO.r, PRETO.g, PRETO.b, PRETO.a);
    SDL_RenderRect(gRenderer, Botao_caixa);

    SDL_RenderTexture(gRenderer, gTexture, NULL, Texto_caixa);
}

void botao_imagem(int eixo_x, int eixo_y, int numero, SDL_FRect* Botao_caixa, SDL_FRect* Imagem_caixa) {

    switch(numero){
        case 1:
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/morango.png");
            break;
        case 2:
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/framboesa.png");
            break;
        case 3:
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/uva.png");
            break;
        case 4:
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/maca.png");
            break;
        case 5:
            gTexture = IMG_LoadTexture(gRenderer, "Imagem/estrela.png");
            break;
    }

    Imagem_caixa->w = 200;
    Imagem_caixa->h = 200;

    Botao_caixa->x = eixo_x;
    Botao_caixa->y = eixo_y;
    Botao_caixa->w = Imagem_caixa->w + 10;
    Botao_caixa->h = Imagem_caixa->h + 10;

    Imagem_caixa->x = Botao_caixa->x + (Botao_caixa->w - Imagem_caixa->w) / 2.0f;
    Imagem_caixa->y = Botao_caixa->y + (Botao_caixa->h - Imagem_caixa->h) / 2.0f;

    SDL_SetRenderDrawColor(gRenderer, 245, 245, 220, 255);
    SDL_RenderFillRect(gRenderer, Botao_caixa);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderRect(gRenderer, Botao_caixa);

    SDL_RenderTexture(gRenderer, gTexture, NULL, Imagem_caixa);
}

void ligar_botoes(SDL_FRect* botao1, SDL_FRect* botao2, SDL_Color cor_linha) {
    float x1 = botao1->x + botao1->w / 2.0f;
    float y1 = botao1->y + botao1->h / 2.0f;

    float x2 = botao2->x + botao2->w / 2.0f;
    float y2 = botao2->y + botao2->h / 2.0f;

    SDL_SetRenderDrawColor(gRenderer, cor_linha.r, cor_linha.g, cor_linha.b, cor_linha.a);
    SDL_RenderLine(gRenderer, x1, y1, x2, y2);
}

void score(int valor, int x, int y){
    char texto[5];
    sprintf(texto, "%d", valor);

    gSurface = TTF_RenderText_Blended(gFonte, texto, 0, PRETO);

    gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);

    SDL_FRect distancia;
    const float escala = 1.0f;

    SDL_GetRenderOutputSize(gRenderer, 0, 0);
    SDL_SetRenderScale(gRenderer, escala, escala);
    SDL_GetTextureSize(gTexture, &distancia.w, &distancia.h);

    distancia.x = x;
    distancia.y = y;

    SDL_RenderTexture(gRenderer, gTexture, NULL, &distancia);
}

bool clicou_no_botao(SDL_FRect* Botao, float inicio_x, float inicio_y){
    if(inicio_x >= Botao->x && inicio_x <= Botao->x + Botao->w && inicio_y >= Botao->y && inicio_y <= Botao->y + Botao->h)
        return true;
    return false;
}

void botao_skill(float eixo_X, float eixo_Y, Blevel* dados, SDL_FRect* aux){
    if(dados->ativado)
        botao(eixo_X, eixo_Y, "MAIS 10", &dados->dimensao, aux, VERM_ESC);
    else
        botao(eixo_X, eixo_Y, "MAIS 10", &dados->dimensao, aux, BRANCO);
}

void barra_level(int eixo_x, int eixo_y, int altura, int comprimento, SDL_FRect* Botao_caixa, SDL_Color cor_meio){

    Botao_caixa->x = eixo_x;
    Botao_caixa->y = eixo_y;
    Botao_caixa->w = comprimento;
    Botao_caixa->h = altura;

    SDL_SetRenderDrawColor(gRenderer, cor_meio.r, cor_meio.g, cor_meio.b, cor_meio.a);
    SDL_RenderFillRect(gRenderer, Botao_caixa);

    SDL_SetRenderDrawColor(gRenderer, PRETO.r, PRETO.g, PRETO.b, PRETO.a);
    SDL_RenderRect(gRenderer, Botao_caixa);
}

void completude_barra(int eixo_x, int eixo_y, int altura, int comprimento, SDL_FRect* Botao_caixa, SDL_Color cor_meio, int* numVitoria, int limite, int* NNivel){

    float porcentagem = *numVitoria / (float)limite;

    if(*numVitoria >= limite){
        *numVitoria = *numVitoria - limite;
        *NNivel = *NNivel + 1;
        return;
    }

    if(porcentagem == 0)
        return;

    Botao_caixa->x = eixo_x;
    Botao_caixa->y = eixo_y;
    Botao_caixa->w = comprimento * porcentagem;
    Botao_caixa->h = altura;

    SDL_SetRenderDrawColor(gRenderer, cor_meio.r, cor_meio.g, cor_meio.b, cor_meio.a);
    SDL_RenderFillRect(gRenderer, Botao_caixa);

    SDL_SetRenderDrawColor(gRenderer, PRETO.r, PRETO.g, PRETO.b, PRETO.a);
    SDL_RenderRect(gRenderer, Botao_caixa);
}

void loop(slot** lista_slot, int tamanho, placar* estatistica){

    SDL_FRect* Botao_caixa = malloc(sizeof(SDL_FRect));
    SDL_FRect* aux = malloc(sizeof(SDL_FRect));

	int num = 0, nivel = 0, numLevel = 0;
	bool tentou = false;
    bool quit = false;
    bool girar_visivel = true;
    bool ok_visivel = false;

    int j, i = 0;
    SDL_Event evento;
    SDL_zero(evento);

    SDL_FRect* Botao_Level = malloc(sizeof(SDL_FRect));
    Blevel* dados_Botao = malloc(sizeof(Blevel) * 7);
    bool level_tela = false; //false true

    for(j = 0; j < 7; j++)
        (dados_Botao + j)->ativado = false;

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

                    if(clicou_no_botao(Botao_caixa, mx, my)){
                        if(girar_visivel){
                            girar_visivel = false;
                            ok_visivel = true;
                        }
                        else{
                            girar_visivel = true;
                            ok_visivel = false;
                        }
                    }

                    if(clicou_no_botao(Botao_Level, mx, my)){
                        if(level_tela)
                            level_tela = false;
                        else
                            level_tela = true;
                    }

                    if(level_tela && nivel > 0){
                        for(j = 0; j < 7; j++)
                            if(clicou_no_botao(&((dados_Botao + j)->dimensao), mx, my)){
                                if(!(dados_Botao + j)->ativado)
                                    switch(j){
                                        case 0:
                                            (dados_Botao + j)->ativado = true;
                                            nivel--;
                                            break;
                                        case 1:
                                            if(!((dados_Botao)->ativado))
                                                break;
                                            (dados_Botao + j)->ativado = true;
                                            nivel--;
                                            break;
                                        case 2:
                                            if(!((dados_Botao)->ativado))
                                            break;
                                            (dados_Botao + j)->ativado = true;
                                            nivel--;
                                            break;
                                        case 3:
                                            if(!((dados_Botao + 1)->ativado))
                                                break;
                                            (dados_Botao + j)->ativado = true;
                                            nivel--;
                                            break;
                                        case 4:
                                            if(!((dados_Botao + 2)->ativado))
                                                break;
                                            (dados_Botao + j)->ativado = true;
                                            nivel--;
                                            break;
                                        case 5:
                                            if(!((dados_Botao + 1)->ativado))
                                                break;
                                            (dados_Botao + j)->ativado = true;
                                            nivel--;
                                            break;
                                        case 6:
                                            if(!((dados_Botao + 2)->ativado))
                                                break;
                                            (dados_Botao + j)->ativado = true;
                                            nivel--;
                                            break;
                                        default:
                                            break;
                                    }
                            }
                    }
                }
        }

        SDL_SetRenderDrawColor(gRenderer, 173, 216, 230, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);

        //*****************************************************************
        if(level_tela){

            for(j = 0; j < 7; j++){
                switch(j){
                    case 0:
                        botao_skill(240, 320, (dados_Botao + j), aux);
                        break;
                    case 1:
                        botao_skill(480, 200, (dados_Botao + j), aux);
                        ligar_botoes(&dados_Botao->dimensao, &(dados_Botao + j)->dimensao, VERM_ESC);
                        break;
                    case 2:
                        botao_skill(480, 440, (dados_Botao + j), aux);
                        ligar_botoes(&dados_Botao->dimensao, &(dados_Botao + j)->dimensao, VERM_ESC);
                        break;
                    case 3:
                        botao_skill(720, 100, (dados_Botao + j), aux);
                        ligar_botoes(&(dados_Botao + 1)->dimensao, &(dados_Botao + j)->dimensao, VERM_ESC);
                        break;
                    case 4:
                        botao_skill(720, 360, (dados_Botao + j), aux);
                        ligar_botoes(&(dados_Botao + 2)->dimensao, &(dados_Botao + j)->dimensao, VERM_ESC);
                        break;
                    case 5:
                        botao_skill(720, 260, (dados_Botao + j), aux);
                        ligar_botoes(&(dados_Botao + 1)->dimensao, &(dados_Botao + j)->dimensao, VERM_ESC);
                        break;
                    case 6:
                        botao_skill(720, 540, (dados_Botao + j), aux);
                        ligar_botoes(&(dados_Botao + 2)->dimensao, &(dados_Botao + j)->dimensao, VERM_ESC);
                        break;
                }
            }

            botao(50, 75, "PONTOS", Botao_Level, aux, VERDE);
            score(nivel, 175, 80);
            botao(1000, 320, "VOLTAR", Botao_Level, aux, BRANCO);
        }
        else{
            titulo_na_tela1();

            barra_level(75, 200, 50, 500, Botao_caixa, BRANCO);

            if(numLevel > 0)
                completude_barra(75, 200, 50, 500, Botao_caixa, LARANJA, &numLevel, 10, &nivel);

            if(!girar_visivel){
                if(tentou){
                    for(j = 0; j < tamanho; j++){
                        botao_imagem((50 + 250 * j), 320, simula_slot(*(lista_slot + j)), Botao_caixa, aux);
                    }
                    num = ganhou(lista_slot);
                }
                else{
                    for(j = 0; j < tamanho; j++){
                        botao_imagem((50 + 250 * j), 320, (*(lista_slot + j))->ultimo_valor, Botao_caixa, aux);
                    }
                }

                if(num > 0){
                    botao(600, 50, "Eh Zika mesmo!", Botao_caixa, aux, VERDE);
                    if(tentou){
                        estatistica->vitoria = estatistica->vitoria + num;
                        numLevel = num + numLevel;
                    }
                }
                tentou = false;
            }

            if(girar_visivel){
                botao(640, 100, "girar", Botao_caixa, aux, VERDE);
                i = 1;
                tentou = true;
            }

            if(ok_visivel){
                botao(760, 100, "OK", Botao_caixa, aux, VERDE);
            }

            score(estatistica->vitoria, 1000, 100);

            if(nivel > 0)
                botao(300, 70, "Melhoria", Botao_Level, aux, AMARELO);
            else
                botao(300, 70, "Melhoria", Botao_Level, aux, BRANCO);
        }


        SDL_RenderPresent(gRenderer);
    }
}
}
