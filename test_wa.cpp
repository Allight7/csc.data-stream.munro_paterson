#include "munro_paterson.h"
#include <iostream>
#include <ctime>

const int MAX_SIZE = 10000;
int a[MAX_SIZE];
int b[MAX_SIZE];

int main(){
	int n[] = {1, 3, 10, MAX_SIZE}; //запуск на различных объемах данных
	int nn = 4;
	int p[] = {1, 2, 4, 6, 20};		//запуск c различным числом проходов
	int pn = 5;
	
	srand(time(nullptr));
	
	forn(q,100){
		forn(i,nn){
			forn(j,n[i]){
				a[j] = rand() % INT_MAX;
				b[j] = a[j];
			}
			std::sort(b,b+n[i]);		
			forn(k,pn){
				int rank = 0;					//запуск c различным числом проходов
				assert(b[rank] == munro_paterson(a, n[i], p[k], rank));
			
				rank = rand() % n[i];
				assert(b[rank] == munro_paterson(a, n[i], p[k], rank));
			
				rank = n[i] - 1;
				assert(b[rank] == munro_paterson(a, n[i], p[k], rank));
			}		
		}
	}
	std::cout << "Test WA: OK" << std::endl;

	return 0;
}