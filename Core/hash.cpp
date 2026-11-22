#include <stdio.h>
#include "hash.hpp"

int calc_file_hash(const char* filename, char* outHex){
	FILE* f;
	f = fopen(filename, "rb");
	
	if(f == NULL){
		return 0;
	}
	
	unsigned long size, sum;
	size = 0;
	sum = 0;
	
	int c;
	while((c = fgetc(f)) != EOF){
		size++;
		sum = sum * 31 + c;
	}
	
	fclose(f);
	
	sprintf(outHex, "%08lx%08lx000000000000000000000000", sum, size);
	
	return 1;
}