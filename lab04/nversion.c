#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/* thread and lock */
pthread_t thread[3];
pthread_mutex_t lock;

void mergesort(int[], int);
void heapsort(int[], int);
void quicksort(int[], int);
int check(int[], int);

void *merge(void *arg);
void *heap(void *arg);
void *quick(void *arg);

struct data
{
  int *a;
  int size;
};

void sort(int a[], int size) {

  int *a1 = (int*) malloc (sizeof(int) * size);
  int *a2 = (int*) malloc (sizeof(int) * size);

  memcpy( (void*)a1, (void*)a, sizeof(int) * size);
  memcpy( (void*)a2, (void*)a, sizeof(int) * size);

  struct data *d = (struct data *)malloc(sizeof(struct data));
  struct data *d1 = (struct data *)malloc(sizeof(struct data));
  struct data *d2 = (struct data *)malloc(sizeof(struct data));
  (*d).a = a;
  (*d).size = size;
  (*d1).a = a1;
  (*d1).size = size;
  (*d2).a = a2;
  (*d2).size = size;
  
  if(pthread_create(&(thread[0]), NULL, quick, (void *)d))
  {
    fprintf(stderr, "Error creating thread.\n");
    exit(1);
  }

  if(pthread_create(&(thread[1]), NULL, merge, (void *)d1))
  {
    fprintf(stderr, "Error creating thread.\n");
    exit(1);
  }

  if(pthread_create(&(thread[2]), NULL, heap, (void *)d2))
  {
    fprintf(stderr, "Error creating thread.\n");
    exit(1);
  }

  if(pthread_join(thread[0], NULL))
  {
    fprintf(stderr, "Error joining thread.\n");
    exit(1);
  }

  if(check(a, size))
  {
    printf("quick is right.\n");
    return;
  }

  if(pthread_join(thread[1], NULL))
  {
    fprintf(stderr, "Error joining thread.\n");
    exit(1);
  }

  if(check(a1, size))
  {
    memcpy( (void*)a, (void*)a1, sizeof(int) * size);
    printf("merge is right.\n");
    return;
  }

  if(pthread_join(thread[2], NULL))
  {
    fprintf(stderr, "Error joining thread.\n");
    exit(1);
  }

  if(check(a2, size))
  {
    memcpy( (void*)a, (void*)a2, sizeof(int) * size);
    printf("heap is right.\n");
    return;
  }

}

void *merge(void *arg)
{
  struct data *d = (struct data*) arg;
  mergesort((*d).a, (*d).size);
}

void *heap(void *arg)
{
  struct data *d = (struct data*) arg;
  heapsort((*d).a, (*d).size);
}

void *quick(void *arg)
{
  struct data *d = (struct data*) arg;
  quicksort((*d).a, (*d).size);
}


int main(int argc, char* argv[]) {
  double tests = 100;
  int k = 0;
  int success = 0;
  int milestone = tests/10;
  printf("Starting simulation...\n");
  for (k = 0; k < tests; k++) {

    if (k % milestone == 0 && k != 0) {
      printf("%d%% done\n", (k/milestone)*10);
    }

    int size = 1000000;
    int* a    = malloc(sizeof(int)*size);
    int i;
    srand(time(NULL));
    for(i=0; i<size; i++) {
        a[i] = rand() % size;
    }
    
    sort(a, size);

    if (check(a, size)) {
      success++;
      //puts("SUCCESS"); 
    }
    else {
      //puts("ERROR!");
    }
    free(a);
  }

  double reliability = (success/tests)*100;
  printf("Reliability: %.2f%\n", reliability);

  return 0;
}
