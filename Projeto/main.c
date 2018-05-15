#include "TADmanipulacaoPGM.h"

int main(int argc, char *argv[])
{
    Ponto inicio_match;//Ponto onde o match se inicia
    PGM *cena, *objeto;//Ponteiros para cena e objeto

    printf("\nLendo Imagens ...");
    cena=LePGM(argv[1]);//L� cena do primeiro argumento ap�s o nome do execut�vel
    objeto=LePGM(argv[2]);//L� objeto do segundo argumento ap�s o nome do execut�vel
    printf("\nPronto!\n");

    printf("\nAplicando o Algoritmo de Correlacao Cruzada por meio da Janela Deslizante...\n");
    if((argv[4]!= NULL)&&(argv[4][0]=='1'))//decide se sera utilizada a janela deslizante ou a janela deslizante modificada
        inicio_match=JanelaDeslizanteMod(&(*cena), &(*objeto));//Chama a fun��o JanelaDeslizanteMod e recebe o ponto inicial de match
    else
        inicio_match=JanelaDeslizante(&(*cena), &(*objeto));//Chama a fun��o JanelaDeslizante e recebe o ponto inicial de match
    printf("\nPronto! ");

    printf("Ponto inicial de Match encontrado: %d %d\n\nGerando Saida...",inicio_match.x, inicio_match.y);
    GeraSaida(inicio_match, argv[3]);//Gera Saida.txt

    LiberaMemoria(cena);//Libera Mem�ria de cena
    LiberaMemoria(objeto);//Libera Mem�ria de objeto
    return 0;//Fim
}
