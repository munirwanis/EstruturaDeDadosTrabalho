#include <stdio.h>
#include <stdlib.h>

#include "ListaSequencial.h"
#include "ListaSequencialOrdenada.h"
#include "CadastroAlunos.h"
#include "ArvoreBinaria.h"

int main()
{
  int opcao,r,matriculaDigitada;
  Aluno novoAluno;
  Aluno *alunoRecuperado;
  
  Turma *minhaTurma;
  
  // Criar uma nova turma
  
  minhaTurma = criarTurma();
  
  do
  {
    // Exibir menu principal na tela
    
    system("cls");
    printf("  CADASTRO DE ALUNOS:\n");
    printf("\n");
    printf("  [1] INCLUIR UM NOVO ALUNO\n");
    printf("  [2] LISTAR TODOS OS ALUNOS\n");
    printf("  [3] PESQUISAR DADOS DE UM ALUNO\n");
    printf("  [4] EXCLUIR UM ALUNO DA TURMA\n");
    printf("  [5] ENCERRAR O PROGRAMA\n");
    printf("\n");
    printf("  OPCAO: ");
    scanf("%d",&opcao);
    
    // OPCAO 1 - INCLUIR UM NOVO ALUNO
    
    if (opcao == 1)
    {
      system("cls");
      printf("  INCLUIR NOVO ALUNO:\n");
      printf("\n");
      printf("Matricula: "); scanf("%d",&(novoAluno.matricula));
      printf("Nome:      "); scanf("%s",novoAluno.nome);
      printf("CR:        "); scanf("%f",&(novoAluno.cr));

      r = incluir(&minhaTurma, &novoAluno);
      
      if (r==INCLUSAO_BEM_SUCEDIDA) printf("\nInclusao bem-sucedida!\n");
      if (r==MEMORIA_INSUFICIENTE)  printf("\nErro 1: Memoria insuficiente!\n");
      if (r==MATRICULA_DUPLICADA)   printf("\nErro 2: Matricula duplicada!\n");

      system("pause");
    }
    
    // OPCAO 2 - LISTAR TODOS OS ALUNOS
    
    if (opcao == 2)
    {
      listar(minhaTurma);
      system("pause");
    }

    // OPCAO 3 - PESQUISAR DADOS DE UM ALUNO

    if (opcao == 3)
    {

      system("cls");
      printf("  PESQUISAR DADOS DE UM ALUNO:\n");
      printf("\n");
      printf("Matricula: "); scanf("%d",&matriculaDigitada);

      alunoRecuperado = pesquisar(minhaTurma,matriculaDigitada);
      
      if (alunoRecuperado == NULL)
      {
        printf("\nERRO: Aluno nao encontrado\n");
      }
      else
      {
        printf("%10d %20s %4.1f\n",
             (*alunoRecuperado).matricula,
             (*alunoRecuperado).nome,
             (*alunoRecuperado).cr);
      }
      system("pause");

    }

    // OPCAO 4 - EXCLUIR UM ALUNO DA TURMA

    if (opcao == 4)
    {

      system("cls");
      printf("  EXCLUIR UM ALUNO:\n");
      printf("\n");
      printf("Matricula: "); scanf("%d",&matriculaDigitada);

      r = excluir(&minhaTurma,matriculaDigitada);
      
      if (r==0) printf("\nExclusao bem-sucedida!\n");
      if (r==1) printf("\nErro 1: Matricula nao encontrada!\n");

    }

  }
  while (opcao != 5);
  
  return 0;
  
}
