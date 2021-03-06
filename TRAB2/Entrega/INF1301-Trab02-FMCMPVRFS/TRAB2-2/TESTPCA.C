/***************************************************************************
*  $MCI M�dulo de implementa��o: TPCA Teste pe�a
*
*  Arquivo gerado:              TestPCA.c
*  Letras identificadoras:      TPCA
*
*  Projeto: Disciplina INF 1301

*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   fmc/mpjv/rfss   03/09/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "PECA.h"

static const char RESET_PECA_CMD        [] = "=resetteste";
static const char CRIAR_PECA_CMD        [] = "=criarpeca";
static const char OBTER_COR_PECA_CMD    [] = "=obtercorpeca";
static const char DESTRUIR_PECA_CMD     [] = "=destruirpeca";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECA 10
#define DIM_VALOR   100

PCA_tpPeca  *vtPeca[DIM_VT_PECA];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int ValidarInxPeca(int inxPeca , int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TPCA &Testar Pe�a
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 pe�as, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de Pe�as.
*     =criarpeca                  inxPeca    CorPeca   CondRetEsp
*     =obtercorpeca               inxPeca    CorPeca   CondRetEsp
*     =destruirpeca               inxPeca	           CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
   {

      int inxPeca  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1,
		  CorPecaEsp = -1;

	  PCA_tpCondRet CondRetObtido   = PCA_CondRetOK;
      PCA_tpCondRet CondRetEsperado = PCA_CondRetOK;
		/* inicializa para qualquer coisa */

      int i;
	  
	  PCA_tpCorPeca CorPeca;

      /* Efetuar reset de teste de pe�a */

         if(strcmp(ComandoTeste , RESET_PECA_CMD) == 0)
         {

            for(i = 0; i < DIM_VT_PECA; i++)
			{
			   CondRetObtido = PCA_DestruirPeca(&vtPeca[i]);
               vtPeca[i] = NULL;
            } /* for */

			return TST_CompararInt(CondRetEsperado , CondRetObtido ,
                                    "Retorno errado ao destruir peca.");

         } /* fim ativa: Efetuar reset de teste de pe�a */

      /* Testar Criar Pe�a */

         else if(strcmp(ComandoTeste , CRIAR_PECA_CMD) == 0)
         {

            numLidos = LER_LerParametros("iii" ,
                       &inxPeca, &CorPeca, &CondRetEsp);

            if((numLidos != 3)
              || (! ValidarInxPeca(inxPeca , VAZIO)))
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido =
                 PCA_CriarPeca(&vtPeca[inxPeca], CorPeca);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro em ponteiro de nova pe�a.");

         } /* fim ativa: Testar Criar Pe�a */

		 /* Testar Obter Cor Pe�a */

		 else if(strcmp(ComandoTeste , OBTER_COR_PECA_CMD) == 0)
         {
			 numLidos = LER_LerParametros("iii" ,
                               &inxPeca, &CorPecaEsp, &CondRetEsp);

            if(numLidos != 3)
            {
               return TST_CondRetParm;
            } /* if */
			
			CondRetObtido =
                 PCA_ObterCorPeca(vtPeca[inxPeca], &CorPeca);
			
            if(TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao obter cor da pe�a.") == TST_CondRetErro)
			{
				return TST_CondRetErro;
			} /* if */

			if(CondRetEsp == PCA_CondRetOK) {
				TST_CompararInt(CorPeca, CorPecaEsp,
				"Erro - valor inserido na peca nao foi obtido corretamente");
			} /* if */

			return TST_CondRetOK;
         } /* fim ativa: Testar Obter Cor Pe�a */

      /* Testar Destruir Pe�a */

         else if(strcmp(ComandoTeste , DESTRUIR_PECA_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                               &inxPeca, &CondRetEsp);
			
            if(numLidos != 2)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido =
                 PCA_DestruirPeca(&vtPeca[inxPeca]);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao destruir peca.");

         } /* fim ativa: Testar Destruir Pe�a */
		 
      return TST_CondRetNaoConhec;

   } /* fim fun��o: tpca &testar pe�a */
	


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TPCA - Validar indice de pe�a
*
***********************************************************************/

   int ValidarInxPeca(int inxPeca , int Modo)
   {

      if((inxPeca <  0)
        || (inxPeca >= DIM_VT_PECA))
      {
         return FALSE;
      } /* if */
         
      if(Modo == VAZIO)
      {
         if(vtPeca[inxPeca] != 0)
         {
            return FALSE;
         } /* if */
      } /* if */
	  else
      {
         if(vtPeca[inxPeca] == 0)
         {
            return FALSE;
         } /* if */
      } /* if */
         
      return TRUE;

   } /* Fim fun��o: TPCA - Validar indice de pe�a */

/********** Fim do m�dulo de implementa��o: TPCA Teste Pe�a **********/

