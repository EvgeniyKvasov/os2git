#define INCL_DOSFILEMGR
#include <os2.h>
#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include "config.hpp"

int cmd_config(int argc, char* argv[]){
	if(argc == 3 && strcmp(argv[2], "--list") == 0){
		FILE* f;
		f = fopen(".git\\os2config", "rb");
		if(f){
			char line[512];
			while(fgets(line, 512, f)){
				cout << line << endl;
			}
			fclose(f);
		}
		
		return 0;
	}
	
	if(argc == 3){
		char val[512];
		if(get_config_value(argv[2], val) == 1){
			cout << val << endl;
			return 0;
		}else{
			cout << "Not found!" << endl;
			return 1;
		}
	}
	
	if(argc == 4){
		const char* key = argv[2];
		const char* newVal = argv[3];
		int klen = strlen(key);
		
		FILE* f = fopen(".git\\os2config", "rb");
		FILE* tmp = fopen(".git\\os2config.tmp", "wb");
		
		if(!tmp){
			if(f) fclose(f);
			return 1;
		}
		
		int updated = 0;
		char line[512];
		
		if(f){
			while(fgets(line, 512, f)){
				line[strcspn(line, "\r\n")] = 0;
				if(strncmp(line, key, klen) == 0 && line[klen] == '='){
					fprintf(tmp, "%s=%s\n", key, newVal);
					updated = 1;
				} else {
					fputs(line, tmp);
					fputc('\n', tmp);
				}
			}
			fclose(f);
		}
		
		if(updated == 0){
			fprintf(tmp, "%s=%s\n", key, newVal);
		}
		fclose(tmp);
		
		DosDelete((PSZ)".git\\os2config");
		DosMove((PSZ)".git\\os2config.tmp", (PSZ)".git\\os2config");
		
		return 0;
	}

	return 1;
}

int get_config_value(const char* key, char* valOut){
	*valOut = 0;
	
	FILE* f;
	f = fopen(".git\\os2config", "rb");
	if(!f){
		return 0;
	}
	
	char line[512];
	int klen = strlen(key);
	
	while(fgets(line, 512, f)){
		line[strcspn(line, "\r\n")] = 0;
		
		if(strncmp(line, key, klen) == 0 && line[klen] == '='){
			strcpy(valOut, line + klen + 1);
			fclose(f);
			return 1;
		}
	}
	
	fclose(f);
	
	return 0;
}