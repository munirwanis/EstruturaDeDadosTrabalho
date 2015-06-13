#include "CadastroAlunos.h"

typedef struct arvore
{
  Aluno raiz;
  struct arvore *subArvEsq;
  struct arvore *subArvDir;
} Turma; // ARVORE BINARIA

// Tipos de Percurso

#define PRE_ORDEM        0
#define ORDEM_SIMETRICA  1
#define POS_ORDEM        2

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
  // 1. Se a árvore estiver vazia, incluir o novo aluno na raiz (caso base 1)

  if ((*t) == NULL)
  {
    // 1.1. Alocar memoria para nova subarvore
  
    *t = malloc(sizeof(Turma));
    if ((*t) == NULL) return MEMORIA_INSUFICIENTE;
  
    // 1.2. Copiar os dados do novo aluno para a raiz da nova subarvore
    
    (*t)->raiz      = *a;
    (*t)->subArvEsq = NULL;
    (*t)->subArvDir = NULL;

    // 1.3. Retornar informando incluso bem-sucedida

    return INCLUSAO_BEM_SUCEDIDA;
  }

  // 2. Verificar se matricula novo aluno == matricula aluno-raiz (caso base 2)
  
  if (a->matricula == (*t)->raiz.matricula) return MATRICULA_DUPLICADA;
 
  // 3. Parte recursiva do algoritmo (matricula novo aluno != matricula raiz)
  
  if (a->matricula < (*t)->raiz.matricula) return incluir( &((*t)->subArvEsq) , a);
                                     else  return incluir( &((*t)->subArvDir) , a);
}

//----------------------------------------------------
// Listar todos os alunos de uma turma
//----------------------------------------------------

void percorrer(Turma *t, int tipoPercurso)
{
  // caso-base: arvore vazia
  
  if (t==NULL) return;

  
  if (tipoPercurso == PRE_ORDEM)
  {
    // listar o elemento armazenado na raiz
    printf("%p : %10d %20s %4.1f (Esq: %p Dir: %p)\n",
             t,
             t->raiz.matricula,
             t->raiz.nome,
             t->raiz.cr,
             t->subArvEsq,
             t->subArvDir);

    // listar todos os elementos da subarvore esquerda
    percorrer(t->subArvEsq, PRE_ORDEM);

    // listar todos os elementos da subarvore direita
    percorrer(t->subArvDir, PRE_ORDEM);
  }

  if (tipoPercurso == POS_ORDEM)
  {
    // listar todos os elementos da subarvore esquerda
    percorrer(t->subArvEsq, POS_ORDEM);

    // listar todos os elementos da subarvore direita
    percorrer(t->subArvDir, POS_ORDEM);

    // listar o elemento armazenado na raiz
    printf("%p : %10d %20s %4.1f (Esq: %p Dir: %p)\n",
             t,
             t->raiz.matricula,
             t->raiz.nome,
             t->raiz.cr,
             t->subArvEsq,
             t->subArvDir);
  }

  if (tipoPercurso == ORDEM_SIMETRICA) // EM_ORDEM
  {
    // listar todos os elementos da subarvore esquerda
    percorrer(t->subArvEsq, ORDEM_SIMETRICA);

    // listar o elemento armazenado na raiz
    printf("%p : %10d %20s %4.1f (Esq: %p Dir: %p)\n",
             t,
             t->raiz.matricula,
             t->raiz.nome,
             t->raiz.cr,
             t->subArvEsq,
             t->subArvDir);

    // listar todos os elementos da subarvore direita
    percorrer(t->subArvDir, ORDEM_SIMETRICA);

  }

}

void listar(Turma *t)
{
  Turma *p;
  
  // 1. Imprimir cabecalho
  
  system("cls");
  printf("t = %p\n\n",t);
  printf ("           MATRICULA  NOME                 CR\n");

  // 2. Listar alunos
  
  printf("\n\nPercurso PRE ORDEM:\n");
  percorrer(t, PRE_ORDEM);
  
  printf("\n\nPercurso POS ORDEM:\n");
  percorrer(t, POS_ORDEM);
  
  printf("\n\nPercurso EM ORDEM SIMETRICA:\n");
  percorrer(t, ORDEM_SIMETRICA);
}



