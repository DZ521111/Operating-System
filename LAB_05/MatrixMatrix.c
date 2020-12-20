// Author : Dhruv B Kakadiya
#include<stdio.h>
#include<pthread.h>

int row1, row2, col1, col2;
int matrix1[50][50];
int matrix2[50][50];
int matrix3[50][50];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *multiplication(void*);

int main()
{
	int i, j, k;
	printf("Enter number of rows and cols for 1st matrix : \n");
	scanf("%d %d", &row1, &col1);

	for (i = 0 ; i < row1 ; i++)
	{
		for (j = 0 ; j < col1 ; j++)
		{
			printf("matrix1[%d][%d] : ", i, j);
			scanf("%d", &matrix1[i][j]);
		}
	}
	
	printf("\nEnter number of rows and cols for 2nd matrix : \n");
	scanf("%d %d", &row2, &col2);

	for (i = 0 ; i < row2 ; i++)
	{
		for (j = 0 ; j < col2 ; j++)
		{
			printf("matrix2[%d][%d] : ", i, j);
			scanf("%d", &matrix2[i][j]);
		}
	}

	pthread_t thread[row1];

	if (col1 == row2)
	{
		for (i = 0 ; i < row1 ; i+=2)
		{
			for (j = 0 ; j < col2 ; j+=2)
			{
				matrix3[i][j] = 0;
			}
		}

		for (i = 0 ; i < row1 ; i++)
		{
			pthread_create(&thread[i], NULL, multiplication, NULL);
		}

		for (i = 0 ; i < row1 ; i++)
		{
			pthread_join(thread[i], NULL);
		}

	}
	else
	{
		printf("\nMultiplication not possible!\n");
	}
	printf("Matrix1 is : \n");
	for (i = 0 ; i < row1 ; i++)
	{
		for (j = 0 ; j < col1 ; j++)
		{
			printf("%d\t", matrix1[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
	printf("Matrix2 is : \n");
	for (i = 0 ; i < row2 ; i++)
	{
		for (j = 0 ; j < col2 ; j++)
		{
			printf("%d\t", matrix2[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

	printf("\nresult is : \n");

	for (i = 0 ; i < row1 ; i++)
	{
		for (j = 0 ; j < col2 ; j++)
		{
			printf("%d\t", matrix3[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

void *multiplication(void *temp)
{
	pthread_mutex_lock(&m);
	int i, j, k;
	for (i = 0 ; i < row1 ; i++)
	{
		for (j = 0 ; j < col2 ; j++)
		{
			for (k = 0 ; k < col1 ; k++)
			{
				matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	pthread_mutex_unlock(&m);
}


