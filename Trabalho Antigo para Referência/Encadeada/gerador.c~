#include <stdio.h>

#ifndef N
#define N 100000
#endif

void gerarnome(char nome[]);
void sortearmatri(int matri[]);

int main()
{
	typedef struct
	{
		int matricula;
		char nome[30];
		int idade;
	}Aluno;

	static Aluno lista;

	int i;
	static int matri[N];

	sortearmatri(matri);

	for(i=0;i<N;i++)
	{
		lista.matricula = matri[i];
		lista.idade = 17 + rand() % ( 9 + 3 + 9) - 3;
		gerarnome(lista.nome);
		printf("%d\n%d\n%s\n",lista.matricula,lista.idade,lista.nome);
	}
}

void gerarnome(char nome[])
{
	int i,tamlista,ran;
	char c;

	tamlista = 8 + (rand() % (12 + 5 + 4));

	for (i=0;i<tamlista;i++)
	{
		ran = rand() % (25 + 1);
		c = 97 + ran; 
		nome[i] = c;
	}
	nome[i+1] = '\0';
}

void sortearmatri(int matri[])
{
	int j,random,posicao;
	
	for (j=0;j<N;j++) // Criar Matriculas de 1 até N. 
		matri[j] = j+1;

	for (j=0;j<N;j++) // Randomiza as Matrículas trocando os números de Posição.
	{
		random = rand() % N;
		posicao = matri[j];
		matri[j] = matri[random];
		matri[random] = posicao;
	}
}
