int check(int a[], int size) {
  int i;
  for(i=1; i<size; i++) {
    if (!(a[i-1] <= a[i])) {
      return 0;
    }
  }
  return 1;
}