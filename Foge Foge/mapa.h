#ifndef MAPA_H_
#define MAPA_H_

#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_H '|'
#define PAREDE_V '-'
#define PILULA 'P'
#define BOMBA 'b'

struct mapa
{
	char** matriz;
	int linhas;
	int colunas;	
};

typedef struct mapa MAPA;

struct posicao {
	int x;
	int y;
};

typedef struct posicao POSICAO;

int podeandar(MAPA* m, char personagem, int x, int y);
int ehvalido(MAPA* m, int x,int  y);
int ehvazio(MAPA* m, int x, int y);
void liberamapa(MAPA* m);
void lemapa(MAPA* m);
void alocamapa(MAPA* m);
int encontramapa(MAPA* m, POSICAO* p, char c);
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiamapa(MAPA* destino, MAPA* origem);
int ehpersonagem(MAPA* m, char personagem, int x, int y);
int ehparede(MAPA* m, int x, int y);

#endif