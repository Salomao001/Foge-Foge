#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'

int praondefantamavai(int xatual, int yatual, int* xdestino, int* ydestino);
void move(char direcao);
int acabou();
int ehdirecao(char direcao);
void fantasma();
void explodepilula();
void explodepilula2(int x, int y, int somax, int somay, int qntd);

#endif