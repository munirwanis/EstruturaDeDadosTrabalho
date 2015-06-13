#define TAM_MAX_NOME_ALUNO  50

typedef enum
{
  INCLUSAO_BEM_SUCEDIDA    = 100,
  MEMORIA_INSUFICIENTE     = 101,
  MATRICULA_DUPLICADA      = 102,

  EXCLUSAO_BEM_SUCEDIDA    = 200,
  MATRICULA_NAO_ENCONTRADA = 201
} CodigoRetorno;

typedef struct
{
  int dia;
  int mes;
  int ano;
} Data;

typedef struct
{
  int   matricula;  // campo chave
  char  nome[TAM_MAX_NOME_ALUNO+1];
  float cr;
  Data  dataNascimento;
} Aluno;

