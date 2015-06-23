#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_tam_vetor 100000

int escolhaVetor()
{
	int opcao;
	do
	{
		printf(" 1 - Vetor crescente\n");
		printf(" 2 - Vetor decrescente\n");
		printf("Opcao: ");
		scanf("%d",&opcao);
		switch(opcao)
		{
			case 1:return 1;
			case 2:return 2;
			default: printf("Opcao invalida.\n");opcao=-1;
		}
		
	}while(opcao<0||opcao>2);
}

void inicializaVetor(int *vet[],int opcao)
{
	int i,temp;

	if (opcao==1)
	{
		temp=0;
		for (i=0;i<max_tam_vetor;i++)
		{
			vet[i]=temp;temp+=100;
		}
	}
	else
	{
		temp=100000;
		for (i=0;i<max_tam_vetor;i++)
		{
			vet[i]=temp;temp-=100;
		}
	}
}

void imprimeVetor(int *vet[])
{
	int i;
	for (i=0;i<max_tam_vetor;i++)
	{
		printf("%d\t",*(vet+i));
	}
}	

void InsertSort(int *vetor[],int n)
{
	int i,j,*temp,passos=0;
	for (j=1;j<=n-1;j++)
	{
		i=j;
		while (i>0 && vetor[i]<vetor[i-1])
		{
			//++passos;
			temp=vetor[i];
			vetor[i]=vetor[i-1];
			vetor[i-1]=temp;
			--i;
		}
		++passos;
	}
	//printf("\nInsertSort (passos): %d\n",passos);
}

void BubbleSort(int *vet[],int tamanho)
{
	int *temp,x,troca=1,passos=0;
	
	while (troca!=0 && tamanho>0)
	{
		for (x=0;x<tamanho-1;x++)
		{
			//++passos;
			troca=0;
			if (vet[x]>vet[x+1])
			{
				temp=vet[x];
				vet[x]=vet[x+1];
				vet[x+1]=temp;
				troca=1;
			}
		}
		--tamanho;
	}
	//printf("\nBubbleSort (passos): %d\n",passos);
}

void QuickSort(int *vet[], int inicio,int fim)
{
	int i,j,meio,*pivo,*aux;
	i=inicio;
	j=fim;
	pivo=vet[(inicio+fim)/2];

	while(i<=j)
	{
		while(vet[i]<pivo && i<fim){i++;}
		while(vet[j]>pivo && j>inicio){j--;}
		if (i<=j)
		{
			aux=vet[i];
			vet[i]=vet[j];
			vet[j]=aux;
			i=i+1;j=j-1;
		}
	}
	if (j>inicio){QuickSort(vet,inicio,j);}
	if(i<fim){QuickSort(vet,i,fim);}
}

void Merge(int *vet[],int tamanho)
{
	int mid;
	int i,j,k;
	int *tmp;

	tmp=(int *)malloc(sizeof(int)*tamanho);
	if (tmp==NULL){exit(1);}
	mid=tamanho/2;
	i=0;j=mid;k=0;
	while (i<mid && j<tamanho)
	{
		if (vet[i]<=vet[j]){tmp[k]=vet[i++];}
		else{tmp[k]=vet[j++];}
		++k;
	}
	if (i==mid)
	{
		while(j<tamanho){tmp[k++]=vet[j++];}
	}
	else
	{
		while (i<mid){tmp[k++]=vet[i++];}
	}
	for (i=0;i<tamanho;++i){vet[i]=tmp[i];}
	free(tmp);
}

void MergeSort(int *vet[],int tamanho)
{
	int mid;

	if (tamanho>1)
	{
		mid=tamanho/2;
		MergeSort(vet,mid);
		MergeSort(vet+mid,tamanho-mid);
		Merge(vet,tamanho);
	}
}

int main()
{
	int *vetor[max_tam_vetor];
	int i,escolha;

	clock_t start, end;
	double cpu_time_used;

	escolha=escolhaVetor();

	printf("\n");

	inicializaVetor(vetor,escolha);
	printf("\nOrdenação\tTempo\n");
	
	start = clock();
	InsertSort(vetor,max_tam_vetor);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("InsertSort\t%.10f\n",cpu_time_used);

	inicializaVetor(vetor,escolha);

	start = clock();
	BubbleSort(vetor,max_tam_vetor);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("BubbleSort\t%.10f\n",cpu_time_used);

	inicializaVetor(vetor,escolha);

	start = clock();
	QuickSort(vetor,0,max_tam_vetor-1);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("QuickSort\t%.10f\n",cpu_time_used);

	inicializaVetor(vetor,escolha);

	start = clock();
	MergeSort(vetor,max_tam_vetor);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("MergeSort\t%.10f",cpu_time_used);

	printf("\n\n");
	
}
