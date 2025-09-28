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
SDL_Color ROXO_CLARO = {200, 162, 200, 255};
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

void botao_custom(float eixo_X, float eixo_Y, char* texto, Ppersonagem* dados, SDL_FRect* aux){
        botao(eixo_X, eixo_Y, texto, &dados->dimensao, aux, ROXO_CLARO);
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

void contar_bilac(int* estrela, int visto){
    switch(visto){
        case 1:
            if(*estrela / 10000)
                *estrela = *estrela - 10000;
            break;
        case 2:
            if((*estrela / 1000) % 10)
                *estrela = *estrela - 2000;
            break;
        case 3:
            if((*estrela / 100) % 10)
                *estrela = *estrela - 300;
            break;
        case 4:
            if((*estrela / 10) % 10)
                *estrela = *estrela - 40;
            break;
        case 5:
            if(*estrela % 10)
                *estrela = *estrela - 5;
            break;
    }
}

void FACE_imagem(int eixo_x, int eixo_y, int numero, SDL_FRect* Botao_caixa, SDL_FRect* Imagem_caixa, int tamanho) {

    char path[21];
    SDL_snprintf(path, sizeof(path), "Persona/face%d.png", numero);
    gTexture = IMG_LoadTexture(gRenderer, path);

    Imagem_caixa->w = 400 / tamanho;
    Imagem_caixa->h = 400 / tamanho;

    Botao_caixa->x = eixo_x;
    Botao_caixa->y = eixo_y;
    Botao_caixa->w = Imagem_caixa->w + 10;
    Botao_caixa->h = Imagem_caixa->h + 10;

    Imagem_caixa->x = Botao_caixa->x + (Botao_caixa->w - Imagem_caixa->w) / 2.0f;
    Imagem_caixa->y = Botao_caixa->y + (Botao_caixa->h - Imagem_caixa->h) / 2.0f;

    SDL_RenderTexture(gRenderer, gTexture, NULL, Imagem_caixa);
}

void CHAPEU_imagem(int eixo_x, int eixo_y, int numero, SDL_FRect* Botao_caixa, SDL_FRect* Imagem_caixa, int tamanho) {

    char path[21];
    SDL_snprintf(path, sizeof(path), "Persona/chapeu%d.png", numero);
    gTexture = IMG_LoadTexture(gRenderer, path);

    Imagem_caixa->w = 200 / tamanho;
    Imagem_caixa->h = 200 / tamanho;

    Botao_caixa->x = eixo_x;
    Botao_caixa->y = eixo_y;
    Botao_caixa->w = Imagem_caixa->w + 10;
    Botao_caixa->h = Imagem_caixa->h + 10;

    Imagem_caixa->x = Botao_caixa->x + (Botao_caixa->w - Imagem_caixa->w) / 2.0f;
    Imagem_caixa->y = Botao_caixa->y + (Botao_caixa->h - Imagem_caixa->h) / 2.0f;

    SDL_RenderTexture(gRenderer, gTexture, NULL, Imagem_caixa);
}


void loop(slot** lista_slot, int tamanho, placar* estatistica){

    SDL_FRect* Botao_caixa = malloc(sizeof(SDL_FRect));
    SDL_FRect* aux = malloc(sizeof(SDL_FRect));

	int num = 0;
	bool tentou = false;
    bool quit = false;
    bool girar_visivel = true;
    bool ok_visivel = false;
    bool mensagem = true;

    int j, i = 0;
    SDL_Event evento;
    SDL_zero(evento);

    SDL_FRect* Botao_Level = malloc(sizeof(SDL_FRect));
    SDL_FRect* Botao_NOME = malloc(sizeof(SDL_FRect));
    Ppersonagem* Botao_PERSONA = malloc(sizeof(Ppersonagem) * 2);
    bool level_missao = true; //false true

    //*********

    bool text_input_complete = false;
    char text[50] = {0};
    SDL_Rect area = {50, 150, 300, 300};
    int cursor = 0;
    SDL_SetTextInputArea(gWindow, &area, cursor);
    SDL_StartTextInput(gWindow);

    //***********
    for(j = 0; j < 2; j++)
        Botao_PERSONA->contador = 0;

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
                            if(level_missao){
                                level_missao = false;
                            }
                            else
                                level_missao = true;
                        }

                        if(clicou_no_botao(Botao_NOME, mx, my)){
                            SDL_StartTextInput(gWindow);
                            memset(text, 0, sizeof(text));
                            text_input_complete = false;
                        }
                        if(clicou_no_botao(&Botao_PERSONA->dimensao, mx, my)){
                            Botao_PERSONA->contador++;
                            if(Botao_PERSONA->contador >= 5)
                                Botao_PERSONA->contador = 0;
                        }
                        if(clicou_no_botao(&(Botao_PERSONA + 1)->dimensao, mx, my)){
                            (Botao_PERSONA + 1)->contador++;
                            if((Botao_PERSONA + 1)->contador >= 7 )
                                (Botao_PERSONA + 1)->contador = 0;
                        }
                    }
                }
            else
                if(evento.type == SDL_EVENT_KEY_DOWN) {
                    /* the pressed key was Escape or Return? */
                    if (evento.key.key == SDLK_ESCAPE || evento.key.key == SDLK_RETURN) {
                        SDL_StopTextInput(gWindow);
                        text_input_complete = true;
                    }
                    /* Handle arrow keys, etc. */
                }
                else
                    if(evento.type == SDL_EVENT_TEXT_INPUT){
                        SDL_strlcat(text, evento.text.text, sizeof(text));
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 173, 216, 230, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);

        //*****************************************************************
        if(level_missao){

            if(!text_input_complete){
                SDL_SetTextInputArea(gWindow, &area, cursor);
            }
            else{
                botao(75, 150, "MUDAR", Botao_NOME, aux, VERM_ESC);
            }

            botao_custom(75, 300, "OUTRA FACE", Botao_PERSONA, aux);
            botao_custom(75, 400, "OUTRO CAPELO", (Botao_PERSONA + 1), aux);
            FACE_imagem(440, 175, Botao_PERSONA->contador, Botao_Level, aux, 1);
            CHAPEU_imagem(540, 25, (Botao_PERSONA + 1)->contador, Botao_Level , aux,1);
            botao(150, 75, text, Botao_Level, aux, BRANCO);
            botao(50, 75, "NOME:", Botao_Level, aux, AMARELO);
            botao(1000, 320, "VOLTAR", Botao_Level, aux, BRANCO);
            i = 1;
        }
        else{
            titulo_na_tela1();

            FACE_imagem(1010, 100, Botao_PERSONA->contador, Botao_Level, aux, 2);
            CHAPEU_imagem(1060, 25, (Botao_PERSONA + 1)->contador, Botao_Level , aux, 2);

            if(!girar_visivel){
                mensagem = false;
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
                    }
                    if(!mensagem){
                        if(num == 4 || num == 6)
                            botao(75,200, "> Nunca vi tantos iguais antes! Vamos em frente!", Botao_Level, aux, LARANJA);
                        if(num == 2 || num == 3)
                            botao(75,200, "> Uma trinca sempre ajuda!", Botao_Level, aux, LARANJA);
                        if(estatistica->vitoria - num == 0)
                            botao(75,200, "> Primeiros pontos, muito bem!", Botao_Level, aux, LARANJA);
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

            botao(75, 150, text, Botao_Level, aux,BRANCO);

            if(mensagem)
                botao(75,200, "> Serei seu ajudante, vamos girar!", Botao_Level, aux, LARANJA);

            botao(300, 70, "PERSONAGEM", Botao_Level, aux, BRANCO);

        }

        SDL_RenderPresent(gRenderer);

    }
}

