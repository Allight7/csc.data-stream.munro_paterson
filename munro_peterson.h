#include <iostream>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <climits>
#include <vector>
#include <algorithm> 


#define forn(i, n) for (int i = 0; i < (int)(n); ++i)

inline void merge(std::vector<int> & v1, std::vector<int> &v2, int s){ //выибирает каждый второй элемент из отсортированного объединения 
	int j = 0, k = 0;													//работает на месте, изменяя содержимое первого вектора
	forn(i, s){
		v1[j] < v2[k] && j < s ? j++ : k++;
		v1[i] = v1[j] < v2[k] && j < s ? v1[j++] : v2[k++];
	}
	return;
};

int munro_peterson(int* a, int an, int p){
	assert(a);
	assert(an > 0);
	assert(p > 0);
	// if(an == 1) return *a;
	float m = an;
	//int r <-;

	float c = 1.;	//const	addition								
	float space = pow(m, 1./p) * c * pow(log2(m), 2. - 2./p);
	int s = floor(space/log2(m));
	int t = ceil(log2(m/s));			//округление вверх, чтобы попали все значения со входа.
	// int real_space = (t+1)*s;
	// std::cout << "m = " << m << (m<1000? '\t' : ' ') <<
	// 	 "\t all = "  << (pow(2,t)*s > m) << 
	// 	 "\t space = "  << space << 
	// 	 "\t real_space = "  << real_space <<
	// 	 "\t win = "  << (((float)an) / real_space) << 
	// 	 std::endl;

	float lower = FLT_MIN;
	float upper = FLT_MAX;
	std::vector<int> v_curr(s);
	std::vector<std::vector<int>> v_per_level(t+1);
	forn(i,t+1)
		v_per_level[i].resize(s);
	std::vector<bool> b_per_level(t+1, false);
	forn(i,p-1){
		forn(curr,an){
			forn(j,s)
				v_curr[curr] = curr < an ? a[curr++] : INT_MAX;			//предполагается, что значения INT_MAX не будут содержаться в a[]
			std::sort(v_curr.begin(), v_curr.end());
			int level = 0;
			while(b_per_level[level]){
				merge(v_curr, v_per_level[level], s);
				b_per_level[level++] = 0;
			}
			v_per_level[level] = v_curr;
			b_per_level[level] = 1;
		}
		int level = 0;
		while(!b_per_level[level]) 
			++level;
		v_curr = v_per_level[level];
		b_per_level[level++] = 0;
		for(; level<t+1; ++level){
			if(b_per_level[level]){
				merge(v_curr, v_per_level[level], s);
				b_per_level[level] = 0;
			}else{
				v_curr = v_per_level[level];
				b_per_level[level] = 0;
				forn(j,s){
					v_curr[j] = 2*j+1 < s ? v_curr[2*j+1] : INT_MAX;
				}

			}
		}
	}

	return 0;
}