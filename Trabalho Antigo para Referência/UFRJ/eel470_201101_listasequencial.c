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
  
  system("cls");
  printf("%4s  %-20s  %4s\n\n","MATR","NOME","CR");
  for (i=0; i<pTurma->nAlunos; i++)
  {
    printf("%4d  %-20s  %4.1f\n",
           pTurma->aluno[i].matricula,
           pTurma->aluno[i].nome,
           pTurma->aluno[i].cr);
  }
}

//-------------------------------------------------------------
// INSERIR UM NOVO ALUNO
//-------------------------------------------------------------

int inserir(Turma *pTurma, const Aluno *pNovoAluno)
{
  int i;

  // 1. Verificar se existe espaço para inserção de um novo item
  
  if (pTurma->nAlunos == NUM_MAX_ALUNOS)
  {
    return 1;  // ERRO 1: Lista Cheia
  }
  
  // 2. Verificar se existe item com mesma chave na coleção
  
  for (i=0; i<pTurma->nAlunos; i++)
  {
    if (pNovoAluno->matricula == pTurma->aluno[i].matricula)
    {
      return 2; // ERRO 2: Matricula Duplicada
    }
  }
  
  // 3. Armazenar o novo item após o último item da lista
  
  pTurma->aluno[pTurma->nAlunos] = *pNovoAluno;
  
  // 4. Incrementar a quantidade de itens

  pTurma->nAlunos++;
  
  // 5. Retornar indicando inclusao bem-sucedida
  
  return 0;

}

//-------------------------------------------------------------
// RECUPERAR DADOS DE UM ALUNO
//-------------------------------------------------------------

Aluno *recuperar(const Turma *pTurma, const int matricula)
{
  int i;
  for (i=0; i<pTurma->nAlunos; i++)
  {
    if (pTurma->aluno[i].matricula == matricula)
    {
      return (Aluno *) &(pTurma->aluno[i]); // Aluno encontrado
    }
  }
  return (Aluno *)NULL;
}

//-------------------------------------------------------------
// REMOVER ALUNO
//-------------------------------------------------------------

int excluir(Turma *pTurma, const int matricula)
{
  int i;
  
  // 1. Localizar o item correspondente à chave fornecida
  
  for (i=0; i<pTurma->nAlunos; i++)
  {
    if (pTurma->aluno[i].matricula == matricula) break;
  }
  if (i==pTurma->nAlunos) return 1; // Aluno nao encontrado

  // 2. Deslocar todos os itens posteriores 1 posição a frente.
  
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
