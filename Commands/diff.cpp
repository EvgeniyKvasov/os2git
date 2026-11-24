#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include "diff.hpp"

int cmd_diff(const char* filename){
	FILE* f;
	f = fopen(".git\\os2index", "rb");
	if(f == NULL){
		cout << "Hash in index not found!" << endl;
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
	
	char objPath[128];
	sprintf(objPath, ".git\\objects\\%.2s\\%s", lastHex, lastHex + 2);
	
	FILE *fOld, *fNew;
	fOld = fopen(objPath, "rb");
	fNew = fopen(filename, "rb");
	
	if(!fOld || !fNew){
		if(fOld){
			fclose(fOld);
		}
		
		if(fNew){
			fclose(fNew);
		}
		cout << "Cannot open file for diff!" << endl;
		return 1;
	}
	
	char lineOld[512];
	char lineNew[512];
	
	char* rOld;
	char* rNew;
	
	while(1){
		rOld = fgets(lineOld, 512, fOld);
		rNew = fgets(lineNew, 512, fNew);
		
		if(!rOld && !rNew){
			break;
		}
		
		if(rOld){
			*(lineOld + strcspn(lineOld, "\r\n")) = 0;
		}
		
		if(rNew){
			*(lineNew + strcspn(lineNew, "\r\n")) = 0;
		}
		
		if(rOld && !rNew){
			cout << "- " << lineOld << endl;
		}else if(!rOld && rNew){
			cout << "+ " << lineNew << endl;
		}else if(strcmp(lineOld, lineNew) != 0){
			cout << "- " << lineOld << endl;
			cout << "+ " << lineNew << endl;
		}
	}
	
	fclose(fOld); 
	fclose(fNew);
	
	return 0;
}