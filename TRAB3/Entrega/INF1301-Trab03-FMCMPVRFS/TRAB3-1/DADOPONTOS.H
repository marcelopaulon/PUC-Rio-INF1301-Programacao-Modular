#if ! defined(DADOPONTOS_)
#define DADOPONTOS_

#include "PECA.H"

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo dado pontos
*
*  Arquivo gerado:              DADOPONTOS.H
*  Letras identificadoras:      DPT
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data          Observa��es
*       1.00   fmc/mpjv/rfss   13/09/2015 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa fun��es para operar um dado de pontos de um jogo.
*     O m�dulo � capaz de trabalhar com n dados de pontos.
*     Ao iniciar a execu��o do programa n�o existe dado de pontos.
*
***************************************************************************/
 
#if defined(DADOPONTOS_OWN)
   #define DADOPONTOS_EXT
#else
   #define DADOPONTOS_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma pe�a */

typedef struct DPT_tagDadoPontos DPT_tpDadoPontos;

/***********************************************************************
*
*  $TC Tipo de dados: DPT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         DPT_CondRetOK,
               /* Executou correto */

		 DPT_CondRetDadoPontosNaoExiste,
			   /* Dado de pontos n�o existe */

		 DPT_CondRetJogadorNaoPossuiDadoPontos,
			   /* Jogador n�o possui dado de pontos no momento */

		 DPT_CondRetNaoHaJogadorDadoPontos,
			   /* N�o h� jogador atual do dado de pontos */

         DPT_CondRetFaltouMemoria
               /* Faltou mem�ria ao alocar dados */

   } DPT_tpCondRet;
   
/***********************************************************************
*
*  $FC Fun��o: DPT Criar dado de pontos
*
*  $ED Descri��o da fun��o
*     Cria um novo dado de pontos.
*
*  $EP Par�metros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser criado. Passado por refer�ncia.
*
*  $FV Valor retornado
*     DPT_CondRetOK
*     DPT_CondRetFaltouMemoria
*
***********************************************************************/

   DPT_tpCondRet DPT_CriarDadoPontos(DPT_tpDadoPontos **pDadoPontos);

/***********************************************************************
*
*  $FC Fun��o: DPT Atualizar jogador que pode dobrar a partida
*
*  $ED Descri��o da fun��o
*     Atualiza o jogador que pode dobrar a partida.
*
*  $EP Par�metros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser utilizado.
*     $P CorPeca - cor do jogador.
*
*  $FV Valor retornado
*     DPT_CondRetOK
*	  DPT_CondRetDadoPontosNaoExiste
*
***********************************************************************/

   DPT_tpCondRet DPT_AtualizarJogadorDobra(DPT_tpDadoPontos *pDadoPontos, PCA_tpCorPeca CorPeca);

/***********************************************************************
*
*  $FC Fun��o: DPT Dobrar pontua��o da partida
*
*  $ED Descri��o da fun��o
*     Dobra a pontua��o da partida.
*
*  $EP Par�metros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser utilizado.
*     $P CorPeca - cor do jogador.
*
*  $FV Valor retornado
*     DPT_CondRetOK
*	  DPT_CondRetDadoPontosNaoExiste
*	  DPT_CondRetJogadorNaoPossuiDadoPontos
*
***********************************************************************/

   DPT_tpCondRet DPT_DobrarPontuacaoPartida(DPT_tpDadoPontos *pDadoPontos, PCA_tpCorPeca CorPeca);

/***********************************************************************
*
*  $FC Fun��o: DPT Obter jogador que pode dobrar partida
*
*  $ED Descri��o da fun��o
*     Obt�m o jogador que pode dobrar a partida.
*
*  $EP Par�metros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser utilizado.
*     $P pCorPeca - ponteiro que receber�, por refer�ncia, a cor da pe�a do jogador.
*
*  $FV Valor retornado
*     DPT_CondRetOK
*	  DPT_CondRetDadoPontosNaoExiste
*	  DPT_CondRetNaoHaJogadorDadoPontos
*
***********************************************************************/

   DPT_tpCondRet DPT_ObterJogadorDobraPartida(DPT_tpDadoPontos *pDadoPontos, PCA_tpCorPeca *pCorPeca);

/***********************************************************************
*
*  $FC Fun��o: DPT Obter pontua��o da partida
*
*  $ED Descri��o da fun��o
*     Obt�m a pontua��o da partida.
*
*  $EP Par�metros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser utilizado.
*     $P pPontuacao - ponteiro que receber�, por refer�ncia, a pontua��o da partida.
*
*  $FV Valor retornado
*     DPT_CondRetOK
*	  DPT_CondRetDadoPontosNaoExiste
*
***********************************************************************/

   DPT_tpCondRet DPT_ObterPontuacaoPartida(DPT_tpDadoPontos *pDadoPontos, int *pPontuacao);

/***********************************************************************
*
*  $FC Fun��o: DPT Destruir dado de pontos
*
*  $ED Descri��o da fun��o
*     Destr�i a pe�a.
*
*  $EP Par�metros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser destru�do. Passado por refer�ncia.
*
*  $FV Valor retornado
*     DPT_CondRetOK
*	  DPT_CondRetDadoPontosNaoExiste
*
***********************************************************************/

   DPT_tpCondRet DPT_DestruirDadoPontos(DPT_tpDadoPontos **pDadoPontos);

#undef DPT_EXT

/********** Fim do m�dulo de defini��o: M�dulo dado de pontos **********/

#else
#endif