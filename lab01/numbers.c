#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* thread and lock */
pthread_t thread;
pthread_mutex_t lock;

/* global parameters */
int max, min, num, total, flag;
float average;
int list[5];

/* thread function */
void *print(void *arg)
{
	while(1)
	{
		sleep(3);
		pthread_mutex_lock(&lock);
		if(num==0)
		{
			printf("You haven't input anything.\n");
		}
		else
		{
			printf("The maximum value input so far: %i\n", max);
			printf("The minimum value input so far: %i\n", min);
			printf("The average of values input so far: %f\n", average);
			printf("The last five values input so far: ");
			int i = (5<num)?5:num;
			for(--i;i>=0;i--)
			{
				printf(" %i", list[i]);
			}
			printf("\n");
		}
		if(flag==1)
		{
			pthread_mutex_unlock(&lock);
			return;
		}
		pthread_mutex_unlock(&lock);
	}
}

main()
{
	
	if(pthread_mutex_init(&lock, NULL) != 0)
	{
		fprintf(stderr, "Error initializing mutex.\n");
		return 1;
	}
	
	if(pthread_create(&thread, NULL, print, NULL))
	{
		fprintf(stderr, "Error creating thread.\n");
		return 1;
	}
    
	printf("Please input integers, or press 'q' to exit.\n");
    
	void *status;
    
	while(1)
	{
		/* user input */
		char str[80];
		scanf("%s", str);
		//fgets(str, 80, stdin);
        
		pthread_mutex_lock(&lock);
        
		/* if input 'q', program terminates */
		if(!strcmp(str, "q"))
		{
			flag = 1;
			pthread_mutex_unlock(&lock);
			pthread_join(thread, &status);
			exit(0);
		}
        
		/* if input an integer, save it */
		int temp = atoi(str);
		char tempstr[80];
		sprintf(tempstr, "%d", temp);
		if((!temp && strcmp(str, "0")) || strcmp(str, tempstr))
		{
			pthread_mutex_unlock(&lock);
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
			list[0] = list[1];
			list[1] = list[2];
			list[2] = list[3];
			list[3] = list[4];
			list[4] = temp;
		}	
        
		pthread_mutex_unlock(&lock);
        
	}
    
	return 0;
    
	
}
