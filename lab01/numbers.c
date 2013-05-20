#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ----- Thread ----- */
pthread_t inputthread;
pthread_t printthread;
pthread_mutex_t lock;

/* ----- Parameters -----*/
int max, min, num, total;
float average;
int list[5];

/* this function takes the input number */
void *input(void *arg)
{

	while(1)
	{
		pthread_mutex_lock(&lock);

		char str[80];
		scanf("%s", str);

		/* if user inputs 'q', program terminates */
		if(!strcmp(str, "q"))
		{
			exit(0);
		}

		/* if user inputs an integer, save it */
		int temp = atoi(str);
		if(!temp)
		{
			continue;
		}

		/* update data */
		num++;
		total+=temp;

		/* initialize if it is the first number */
		if(num == 1)
		{
			max = min = temp;
		} 

		/* update max, min, average, and recent list */
		max = (temp > max)?temp:max;
		min = (temp < min)?temp:min;
		average = total / (float) num;

		if(num <= 5)
		{
			list[num-1] = temp;
		}
		else
		{
			list[0]=list[1];
			list[1]=list[2];
			list[2]=list[3];
			list[3]=list[4];
			list[4]=temp;
		}
		pthread_mutex_unlock(&lock);


	}


}

/* this function sums the number */
void *print(void *arg)
{
	while(1)
	{
		sleep(10);
		pthread_mutex_lock(&lock);
		printf("The maximum value input so far: %i\n", max);
		printf("The minimum value input so far: %i\n", min);
		printf("The average value: %f\n", average);
		printf("The last five values input:");
		int i = (5<num)?5:num;
		for(--i;i>=0;i--)
		{
			printf(" %i", list[i]);
		}
		printf("\n");
		pthread_mutex_unlock(&lock);
	}
}

int main()
{

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		fprintf(stderr, "Error initializing mutex.\n");
		return 1;
	}

	if(pthread_create(&inputthread, NULL, input, NULL))
	{
		fprintf(stderr, "Error creating thread.\n");
		return 1;
	}
	if(pthread_create(&printthread, NULL, print, NULL))
	{
		fprintf(stderr, "Error creating thread.\n");
		return 1;
	}

	printf("Please input integers, or press 'q' to exit.\n");

	while(1);

	pthread_mutex_destroy(&lock);

}