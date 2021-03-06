#if ! defined(DADO_)
#define DADO_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo dado
*
*  Arquivo gerado:              DADO.H
*  Letras identificadoras:      DAD
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data          Observa��es
*       1.00   fmc/mpjv/rfss   12/09/2015 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa fun��es para operar um par de dados de um jogo
*     de gam�o.
*     O m�dulo � capaz de trabalhar com n pares de dados.
*     Ao iniciar a execu��o do programa n�o existe dados.
*
***************************************************************************/
 
#if defined(DADO_OWN)
   #define DADO_EXT
#else
   #define DADO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um dado */

typedef struct DAD_tagDado DAD_tpDado;

/***********************************************************************
*
*  $TC Tipo de dados: DAD Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         DAD_CondRetOK,
               /* Executou correto */

		 DAD_CondRetDadoNaoExiste,
			   /* Dado n�o existe */

		 DAD_CondRetDadoNaoLancado,
			   /* Dado n�o lan�ado */

         DAD_CondRetFaltouMemoria
               /* Faltou mem�ria ao alocar dados */

   } DAD_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: DAD Criar dados
*
*  $ED Descri��o da fun��o
*     Cria um novo par de dados.
*
*  $EP Par�metros
*     $P pDados - ponteiro para o par de dados a ser criado. Passado por refer�ncia.
*
*  $FV Valor retornado
*     DAD_CondRetOK
*     DAD_CondRetFaltouMemoria
*
***********************************************************************/

   DAD_tpCondRet DAD_CriarDados(DAD_tpDado **pDados);

/***********************************************************************
*
*  $FC Fun��o: DAD Jogar dados
*
*  $ED Descri��o da fun��o
*     Joga os dados.
*
*  $EP Par�metros
*     $P pDados - ponteiro para o par de dados a ser utilizado.
*
*  $FV Valor retornado
*     DAD_CondRetOK
*     DAD_CondRetDadoNaoExiste
*
***********************************************************************/

   DAD_tpCondRet DAD_JogarDados(DAD_tpDado *pDados);

/***********************************************************************
*
*  $FC Fun��o: DAD Obter valores
*
*  $ED Descri��o da fun��o
*     Obt�m os valores do par de dados.
*
*  $EP Par�metros
*     $P pDados - ponteiro para o par de dados a ser utilizado.
*     $P pValorDado1 - ponteiro para o inteiro que armazenar� o valor do dado 1.
*     $P pValorDado2 - ponteiro para o inteiro que armazenar� o valor do dado 2.
*
*  $FV Valor retornado
*     DAD_CondRetOK
*	  DAD_CondRetDadoNaoExiste
*	  DAD_CondRetDadoNaoLancado
*
***********************************************************************/

   DAD_tpCondRet DAD_ObterValores(DAD_tpDado *pDados, int *pValorDado1, int *pValorDado2);


/***********************************************************************
*
*  $FC Fun��o: DAD Destruir dado
*
*  $ED Descri��o da fun��o
*     Destr�i o par de dados.
*
*  $EP Par�metros
*     $P pDados - ponteiro para o par de dados a ser exclu�do.
*
*  $FV Valor retornado
*     DAD_CondRetOK
*	  DAD_CondRetDadoNaoExiste
*
***********************************************************************/

   DAD_tpCondRet DAD_DestruirDados(DAD_tpDado **pDados);

#undef DAD_EXT

/********** Fim do m�dulo de defini��o: M�dulo dado **********/

#else
#endif