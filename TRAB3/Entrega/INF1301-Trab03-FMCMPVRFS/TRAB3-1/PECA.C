/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo pe�a
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      PCA
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   fmc/mpjv/rfss   02/09/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PCA Descritor da pe�a
*
*
***********************************************************************/

typedef struct PCA_tagPeca {

	PCA_tpCorPeca CorPeca;
	/* Cor da pe�a */

} PCA_tpPeca;

/*****  Dados encapsulados no m�dulo  *****/

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PCA Criar pe�a
* 
****/
PCA_tpCondRet PCA_CriarPeca(PCA_tpPeca **pPeca, PCA_tpCorPeca CorPeca)
{

	*pPeca = (PCA_tpPeca *) malloc(sizeof(PCA_tpPeca));
	if(*pPeca == NULL)
	{
		return PCA_CondRetFaltouMemoria ;
	} /* if */

	(*pPeca)->CorPeca = CorPeca;

	return PCA_CondRetOK ;

} /* Fim fun��o: PCA Criar pe�a */

/***************************************************************************
*
*  Fun��o: PCA Obter cor da pe�a
*  
****/
PCA_tpCondRet PCA_ObterCorPeca(PCA_tpPeca *pPeca, PCA_tpCorPeca *pCorPeca)
{
	if(pPeca == NULL) 
	{
		return PCA_CondRetPecaNaoExiste;
	} /* if */

	*pCorPeca = pPeca->CorPeca;

	return PCA_CondRetOK ;

} /* Fim fun��o: Obter cor da pe�a */

/***************************************************************************
*
*  Fun��o: PCA Destruir pe�a
*  
****/
PCA_tpCondRet PCA_DestruirPeca(PCA_tpPeca **pPeca)
{
	if(*pPeca == NULL) 
	{
		return PCA_CondRetPecaNaoExiste;
	} /* if */

	free(*pPeca);
	*pPeca = NULL;

	return PCA_CondRetOK ;

} /* Fim fun��o: PCA Destruir pe�a */

/********** Fim do m�dulo de implementa��o: M�dulo pe�a **********/