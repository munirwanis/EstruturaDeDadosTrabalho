#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_tamanho_nome 51
#define max_tamanho_telefone 12

typedef struct Contatos
{	char Nome[max_tamanho_nome];
	char tel[max_tamanho_telefone];
	struct Contatos *proximo;
}Contatos;

typedef struct ListaLinear
{	Contatos *inicio;
	int N;
}ListaLinear;

int TamanhoLista(ListaLinear *L){return L->N;}

void ConstroiLista(ListaLinear *L)
{
	L->inicio=NULL;
	L->N=0;
}

int DestroiLista(ListaLinear *L)
{
	Contatos *aux,*p,*pproximo;

	pproximo=L->inicio;

	while (pproximo!=NULL)
	{
		aux=pproximo;
		pproximo=pproximo->proximo;
		p=aux;
		free(p);
		L->N=L->N-1;
	}
	
}

int InsereLista(ListaLinear *L, char nome[],char telefone[],int Posicao)
{
	Contatos *novo,*p,*aux;
	novo=(Contatos *)malloc(sizeof(Contatos));
	strcpy(novo->Nome,nome);
	strcpy(novo->tel,telefone);
	int i;

	p=L->inicio;

	if (Posicao==1)
	{
		aux=L->inicio;
		L->inicio=novo;
		novo->proximo=aux;
	}
	else
	{
		for (i=1;i<Posicao-2;i++){p=p->proximo;}
		
		aux=p->proximo;
		p->proximo=novo;
		novo->proximo=aux;
	}
	L->N=L->N+1;
}

void EnumeraLista(ListaLinear *L)
{
	Contatos *p;
	p=L->inicio;
	printf("\t\tNome\t\t\tTelefone\n");
	while(p!=NULL)
	{
		printf("\t\t%s\t\t\t%s\n",p->Nome,p->tel);
		p=p->proximo;
	}
}

int BuscaNaoOrdenadaLista(ListaLinear *L, char nome[])
{
	Contatos *p;
	int i,comparacao;i=0;
	p=L->inicio;
	while (p!=NULL && ((comparacao=strcmp(p->Nome,nome))!=0))
		{p=p->proximo;++i;}
	if (p!=NULL && (comparacao==0)){return i;}
	else{return -1;}
}

void RemovePosicaoEm(ListaLinear *L, int posicao)
{
	Contatos *p,*pAnt;
	int i;i=0;

	p=L->inicio;

	if (posicao==0){pAnt=NULL;p=L->inicio;}
	else
	{
		pAnt=L->inicio;
		for (i;i<posicao-1;i++){pAnt=pAnt->proximo;}
		p=pAnt->proximo;
	}
	
	if (pAnt==NULL){L->inicio=L->inicio->proximo;}
	else{pAnt->proximo=p->proximo;}
	free(p);
	L->N=L->N-1;
	printf("\n\t\tPosicao %d removida com sucesso.\n\n",posicao);
}

void menu(ListaLinear *L)
{
	int i,status_menu;
	status_menu=0;
	
	do
	{
		printf("\n");
		printf("\n");
		printf("\t\t---------------------Lista de contatos---------------------\n\n");
		printf("Informe uma das seguintes opções:\n");
		printf("1 - Criar lista\n");
		printf("2 - Adicionar Contato\n");
		printf("3 - Enumerar Contato\n");
		printf("4 - Pesquisar Contatos por nome\n");
		printf("5 - Remover Contato com base na posicao\n");
		printf("6 - Remover Contato com base no nome\n");
		printf("7 - Tamanho da lista\n");
		printf("8 - Remover lista\n");
		printf("9 - Sair\n");
		printf("Opção: ");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
			{
				if (!L)
				{
					if (L=(ListaLinear *) malloc (sizeof(ListaLinear)))
					{ConstroiLista(L);printf("\t\tLista criada.\n\n");}
					else{printf("\t\tNão foi possível criar lista.\n\n");}
				}else{printf("\t\tLista já está criada.\n\n");}
				break;
			}
			case 2:
			{
				if (L!=NULL)
				{
					char nome[max_tamanho_nome],telefone[max_tamanho_telefone];

					printf("Informe o nome: ");scanf("%50s",nome);
					printf("Informe o telefone: ");scanf("%11s",telefone);

					if (InsereLista(L,nome,telefone,TamanhoLista(L)+1)){printf ("\n\t\tContato inserido com sucesso.\n\n");}
					else{printf("\t\tNão foi possível inserir contato na lista.\n\n");}

				}else{printf("\t\tLista inexistente.\n\n");}
				break;
			}
			case 3:
			{
				if (L)
				{
					if (L->inicio!=NULL){EnumeraLista(L);}else{printf("\t\tLista está vazia.\n\n");}
				}
				else{printf("\t\tLista inexistente.\n\n");}
				break;
			}
			case 4:
			{
				if (L)
				{
					if (L->inicio!=NULL)
					{
						char nome[max_tamanho_nome];int pos;
						printf("Informe o nome: ");scanf("%50s",nome);
						pos=BuscaNaoOrdenadaLista(L,nome);
				
						if (pos!=-1){printf("\n\t\tContato encontrado na posição %d.\n\n",pos);}
						else{printf("\n\t\tContato não foi encontrado na lista.\n\n");}
					}else{printf("\t\tLista está vazia.\n\n");}
				}else{printf("\t\tLista inexistente.\n\n");}
				break;
			}
			case 5:
			{
				if(L)
				{
					if (L->inicio!=NULL)
					{
						int i;
						printf("Informe a posição a ser removida: ");
						scanf("%d",&i);
						RemovePosicaoEm(L,i);
					}else{printf("\t\tLista está vazia.\n\n");}
				}else{printf("\t\tLista inexistente.\n\n");}
				break;
			}
			case 6:
			{
				if (L)
				{
					if (L->inicio!=NULL)
					{
						char nome[max_tamanho_nome];int pos;
						printf("Informe o nome: ");scanf("%50s",nome);
						pos=BuscaNaoOrdenadaLista(L,nome);
				
						if (pos!=-1){RemovePosicaoEm(L,pos);}
						else{printf("\n\t\tContato não foi encontrado na lista.\n\n");}
					}else{printf("\t\tLista está vazia.\n\n");}
				}else{printf("\t\tLista inexistente.\n\n");}
				break;
			}
			case 7:
			{
				if (L){printf("\n\t\tTamanho atual da lista: %d\n\n",TamanhoLista(L));}
				else{printf("\t\tLista inexistente.\n\n");}
				break;
			}
			case 8:
			{
				if (L)
				{
					char c;
					while ( (c=getchar())!='s' && c!='S' && c!='n' && c!='N' )
					{
						printf("\n\t\tDeseja remover lista (s/S/n/N)? ");
					}
					if (c=='s' || c=='S')
					{
						if (L->inicio!=NULL)
						{DestroiLista(L);printf("\n\t\tLista removida com sucesso.");}
						else{printf("\n\t\tLista está vazia.");}
					}
				}else{printf("\t\tLista inexistente.\n\n");}
				break;				
			}
			case 9: {printf("\t\tEncerrando programa.\n\n");status_menu=1;break;}
			default: printf("\t\tOpção inválida.\n\n");break;
		}
	}while(status_menu==0);
	exit(0);
}


int main()
{
	ListaLinear *L;
	menu(L);
}


