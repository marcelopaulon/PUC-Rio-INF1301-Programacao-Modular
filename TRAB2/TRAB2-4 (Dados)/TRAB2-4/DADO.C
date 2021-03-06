/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo dado
*
*  Arquivo gerado:              DADO.C
*  Letras identificadoras:      DAD
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   fmc/mpjv/rfss   12/09/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <time.h>

#define DADO_OWN
#include "DADO.H"
#undef DADO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: DAD Descritor do dado
*
*
***********************************************************************/

typedef struct DAD_tagDado {

	int ValorDado1;
	/* Valor do dado 1 */

	int ValorDado2;
	/* Valor do dado 2 */

} DAD_tpDado;

/*****  Dados encapsulados no m�dulo  *****/

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: DAD Criar par de dados
* 
****/
DAD_tpCondRet DAD_CriarDados(DAD_tpDado **pDados)
{
	*pDados = (DAD_tpDado *) malloc(sizeof(DAD_tpDado));
	if(*pDados == NULL)
	{
		return DAD_CondRetFaltouMemoria ;
	} /* if */

	(*pDados)->ValorDado1 = -1;
	(*pDados)->ValorDado2 = -1;

	return DAD_CondRetOK ;

} /* Fim fun��o: PCA Criar par de dados */

/***************************************************************************
*
*  Fun��o: DAD Jogar dados
*  
****/
DAD_tpCondRet DAD_JogarDados(DAD_tpDado *pDados)
{
	if(pDados == NULL) 
	{
		return DAD_CondRetDadoNaoExiste;
	} /* if */

	srand((unsigned int) time(0));

	rand();

	pDados->ValorDado1 = (rand() % 6 + 1);
	pDados->ValorDado2 = (rand() % 6 + 1);

	return DAD_CondRetOK ;

} /* Fim fun��o: DAD Jogar dados */

/***************************************************************************
*
*  Fun��o: DAD Obter valores
*  
****/
DAD_tpCondRet DAD_ObterValores(DAD_tpDado *pDados, int *pValorDado1, int *pValorDado2)
{
	if(pDados == NULL) 
	{
		return DAD_CondRetDadoNaoExiste;
	} /* if */

	*pValorDado1 = pDados->ValorDado1;
	*pValorDado2 = pDados->ValorDado2;

	if(pDados->ValorDado1 < 0 || pDados->ValorDado2 < 0)
	{
		return DAD_CondRetDadoNaoLancado;
	} /* if */

	return DAD_CondRetOK ;

} /* Fim fun��o: DAD Obter valores */

/***************************************************************************
*
*  Fun��o: DAD Destruir dados
*  
****/
DAD_tpCondRet DAD_DestruirDados(DAD_tpDado **pDados)
{
	if(*pDados == NULL) 
	{
		return DAD_CondRetDadoNaoExiste;
	} /* if */

	free(*pDados);
	*pDados = NULL;

	return DAD_CondRetOK ;

} /* Fim fun��o: DAD Destruir dados */

/********** Fim do m�dulo de implementa��o: M�dulo dado **********/