#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {//estrutura de dados para salvar a imagem PGM
    unsigned char maximo;//Valor máximo que um pixel pode assumir
    unsigned char **dados;//Matriz para guardar os valores de cada pixel
    int c;//comprimento da imagem em pixels (número de colunas da matriz)
    int l;//altura da imagem em pixels (número de linhas da matriz)
}PGM;
typedef struct{//estrutura da dados para indicar um ponto na imagem(matriz)
    int x, y;//coordenadas x e y
}Ponto;

PGM* LePGM(char* entrada);
Ponto JanelaDeslizante(PGM *cena, PGM *obj);
int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto *p);
void GeraSaida(Ponto p, char *nomearquivo);
void LiberaMemoria(PGM *img);
Ponto JanelaDeslizanteMod(PGM *cena, PGM *obj);
int CorrelacaoCruzadaMod(PGM *cena, PGM *obj, Ponto *p);
