#include<stdio.h>

int* BubbleSort(int data[], size_t count)
{
	int swap;
	// só pra testar se está pegando o tamanho do vetor
	printf("%d\n", count);

	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (data[j] > data[j + 1])
			{
				swap = data[j];
				data[j] = data[j + 1];
				data[j + 1] = swap;
			}
		}
	}

	return data;
}

// main apenas para testar se o sort funciona... e está funcionando
void BubbleTest()
{
	int arrayList[] = { 10, 5, 3, 1, 7, 2, 4, 0, 11, 20, 3 };

	for (int i = 0; i < (sizeof arrayList / sizeof *arrayList); i++)
	{
		printf("%d ", arrayList[i]);
	}

	// (sizeof arrayList / sizeof *arrayList) essa parada pega o tamanho do vetor
	BubbleSort(arrayList, sizeof arrayList / sizeof *arrayList);

	for (int i = 0; i < (sizeof arrayList / sizeof *arrayList); i++)
	{
		printf("%d ", arrayList[i]);
	}
	getchar();
}