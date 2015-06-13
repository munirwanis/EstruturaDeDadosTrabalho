#include <stdio.h>
#include <stdlib.h>

// CONSTANTES

#define NUM_MAX_ALUNOS 60

typedef struct
{
  int   matricula;  // chave de pesquisa (unica)
  char  nome[51];
  float cr;
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
// LISTAR TODOS ALUNOS
//-------------------------------------------------------------

void listar(const Turma *pTurma)
{
  Celula *p;
  
  //system("cls");
  printf("%10s  %4s  %-20s  %4s\n\n","ENDERECO","MATR","NOME","CR");
  for (p=pTurma->pPrimeiraCelula; p; p=p->pProximaCelula)
  {
    printf("[%8p] %4d  %-20s  %4.1f\n",
           p,
           p->aluno.matricula,
           p->aluno.nome,
           p->aluno.cr);
  }
}

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
  int r=1; // ELEMENTO NAO ENCONTRADO

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
// PROGRAMA PRINCIPAL
//-------------------------------------------------------------


int main()
{
  Aluno meuAluno;
  Turma minhaTurma;
  int resultado,opcao,m;
  Aluno *pAluno;

  // Iniciar com a lista vazia
  
  minhaTurma.pPrimeiraCelula = NULL;
  
  // Menu principal

  do
  {
    system("cls");
    printf("\n");
    printf(" CADASTRO DE ALUNOS\n");
    printf("\n");
    printf(" 1 - INCLUIR UM NOVO ALUNO\n");
    printf(" 2 - EXIBIR LISTA\n");
    printf(" 3 - PESQUISAR ALUNO\n");
    printf(" 4 - EXCLUIR ALUNO\n");
    printf(" 5 - SAIR DO PROGRAMA\n");
    printf("\n");
    printf("OPCAO DESEJADA: "); scanf("%d",&opcao);
    
    // 1 - INSERIR NOVO ALUNO
    
    if (opcao == 1)
    {
      system("cls");
      printf("\nINCLUIR NOVO ALUNO\n\n");
      printf("Matricula: "); scanf("%d",&(meuAluno.matricula));
      printf("Nome:      "); scanf("%s",meuAluno.nome);
      printf("C.R.:      "); scanf("%f",&(meuAluno.cr));

      resultado = inserir(&minhaTurma,&meuAluno);

      if (resultado==0) printf("\n\nInclusao bem sucedida\n\n");
      if (resultado==1) printf("\n\nErro 1: Lista cheia\n\n");
      if (resultado==2) printf("\n\nErro 2: Matricula Duplicada\n\n");
    }
    
    // 2 - EXIBIR LISTA

    if (opcao == 2)
    {
      listar(&minhaTurma);
    }

    // 3 - PESQUISAR ALUNO


    if (opcao == 3)
    {
      //system("cls");
      printf("\nPESQUISAR ALUNO\n\n");
      printf("Matricula: "); scanf("%d",&m);
      pAluno = recuperar(&minhaTurma,m);

      if (pAluno)
      {
         printf("\nNome = %s\n",pAluno->nome);
         printf(  "C.R. = %4.1f\n\n",pAluno->cr);
      }
      else
      {
        printf("\n\n ERRO: Aluno nao encontrado\n\n");
      }
    }

    // 4 - EXCLUIR ALUNO


    if (opcao == 4)
    {
      //system("cls");
      printf("\nEXCLUIR ALUNO\n\n");
      printf("Matricula: "); scanf("%d",&m);
      resultado = excluir(&minhaTurma,m);

      if (resultado==0) printf("\n\nExclusao bem sucedida.\n\n");
      if (resultado==1) printf("\n\nAluno nao encontrado.\n\n");
      if (resultado==2) printf("\n\nLista vazia.\n\n");
    }

    //system("pause");
  }
  while (opcao != 5);


  return 0;
}
