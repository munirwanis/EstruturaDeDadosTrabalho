#define QTD_MAX_ALUNOS     200

#include "CadastroAlunos.h"

typedef struct
{
  int   nAlunos;
  Aluno aluno[QTD_MAX_ALUNOS];
} Turma; // LISTA SEQUENCIAL

//----------------------------------------------------
// Criar uma nova turma
//----------------------------------------------------

Turma *criarTurma()
{
  Turma *t;
  t = malloc(sizeof(Turma));
  (*t).nAlunos = 0;
  return t;
}

//----------------------------------------------------
// Incluir um novo aluno em uma turma
//----------------------------------------------------

CodigoRetorno incluir(Turma *t, Aluno *a)
{
  int i;
  
  // 1. Verificar se ha espaco na lista
  
  if ((*t).nAlunos==QTD_MAX_ALUNOS) return MEMORIA_INSUFICIENTE;
  
  // 2. Verificar se a matricula do novo aluno ja existe na lista
  //    e determinar a posicao onde o novo aluno sera inserido
  
  i = (*t).nAlunos-1;
  while (i >= 0 && (*t).aluno[i].matricula > (*a).matricula)
  {
    (*t).aluno[i+1] = (*t).aluno[i];
    i--;
  }
  
  // 3. Incluir o novo aluno na primeira posicao vaga da lista

  (*t).aluno[i+1] = *a;

  // 4. atualizar o numero de alunos cadastrados na turma

  (*t).nAlunos++;
  
  // 5. Retornar informando inclusao bem-sucedida
  
  return INCLUSAO_BEM_SUCEDIDA;
}

//----------------------------------------------------
// Listar todos os alunos de uma turma
//----------------------------------------------------

void listar(Turma *t)
{
  int i;
  
  // 1. Imprimir cabecalho
  
  system("cls");
  printf ("MATRICULA  NOME                 CR\n");

  // 2. Imprimir alunos

  for (i=0; i<(*t).nAlunos; i++)
  {
    printf("%10d %20s %4.1f\n",
             (*t).aluno[i].matricula,
             (*t).aluno[i].nome,
             (*t).aluno[i].cr);
  }
}

//----------------------------------------------------
// Pesquisar dados de um aluno
//----------------------------------------------------

Aluno *pesquisar(Turma *t, int matriculaProcurada)
{
  int i,m,f;
  
  // pesquisar aluno com a matricula dada

  i = 0;
  f = (*t).nAlunos-1;
  while (i<=f)
  {
    m = (i+f)/2;
    if ((*t).aluno[m].matricula == matriculaProcurada)
    {
      return &((*t).aluno[m]);
    }
    if ((*t).aluno[m].matricula >  matriculaProcurada) f = m-1;
                                                 else  i = m+1;
  }
  
  // se a matricula nao tiver sido encontrada retornar NULL

  return NULL;
}

//----------------------------------------------------
// Excluir um aluno de uma turma
//----------------------------------------------------

CodigoRetorno excluir(Turma *t, int matriculaProcurada)
{
  int i;

  // 1. Localizar o registro a ser excluido da lista
  
  for (i=0; i<(*t).nAlunos; i++)
  {
    if ((*t).aluno[i].matricula == matriculaProcurada) break;
  }
  
  // 2. se a matricula procurada tiver sido encontrada

  if (i<(*t).nAlunos)
  {
    // 2.1. Deslocar 1 posicao a frente todos os elementos
    //      posteriores ao elemento removido (posicao i)
    
    for ( ;i<(*t).nAlunos; i++) (*t).aluno[i] = (*t).aluno[i+1];
    
    // 2.2. Atualizar o numero de alunos cadastrados na turma
    
    (*t).nAlunos--;
    
    // 2.3. Retornar indicando exclusao bem sucedida
    
    return EXCLUSAO_BEM_SUCEDIDA;
  }
  else  // matricula nao encontrada
  {
    return MATRICULA_NAO_ENCONTRADA;
  }
}
