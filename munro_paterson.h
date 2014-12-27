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

//выибирает каждый второй элемент из отсортированного объединения двух векторов

inline void merge(std::vector<int> & v1, std::vector<int> &v2, int s){ 
	int j = 0, k = 0;
	std::vector<int> res(s);
	forn(i, s){
		k >=s || (j < s && v1[j] < v2[k]) ? j++ : k++;
		res[i] = k >=s || (j < s && v1[j] < v2[k]) ? v1[j++] : v2[k++];
	}
	v1 = res;
	return;
};

/*
	int* a - исходная последовательсть 
	int an - длина последовательности 
	int p - число проходов по полседовательности
	int rank - ранг искомого элемента в исходной последовательсти
	
	return - искомый элемент с рангом rank
*/

inline int munro_paterson(int* a, int an, int p, int rank){
	assert(a && an > 0);						//непустая последовательность
	assert(p > 0);								//ненулевое кол-во проходов
	assert(rank >= 0 && rank < an);				//валидное значение ранга
	if(an == 1) return *a;
	
	
	float m = an;
	float c = 2.;	//const	addition								
	int lower = INT_MIN;
	int upper = INT_MAX;
	

	float first_predicted_space = pow(m, 1./p) * c * pow(log2(m), 2. - 2./p);	//оценка максимума памяти для алгоритма в 1/sizeof(int).

	forn(i,p-1){																
		if(m <= first_predicted_space) break;									
		float space = pow(m, 1./(p-i)) * c * pow(log2(m), 2. - 2./(p-i));		
		int s = floor(space/log2(m));											//округление вверх. охват всей последовательности,	
		int t = ceil(log2(m/s));												//требуется заполнение фиктивн. элем.
		int m_taken = pow(2,t)*s;												//разм. расшир. послед.
		int t_2 = pow(2,t);
		int rank_offset = 0;
		if(i == 0){
			int real_space = (t+1)*s;
			std::cout << "p = " << p << ";\treal_space = " << real_space;
		}
		std::vector<int> v_curr(s);												//текущий сэмпл
		std::vector<bool> b_per_level(t+1, false);								//наличие сохраненных сэмплов для конкр. уровня.
		std::vector<std::vector<int>> v_per_level(t+1);							//контейнер с сэмплами разных уровней, ожидающих слияния
		forn(i,t+1)
			v_per_level[i].resize(s);											

		for(int curr = 0, taken = 0; taken < m_taken;){							/*=================================================*/
			if(curr < an){														
				forn(j,s){
					while(curr < an && (a[curr] < lower || a[curr] > upper)){
						if(a[curr] < lower) ++rank_offset;
						++curr;
					}
					v_curr[j] = curr < an ? a[curr++] : INT_MAX;
				}
				taken += s;
				sort(v_curr.begin(), v_curr.end());												/*	Сэмплирование	*/
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
		}																		/*=================================================*/

		forn(i,t)																	//проверка корректности сэмплирования:
			assert(!b_per_level[i]);												//все уровни, кроме последнего должны быть пусты
		assert(b_per_level[t]);
		
		v_curr = v_per_level[t];

		int l = floor(static_cast<float>(rank - rank_offset) / (t_2)) - t;			//расчет индексов новых границ внутри t-сэмпла
		int u = ceil(static_cast<float>(rank - rank_offset) / (t_2));

		if(l >= 0 && l < s && v_curr[l] < upper && v_curr[l] > lower) lower = v_curr[l];	//обновление границ с проверкой корректности
		if(u >= 0 && u < s && v_curr[u] > lower && v_curr[u] < upper) upper = v_curr[u];		

		int lbound = t_2 * (l);
		int ubound = t_2 * (u + t);													//обновление максимально возможного числа элементов
		m = ubound - lbound > 0 ? ubound - lbound : 1;								//для следующего прохода
	}
																				/*================================================*/
																							/*	Последний проход	*/
	assert(first_predicted_space >= m);												//проверка ограничения используемой памяти
	std::cout << "\t\tm = " << m << "\t\tpred_space = " << static_cast<int>(first_predicted_space) << std::endl;


	int rank_offset = 0;
	std::vector<int> res;
	for(int curr = 0; curr < an;){
		while(curr < an && (a[curr] < lower || a[curr] > upper)){					//отсев элементов; увеличение оффсэта ранга, 
			if(a[curr] < lower) ++rank_offset;										//если эл-т не проходит по левой границе
			++curr;
		}
		if(curr >= an)
			break;
		res.push_back(a[curr++]);
	}

	sort(res.begin(), res.end());

	assert(rank - rank_offset >= 0);												//проверка корректрости рассчета оффсета ранга
	return res[rank-rank_offset];
}