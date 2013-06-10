#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// int one(int *A, int *B){
int one(int *A, int *B, int num_A, int num_B) {

  /* check if A or B is null */
  if (A == NULL | B == NULL)
    return -1;

  /* check if size of A, size of B */
  if (num_A < 4 | num_B < 2)
    return -1;

  /* check if A[3] is zero */
  if (A[3] == 0)
    return -1;

  int temp;
  long int long_temp;
  // temp = A[2] +  B[1] / A[3];
  long_temp = (long int) A[2] +  (long int) B[1] / A[3];  // check add overflow
  if (long_temp >= INT_MAX || long_temp <= INT_MIN)
    return -1;
  else
    temp = long_temp;

  // if (temp = *A) temp++;
  temp = *A;
  if (temp) temp++;
  return temp;
}

int two(int a) {
  // int sum = *(int *)malloc(sizeof(int));
  // avoid memory leak
  int sum = 0;
  int i;
  for (i = 0; i <= a; i++) {
    // sum += i;
    sum += i;
  }
  // return sum;
  return sum;
}

int three(int a, int b, int c) {
  // int k;
  int k = 0;
  int *ptr = (int*)malloc(sizeof(int));
  *ptr = a + c;

  if (a == 5 | b + c > 8) k = 9;

  if (b % 2) {
    // point the pointer to k
    // ptr = &k;
    *ptr = k;
  }

  // this will either update k or 
  // the value on the heap
  if (a > 0) *ptr = *ptr * 2;
  
  b = k + *ptr;

  free(ptr);  
  return b;
}

// int four(int *A) {
int four(int *A, int num_A) {

  if (A == NULL)
    return -1;
  if (num_A == 0)
    return -1;

  // int *p = (int *)malloc(sizeof(int)*sizeof(A));
  int *p = (int *)malloc(sizeof(int)*num_A);
  int i, count = 0, sum = 0;
  
  for (i = 0; i < num_A; i++) {
    if (A[i] < 0) {
      *(p+i) = A[i] * -1;
      count++;
    }
    else *(p+i) = A[i];
  }
 
  //printf("count is %d\n", count);
  // if (count == 0) free(p);
  // else {
  if (count != 0) {
    for (i = 0; i < sizeof(p); i++)
      sum += p[i];
  }
  
  free(p);
  return sum;
}
