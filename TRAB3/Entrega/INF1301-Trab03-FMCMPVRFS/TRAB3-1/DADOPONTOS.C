/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo dado de pontos
*
*  Arquivo gerado:              DADOPONTOS.C
*  Letras identificadoras:      DPT
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   fmc/mpjv/rfss   13/09/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define DADOPONTOS_OWN
#include "DADOPONTOS.H"
#undef DADOPONTOS_OWN

/***********************************************************************
*
*  $TC Tipo de dados: DPT Descritor do dado de pontos
*
*
***********************************************************************/

typedef struct DPT_tagDadoPontos
{

	int Pontuacao;
	/* Pontua��o */

	PCA_tpCorPeca CorPeca;
	/* Cor da pe�a do jogador detentor do dado de pontos */

} DPT_tpDadoPontos;

/*****  Dados encapsulados no m�dulo  *****/

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: DPT Criar dado de pontos
* 
****/
DPT_tpCondRet DPT_CriarDadoPontos(DPT_tpDadoPontos **pDadoPontos)
{
	*pDadoPontos = (DPT_tpDadoPontos *) malloc(sizeof(DPT_tpDadoPontos));
	if(*pDadoPontos == NULL)
	{
		return DPT_CondRetFaltouMemoria ;
	} /* if */

	(*pDadoPontos)->Pontuacao = 1;

	return DPT_CondRetOK ;

} /* Fim fun��o: DPT Criar dado de pontos */

/***************************************************************************
*
*  Fun��o: DPT Atualizar jogador
*  
****/
DPT_tpCondRet DPT_AtualizarJogadorDobra(DPT_tpDadoPontos *pDadoPontos, PCA_tpCorPeca CorPeca)
{
	if(pDadoPontos == NULL) 
	{
		return DPT_CondRetDadoPontosNaoExiste;
	} /* if */

	pDadoPontos->CorPeca = CorPeca;

	return DPT_CondRetOK ;

} /* Fim fun��o: Atualizar jogador */

/***************************************************************************
*
*  Fun��o: DPT Dobrar pontua��o da partida
*  
****/
DPT_tpCondRet DPT_DobrarPontuacaoPartida(DPT_tpDadoPontos *pDadoPontos, PCA_tpCorPeca CorPeca)
{
	if(pDadoPontos == NULL) 
	{
		return DPT_CondRetDadoPontosNaoExiste;
	} /* if */

	if(pDadoPontos->CorPeca != CorPeca)
	{
		return DPT_CondRetJogadorNaoPossuiDadoPontos;
	} /* if */

	pDadoPontos->Pontuacao *= 2;

	return DPT_CondRetOK ;
}

/***************************************************************************
*
*  Fun��o: DPT Obter jogador que possui o dado de pontos
*  
****/
DPT_tpCondRet DPT_ObterJogadorDobraPartida(DPT_tpDadoPontos *pDadoPontos, PCA_tpCorPeca *pCorPeca)
{
	if(pDadoPontos == NULL)
	{
		return DPT_CondRetDadoPontosNaoExiste;
	} /* if */

	if(pDadoPontos->Pontuacao == 1)
	{
		return DPT_CondRetNaoHaJogadorDadoPontos;
	}

	*pCorPeca = pDadoPontos->CorPeca;

	return DPT_CondRetOK ;
}

/***************************************************************************
*
*  Fun��o: DPT Obter pontua��o da partida
*  
****/
DPT_tpCondRet DPT_ObterPontuacaoPartida(DPT_tpDadoPontos *pDadoPontos, int *pPontuacao)
{
	if(pDadoPontos == NULL) 
	{
		return DPT_CondRetDadoPontosNaoExiste;
	} /* if */

	*pPontuacao = pDadoPontos->Pontuacao;

	return DPT_CondRetOK ;
}

/***************************************************************************
*
*  Fun��o: DPT Destruir dado de pontos
*  
****/
DPT_tpCondRet DPT_DestruirDadoPontos(DPT_tpDadoPontos **pDadoPontos)
{
	if(*pDadoPontos == NULL) 
	{
		return DPT_CondRetDadoPontosNaoExiste;
	} /* if */

	free(*pDadoPontos);
	*pDadoPontos = NULL;

	return DPT_CondRetOK;

} /* Fim fun��o: DPT Destruir dado de pontos */

/********** Fim do m�dulo de implementa��o: M�dulo dado de pontos **********/