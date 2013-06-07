
#include <stdio.h>
#include <stdlib.h>

int one(int *A, int *B);
int two(int a);
int three(int a, int b, int c);
int four(int *A);

void test(char *function, int expected, int actual) {
  if (expected != actual) {
    printf("Error testing function '%s': expected %d but return value was %d\n", function, expected, actual);
    exit(0);
  }
}

void run_new_tests() {

  /* WRITE YOUR TESTS HERE! */
}

void run_provided_tests() {
  int result;

  /* one */
  int A[] = { 5, 7, 4, 1 };
  int B[] = { 8, 1 };
  test("one", 6, one(A, B));

  int C[] = { 0, 4, 2, 8 };
  test("one", 0, one(C, B));


  /* two */
  test("two", 15, two(5));


  /* three */
  test("three", 21, three(5, 4, 1));
  test("three", 35, three(8, 6, 5));


  /* four */
  int M[] = {0, -1, 2, 3, 4, 5, 6, 7 };
  test("four", 28, four(M));


  printf("ALL TESTS PASSED!\n");

}

main() {

  run_provided_tests();

  run_new_tests();

}