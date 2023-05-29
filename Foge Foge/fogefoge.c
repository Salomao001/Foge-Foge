#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;

int praondefantamavai(int xatual, int yatual, int* xdestino, int* ydestino) {
	int opcoes[4][2] = {{xatual, yatual+1}, {xatual+1, yatual}, {xatual, yatual-1}, {xatual-1, yatual}};

	srand(time(0));
	for(int i; i < 10; i++) {
		int posicao = rand() % 4;

		if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];

			return 1;
			
		}
	}
	return 0;
}

void fantasma() {
	MAPA copia;

	copiamapa(&copia, &m);

	for(int i = 0; i < m.linhas; i++) {
		for(int j = 0; j < m.colunas; j++) {

			if (copia.matriz[i][j] == FANTASMA) {

				int xdestino;
				int ydestino;

				int encontrou = praondefantamavai(i, j, &xdestino, &ydestino);
				if(encontrou) {
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}	
	liberamapa(&copia);
}

int acabou() {
	POSICAO pos;
	int fogefogenomapa = encontramapa(&m, &pos, HEROI);
	return !fogefogenomapa;
}

int ehdirecao(char direcao) {
	return(direcao == CIMA ||
		direcao == ESQUERDA ||
		direcao == BAIXO ||
		direcao == DIREITA);

}

void move(char direcao) {

	if(!ehdirecao(direcao))
		return;

	int proximox = heroi.x;
	int proximoy = heroi.y;

	switch(direcao) {
		case 'a':
			proximoy--;
			break;
		case 'd':
			proximoy++;
			break;
		case 'w':
			proximox--;
			break;
		case 's':
			proximox++;
			break;
	} 

	if(!podeandar(&m, HEROI, proximox, proximoy))
		return;


	if(ehpersonagem(&m, PILULA, proximox, proximoy))
		tempilula = 1;

	andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;

}

void explodepilula(){
	if(!tempilula) return;

	explodepilula2(heroi.x, heroi.y, 0, 1, 3);
	explodepilula2(heroi.x, heroi.y, 0, -1, 3);
	explodepilula2(heroi.x, heroi.y, 1, 0, 3);
	explodepilula2(heroi.x, heroi.y, -1, 0, 3);

	tempilula = 0;
}

void explodepilula2(int x, int y, int somax, int somay, int qntd) {
	if(qntd == 0) return;

	int novox = x + somax;
	int novoy = y + somay;

	if(!ehvalido(&m, novox, novoy)) return;
	if(ehparede(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = VAZIO;
	explodepilula2(novox, novoy, somax, somay, qntd-1);

}

int main(){

	lemapa(&m);
	encontramapa(&m, &heroi, HEROI);

	do {
		printf("Tem pilula? %s\n", (tempilula == 0 ? "NAO" : "SIM"));
		imprimimapa(&m);

		char comando;
		scanf(" %c", &comando);
		move(comando);
		if(comando == BOMBA) explodepilula();
		fantasma();

	} while(!acabou());

	liberamapa(&m);
}