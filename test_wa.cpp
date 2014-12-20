#include "munro_peterson.h"
#include <iostream>

const int N_MAX = 100;


int main(){
	// int p[] = {2, 3, 4, 6, 9};
	// int m[] = {10, 20, 100, 1000, 100000};
	// int pn = 5;
	// int mn = 5;
	// forn(i,mn){
	// 	forn(j,pn){
	// 		munro_peterson(&pn, m[i], p[j]);
	// 	}
	// 	std::cout << DBL_MIN << DBL_MAX << std::endl;
	// }

	int a[N_MAX];
	int n = N_MAX;
	forn(i,n){
		a[i] = rand() % 32000;
//		std::cout << a[i] << std::endl;
	}
	std::cout << "-------------" << std::endl;
	munro_peterson(a, n, 2, 50);
	std::sort(a,a+n);
//	forn(i,n)
//		std::cout << a[i] << std::endl;
	std::cout << a[49] << std::endl;
	return 0;
}