
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergesort(int[], int);
void quicksort(int[], int);
void heapsort(int[], int);
int check(int[], int);

enum sorts {merge, quick, heap};

void usage(char *name) {
  printf("Usage: %s [mergesort|quicksort|heapsort]\n", name);
  exit(0);
}

int main(int argc, char* argv[]) {

  if (argc < 2) {
    usage(argv[0]);
  }

  // determine which sorting algorithm to use
  enum sorts sort;
  if (strcmp(argv[1], "mergesort") == 0) sort = merge;
  else if (strcmp(argv[1], "quicksort") == 0) sort = quick;
  else if (strcmp(argv[1], "heapsort") == 0) sort = heap;
  else usage(argv[0]);

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

    if (sort == heap) heapsort(a, size);
    else if (sort == merge) mergesort(a, size);
    else if (sort == quick) quicksort(a, size);

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