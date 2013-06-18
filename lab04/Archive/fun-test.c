
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int one(int *A, int *B, int num_A, int num_B);
int two(int a);
int three(int a, int b, int c);
int four(int *A, int num_A);

void test(char *function, int expected, int actual) {
  if (expected != actual) {
    printf("Error testing function '%s': expected %d but return value was %d\n", function, expected, actual);
    exit(0);
  }
}

void run_new_tests() {

  printf("BEGIN NEW TESTS.\n");

  int result;

  /* one */
  int *X;
  int *Y;
  test("one", -1, one(X, Y, 0, 0));

  int S[] = {1, 2, 3};
  int T[] = {4, 5, 6};
  test("one", -1, one(S, T, 3, 3));

  int S2[] = {1, 2, 3, 0};
  int T2[] = {2, 300, 4, 5};
  test("one", -1, one(S2, T2, 4, 4));

  S2[2] = 2147483647;
  S2[3] = 1;
  test("one-", -1, one(S2, T2, 4, 4));


  // test("one", 2, one(C, B, 4, 2));

  // int D[] = {1};
  // test("one", -1, one(D, B, 1, 2));

  /* two */
  // no test case here

  /* three */
  // no test case here


  /* four */
  int *N;
  test("four", -1, four(N, 0));


  printf("ALL TESTS PASSED!\n");

}

void run_provided_tests() {

  printf("BEGIN ORIGINAL TESTS.\n");

  int result;

  /* one */
  int A[] = { 5, 7, 4, 1 };
  int B[] = { 8, 1 };
  test("one", 6, one(A, B, 4, 2));

  int C[] = { 0, 4, 2, 8 };
  test("one", 0, one(C, B, 4, 2));


  /* two */
  test("two", 15, two(5));


  /* three */
  test("three", 21, three(5, 4, 1));
  test("three", 35, three(8, 6, 5));


  /* four */
  int M[] = {0, -1, 2, 3, 4, 5, 6, 7 };
  test("four", 28, four(M, 8));

  printf("ALL TESTS PASSED!\n");

}

// main() {
int main() {

  run_provided_tests();

  run_new_tests();

  return 0;

}