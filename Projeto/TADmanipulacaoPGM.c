#include "TADmanipulacaoPGM.h"

/*------------------------------------------------------------------------------------------
Prot�tipo: void LePGM(char* entrada, PGM *img)
Fun��o : Ler a imagem do arquivo em pgm
Entrada : Nome da imagem, endere�o da vari�vel do tipo PGM alocada
Sa�da : --
------------------------------------------------------------------------------------------*/
PGM* LePGM(char* entrada)
{
    FILE *arq;//cria ponteiro para leitura do arquivo
    int i,j;
    char P2[5];//para salvar o tipo de imagem
    PGM *img = (PGM*) malloc(sizeof(PGM));//cria ponteiro e aloca dinamicamente um PGM, para que o link nao seja perdido ao sair da fun��o
    arq = fopen(entrada,"r");//abre o arquivo com nome salvo em entrada
    if(arq == NULL)//ponteiro aponta para NULL?
    {//Sim, arquivo nao encontrado ou problema de permiss�o
        printf("Erro ao abrir o arquivo\n");
        exit(1);//fim da fun��o com erro
    }
    fscanf(arq,"%s",P2);//L� e salva o tipo de imagem
    fscanf(arq,"%d %d %hhu",&img->c,&img->l,&img->maximo);//Salva numero maximo de linhas, de colunas e valor do pixel
    img->dados = (unsigned char **) malloc(img->l*sizeof(unsigned char *));//aloca linhas da matriz dados
    for (i=0;i<img->l;i++)//for para varrer linhas
    {
        img->dados[i] = (unsigned char *) malloc(img->c*sizeof(unsigned char));//divide linhas alocadas em colunas
    }
    for (i=0;i<img->l;i++)//varre linhas
        for(j=0;j<img->c;j++)//varre colunas
                fscanf(arq,"%hhu",&img->dados[i][j]);//salva valores contidos no arquivo na matriz
    fclose(arq);//fecha o arquivo
    return img;//retorna ponteiro para img
}

/*------------------------------------------------------------------------------------------
Prot�tipo: Ponto JanelaDeslizante(PGM *cena , PGM *obj)
Fun��o : Deslizar pela matriz contendo os dados da cena alinhando os pontos para a aplica��o
da Correla��o Cruzada para encontrar o ponto inicial do Match.
Entrada : Endere�o da estrutura contendo os dados da imagem cena e objeto em pgm
Sa�da : Ponto inicial do Match.
------------------------------------------------------------------------------------------*/
Ponto JanelaDeslizante(PGM *cena, PGM *obj)
{
    Ponto atual_cena, img_match;//declara pontos variaveis, onde esta multiplicando e o Match
    atual_cena.x=0;//Ponto Inicial zerado
    atual_cena.y=0;//
    int i, j;
    int temp=0, corr_cruz_atual=0;//variavel p/ guardar correlacao temporaria e a maior at� o momento
    for(i=0;i<(cena->l-obj->l);i++)//for para percorrer linhas de cena, para de deslizar quando obj for "sair" de cena
    {
        for(j=0;j<(cena->c-obj->c);j++)//for para percorrer colunas de cena, para de deslizar quando obj for "sair" de cena
        {

            temp=CorrelacaoCruzada(&(*cena), &(*obj), &atual_cena);//Salva a Correla��o Cruzada do ponto atual na vari�vel tempor�ria
            if(temp>corr_cruz_atual)//Variavel tempor�ria � maior do que a maior Correla��o at� aqui?
            {//Sim
                corr_cruz_atual=temp;//maior correla��o at� aqui recebe a tempor�ria
                img_match=atual_cena;//Ponto de match recebe o ponto em que a maior correla��o foi encontrada

            }
            atual_cena.x++;//incrementa um na coordenada x(coluna) de ponto atual
        }
        atual_cena.y++;//incrementa um na coordenada y(linha) de ponto atual
        atual_cena.x=0;//zera a coordenada x(coluna) de ponto atual
    }
    return img_match;//retorna o ponto de match. Fim
}

/*------------------------------------------------------------------------------------------
Prot�tipo: int CorrelacaoCruzada(PGM *cena , PGM *obj, Ponto *p)
Fun��o : Multiplicar as posi��es de mesmo �ndice das matrizes (objeto e recorte de cena) e
somar os resultados. O ponto de maior valor na correla��o cruzada ser� o ponto de Match.
Entrada : Endere�o da estrutura contendo os dados da cena e do objeto em pgm, ponto de inicio
na imagem cena.
Sa�da : Valor maior correla��o cruzada no ponto chamado.
------------------------------------------------------------------------------------------*/
int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto *p)
{
    int i, j;
    int res=0;
    for(i=0;i<obj->l;i++)//for para percorrer linhas para multiplica��o
    {
        for(j=0;j<obj->c;j++)//for para percorrer colunas para multiplica��o
            res=res + (cena->dados[(p->y)+i][(p->x)+j] * obj->dados[i][j]);//soma a multiplica��o dos valores de
                                                                           //cena a partir do ponto pelos de objeto
    }
    return res;//retorna resultado. Fim
}


