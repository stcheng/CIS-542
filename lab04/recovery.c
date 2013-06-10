#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void mergesort(int[], int);
void heapsort(int[], int);
void quicksort(int[], int);
int check(int[], int);

void sort(int a[], int size) {

  int *a1 = (int*) malloc (sizeof(int) * size);
  int *a2 = (int*) malloc (sizeof(int) * size);

  memcpy( (void*)a1, (void*)a, sizeof(int) * size);
  memcpy( (void*)a2, (void*)a, sizeof(int) * size);

  quicksort(a, size);
  if (!check(a, size))
  {
    mergesort(a1, size);
    if (!check(a1, size))
    {
      heapsort(a2, size);
      memcpy( (void*)a, (void*)a2, sizeof(int) * size);
    }
    else
    {
      memcpy( (void*)a, (void*)a1, sizeof(int) * size);
    }
  }
  

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