//----------------------------------------------------
// Pesquisar dados de um aluno
//----------------------------------------------------

Aluno *pesquisar(Turma *t, int matriculaProcurada)
{
  // 1. Se a arvore estiver vazia,
  //      retornar ponteiro nulo (aluno nao encontrado)

  if (t==NULL) return NULL;
  
  // 2. Se matricula do aluno-raiz == matricula prociurada,
  //      retornar ponteiro para o aluno-raiz

  if (t->raiz.matricula == matriculaProcurada) return &(t->raiz);

  // 3. Parte recursiva do algoritmo (matricula raiz != matricula procurada)

  if (matriculaProcurada < t->raiz.matricula)
    return pesquisar(t->subArvEsq, matriculaProcurada);
  else
    return pesquisar(t->subArvDir, matriculaProcurada);
}


//----------------------------------------------------
// Excluir um aluno de uma turma
//----------------------------------------------------

int excluir(Turma **ppArvore, int matriculaExcluir)
{
  Turma *pVerticeExcluir, *pSucessor, **ppSucessor;

  // 1. Se a arvore estiver vazia, retornar erro 1

  if (!(*ppArvore)) return MATRICULA_NAO_ENCONTRADA; // elemento nao encontrado

  // 2. Se a matricula a ser excluida for menor que a matricula armazenada na raiz,
  //      excluir matricula na subarvore esquerda

  if ( matriculaExcluir < (*ppArvore)->raiz.matricula )
    return excluir(&((*ppArvore)->subArvEsq),matriculaExcluir);

  // 3. Se a matricula a ser excluida for maior que a matricula armazenada na raiz,
  //      excluir matricula na subarvore direita

  if ( matriculaExcluir > (*ppArvore)->raiz.matricula )
    return excluir(&((*ppArvore)->subArvDir),matriculaExcluir);

  // 4. Aqui o vertice a ser excluido foi encontrado (eh a raiz da arvore)

  pVerticeExcluir = *ppArvore;

  // 5. Se o vertice a ser excluido nao tiver filho esquerdo,
  //      o vertice-pai passa a apontar o filho direito do vertice a ser excluido

  if (!((*ppArvore)->subArvEsq))
  {
     *ppArvore = (*ppArvore)->subArvDir;
  }

  // 6. Se o vertice a ser excluido tiver filho esquerdo mas nao tiver filho direito,
  //      o vertice-pai passa a apontar o filho esquerdo do vertice a ser excluido

  else if ((!(*ppArvore)->subArvDir))
  {
     *ppArvore = (*ppArvore)->subArvEsq;
  }

  // 7. Se o vertice a ser excluido tiver 2 filhos
  //
  //    7.1. localizar o sucessor do vertice a ser excluido
  //         (sucessor = descendente mais a esquerda do filho direito)
  //
  //    7.2. pai do sucessor passa a apontar filho direito do sucessor
  //
  //    7.3. sucessor passa a ocupar o lugar do vertice a ser excluido (raiz da arvore)

  else
  {
     // 7.1. localizar o sucessor do vertice a ser excluido
     //      (sucessor = descendente mais a esquerda do filho direito)

     ppSucessor = &(pVerticeExcluir->subArvDir);
     while ((*ppSucessor)->subArvEsq) ppSucessor = &((*ppSucessor)->subArvEsq);
     pSucessor = *ppSucessor;

     // 7.2. pai do sucessor passa a apontar filho direito do sucessor

     *ppSucessor = pSucessor->subArvDir;

     // 7.3. sucessor passa a ocupar o lugar do vertice a ser excluido (raiz da arvore)

     *ppArvore = pSucessor;
     pSucessor->subArvEsq = pVerticeExcluir->subArvEsq;
     pSucessor->subArvDir = pVerticeExcluir->subArvDir;

  }

  // 8. Desalocar memoria ocupada pela antiga posicao do sucessor

  free(pVerticeExcluir);

  // 9. Retornar codigo de exclusao bem sucedida

  return EXCLUSAO_BEM_SUCEDIDA;

}



