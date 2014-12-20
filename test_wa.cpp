#include "munro_peterson.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>

const int MAX_SIZE = 10000;
int a[MAX_SIZE];
int b[MAX_SIZE];

int main(){
	int n[] = {1, 3, 10, MAX_SIZE}; //запуск на различных объемах данных
	int nn = 4;
	int p[] = {1, 2, 4, 6, 20};		//запуск c различным числом проходов
	int pn = 5;
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> distribution(0,INT_MAX-1);

	forn(q,100){
		forn(i,nn){
			forn(j,n[i]){
				a[j] = distribution(generator);
				b[j] = a[j];
			}
			std::sort(b,b+n[i]);		
			int ass = 12;
			forn(k,pn){
				int rank = 0;					//запуск c различным числом проходов
				assert(b[rank] == munro_peterson(a, n[i], p[k], rank));
			
				rank = rand() % n[i];
				assert(b[rank] == munro_peterson(a, n[i], p[k], rank));
			
				rank = n[i] - 1;
				assert(b[rank] == munro_peterson(a, n[i], p[k], rank));
			}		
		}
	}
	std::cout << "Test WA: OK" << std::endl;

	return 0;
}