/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo pe�as finalizadas
*
*  Arquivo gerado:              PECASFINALIZADAS.C
*  Letras identificadoras:      PCF
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   fmc/mpjv/rfss   17/09/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define PECASFINALIZADAS_OWN
#include "PECASFINALIZADAS.H"
#undef PECASFINALIZADAS_OWN

#include "PECA.H"

#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: PCF Descritor da pe�a finalizada
*
*
***********************************************************************/

typedef struct PCF_tagPecasFinalizadas {

	LIS_tppLista listaPecasBrancas;
	/* Lista de pe�as brancas finalizadas */

	LIS_tppLista listaPecasPretas;
	/* Lista de pe�as pretas finalizadas */

} PCF_tpPecasFinalizadas;

/*****  Dados encapsulados no m�dulo  *****/

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

void LiberarPeca(void *pPeca);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PCF Criar lista de pe�as finalizadas
* 
****/
PCF_tpCondRet PCF_CriarListaPecasFinalizadas(PCF_tpPecasFinalizadas **pPecasFinalizadas)
{

	*pPecasFinalizadas = (PCF_tpPecasFinalizadas *) malloc(sizeof(PCF_tpPecasFinalizadas));
	if(*pPecasFinalizadas == NULL)
	{
		return PCF_CondRetFaltouMemoria ;
	} /* if */

	(*pPecasFinalizadas)->listaPecasBrancas = LIS_CriarLista(LiberarPeca);
	(*pPecasFinalizadas)->listaPecasPretas = LIS_CriarLista(LiberarPeca);

	return PCF_CondRetOK ;

} /* Fim fun��o: PCF Criar lista de pe�as finalizadas */

/***************************************************************************
*
*  Fun��o: PCF Inserir pe�a
*  
****/
PCF_tpCondRet PCF_InserirPeca(PCF_tpPecasFinalizadas *pPecasFinalizadas, PCA_tpPeca *pPeca)
{
	PCA_tpCorPeca CorPeca;

	if(pPecasFinalizadas == NULL) 
	{
		return PCF_CondRetListaPecasFinalizadasNaoExiste;
	} /* if */

	PCA_ObterCorPeca(pPeca, &CorPeca);	
	
	if(CorPeca == PCA_PecaBranca)
	{
		LIS_InserirElementoAntes(pPecasFinalizadas->listaPecasBrancas, pPeca);
	} /* if */
	else
	{
		LIS_InserirElementoAntes(pPecasFinalizadas->listaPecasPretas, pPeca);
	} /* else */
	
	return PCF_CondRetOK;

} /* Fim fun��o: PCF Inserir pe�a */

/***************************************************************************
*
*  Fun��o: PCF Conta pe�as
*  
****/
PCF_tpCondRet PCF_ContarPecas(PCF_tpPecasFinalizadas *pPecasFinalizadas, PCA_tpCorPeca CorPeca, int *pContagem)
{
	LIS_tppLista ListaPecas;

	if(pPecasFinalizadas == NULL) 
	{
		return PCF_CondRetListaPecasFinalizadasNaoExiste;
	} /* if */

	*pContagem = 0;

	if(CorPeca == PCA_PecaBranca)
	{
		ListaPecas = pPecasFinalizadas->listaPecasBrancas;
	} /* if */
	else 
	{
		ListaPecas = pPecasFinalizadas->listaPecasPretas;
	} /* else */

	IrInicioLista(ListaPecas);

	if(LIS_ObterValor(ListaPecas) != NULL)
	{
		do
		{
			(*pContagem)++;
		} while(LIS_AvancarElementoCorrente(ListaPecas, 1) == LIS_CondRetOK); /* do */
	} /* if */

	return PCF_CondRetOK ;

} /* Fim fun��o: PCF Conta pe�as */

/***************************************************************************
*
*  Fun��o: PCF Destruir lista de pe�as finalizadas
*  
****/
PCF_tpCondRet PCF_DestruirListaPecasFinalizadas(PCF_tpPecasFinalizadas **pPecasFinalizadas)
{
	if(*pPecasFinalizadas == NULL || ((*pPecasFinalizadas)->listaPecasBrancas == NULL && (*pPecasFinalizadas)->listaPecasPretas == NULL)) 
	{
		return PCF_CondRetListaPecasFinalizadasNaoExiste;
	} /* if */

	if((*pPecasFinalizadas)->listaPecasBrancas != NULL)
	{
		LIS_DestruirLista((*pPecasFinalizadas)->listaPecasBrancas);
	} /* if */

	if((*pPecasFinalizadas)->listaPecasPretas != NULL)
	{
		LIS_DestruirLista((*pPecasFinalizadas)->listaPecasPretas);
	} /* if */

	free(*pPecasFinalizadas);
	*pPecasFinalizadas = NULL;

	return PCF_CondRetOK ;

} /* Fim fun��o: PCF Destruir lista de pe�as finalizadas */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: Libera pe�a
*
*  $ED Descri��o da fun��o
*     Libera uma pe�a.
*
***********************************************************************/
void LiberarPeca(PCA_tpPeca *pPeca)
{
	PCA_DestruirPeca(&pPeca);
}

/********** Fim do m�dulo de implementa��o: M�dulo pe�as finalizadas **********/