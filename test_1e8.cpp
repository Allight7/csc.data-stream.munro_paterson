#include "munro_paterson.h"
#include <iostream>
#include <ctime>

const int MAX_SIZE = static_cast<int>(1e8);
int a[MAX_SIZE];
int b[MAX_SIZE];

int main(){
	int n[] = {MAX_SIZE}; //запуск на различных объемах данных
	int nn = 1;
	int p[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};		//запуск c различным числом проходов
	int pn = 19;
	
	srand(time(nullptr));
	

	forn(i,nn){
		forn(j,n[i]){
			a[j] = rand() % INT_MAX;
			b[j] = a[j];
		}
		std::sort(b,b+n[i]);		
		forn(k,pn){
			int rank = n[i]/2;					//запуск c различным числом проходов
			assert(b[rank] == munro_paterson(a, n[i], p[k], rank));
		}		
	}
	std::cout << "Test 1e8 for graph: end" << std::endl;

	return 0;
}