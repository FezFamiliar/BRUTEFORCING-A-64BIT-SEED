#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <limits.h>
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
			state = (state << 1) ^ (state >> 61);
			state &= ULONG_MAX;
			state ^= ULONG_MAX;

			for(int j = 0;j < 64;j+=4){
				cur = (state >> j) & 15;
				cur = (cur >> 3) | ((cur >> 2) & 2) | ((cur << 3) & 8) | ((cur << 2) & 4);
				state ^= cur << j;
				//printf("%u\n",cur);

			}
			//exit(1);

		}

	}

	return ret;

}

void try_seed(unsigned long long i){

	unsigned long long next1 = Next(64);

	if(next1 == 16594110785577318429UL){
		unsigned long long next2 = Next(64);
		if(next2 == 5386378113087067590UL) printf("Found! Seed: %llu",i);
	}
}

int main(){
	srand(time(NULL));
	unsigned long long i;
	unsigned long long x = ((rand() % 65536UL) << 48) | ((rand() % 65536UL) << 32) | ((rand() % 65536UL) << 16) | (rand() % 65536);
	Setup(x);

	#pragma omp for
	for(i = 0;i < ULONG_MAX;i++)
		try_seed(i);


	return 0;
}
