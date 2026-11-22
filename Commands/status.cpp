#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include "status.hpp"
#include "..\Core\hash.hpp"

int cmd_status(){
	FILE* f;
	f = fopen(".git\\os2index", "rb");
	if(f == NULL){
		cout << "File not found!" << endl;
		return 0;
	}
	
	char line[512];
	char currentHex[512];
	
	while(fgets(line, 512, f)){
		char* sp = strchr(line, ' ');
		if(!sp){
			continue;
		}
		
		*sp = 0;
		char* filename = sp + 1;
		*(filename + strcspn(filename, "\r\n")) = 0;
		
		if(calc_file_hash(filename, currentHex) == 0){
			cout << "File " << filename << " has deleted!" << endl;
		} else if(strcmp(line, currentHex) != 0){
			cout << "File " << filename << " has modified by user!" << endl;
		}else{
			cout << "File " << filename << " has staged!" << endl;
		}
	}
	
	fclose(f);
	
	return 0;
}