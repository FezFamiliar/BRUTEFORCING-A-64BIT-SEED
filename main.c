#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <limits.h>
#include <unistd.h>
unsigned long long state;
void Setup(unsigned long long seed){

	state = 0;
	unsigned int cur;
	for(int i = 0;i < 16;i++){

		cur = seed & 3;
		seed >>= 2;
 		state = (state << 4) | ((state & 3) ^ cur);
		state |= cur << 2;

	}

}


unsigned long long Next(unsigned long long bits){


	unsigned long long ret = 0;
	unsigned long long cur;
	for(int i = 0;i < bits;i++){

		ret <<= 1;
		ret |= state & 1;
		for(int k = 0;k < 3;k++){
			printf("%llu\n",state);
			state = (state << 1) ^ (state >> 61);
			state &= ULONG_MAX;
			state ^= ULONG_MAX;
			printf("%llu\n",state);
			exit(1);
			for(int j = 0;j < 64;j+=4){
				cur = (state >> j) & 15;
				cur = (cur >> 3) | ((cur >> 2) & 2) | ((cur << 3) & 8) | ((cur << 2) & 4);
				state ^= cur << j;

			}

		}
	}
	printf("%llu",ret);
	exit(1);
	return ret;

}

void try_seed(long i,clock_t t){
	Setup(i);
	unsigned long long next1 = Next(64);

	if(i % 1000000 == 0) printf("%ld\n",i);


	if(next1 == 10718270564983086108UL){
	        printf("Found! Seed: %ld\n",i);
		t = clock() - t;
		double time_elapsed = ((double)t)/CLOCKS_PER_SEC;
		printf("Time: %f",time_elapsed);
		exit(1);
	}
}

int main(){

	long i;

	Setup(10000000);
	Next(64);
	/*clock_t t;
	t = clock();
	#pragma omp parallel
	{
	#pragma omp for
	for(i = UINT_MAX;i >= 0;i--) try_seed(i,t);
	}
*/
	return 0;
}
