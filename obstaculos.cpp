
#define menor( a, b ) (a < b) ? a : b //retorna menor valor
#define COR_TRANSPARENTE makecol( 255, 0, 255 )
typedef struct FIGURA{
 int x;
 int y;
 int largura;
 int altura;
 BITMAP *imagem;
}Figura;
typedef struct QUADRADO{ //retângulo da área dobreposta
 int esquerda;
 int direita;
 int cima;
 int baixo;
}Quadrado;
//checa colisão por BoundingBox
int checaBoundingBox( Figura *figura1, Figura *figura2 ){
 int esquerda1, direita1, cima1, baixo1;
 int esquerda2, direita2, cima2, baixo2;

 esquerda1 = figura1->x;
 direita1 = figura1->x + figura1->largura;
 cima1 = figura1->y;
 baixo1 = figura1->y + figura1->altura;

 esquerda2 = figura2->x;
 direita2 = figura2->x + figura2->largura;
 cima2 = figura2->y;
 baixo2 = figura2->y + figura2->altura;

 if( esquerda1 > direita2 )
 return 0;
 if( direita1 < esquerda2 )
 return 0;
 if( cima1 > baixo2 )
 return 0;
 if( baixo1 < cima2 )
 return 0;

 return 1;
}
void achaQuadradoSobreposto( Figura *figura1, Figura *figura2, Quadrado *quadrado ){
 int esquerda1, direita1, cima1, baixo1;
 int esquerda2, direita2, cima2, baixo2;

 esquerda1 = figura1->x;
 direita1 = figura1->x + figura1->largura;
 cima1 = figura1->y;
 baixo1 = figura1->y + figura1->altura;

 esquerda2 = figura2->x;
 direita2 = figura2->x + figura2->largura;
 cima2 = figura2->y;
 baixo2 = figura2->y + figura2->altura;

 quadrado->esquerda = maior( esquerda1, esquerda2 );
 quadrado->direita = menor( direita1, direita2 );
 quadrado->cima = maior( cima1, cima2 );
 quadrado->baixo = menor( baixo1, baixo2 );
}
int checaColisaoPixel( Figura *figura1, Figura *figura2, Quadrado *quadrado ){
 int x, y, i, j;
 int pixel1, pixel2;

 for( i = quadrado->esquerda; i < quadrado->direita; i++ ){
 for( j = quadrado->cima; j < quadrado->baixo; j++ ){

 x = i - figura1->x; //acha coordenada x do quadrado comum na figura 1
 y = j - figura1->y; //acha coordenada y do quadrado comum na figura 1
 pixel1 = getpixel( figura1->imagem, x, y ); //pega pixel na figura 1

 x = i - figura2->x; //acha coordenada x do quadrado comum na figura 2
 y = j - figura2->y; //acha coordenada y do quadrado comum na figura 2
 pixel2 = getpixel( figura2->imagem, x, y ); //pega pixel na figura 2

 if( ( pixel1 != COR_TRANSPARENTE ) && ( pixel2 != COR_TRANSPARENTE) ){
 return 1; //Colisão!!!
 }
 }
 }
 return 0; //não-colisão
}
int realizaPixelPerfect( Figura *figura1, Figura *figura2 ){
 Quadrado quadrado;

 if( checaBoundingBox( figura1, figura2 ) == 1 ){
 achaQuadradoSobreposto( figura1, figura2, &quadrado );
 return checaColisaoPixel( figura1, figura2, &quadrado );
 }
 return 0;
}
