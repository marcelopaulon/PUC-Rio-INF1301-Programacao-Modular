/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs,fmc,mpv,rfs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor            Data           Observa��es
*	  5       fmc,mpv,rfs  27/nov/2015 instrumenta��o / cobertura
*     4       avs          01/fev/2006 criar linguagem script simb�lica
*     3       avs          08/dez/2004 uniformiza��o dos exemplos
*     2       avs          07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs          16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemLista {

#ifdef _DEBUG

	LIS_tppLista pCabeca ;
	/* Ponteiro para cabeca
	*
	*$ED Descri��o
	*   Todos os n�s da lista devem apontar para a respectiva cabe�a.
	*   Esse ponteiro corresponde a um identificador da lista para fins
	*   de verifica��o da integridade. */

	char Tipo ;
	/* Tipo do elemento */

#endif

	void * pValor ;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista * pAnt ;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista * pProx ;
	/* Ponteiro para o elemento sucessor */

} tpElemLista ;

/*****  Dados encapsulados no m�dulo  *****/

#ifdef _DEBUG

static char EspacoLixo[ 256 ] =
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
/* Espa�o de dados lixo usado ao testar */

#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

typedef struct LIS_tagLista {

	tpElemLista * pOrigemLista ;
	/* Ponteiro para a origem da lista */

	tpElemLista * pFimLista ;
	/* Ponteiro para o final da lista */

	tpElemLista * pElemCorr ;
	/* Ponteiro para o elemento corrente da lista */

	int NumeroDeElementos ;
	/* N�mero de elementos da lista */

	void (* ExcluirValor) (void * pValor) ;
	/* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

	#ifdef _DEBUG
		char Tipo ;
		/* Tipo do elemento */
	#endif

} LIS_tpLista ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void LiberarElemento(LIS_tppLista   pLista ,
	tpElemLista  * pElem ) ;

static tpElemLista * CriarElemento(LIS_tppLista pLista ,
	void *       pValor) ;

static void LimparCabeca(LIS_tppLista pLista) ;

#ifdef _DEBUG

static LIS_tpCondRet VerificarNo(LIS_tppLista * pNo) ;

#endif

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

LIS_tppLista LIS_CriarLista(
	void   (* ExcluirValor) (void * pDado))
{

	LIS_tpLista * pLista = NULL ;

	pLista = (LIS_tpLista *) malloc(sizeof(LIS_tpLista)) ;
	if (pLista == NULL)
	{
		return NULL ;
	} /* if */

	LimparCabeca(pLista) ;

#ifdef _DEBUG
	pLista->Tipo = LIS_TipoEspacoCabeca;
	CED_DefinirTipoEspaco(pLista , LIS_TipoEspacoCabeca) ;
#endif

	pLista->ExcluirValor = ExcluirValor ;

	return pLista ;

} /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

void LIS_DestruirLista(LIS_tppLista pLista)
{

	if (pLista == NULL) 
	{

		return;
	}
	
	LIS_EsvaziarLista(pLista) ;

	free(pLista) ;

} /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista(LIS_tppLista pLista)
{

	tpElemLista * pElem ;
	tpElemLista * pProx ;
	
	if (pLista == NULL) 
	{
		return;
	}

	pElem = pLista->pOrigemLista ;
	while (pElem != NULL)
	{
		pProx = pElem->pProx ;
		LiberarElemento(pLista , pElem) ;
		pElem = pProx ;
	} /* while */

	LimparCabeca(pLista) ;

} /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista ,
	void * pValor      )
{

	tpElemLista * pElem ;

	#ifdef _DEBUG
      void * PonteiroVoid = NULL ;
      int TipoEspaco = -1 ;
      int Retorno = -1 ;
    #endif

	if (pLista == NULL) 
	{
		return LIS_CondRetNaoExiste;
	}

	/* Criar elemento a inserir antes */

	pElem = CriarElemento(pLista , pValor) ;
	if (pElem == NULL)
	{
		return LIS_CondRetFaltouMemoria ;
	} /* if */

#ifdef _DEBUG
	pElem->pCabeca = pLista ;
	pElem->Tipo = LIS_TipoEspacoNo;
	CED_DefinirTipoEspaco(pElem , LIS_TipoEspacoNo) ;
#endif

	/* Encadear o elemento antes do elemento corrente */

	if (pLista->pElemCorr == NULL)
	{
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
		if (pLista->pElemCorr->pAnt != NULL)
		{
			pElem->pAnt  = pLista->pElemCorr->pAnt ;
			pLista->pElemCorr->pAnt->pProx = pElem ;
		} else
		{
			pLista->pOrigemLista = pElem ;
		} /* if */

		pElem->pProx = pLista->pElemCorr ;
		pLista->pElemCorr->pAnt = pElem ;
	} /* if */

	pLista->pElemCorr = pElem ;

	/* Atribui��es para checar vazamento de mem�ria em modo DEBUG */
    #ifdef _DEBUG
        PonteiroVoid = (void *) pLista ;
        TipoEspaco = CED_ObterTipoEspaco(PonteiroVoid) ;
        
        PonteiroVoid = (void *) pElem ;
        CED_DefinirTipoEspaco(PonteiroVoid, TipoEspaco) ;
          
        PonteiroVoid = (void *) pValor ;
        Retorno = CED_DefinirTipoEspaco(PonteiroVoid, TipoEspaco) ;
    #endif

	return LIS_CondRetOK ;

} /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista ,
	void * pValor      )

