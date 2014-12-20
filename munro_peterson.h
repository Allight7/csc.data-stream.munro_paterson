#include <iostream>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <climits>
#include <vector>
#include <algorithm> 
#include <exception> 

#define forn(i, n) for (int i = 0; i < (int)(n); ++i)

inline double log2(double n){
	return log(n) / log(2);
}

inline void merge(std::vector<int> & v1, std::vector<int> &v2, int s){ //выибирает каждый второй элемент из отсортированного объединения 
	int j = 0, k = 0;
	std::vector<int> res(s);
	forn(i, s){
		k >=s || (j < s && v1[j] < v2[k]) ? j++ : k++;
		res[i] = k >=s || (j < s && v1[j] < v2[k]) ? v1[j++] : v2[k++];
	}
	v1 = res;
	return;
};

inline int munro_peterson(int* a, int an, int p, int rank){
	assert(a);
	assert(an > 0);
	assert(p > 0);
	assert(rank >= 0 && rank < an);
	if(an == 1) return *a;
	
	
	float m = an;
	float c = 2.;	//const	addition								
	int lower = INT_MIN;
	int upper = INT_MAX;
	

	float first_predicted_space = pow(m, 1./p) * c * pow(log2(m), 2. - 2./p);

	forn(i,p-1){
		if(m <= first_predicted_space) break;
		float space = pow(m, 1./(p-i)) * c * pow(log2(m), 2. - 2./(p-i));
		int s = floor(space/log2(m));
		int t = ceil(log2(m/s));			//округление вверх, полный охват, придется заполнять INT_MAX.
		int m_taken = pow(2,t)*s;
		int t_2 = pow(2,t);
		int rank_offset = 0;
//		int real_space = (t+1)*s;
//		std::cout << "m = " << m << std::endl <<
//	 		"all = "  << (pow(2,t)*s > m) << std::endl << 
//	 		"t = "  << t << std::endl << 
//	 		"space = "  << space << std::endl << 
//	 		"real_space = "  << real_space << std::endl <<
//	 		"win = "  << (static_cast<float>(an) / real_space) << std::endl;
		std::vector<std::vector<int>> v_per_level(t+1);
		std::vector<int> v_curr(s);
		forn(i,t+1)
			v_per_level[i].resize(s);
		std::vector<bool> b_per_level(t+1, false);

		for(int curr = 0, taken = 0; taken < m_taken;){
			if(curr < an){
				forn(j,s){
					while(curr < an && (a[curr] < lower || a[curr] > upper)){
						if(a[curr] < lower) ++rank_offset;
						++curr;
					}
					v_curr[j] = curr < an ? a[curr++] : INT_MAX;
				}
				taken += s;
				sort(v_curr.begin(), v_curr.end());
			}
			else{
				v_curr = std::vector<int>(s, INT_MAX);			
				taken += s;
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

		int l = floor(static_cast<float>(rank - rank_offset) / (t_2)) - t;
		int u = ceil(static_cast<float>(rank - rank_offset) / (t_2));
//		std::cout << "l: " << l << std::endl;
//		std::cout << "r: " << r << std::endl;


		if(l >= 0 && l < s && v_curr[l] < upper && v_curr[l] > lower) lower = v_curr[l];
//		else if(l >= 0 && l < s && v_curr[l] < upper) 
//			std::cout << "here was the bug";
		if(u >= 0 && u < s && v_curr[u] > lower && v_curr[u] < upper) upper = v_curr[u];		
//		else if(u >= 0 && u < s && v_curr[u] > lower)
//			std::cout << "here was the bug";
//		std::cout << "lower: " << lower << std::endl;
//		std::cout << "upper: " << upper << std::endl;
		int lbound = t_2 * (l);
		int ubound = t_2 * (u + t);
		m = ubound - lbound > 0 ? ubound - lbound : 1;
//		std::cout << "lbound: " << lbound << std::endl;
//		std::cout << "ubound: " << ubound << std::endl;
//		std::cout << "new m: " << m << std::endl;

	}
//	std::cout << "rank: " << rank <<std::endl;
	assert(first_predicted_space >= m);

	int rank_offset = 0;
	std::vector<int> res;
	for(int curr = 0; curr < an;){
		while(curr < an && (a[curr] < lower || a[curr] > upper)){
			if(a[curr] < lower) ++rank_offset;
			++curr;
		}
		if(curr >= an)
			break;
		res.push_back(a[curr++]);
	}

	sort(res.begin(), res.end());
//	std::cout << "sort complete" <<std::endl;
//	std::cout << "rank: " << rank <<std::endl;
//	std::cout << "res.size(): " << res.size() <<std::endl <<std::endl;
	assert(rank - rank_offset > 0);
	int result = res[rank-rank_offset];
//	std::cout << "get complete" <<std::endl;
	return result;
}