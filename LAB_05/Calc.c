// Author : Dhruv B Kakadiya
#include<stdio.h>
#include<pthread.h>

float num1, num2;
void* addition(void*);
void* substraction(void*);
void* multiplication(void*);
void* division(void*);

int main()
{
	pthread_t t1, t2, t3, t4;
	printf("Enter the two numbrs : \n");
	scanf("%f %f", &num1, &num2);
	pthread_create(&t1, NULL, addition, NULL);
	pthread_join(t1, NULL);
	pthread_create(&t2, NULL, substraction, NULL);
	pthread_join(t2, NULL);
	pthread_create(&t3, NULL, multiplication, NULL);
	pthread_join(t3, NULL);
	pthread_create(&t4, NULL, division, NULL);
	pthread_join(t4, NULL);
	return 0;
}

void* addition(void* temp)
{
	printf("Addition of %f and %f is : %f\n\n", num1, num2, num1 + num2);
}

void* substraction(void* temp)
{
	printf("Substraction of %f and %f is : %f\n\n", num1, num2, num1 - num2);
}

void* multiplication(void* temp)
{
	printf("Multiplication of %f and %f is : %f\n\n", num1, num2, num1 * num2);
}

void* division(void* temp)
{
	if (num2 != 0)
		printf("Division of %f and %f is : %f\n\n", num1, num2, num1 / num2);
	else
		printf("Division is Not possible\n");
}
