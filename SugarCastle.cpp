#include <allegro.h>
#include <time.h>
#include "menu.h"
#include "movimento.h"
#define NITERACOES 100
#include <math.h>



void init();
void deinit();
void incrementa();
void jogar();
int menu();
bool grounded;
int auxground= 340;//controle em relação ao solo
//inicializaão das variaveis
int cont;
int largura = 107;//largura do personagem
int altura = 60;//altura do personagem
int frame_atual =0;
int tempo_troca =100;
int num_frame =2;

bool isJumping = false;


int vetObj[4] = {410,515,1057,1173};
int vetObj_Y[2] = {333,267};

volatile int milisegundos;//controle de FPS
void msec_counter(){milisegundos++;}
END_OF_FUNCTION(msec_counter)





void incrementa(){//contador para o FPS
    cont++;
}


//####################################FUNÇÃOD E COLISÃO#######################################

bool colideLado(int ax1,int ay1,int ax2,int ay2,int bx1,int by1,int bx2,int by2){
        if(abs(ax2-bx1)<3){
            if(by1>ay1 && by1<ay2)return true;
            if(by2>ay1 && by1<ay2)return true;
            if(ay1>by1 && ay1<by2)return true;

        }
        return false;
}
bool colide (int ax1,int ay1,int ax2,int ay2,int bx1,int by1,int bx2,int by2){
    if(colideLado(ax1,ay1,ax2,ay2,bx1,by1,bx2,by2))return true;
    if(colideLado(bx1,by1,bx2,by2,ax1,ay1,ax2,ay2))return true;
    if(colideLado(ay1,ax1,ay2,ax2,by1,bx1,by2,bx2))return true;
    if(colideLado(by1,bx1,by2,bx2,ay1,ax1,ay2,ax2))return true;

        return false;

}
bool verificaGround(int Ax1,int Ay1,int Ax2, int Ay2,int Bx1, int By1, int Bx2, int By2)
{
    if(Ax2 > Bx1 && Ax1 < Bx2 && Ay2 == By1)
    {
        return true;

    }
    return false;
}
//#################################JOGO COMPLETO################################################

