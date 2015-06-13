#include "CadastroAlunos.h"

typedef struct tipoTurma
{
  Aluno aluno;
  struct tipoTurma *proximoAluno;
} Turma; // LISTA ENCADEADA

//----------------------------------------------------
// Criar uma nova turma
//----------------------------------------------------

Turma *criarTurma()
{
  return NULL;
}

//----------------------------------------------------
// Incluir um novo aluno em uma turma
//----------------------------------------------------

CodigoRetorno incluir(Turma **t, Aluno *a)
{
  Turma *novaCelula;

  // 1. Criar uma nova celula para armazenar o novo item
  
  novaCelula = malloc(sizeof(Turma));
  if (novaCelula == NULL) return MEMORIA_INSUFICIENTE;

  // 2. Armazenar o novo aluno na nova celula.
  
  novaCelula->aluno = *a;
  
  // 3. Fazer a nova celula referenciar a primeira celula da lista
  
  novaCelula->proximoAluno = *t;
  
  // 4. Passar a referenciar como primeira celula da lista a nova celula.

  *t = novaCelula;
  
  // 5. Retornar informando incluso bem-sucedida
  
  return INCLUSAO_BEM_SUCEDIDA;
}


//----------------------------------------------------
// Listar todos os alunos de uma turma
//----------------------------------------------------

void listar(Turma *t)
{
  Turma *p;
  
  // 1. Imprimir cabecalho
  
  system("cls");
  printf("t = %p\n\n",t);
  printf ("           MATRICULA  NOME                 CR\n");

  // 2. Imprimir alunos


  for (p=t; p; p=p->proximoAluno)
  {
    printf("%p : %10d %20s %4.1f (proximo: %p)\n",
             p,
             p->aluno.matricula,
             p->aluno.nome,
             p->aluno.cr,
             p->proximoAluno);
  }
}

//----------------------------------------------------
// Pesquisar dados de um aluno
//----------------------------------------------------

Aluno *pesquisar(Turma *t, int matriculaProcurada)
{
  Turma *p;

  for (p=t; p; p=p->proximoAluno)
  {
    if (p->aluno.matricula == matriculaProcurada) return &(p->aluno);
  }
  return NULL;
}

//----------------------------------------------------
// Excluir um aluno de uma turma
//----------------------------------------------------

int excluir(Turma **t, int matriculaProcurada)
{
  Turma *p, *anterior;

  // 1. Localizar o registro a ser excluido da lista
  
  anterior = NULL;
  for (p=*t; p; p=p->proximoAluno)
  {
    if (p->aluno.matricula == matriculaProcurada) break;
    anterior = p;
  }

  // 2. se a matricula procurada tiver sido encontrada
  
  if (p)
  {
     if (anterior) // aluno a ser excluido NAO eh o primeiro da lista
     {
        // aluno anterior passa a apontar o aluno seguinte ao excluido
        anterior->proximoAluno = p->proximoAluno;
        
        // liberar memoria ocupada pelo aluno excluido
        free(p);
     }
     else          // aluno a ser excluido eh o primeiro da lista
     {
        // liberar memoria ocupada pelo aluno excluido
        free(*t);

        // aluno seguinte ao excluido passa a ser o primeiro da lista
        *t = p->proximoAluno;
     }

    // 2.3. Retornar indicando exclusao bem sucedida
    
    return EXCLUSAO_BEM_SUCEDIDA;
  }
  else  // matricula nao encontrada
  {
    return MATRICULA_NAO_ENCONTRADA;
  }
}
