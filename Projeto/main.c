#include "TADmanipulacaoPGM.h"

int main(int argc, char *argv[])
{
    Ponto inicio_match;//Ponto onde o match se inicia
    PGM *cena, *objeto;//Ponteiros para cena e objeto

    printf("\nLendo Imagens ...");
    cena=LePGM(argv[1]);//Lê cena do primeiro argumento após o nome do executável
    objeto=LePGM(argv[2]);//Lê objeto do segundo argumento após o nome do executável
    printf("\nPronto!\n");

    printf("\nAplicando o Algoritmo de Correlacao Cruzada por meio da Janela Deslizante...\n");
    if((argv[4]!= NULL)&&(argv[4][0]=='1'))//decide se sera utilizada a janela deslizante ou a janela deslizante modificada
        inicio_match=JanelaDeslizanteMod(&(*cena), &(*objeto));//Chama a função JanelaDeslizanteMod e recebe o ponto inicial de match
    else
        inicio_match=JanelaDeslizante(&(*cena), &(*objeto));//Chama a função JanelaDeslizante e recebe o ponto inicial de match
    printf("\nPronto! ");

    printf("Ponto inicial de Match encontrado: %d %d\n\nGerando Saida...",inicio_match.x, inicio_match.y);
    GeraSaida(inicio_match, argv[3]);//Gera Saida.txt

    LiberaMemoria(cena);//Libera Memória de cena
    LiberaMemoria(objeto);//Libera Memória de objeto
    return 0;//Fim
}
