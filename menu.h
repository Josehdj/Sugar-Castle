#include <allegro.h>

int menu()
{   //criação do buffer para o menu
    BITMAP *buffer = create_bitmap(800,400);
    BITMAP *botao1 = load_bitmap("jogar.bmp",NULL);
    BITMAP *botao2 = load_bitmap("sair.bmp",NULL);
    BITMAP *fundo = load_bitmap("fundo.bmp",NULL);

    while (true){
            //renderiza o menu
            blit(fundo, buffer, 0,0,0,0,800,400);
           masked_blit(botao1, buffer,0,0,270, 200,250,50);
           masked_blit(botao2, buffer,0,0,270, 250,250,50);
    //produz o comportamento do mouse passando por cima
           if(mouse_x>160 && mouse_x<410 &&
              mouse_y>200 && mouse_y<250){
                  masked_blit(botao1, buffer,0,0,270, 200,250,50);
           }else if(mouse_x>160 && mouse_x<410 &&
              mouse_y>250 && mouse_y<300){
                  masked_blit(botao2, buffer,0,0,270, 250,250,50);
           }

          //se houver o click do mouse, retornar o valor
           if(mouse_b & 1){
                if(mouse_x>160 && mouse_x<410 &&
                   mouse_y>200 && mouse_y<250){
                         return 1;
                }else if(mouse_x>160 && mouse_x<410 &&
                   mouse_y>250 && mouse_y<300){
                         return 2;
                }
           }

           show_mouse(buffer);
           blit(buffer, screen, 0,0,0,0,800,400);

    }
    }






