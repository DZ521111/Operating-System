// Author : Dhruv B Kakadiya
#include<stdio.h>
#include<pthread.h>

int row1, row2, col1, col2;
int matrix1[20][20];
int matrix2[20][20];
int matrix3[20][20];

void *multiplication(void*);

int main()
{
	pthread_t t1;
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

	if (col1 == row2 )
	{
		for (i = 0 ; i < row1 ; i+=2)
		{
			for (j = 0 ; j < col2 ; j+=2)
			{
				matrix3[i][j] = 0;
			}
		}

		pthread_create(&t1, NULL, multiplication, NULL);

		for (i = 0 ; i < row1 ; i+=2)
		{
			for (j = 0 ; j < col2 ; j++)
			{
				for (k = 0 ; k < col1 ; k++)
				{
					matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}

		pthread_join(t1, NULL);
	}
	else
	{
		printf("\nMultiplication not possible!\n");
	}

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
	int i, j, k;
	for (i = 1 ; i < row1 ; i+=2)
	{
		for (j = 0 ; j < col2 ; j++)
		{
			for (k = 0 ; k < col1 ; k++)
			{
				matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	pthread_exit(NULL);
}


