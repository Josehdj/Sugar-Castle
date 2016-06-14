#include <allegro.h>
#define NITERACOES 100
#include <time.h>


int posX=0;
float x=0;//posição x da tela
float y=340;//posição do personagem
bool bloqueia_pers = false;
bool bloqueia_queda = false;


bool esperarTempo(int iteracoes,bool ativa)
{
    static int tempo_inicial=iteracoes;
    if(ativa && tempo_inicial==0)
    {
        tempo_inicial=iteracoes;
        return true;
    }
    else if(tempo_inicial>0)
    {
        tempo_inicial--;
        return true;
    }
    return false;
}



void moverPersonagemDireita(BITMAP *sprite, BITMAP *buffer, int tamanhox, int tamanhoy, int px,int py)
{
    static bool ativa=true;
    static int atual=0;
    esperarTempo(NITERACOES,ativa);
    ativa=false;
    masked_blit(sprite,buffer,atual*tamanhox+4,tamanhoy+4,px,py,tamanhox-10,tamanhoy);
    if(!esperarTempo(NITERACOES,ativa))
    {
        atual=(atual+1)%4;
        ativa=true;
    }
}
void moverPersonagemEsquerda(BITMAP *sprite, BITMAP *buffer, int tamanhox, int tamanhoy, int px, int py)
{
    static bool ativa=true;
    static int atual=0;
    esperarTempo(NITERACOES,ativa);
    ativa=false;
    masked_blit(sprite,buffer,atual*tamanhox+4,tamanhoy+4,px,py,tamanhox-10,tamanhoy);
    if(!esperarTempo(NITERACOES,ativa))
    {
        atual=(atual+1)%4;
        ativa=true;
    }
}
