#include "munro_paterson.h"
#include <iostream>
#include <vector>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

void gen( int n, vector <int> &a ) {
  a.resize(n);
  forn(i, n)
    a[i] = rand();
}

const int maxN = 1e5;
Heap<int, INT_MAX, maxN> h;

int main() {
  vector <int> x;
  int n = maxN;
  forn(t, 10) { // number of tests
    // test extractMin
    gen(n, x);
    h.build(n, x.begin());
    forn(i, n)
      h.extractMin();
    // test add
    gen(n, x);
    h.clear();
    forn(i, n)
      h.add(x[i]);
  }
  fprintf(stderr, "Test for TL: OK. Time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC);
}