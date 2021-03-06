#include <stdio.h>
#include <stdlib.h>

// CONSTANTES
#ifndef
#define NUM_MAX_ALUNOS 100
#endif

typedef struct
{
  int   matricula;  // chave de pesquisa (unica)
  int idade;
  char  nome[30];

}
Aluno;

typedef struct
{
  Aluno aluno[NUM_MAX_ALUNOS];
  int   nAlunos;
}
Turma; // LISTA SEQUENCIAL



//-------------------------------------------------------------
// LISTAR TODOS ALUNOS
//-------------------------------------------------------------

void listar(const Turma *pTurma)
{
  int i;
  
  printf("%4s  %-20s  %4s\n\n","MATR","IDADE","NOME");
  for (i=0; i<pTurma->nAlunos; i++)
  {
    printf("%4d  %-20s  %4.1f\n",
           pTurma->aluno[i].matricula,
           pTurma->aluno[i].idade,
           pTurma->aluno[i].nome);
  }
}

//-------------------------------------------------------------
// INSERIR UM NOVO ALUNO
//-------------------------------------------------------------

int inserir(Turma *pTurma, const Aluno *pNovoAluno)
{
  int i;

  // 1. Verificar se existe espa�o para inser��o de um novo item
  
  if (pTurma->nAlunos == NUM_MAX_ALUNOS)
  {
    return 1;  // ERRO 1: Lista Cheia
  }
  
  // 2. Verificar se existe item com mesma chave na cole��o
  
  for (i=0; i<pTurma->nAlunos; i++)
  {
    if (pNovoAluno->matricula == pTurma->aluno[i].matricula)
    {
      return 2; // ERRO 2: Matricula Duplicada
    }
  }
  
  // 3. Deslocar 1 posicao a direita todos os itens com
  //    chave maior que a chave do item a ser inserido
  
  i = pTurma->nAlunos - 1;
  while (i >= 0
         && pTurma->aluno[i].matricula > pNovoAluno->matricula)
  {
    pTurma->aluno[i+1] = pTurma->aluno[i];
    i--;
  }
  
  // 4. Armazenar o novo item na posicao i+1
  
  pTurma->aluno[i+1] = *pNovoAluno;
  
  // 5. Incrementar a quantidade de itens

  pTurma->nAlunos++;
  
  // 6. Retornar indicando inclusao bem-sucedida
  
  return 0;

}

//-------------------------------------------------------------
// RECUPERAR DADOS DE UM ALUNO
//-------------------------------------------------------------

Aluno *recuperar(const Turma *pTurma, const int matricula)
{
  int i,m,f;  // inicio, meio, fim
  
  i = 0;
  f = pTurma->nAlunos-1;
  while (i<=f)
  {
    m = (i+f)/2;
    if (pTurma->aluno[m].matricula == matricula)
    {
      return (Aluno *) &(pTurma->aluno[m]);
    }
    if (pTurma->aluno[m].matricula > matricula) f = m-1;
                                           else i = m+1;
  }
  return (Aluno *)NULL;
}

//-------------------------------------------------------------
// REMOVER ALUNO
//-------------------------------------------------------------

int excluir(Turma *pTurma, const int matricula)
{
  int i;
  
  // 1. Localizar o item correspondente � chave fornecida
  
  for (i=0; i<pTurma->nAlunos; i++)
  {
    if (pTurma->aluno[i].matricula == matricula) break;
  }
  if (i==pTurma->nAlunos) return 1; // Aluno nao encontrado

  // 2. Deslocar todos os itens posteriores 1 posi��o a frente.
  
  while(i < pTurma->nAlunos-1)
  {
    pTurma->aluno[i] = pTurma->aluno[i+1];
    i++;
  }

  // 3. Decrementar a quantidade de alunos

  pTurma->nAlunos--;


  // 4. Retornar indicando exclusao bem sucedida
  
  return 0;
  
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
  
  minhaTurma.nAlunos = 0;
  
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
      printf("Idade:     "); scanf("%d",&(meuAluno.idade));

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
      system("cls");
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
      system("cls");
      printf("\nEXCLUIR ALUNO\n\n");
      printf("Matricula: "); scanf("%d",&m);
      resultado = excluir(&minhaTurma,m);

      if (resultado==0) printf("\n\nExclusao bem sucedida.\n\n");
      if (resultado==1) printf("\n\nAluno nao encontrado.\n\n");
    }

    system("pause");
  }
  while (opcao != 5);


  return 0;
}