void jogar()//Jogo após selecionado no Menu
{



install_int_ex(incrementa,MSEC_TO_TIMER(5));//contador de fps


    milisegundos =0;//controlar animação da sprite
    LOCK_FUNCTION(msec_counter);
    LOCK_VARIABLE(milisegundos);
    install_int_ex(msec_counter,MSEC_TO_TIMER(10));

//###################################ESTRUTURAS####################################################
   typedef struct
    {
        int x;
        int y;
        int tamx;
        int tamy;
    }BLOCO;

    BLOCO bloco1;
    bloco1.x = 410;
    bloco1.y = 333;
    bloco1.tamx = 20;
    bloco1.tamy = 66;//tamanhos do primeiro bloco do cenario




    typedef struct
    {
        int pos_pers_mundo;
        int pos_pers_tela;
        int pos_pers_x;
        int pos_y;  //2000 de tamanho
        int pos_tam;


        BITMAP *person; //ponteiro de bit para pers
    } PERSONAGEM;


    typedef struct
    {
        int pos_sprite;
        int sprite_atual;
        int sprite_limite;

        BITMAP *sprites[2]; //ponteiro de bit para sprites
    } SPRITES;

    PERSONAGEM jogador;
    jogador.pos_pers_mundo=0;
    jogador.pos_pers_tela=0;
    jogador.pos_pers_x=0;
    jogador.pos_y=340;

    SPRITES tela;
    tela.pos_sprite=0;
    tela.sprite_atual=0;
    tela.sprite_limite=2000;
//####################################################################################
    //abrir as imagens


    tela.sprites[0]=load_bitmap("cenario.bmp",NULL);
    tela.sprites[1]=load_bitmap("cenario2.bmp",NULL);
    //tela.sprites[2]=load_bitmap("sprite4.bmp",NULL);

    jogador.person=load_bitmap("sugar.bmp",NULL);

    //double buffer
    BITMAP *buffer=create_bitmap(2000,400);

    bool andando_direita=false,
         andando_esquerda=false,
         pulando=false;
         cont=1;
    int Person_w = jogador.person -> w;



    while (!key[KEY_ESC])
    {


        frame_atual =(milisegundos / tempo_troca) % num_frame;

        while(cont>0){

                cont--;//contador fps
        //imprime as sprites
        int nsprite=tela.sprite_atual;//pega a sprite atual
        for(int i=0; i<2; i++)
        {
            //começa imprimindo da sprite atual usando um buffer circular
            blit(tela.sprites[nsprite],buffer,0,0,(i*2000)+tela.pos_sprite,0,2000,400);
            nsprite=(nsprite+1) % 2;//atualiza o numero da sprite
        }
        //verifica o estado ativo de acao
        if(andando_direita)
        {

            moverPersonagemDireita(jogador.person, buffer, 108, 69, jogador.pos_pers_tela,jogador.pos_y);


        }
        else if(andando_esquerda)
        {
            moverPersonagemDireita(jogador.person, buffer, 108, 144, jogador.pos_pers_tela,jogador.pos_y);
        }
        else
        {
            masked_blit(jogador.person,buffer,frame_atual*112,1,jogador.pos_pers_tela,jogador.pos_y,109,68);
        }

        //retorna o estado ativo de acao ao normal
        andando_direita=andando_esquerda=false;
        //imprime tudo no monitor
        blit(  buffer, screen, 0,0,0,0,2000,400);


//##########################MOVIMENTAÇÃO PELO TECLADO####################################


        if(key[KEY_RIGHT])
        {

            jogador.pos_pers_mundo++; //move pers no mundo
            jogador.pos_pers_tela++;  //move pers na tela


            if(colide(jogador.pos_pers_mundo,jogador.pos_y,jogador.pos_pers_mundo+81,jogador.pos_y+69,bloco1.x,bloco1.y,bloco1.x+bloco1.tamx,bloco1.y+bloco1.tamy)){
                  jogador.pos_pers_mundo--;
                   jogador.pos_pers_tela--;
                }

            if(jogador.pos_pers_tela>600)
            {
                jogador.pos_pers_tela--; //recupera mov pers
                tela.pos_sprite--; //move tela


               if(colide(jogador.pos_pers_mundo,jogador.pos_y,jogador.pos_pers_mundo+81,jogador.pos_y+69,bloco1.x,bloco1.y,bloco1.x+bloco1.tamx,bloco1.y+bloco1.tamy)){
                jogador.pos_pers_mundo--;


                }


                if((tela.pos_sprite % 2000)==0)  //se tela chegou ao limite
                {
                    //muda a sprite atual
                    tela.sprite_atual=(tela.sprite_atual +1) % 3;
                    tela.pos_sprite=0; //reseta a posicao
                }
            }

                    andando_direita = true;



        }//FIM IF
        else if(key[KEY_LEFT])
        {

            jogador.pos_pers_mundo--; //move pers no mundo
            jogador.pos_pers_tela--;  //move pers na tela

            if(colide(jogador.pos_pers_mundo-65,jogador.pos_y,jogador.pos_pers_mundo+15,jogador.pos_y+69,bloco1.x,bloco1.y,bloco1.x+bloco1.tamx,bloco1.y+bloco1.tamy)){
                  jogador.pos_pers_mundo++;
                   jogador.pos_pers_tela++;
                }
            if(jogador.pos_pers_tela<100)
            {
                jogador.pos_pers_tela++; //recupera mov pers
                tela.pos_sprite++; //move tela

                if(colide(jogador.pos_pers_mundo,jogador.pos_y,jogador.pos_pers_x,jogador.pos_y+69,bloco1.x,bloco1.y,bloco1.x+bloco1.tamx,bloco1.y+bloco1.tamy)){
                jogador.pos_pers_mundo++;


                }
                if(((tela.pos_sprite-1) % 2000)==0)  //se tela chegou ao limite
                {
                    //muda a sprite atual
                    tela.sprite_atual--;
                    tela.sprite_atual=(tela.sprite_atual<0?2:tela.sprite_atual);
                    tela.pos_sprite=-1999; //reseta a posicao
                }
            }
            andando_esquerda=true;
        }//FIM IF
  //###########################################################################
            if(jogador.pos_y == 340 || jogador.pos_y == auxground) {//teste para o pulo do personagem

                    grounded = true;

            }else{
                    grounded=false;
            }
 //############################################################################
if(colide(jogador.pos_pers_mundo,jogador.pos_y+210,jogador.pos_pers_mundo+81,jogador.pos_y+60,bloco1.x,bloco1.y,bloco1.x+bloco1.tamx,bloco1.y+bloco1.tamy)){
                        auxground = jogador.pos_y;
                        grounded= true;

                    }
                    else{
                        auxground = 340;
                    }
            if(key[KEY_UP]&& grounded){
                    isJumping = true;

                }//FIM IF

            if(isJumping){
                    jogador.pos_y--;





                if(jogador.pos_y == 250){
                    isJumping = false;
                }

            }if(!isJumping && jogador.pos_y < 340){
                jogador.pos_y++;


            }

        }
    }

}


int main()
{

int menu();
    init();
    int opcao=0;

    while(opcao!=2){
        opcao=menu();
        if(opcao ==1)
            jogar();
    } //fim da escolha do menu


    deinit();
    return 0;


}

END_OF_MAIN();
void init()
{
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if (depth == 0) depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 400, 0, 0);
    if (res != 0)
    {
        allegro_message(allegro_error);
        exit(-1);
    }

    install_timer();
    install_keyboard();
    install_mouse();
    /* add other initializations here */
}

void deinit()
{
    clear_keybuf();
    /* add other deinitializations here */
}

