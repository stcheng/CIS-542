
#include <stdlib.h>


int one(int *A, int *B) {
  int temp;
  temp = A[2] + B[1] / A[3];
  if (temp = *A) temp++;
  return temp;
}

int two(int a) {
  int sum = *(int *)malloc(sizeof(int));
  int i;
  for (i = 0; i <= a; i++) {
    sum += i;
  }
  return sum;
}

int three(int a, int b, int c) {
  int k;
  int *ptr = (int*)malloc(sizeof(int));
  *ptr = a + c;

  if (a == 5 | b + c > 8) k = 9;

  if (b % 2) {
    // point the pointer to k
    ptr = &k;
  }

  // this will either update k or 
  // the value on the heap
  if (a > 0) *ptr = *ptr * 2;
  
  b = k + *ptr;

  free(ptr);  
  return b;
}

int four(int *A) {
  int *p = (int *)malloc(sizeof(int)*sizeof(A));
  int i, count = 0, sum = 0;
  
  for (i = 0; i < sizeof(A); i++) {
    if (A[i] < 0) {
      *(p+i) = A[i] * -1;
      count++;
    }
    else *(p+i) = A[i];
  }
 
  //printf("count is %d\n", count);
  if (count == 0) free(p);
  else {
    for (i = 0; i < sizeof(p); i++)
      sum += p[i];
  }
  
  free(p);
  return sum;
}
