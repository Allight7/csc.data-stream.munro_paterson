#include "munro_peterson.h"
#include <iostream>
#include <ctime>

const int N_MAX = 1200;
const int rank  = 1100;
const int p		= 400;

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
	int my_res, std_res;
	srand (time(nullptr));
	forn(i,n){
		a[i] = rand() % INT_MAX;
//		std::cout << a[i] << std::endl;
	}
	std::cout << "-------------" << std::endl;
	my_res = munro_peterson(a, n, p, rank);
	std::cout << my_res << std::endl;
	std::cout << "-------------" << std::endl;
	std::cout << "-------------" << std::endl;
	std::sort(a,a+n);
//	forn(i,n)
//		std::cout << a[i] << std::endl;
	std_res = a[rank];
	std::cout << std_res << std::endl;
	assert(my_res == std_res);
	return 0;
}