#include <iostream>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <climits>
#include <vector>
#include <algorithm> 


#define forn(i, n) for (int i = 0; i < (int)(n); ++i)

inline double log2(double n){
	return log(n) / log(2);
}

inline void merge(std::vector<int> & v1, std::vector<int> &v2, int s){ //выибирает каждый второй элемент из отсортированного объединения 
	int j = 0, k = 0;
	std::vector<int> res(s);
	forn(i, s){
		k >=s || j < s && v1[j] < v2[k] ? j++ : k++;
		res[i] = k >=s || j < s && v1[j] < v2[k] ? v1[j++] : v2[k++];
	}
	v1 = res;
	return;
};

inline int munro_peterson(int* a, int an, int p, int rank){
	assert(a);
	assert(an > 0);
	assert(p > 0);
	// if(an == 1) return *a;
	float m = an;
	//int r <-;

	float c = 1.;	//const	addition								
	float space = pow(m, 1./p) * c * pow(log2(m), 2. - 2./p);		//сейчас используется десятичный логарифм!
	int s = floor(space/log2(m));
	int t = floor(log2(m/s));			//округление вверх, полный охват, придеться заполнять INT_MAX.
	int m_taken = pow(2,t)*s;
	int t_2 = pow(2,t);
	 int real_space = (t+1)*s;
	 std::cout << "m = " << m << std::endl <<
	 	 "all = "  << (pow(2,t)*s > m) << std::endl << 
	 	 "space = "  << space << std::endl << 
	 	 "real_space = "  << real_space << std::endl <<
	 	 "win = "  << (static_cast<float>(an) / real_space) << std::endl;

	int lower = INT_MIN;
	int upper = INT_MAX;
	std::vector<int> v_curr(s);
	std::vector<std::vector<int>> v_per_level(t+1);
	forn(i,t+1)
		v_per_level[i].resize(s);
	std::vector<bool> b_per_level(t+1, false);
	forn(i,p-1){
		for(int curr = 0; curr < m_taken;){
			if(curr + s < an){
				v_curr = std::vector<int> (a + curr, a + curr + s);
				sort(v_curr.begin(), v_curr.end());
				curr += s;
			}
			else if(curr < an){
				forn(j,s){
					v_curr[j] = curr < an ? a[curr] : INT_MAX;
					curr++;
				}
				sort(v_curr.begin(), v_curr.end());
			}
			else{
				v_curr = std::vector<int>(s, INT_MAX);			
				curr += s;
			}
			int level = 0;
			while(b_per_level[level]){
				merge(v_curr, v_per_level[level], s);
				b_per_level[level++] = 0;
			}
			v_per_level[level] = v_curr;
			b_per_level[level] = 1;
		}
		
		forn(i,t)
			assert(!b_per_level[i]);
		assert(b_per_level[t]);
		
		v_curr = v_per_level[t];
		forn(i,s)
			std::cout << v_curr[i] << " ";
		std::cout << std::endl;

		int l = floor(rank / t_2) - t;
		int r = ceil(rank / t_2);
		std::cout << "l: " << l << std::endl;
		std::cout << "r: " << r << std::endl;
		lower = t_2 * (l);
		upper = t_2 * (r + t);
		
		std::cout << "lower: " << lower << std::endl;
		std::cout << "upper: " << upper << std::endl;
		
		
		std::cout << "cached: " << std::endl;
		int catched = 0;
		forn(i,an)
			if(lower <= a[i] && a[i] <= upper){
				++catched;
				std::cout << a[i] << std::endl;
			}
		std::cout << "m_taken: " << m_taken << std::endl;
		std::cout << "catched: " << catched << std::endl;
	}

	return 0;
}