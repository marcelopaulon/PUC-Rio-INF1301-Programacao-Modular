#if ! defined(TABULEIRO_)
#define TABULEIRO_

#include "PECA.H"

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo tabuleiro
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data          Observa��es
*       1.00   fmc/mpjv/rfss   02/09/2015 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um tabuleiro de gam�o.
*     O tabuleiro possui uma refer�ncia para a casa corrente do tabuleiro.
*     O m�dulo � capaz de trabalhar com n tabuleiros.
*     Ao iniciar a execu��o do programa n�o existe tabuleiro.
*     O tabuleiro poder� estar vazio. Neste caso a casa corrente
*     ser� nula, embora a cabe�a esteja definida.
*     A casa corrente ser� nula se e somente se o tabuleiro estiver vazio.
*
***************************************************************************/
 
#if defined(TABULEIRO_OWN)
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um tabuleiro */

typedef struct TAB_tagTabuleiro TAB_tpTabuleiro;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
***********************************************************************/

   typedef enum {

         TAB_CondRetOK,
               /* Executou correto */

         TAB_CondRetTabuleiroNaoExiste,
               /* Tabuleiro n�o existe */

		 TAB_CondRetCasaNaoExiste,
				/* Casa desejada n�o existe */

		 TAB_CondRetPecaNaoExiste,
				/* Pe�a desejada n�o existe */

         TAB_CondRetFaltouMemoria
               /* Faltou mem�ria ao alocar dados */

   } TAB_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: TAB Criar Tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria um novo tabuleiro vazio.
*
*  $EP Par�metros
*     $P pTabuleiro - ponteiro para o tabuleiro a ser criado. Passado por refer�ncia.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpTabuleiro **pTabuleiro);


/***********************************************************************
*
*  $FC Fun��o: TAB Inserir Pe�a
*
*  $ED Descri��o da fun��o
*     Insere uma pe�a em um tabuleiro.
*
*  $EP Par�metros
*     $P pTabuleiro - ponteiro para o tabuleiro no qual a pe�a ser� inserida.
*     $P pPeca - cont�m o tipo (cor) da pe�a a ser inserida.
*     $P NumeroCasa - cont�m o n�mero da casa na qual a pe�a ser� inserida.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*	  TAB_CondRetTabuleiroNaoExiste
*	  TAB_CondRetCasaNaoExiste
*	  TAB_CondRetFaltouMemoria
*
***********************************************************************/

   TAB_tpCondRet TAB_InserirPeca(TAB_tpTabuleiro *pTabuleiro, PCA_tpPeca *pPeca, int NumeroCasa);


/***********************************************************************
*
*  $FC Fun��o: TAB Remover Pe�a
*
*  $ED Descri��o da fun��o
*     Remove uma pe�a de um tabuleiro.
*
*  $EP Par�metros
*     $P pTabuleiro - ponteiro para o tabuleiro da onde a pe�a ser� removida.
*	  $P CorPeca - cor da pe�a a ser removida.
*     $P pPeca - ponteiro para a colocar a pe�a a ser removida. Passado por refer�ncia.
*     $P NumeroCasa - n�mero da casa onde a pe�a a ser removida est� localizada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetCasaNaoExiste
*	  TAB_CondRetPecaNaoExiste
*
***********************************************************************/

   TAB_tpCondRet TAB_RemoverPeca(TAB_tpTabuleiro *pTabuleiro, PCA_tpCorPeca CorPeca, PCA_tpPeca **pPeca, int NumeroCasa);

   
/***********************************************************************
*
*  $FC Fun��o: TAB Mover Pe�a
*
*  $ED Descri��o da fun��o
*     Move uma pe�a de uma casa para outra em um tabuleiro
*
*  $EP Par�metros
*     $P pTabuleiro - ponteiro para o tabuleiro onde se localiza a pe�a a ser movida.
*     $P CorPeca - cor da pe�a a ser movida.
*     $P NumeroCasaOrigem - n�mero da casa onde se localiza a pe�a a ser movida.
*     $P NumeroCasaDestino - n�mero da casa para onde a pe�a ser� movida.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*     TAB_CondRetCasaNaoExiste
*	  TAB_CondRetPecaNaoExiste
*	  TAB_CondRetFaltouMemoria
*
***********************************************************************/

   TAB_tpCondRet TAB_MoverPeca(TAB_tpTabuleiro *pTabuleiro, PCA_tpCorPeca CorPeca, int NumeroCasaOrigem, int NumeroCasaDestino);

/***********************************************************************
*
*  $FC Fun��o: TAB Contar Pe�as
*
*  $ED Descri��o da fun��o
*     Conta o n�mero de pe�as presentes em uma casa de um tabuleiro
*
*  $EP Par�metros
*     $P pTabuleiro - ponteiro para o tabuleiro aonde est� a casa que ter� suas pe�as contadas
*     $P NumeroCasa - n�mero da casa que ter� suas pe�as contadas
*     $P CorPeca - cor das pe�as a serem contadas
*     $P pContagem - ponteiro que receber�, por refer�ncia, o n�mero de pe�as da cor escolhida na casa indicada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*	  TAB_CondRetCasaNaoExiste
*	  TAB_CondRetPecaNaoExiste
*
***********************************************************************/

   TAB_tpCondRet TAB_ContarPecas(TAB_tpTabuleiro *pTabuleiro, int NumeroCasa, PCA_tpCorPeca CorPeca, int *pContagem);

/***********************************************************************
*
*  $FC Fun��o: TAB Destruir Tabuleiro
*
*  $ED Descri��o da fun��o
*     Destr�i o tabuleiro, anulando o n� que aponta para o mesmo.
*
*  $EP Par�metros
*     $P pTabuleiro - ponteiro para o tabuleiro a ser destru�do.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNaoExiste
*
***********************************************************************/

   TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tpTabuleiro **pTabuleiro);

#undef TAB_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif