#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include "checkout.hpp"
#include "..\Core\objects.hpp"

int cmd_checkout(const char* filename){
	FILE* f;
	f = fopen(".git\\os2index", "rb");
	if(f == NULL){
		cout << "Index not found!" << endl;
		return 1;
	}
	
	char line[512];
	char lastHex[48];
	
	int found = 0;
	
	while(fgets(line, 512, f)){
		char* sp = strchr(line, ' ');
		if(!sp){
			continue;
		}
		
	*sp = 0;
	char* entryName = sp + 1;
	*(entryName + strcspn(entryName, "\r\n")) = 0;
	
	if(strcmp(entryName, filename) == 0){
		strcpy(lastHex, line);
		found = 1;
		}
	}
	
	fclose(f);
	
	if(!found){
		cout << "File not found in index!" << endl;
		return 1;
	}
	
	if(restore_file_object(lastHex, filename) == 0){
		cout << "Restored " << filename << " unsuccesfull!" << endl;
		return 1;
	}else{
		cout << "Restored " << filename << " succesfully!" << endl;
		return 0;
	}
}