{

	tpElemLista * pElem ;
	
	if (pLista == NULL) 
	{
		return LIS_CondRetNaoExiste;
	}

	/* Criar elemento a inerir ap�s */

	pElem = CriarElemento(pLista , pValor) ;
	if (pElem == NULL)
	{
		return LIS_CondRetFaltouMemoria ;
	} /* if */

#ifdef _DEBUG
	pElem->pCabeca = pLista ;
	pElem->Tipo = LIS_TipoEspacoNo;
	CED_DefinirTipoEspaco(pElem , LIS_TipoEspacoNo) ;
#endif

	/* Encadear o elemento ap�s o elemento */

	if (pLista->pElemCorr == NULL)
	{
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
		if (pLista->pElemCorr->pProx != NULL)
		{
			pElem->pProx  = pLista->pElemCorr->pProx ;
			pLista->pElemCorr->pProx->pAnt = pElem ;
		} else
		{
			pLista->pFimLista = pElem ;
		} /* if */

		pElem->pAnt = pLista->pElemCorr ;
		pLista->pElemCorr->pProx = pElem ;

	} /* if */

	pLista->pElemCorr = pElem ;
	
	return LIS_CondRetOK ;

} /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista)
{

	tpElemLista * pElem ;
	
	if (pLista == NULL) 
	{
		return LIS_CondRetNaoExiste;
	}

	if (pLista->pElemCorr == NULL)
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pElem = pLista->pElemCorr ;

	/* Desencadeia anterior */

	if (pElem->pAnt != NULL)
	{
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} else {
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */

	/* Desencadeia pr�ximo */

	if (pElem->pProx != NULL)
	{
		pElem->pProx->pAnt = pElem->pAnt ;
	} else
	{
		pLista->pFimLista = pElem->pAnt ;
	} /* if */

	LiberarElemento(pLista , pElem) ;
	
	return LIS_CondRetOK ;

} /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

void * LIS_ObterValor(LIS_tppLista pLista)
{
	if (pLista == NULL) 
	{
		return NULL;
	}

	if (pLista->pElemCorr == NULL)
	{
		return NULL ;
	} /* if */
	
	return pLista->pElemCorr->pValor ;

} /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

void IrInicioLista(LIS_tppLista pLista)
{
	if (pLista == NULL) 
	{
		return;
	}
	
	pLista->pElemCorr = pLista->pOrigemLista ;

} /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

void IrFinalLista(LIS_tppLista pLista)
{
	if (pLista == NULL) 
	{
		return;
	}
	
	pLista->pElemCorr = pLista->pFimLista ;

} /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista ,
	int NumeroDeElementos)
{

	int i ;

	tpElemLista * pElem ;
	
	if (pLista == NULL) 
	{
		return LIS_CondRetNaoExiste;
	}

	/* Tratar lista vazia */

	if (pLista->pElemCorr == NULL)
	{
		return LIS_CondRetListaVazia ;

	} /* fim ativa: Tratar lista vazia */

	/* Tratar avan�ar para frente */

	if (NumeroDeElementos > 0)
	{

		pElem = pLista->pElemCorr ;
		for(i = NumeroDeElementos ; i > 0 ; i--)
		{
			if (pElem == NULL)
			{
				break ;
			} /* if */
			
			pElem    = pElem->pProx ;
		} /* for */

		if (pElem != NULL)
		{
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */
		
		pLista->pElemCorr = pLista->pFimLista ;
		return LIS_CondRetFimLista ;

	} /* fim ativa: Tratar avan�ar para frente */

	/* Tratar avan�ar para tr�s */

	else if (NumeroDeElementos < 0)
	{
		pElem = pLista->pElemCorr ;
		for(i = NumeroDeElementos ; i < 0 ; i++)
		{
			if (pElem == NULL)
			{
				break ;
			} /* if */

			pElem    = pElem->pAnt ;
		} /* for */

		if (pElem != NULL)
		{
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */

		pLista->pElemCorr = pLista->pOrigemLista ;
		return LIS_CondRetFimLista ;

	} /* fim ativa: Tratar avan�ar para tr�s */

	/* Tratar n�o avan�ar */

	return LIS_CondRetOK ;

} /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/

LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista ,
	void * pValor      )
{

	tpElemLista * pElem ;

	if (pLista == NULL) 
	{
		return LIS_CondRetNaoExiste;
	}

	if (pLista->pElemCorr == NULL)
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	for (pElem  = pLista->pElemCorr ;
		pElem != NULL ;
		pElem  = pElem->pProx)
	{
		if (pElem->pValor == pValor)
		{
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */
	} /* for */
	
	return LIS_CondRetNaoAchou ;

} /* Fim fun��o: LIS  &Procurar elemento contendo valor */

//////////////////////////////////////////////////////////////////

/***************************************************************************
*
*  Fun��o: LIS Deturpar Lista
*  
****/

#ifdef _DEBUG

LIS_tpCondRet LIS_DeturparLista(LIS_tppLista pLista , LIS_tpModosDeturpacao acao)
{

	if (pLista == NULL)
	{
		return LIS_CondRetNaoExiste ;
	} /* if */

	switch (acao)
	{
		case LIS_NaoDeturpa :
			break ;

		case LIS_DeturpaEliminaCorrente :
			if (pLista->pElemCorr == NULL)
			{
				return LIS_CondRetCorrenteIndefinido;
			}  /* if */
			else
			{
				free(pLista->pElemCorr) ;
				pLista->pElemCorr = NULL ;
			} /* else */
			pLista->NumeroDeElementos-- ;
			break ;

		case LIS_DeturpaNULLpProx :
			if (pLista->pElemCorr == NULL)
			{
				return LIS_CondRetCorrenteIndefinido ;
			}  /* if */
			else
			{
				pLista->pElemCorr->pProx = NULL ;
			} /* else */
			break ;

		case LIS_DeturpaNULLpAnt :
			if (pLista->pElemCorr == NULL)
			{
				return LIS_CondRetCorrenteIndefinido ;
			}  /* if */
			else
			{
				pLista->pElemCorr->pAnt = NULL ;
			} /* else */
			break ;

		case LIS_DeturpaLixopProx :
			if (pLista->pElemCorr == NULL)
			{
				return LIS_CondRetCorrenteIndefinido ;
			} /* if */
			else
			{
				pLista->pElemCorr->pProx = (tpElemLista *) EspacoLixo ;
			} /* else */
			break ;

		case LIS_DeturpaLixopAnt :
			if (pLista->pElemCorr == NULL)
			{
				return LIS_CondRetCorrenteIndefinido ;
			}  /* if */
			else
			{
				pLista->pElemCorr->pAnt = (tpElemLista *) EspacoLixo ;
			} /* else */
			break ;

		case LIS_DeturpaNULLpValorCorrente :
			if (pLista->pElemCorr == NULL)
			{
				return LIS_CondRetCorrenteIndefinido ;
			}  /* if */
			else
			{
				pLista->pElemCorr->pValor = NULL ;
			} /* else */
			break ;

		case LIS_DeturpaAlteraTipoEstrutura :
			pLista->Tipo++;
			break ;

		case LIS_DeturpaDesencadeiaSemFree :
			if (pLista->pElemCorr == NULL)
			{
				return LIS_CondRetCorrenteIndefinido ;
			}  /* if */
			else
			{
				if (pLista->pElemCorr->pAnt != NULL)
				{
					pLista->pElemCorr->pAnt->pProx = pLista->pElemCorr->pProx ;
				} /* if */
				else
				{
					pLista->pOrigemLista = pLista->pElemCorr->pProx ;
				} /* else */

				if (pLista->pElemCorr->pProx != NULL)
				{
					pLista->pElemCorr->pProx->pAnt = pLista->pElemCorr->pAnt ;
				} /* if */
				else
				{
					pLista->pFimLista = pLista->pElemCorr->pAnt ;
				} /* else */
			} /* if */
		
			pLista->NumeroDeElementos-- ;
			pLista->pElemCorr = NULL ;
			break ;

		case LIS_DeturpaNULLpCorrente :
			pLista->pElemCorr->pValor = NULL ;
			break ;
		
		case LIS_DeturpaNULLpOrigem :
			pLista->pOrigemLista = NULL ;
			break ;

		case LIS_DeturpaAumentaNumeroElementos:
			pLista->NumeroDeElementos++ ;
			break ;
	   
	    case LIS_DeturpaNULLpUltimo:
			pLista->pFimLista = NULL ;
			break ;

		case LIS_DeturpaLixopUltimo:
			pLista->pFimLista = (tpElemLista *) EspacoLixo ;
			break ;
		
		case LIS_DeturpaLixopCorrente:
			pLista->pElemCorr = (tpElemLista *) EspacoLixo ;
			break ;

		case LIS_DeturpaAlteraTipoNoCorrente:
			pLista->pElemCorr->Tipo++;
			break ;

		case LIS_DeturpaAlteraTipoOrigem:
			pLista->pOrigemLista->Tipo++;
			break ;

		case LIS_DeturpaAlteraTipoUltimo:
			pLista->pFimLista->Tipo++;
			break ;

		case LIS_DeturpaNULLCabeca:
			pLista->pElemCorr->pCabeca = NULL;
			break ;

		case LIS_DeturpaNumeroDeElementosNegativo:
			pLista->NumeroDeElementos = -2;
			break ;

		case LIS_DeturpaLixopValorCorrente:
			pLista->pElemCorr->pValor = (tpElemLista *) EspacoLixo ;
			break ;

		default :
			return LIS_CondRetAcaoDeturpacaoInexistente ;

	} /* switch */

	return LIS_CondRetOK;

} /* Fim fun��o: LIS Deturpar Lista */

#endif

/***************************************************************************
*
*  Fun��o: LIST Verificar Lista
*  
****/

#ifdef _DEBUG

LIS_tpVerificar LIS_VerificarLista (LIS_tppLista pLista)
{
	int ContadorDeElementos = 0 ;
	int AchouCorrente = 0 ;

	void * PonteiroVoid = NULL ;
	tpElemLista * pElemento = NULL ;

	int TipoCabeca = -1 ;
	int TipoValor  = -1 ;

	int Iterador    = -1 ;
	int NumEspacos = -1 ;
	int EstaAtivo    = -1 ;
	int TipoEspaco = -1 ;

	/*
	*    Se pLista == NULL , ent�o ela n�o existe
	*/

	if (pLista == NULL)
	{
		CNT_CONTAR("LIS_Verificar_ListaInexistente") ;
		return LIS_Verificar_ListaInexistente ;
	} /* if */

	/*
	*   Se pPrimeiro == NULL , ent�o pCorrente == NULL e
	*                                pUltimo == NULL e
	*                                NumeroDeElementos == 0
	*   Se pUltimo == NULL , ent�o pCorrente == NULL e
	*                              pPrimeiro == NULL e
	*                              NumeroDeElementos == 0
	*   Se NumeroDeElementos == 0 , ent�o pCorrente == NULL e
	*                                     pUltimo == NULL e
	*                                     pPrimeiro == NULL
	*/

	if (pLista->pOrigemLista == NULL)
	{
		if ((pLista->pElemCorr != NULL) ||
			(pLista->pFimLista != NULL) ||
			(pLista->NumeroDeElementos != 0))
		{
			CNT_CONTAR("LIS_Verificar_Cabeca_pPrimeiroNull") ;
			return LIS_Verificar_Cabeca_pPrimeiroNull ;
		} /* if */
	} /* if */

	if (pLista->pFimLista == NULL)
	{
		if ((pLista->pElemCorr != NULL) ||
			(pLista->pOrigemLista != NULL) ||
			(pLista->NumeroDeElementos != 0))
		{
			CNT_CONTAR("LIS_Verificar_Cabeca_pUltimoNull") ;
			return LIS_Verificar_Cabeca_pUltimoNull ;
		} /* if */
	} /* if */

	/*
	*   NumeroDeElementos � sempre maior ou igual � 0
	*   Se pPrimeiro != NULL , ent�o pPrimeiro->pAnterior == NULL
	*   Se pUltimo != NULL , ent�o pUltimo->pProximo == NULL
	*/

	if (pLista->NumeroDeElementos < 0)
	{
		CNT_CONTAR("LIS_Verificar_Cabeca_NumeroDeElementosInvalido") ;
		return LIS_Verificar_Cabeca_NumeroDeElementosInvalido ;
	} /* if */

	if (pLista->pOrigemLista != NULL)
	{
		if (pLista->pOrigemLista->pAnt != NULL)
		{
			CNT_CONTAR("LIS_Verificar_Cabeca_pPrimeiroIncorreto") ;
			return LIS_Verificar_Cabeca_pPrimeiroIncorreto ;
		} /* if */
	} /* if */

	if (pLista->pFimLista != NULL)
	{
		if (pLista->pFimLista->pProx != NULL)
		{
			CNT_CONTAR("LIS_Verificar_Cabeca_pUltimoIncorreto") ;
			return LIS_Verificar_Cabeca_pUltimoIncorreto ;
		} /* if */
	} /* if */
	
	/* Marca todos os espa�os alocados como inativos */
	CED_MarcarTodosEspacosInativos() ;

	/* Guarda o tipo da cabe�a da lista e a marca como ativa */
	PonteiroVoid = (void *) pLista ;
	TipoCabeca = CED_ObterTipoEspaco(PonteiroVoid) ;
	CED_MarcarEspacoAtivo(PonteiroVoid) ;

	if(TipoCabeca != LIS_TipoEspacoCabeca)
	{
		CNT_CONTAR("LIS_Verificar_Cabeca_TipoInconsistente") ;
		return LIS_Verificar_Cabeca_TipoInconsistente ;
	}

	/*
	*   Se pElemento->pAnterior == NULL , ent�o lista->pPrimeiro == pElemento
	*   Se pElemento->pAnterior != NULL , ent�o pElemento->pAnterior->pProximo == pElemento
	*   Se pElemento->pProximo == NULL , ent�o lista->pUltimo == pElemento
	*   Se pElemento->pProximo != NULL , ent�o pElemento->pProximo->pAnterior == pElemento
	*/
	for (pElemento = pLista->pOrigemLista ; pElemento != NULL ; pElemento = pElemento->pProx)
	{
		if(CED_ObterTipoEspaco(pElemento) != pElemento->Tipo)
		{
			CNT_CONTAR("LIS_Verificar_Elemento_TipoInconsistente") ;
			return LIS_Verificar_Elemento_TipoInconsistente ;
		} /* if */

		if(CED_ObterTipoEspaco(pElemento->pCabeca) != pLista->Tipo)
		{
			CNT_CONTAR("LIS_Verificar_Cabeca_TipoInconsistente") ;
			return LIS_Verificar_Cabeca_TipoInconsistente ;
		}

		if (pElemento->pAnt == NULL)
		{
			if (pLista->pOrigemLista != pElemento)
			{
				CNT_CONTAR("LIS_Verificar_Elemento_ErroNoEncadeamento") ;
				return LIS_Verificar_Elemento_ErroNoEncadeamento ;
			} /* if */
		}
		else
		{
			if (pElemento->pAnt->pProx != pElemento)
			{
				CNT_CONTAR("LIS_Verificar_Elemento_ErroNoEncadeamento") ;
				return LIS_Verificar_Elemento_ErroNoEncadeamento ;
			} /* if */
		} /* if */


		if (pElemento->pProx == NULL)
		{
			if (pLista->pFimLista != pElemento)
			{
				CNT_CONTAR("LIS_Verificar_Elemento_ErroNoEncadeamento") ;
				return LIS_Verificar_Elemento_ErroNoEncadeamento ;
			} /* if */
		}
		else
		{
			if (pElemento->pProx->pAnt != pElemento)
			{
				CNT_CONTAR("LIS_Verificar_Elemento_ErroNoEncadeamento") ;
				return LIS_Verificar_Elemento_ErroNoEncadeamento ;
			} /* if */
		} /* if */

		/*
		*   Se pElemento, ent�o pElemento->pValor != NULL
		*   O tipo do pElemento deve ser igual ao tipo da cabe�a da lista
		*/

		if (pElemento->pValor == NULL)
		{
			CNT_CONTAR("LIS_Verificar_Elemento_pValorNull") ;
			return LIS_Verificar_Elemento_pValorNull ;
		} /* if */

		/*
		*   Detecta se o valor foi deturpado (lixo)
		*/

		if(pElemento->pValor == EspacoLixo)
		{
			CNT_CONTAR("LIS_Verificar_Elemento_pValorErro");
			return LIS_Verificar_Elemento_pValorErro;
		} /* if */

		/* Checa atribui��es no controle de espa�o din�mico e marca os espa�os visitados como ativos */
		PonteiroVoid = (void *) pElemento ;
		CED_MarcarEspacoAtivo(PonteiroVoid) ;

		PonteiroVoid = (void *) pElemento->pValor ;
		TipoValor = CED_ObterTipoEspaco(PonteiroVoid) ;
		CED_MarcarEspacoAtivo(PonteiroVoid) ;
		
		/* Checa se o elemento em quest�o � o elemento corrente da cabe�a da lista */
		if (pLista->pElemCorr == pElemento)
		{
			/* Se achou o elemento referenciado pelo pCorrente, muda a vari�vel para 1 */
			AchouCorrente = 1 ;
		} /* if */

		ContadorDeElementos++ ;
	} /* for */

	/*
	*   O NumeroDeElementos deve ser igual ao n�mero de elementos contidos na lista
	*   Se pCorrente != NULL , ent�o o elemento referenciado por pCorrente deve pertencer � lista
	*/

	if (pLista->NumeroDeElementos != ContadorDeElementos)
	{
		CNT_CONTAR("LIS_Verificar_Cabeca_NumeroDeElementosInconsistente") ;
		return LIS_Verificar_Cabeca_NumeroDeElementosInconsistente ;
	} /* if */

	if (pLista->pElemCorr != NULL)
	{
		if (AchouCorrente == 0)
		{
			CNT_CONTAR("LIS_Verificar_Cabeca_pCorrenteInconsistente") ;
			return LIS_Verificar_Cabeca_pCorrenteInconsistente ;
		} /* if */
	} /* if */

	/* Controle de Vazamento de Mem�ria */
	NumEspacos = CED_ObterNumeroEspacosAlocados() ;

	CED_InicializarIteradorEspacos() ;

	for (Iterador = 0 ; Iterador < NumEspacos ; Iterador++)
	{
		PonteiroVoid = CED_ObterPonteiroEspacoCorrente() ;
		EstaAtivo = CED_EhEspacoAtivo(PonteiroVoid) ;
		TipoEspaco = CED_ObterTipoEspaco(PonteiroVoid) ;
		if (TipoEspaco == TipoCabeca)
		{
			if (EstaAtivo == 0)
			{
				CNT_CONTAR("LIS_Verificar_Lista_VazamentoDeMemoria") ;
				CED_TerminarIteradorEspacos() ;
				return LIS_Verificar_Lista_VazamentoDeMemoria ;
			} /* if */
		} /* if */
		CED_AvancarProximoEspaco() ;
	} /* for */

	CED_TerminarIteradorEspacos() ;

	CNT_CONTAR("LIS_Verificar_ListaValida") ;
	return LIS_Verificar_ListaValida ;

} /* Fim fun��o: LIS Verificar Lista */

#endif

//////////////////////////////////////////////////////////////////

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

void LiberarElemento(LIS_tppLista   pLista ,
	tpElemLista  * pElem )
{
	if ((pLista->ExcluirValor != NULL)
		&& (pElem->pValor != NULL      ))
	{
		pLista->ExcluirValor(pElem->pValor) ;
	} /* if */

	free(pElem) ;

	pLista->NumeroDeElementos-- ;
} /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

tpElemLista * CriarElemento(LIS_tppLista pLista ,
	void *       pValor)
{

	tpElemLista * pElem ;

	pElem = (tpElemLista *) malloc(sizeof(tpElemLista)) ;
	if (pElem == NULL)
	{
		return NULL ;
	} /* if */

	pElem->pValor = pValor ;
	pElem->pAnt   = NULL  ;
	pElem->pProx  = NULL  ;

	pLista->NumeroDeElementos ++ ;

	return pElem ;

} /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

void LimparCabeca(LIS_tppLista pLista)
{

	pLista->pOrigemLista = NULL ;
	pLista->pFimLista = NULL ;
	pLista->pElemCorr = NULL ;
	pLista->NumeroDeElementos   = 0 ;
} /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/

