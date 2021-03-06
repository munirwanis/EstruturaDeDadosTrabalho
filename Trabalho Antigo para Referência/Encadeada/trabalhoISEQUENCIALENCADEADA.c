#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// CONSTANTES
#ifndef NUM_MAX_ALUNOS
#define NUM_MAX_ALUNOS 100
#endif

typedef struct
{
  int   matricula;  // chave de pesquisa (unica)
  int   idade;
  char  nome[30];
}
Aluno;

typedef struct celula
{
  Aluno        aluno;
  struct celula *pProximaCelula;
}
Celula;

typedef struct
{
  Celula *pPrimeiraCelula;
}
Turma; // LISTA ENCADEADA


//-------------------------------------------------------------
// INSERIR UM NOVO ALUNO
//-------------------------------------------------------------

int inserir(Turma *pTurma, const Aluno *pNovoAluno)
{
  Celula *pNovaCelula;
  
  // 1.Criar uma nova celula para armazenar o novo aluno
  
  pNovaCelula = malloc(sizeof(Celula));
  
  if (!pNovaCelula) return 1; // Erro 1: memoria esgotada
  
  // 2.Armazenar o novo aluno na nova celula
  
  pNovaCelula->aluno = *pNovoAluno;
  
  // 3.Fazer a nova celula referenciar a primeira celula da lista

  pNovaCelula->pProximaCelula = pTurma->pPrimeiraCelula;

  // 4.Passar a referenciar a nova celula como primeira da lista

  pTurma->pPrimeiraCelula = pNovaCelula;
  
  // 5. Retornar indicando inclusao bem-sucedida
  
  return 0;

}

//-------------------------------------------------------------
// RECUPERAR DADOS DE UM ALUNO
//-------------------------------------------------------------


Aluno *recuperar(const Turma *pTurma, const int matricula)
{
  Celula *p;
  
  for (p=pTurma->pPrimeiraCelula; p; p=p->pProximaCelula)
  {
    if (p->aluno.matricula == matricula)
    {
      return (Aluno *) &(p->aluno);
    }
  }
  return (Aluno *) NULL;
}


//-------------------------------------------------------------
// REMOVER ALUNO
//-------------------------------------------------------------


int excluir(Turma *pTurma, const int matricula)
{
  Celula *p, *pExcluir;
  int r; // ELEMENTO NAO ENCONTRADO

  if (pTurma->pPrimeiraCelula == NULL) return 2; // lista Vazia

  if (pTurma->pPrimeiraCelula->aluno.matricula == matricula)
  {
    // Excluir primeiro item da lista
    
    pExcluir = pTurma->pPrimeiraCelula;
    pTurma->pPrimeiraCelula = pTurma->pPrimeiraCelula->pProximaCelula;
    free(pExcluir);
    r=0;
  }
  else
  {
    // Excluir item que nao e o primeiro da lista

    for (p=pTurma->pPrimeiraCelula; p!=NULL; p=p->pProximaCelula)
    {
      if (p->pProximaCelula->aluno.matricula == matricula)
      {
        pExcluir = p->pProximaCelula;
        p->pProximaCelula = p->pProximaCelula->pProximaCelula;
        free(pExcluir);
        r=0; break;
      }
    }
  }
  
  return r;
}
//-------------------------------------------------------------
// LISTAR TODOS ALUNOS
//-------------------------------------------------------------

void listar(const Turma *pTurma)
{
  Celula *p;
  
  //system("cls");
  printf("%10s  %4s  %-20s  %4s\n\n","ENDERECO","MATR","IDADE","NOME");
  for (p=pTurma->pPrimeiraCelula; p; p=p->pProximaCelula)
  {
    printf("[%8p] %4d  %-20d  %s\n",
           p,
           p->aluno.matricula,
           p->aluno.idade,
           p->aluno.nome);
  }
}

//-------------------------------------------------------------
// PROGRAMA PRINCIPAL
//-------------------------------------------------------------


int main()
{
  FILE *fInsert;
  FILE *fBusca;
  FILE *fRemove;
  fInsert = fopen("insertenc.csv", "a");
  fBusca = fopen("buscaenc.csv", "a");
  fRemove = fopen("removeenc.csv", "a");
  clock_t timeINS, timeBUSC, timeREM;
  Aluno meuAluno;
  Turma minhaTurma;
  int resultado,opcao,m, i,j;
  int vetor[NUM_MAX_ALUNOS];
  Aluno *pAluno;

  // Iniciar com a lista vazia
  
  minhaTurma.pPrimeiraCelula = NULL;
  

// INCLUIR ALUNO
	timeINS = clock();
	for (i=1;i<=NUM_MAX_ALUNOS;i++)
	    {
	      scanf("%d",&(meuAluno.matricula));
	      vetor[i] = meuAluno.matricula;
	      scanf("%d",&(meuAluno.idade));
	      scanf("%s",(meuAluno.nome));
	      resultado = inserir(&minhaTurma,&meuAluno);
	    }
	    
	 timeINS = clock() - timeINS;
	 fprintf(fInsert, "%6d,%f\n",
	  NUM_MAX_ALUNOS, (((float)timeINS)/(CLOCKS_PER_SEC/1000)));

// BUSCAR ALUNO VIA MATRICULA
	timeBUSC = clock();
	for (i=1;i<=NUM_MAX_ALUNOS;i++) {
      m = rand()%NUM_MAX_ALUNOS;
      pAluno = recuperar(&minhaTurma,m);
      }
     timeBUSC = clock() - timeBUSC;
	 fprintf(fBusca, "%6d,%f\n",
	  NUM_MAX_ALUNOS, (((float)timeBUSC)/(CLOCKS_PER_SEC/1000)));

// EXCLUIR ALUNO
	timeREM = clock();
	for (i=1;i<=NUM_MAX_ALUNOS;i++) {
	  m = vetor[i];
      resultado = excluir(&minhaTurma,m);
         
    
      }
     timeREM = clock() - timeREM;
	 fprintf(fRemove, "%6d,%f\n",
	  NUM_MAX_ALUNOS, (((float)timeREM)/(CLOCKS_PER_SEC/1000)));

fclose(fInsert);
fclose(fBusca);
fclose(fRemove);
}