/*------------------------------------------------------------------------------------------
Prot�tipo: void GeraSaida(Ponto p)
Fun��o : Gerar um arquivo txt com as coordenadas do ponto em que o Match se inicia
Entrada : Ponto inicial do Match
Sa�da : --
------------------------------------------------------------------------------------------*/
void GeraSaida(Ponto p, char *nomearquivo)
{
    FILE *file;//ponteiro para o arquivo
    file=fopen(nomearquivo,"w");//cria Saida.txt, modo escrita (write)
    if(file==NULL)//Ponteiro aponta para NULL?
    {//Sim: problema de permiss�o no diret�rio do programa ou algo do tipo
        printf("ERRO! Arquivo %s nao pode ser criado.\n",nomearquivo);
        return;//return com erro
    }
    fprintf(file,"%d %d", p.x, p.y);//Escreve as coordenadas do ponto de match em Saida.txt
    fclose(file);//fecha o arquivo
    printf("\nPronto!  Arquivo %s\n",nomearquivo);
    return;//fim
}

/*------------------------------------------------------------------------------------------
Prot�tipo: void LiberaMemoria(PGM *img)
Fun��o : Liberar a mem�ria alocada dinamicamente no programa
Entrada : Endere�o da estrutura contendo os dados da imagem em pgm
Sa�da : --
------------------------------------------------------------------------------------------*/
void LiberaMemoria(PGM *img)
{
    int  i;
    for (i=0; i<(img->l); i++)//for para varrer linhas
        free(img->dados[i]);//libera linhas
    free(img->dados);//libera �rea da matriz
    free(img);//libera PGM alocado dinamicamente em LePGM
    return;//Fim
}

/*------------------------------------------------------------------------------------------
Prot�tipo: Ponto JanelaDeslizante(PGM *cena , PGM *obj)
Fun��o : Deslizar pela matriz contendo os dados da cena alinhando os pontos para a aplica��o
da Correla��o Cruzada Modificada para encontrar o ponto inicial do Match.
Entrada : Endere�o da estrutura contendo os dados da imagem cena e objeto em pgm
Sa�da : Ponto inicial do Match.
------------------------------------------------------------------------------------------*/
Ponto JanelaDeslizanteMod(PGM *cena, PGM *obj)
{
    Ponto atual_cena, img_match;//declara pontos variaveis, onde esta multiplicando e o Match
    atual_cena.x=0;//Ponto Inicial zerado
    atual_cena.y=0;//
    int i, j;
    int temp;//variavel p/ guardar correlacao temporaria
    for(i=0;i<(cena->l-obj->l);i++)//for para percorrer linhas de cena, para de deslizar quando obj for "sair" de cena
    {
        for(j=0;j<(cena->c-obj->c);j++)//for para percorrer colunas de cena, para de deslizar quando obj for "sair" de cena
        {
            temp=CorrelacaoCruzadaMod(&(*cena), &(*obj), &atual_cena);//Salva a Correla��o Cruzada do ponto atual na vari�vel tempor�ria
            if(temp==0)//Variavel tempor�ria � igual a 0?
            {//Sim
                img_match=atual_cena;//Ponto de match recebe o ponto em que a correla��o igual a 0 foi encontrada
            }
            atual_cena.x++;//incrementa um na coordenada x(coluna) de ponto atual
        }
        atual_cena.y++;//incrementa um na coordenada y(linha) de ponto atual
        atual_cena.x=0;//zera a coordenada x(coluna) de ponto atual
    }
    return img_match;//retorna o ponto de match. Fim
}

/*------------------------------------------------------------------------------------------
Prot�tipo: int CorrelacaoCruzadaMod(PGM *cena , PGM *obj, Ponto *p)
Fun��o : Subtrair as posi��es de mesmo �ndice das matrizes (objeto e recorte de cena) e
somar os resultados. O ponto em que a correla��o cruzada seja 0, ser� o ponto de Match.
Entrada : Endere�o da estrutura contendo os dados da cena e do objeto em pgm, ponto de inicio
na imagem cena.
Sa�da : Valor da correla��o cruzada no ponto chamado.
------------------------------------------------------------------------------------------*/
int CorrelacaoCruzadaMod(PGM *cena, PGM *obj, Ponto *p)
{
    int i, j;
    int res=0;
    for(i=0;i<obj->l;i++)//for para percorrer linhas
    {
        for(j=0;j<obj->c;j++)//for para percorrer colunas
        {
            res+=cena->dados[p->y+i][p->x+j] - obj->dados[i][j];//soma a diferen�a das posi��es
                                                                //de mesmo �ndice do recorte de cena e do objeto        }
        }
    }
    return res;//retorna resultado da correlacao nesse ponto. Fim
}
