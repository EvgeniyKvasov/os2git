#define INCL_DOSFILEMGR
#include <os2.h> 
#include <stdio.h> 
#include <string.h> 
#include "objects.hpp"

int save_file_object(const char* filename, const char* hexHash){
	char dirPath[128];
	sprintf(dirPath, ".git\\objects\\%.2s", hexHash);
	
	DosCreateDir((PSZ)dirPath, NULL);
	
	char objPath[128];
	sprintf(objPath, ".git\\objects\\%.2s\\%s", hexHash, hexHash + 2);
	
	FILE *src, *dst;
	src = fopen(filename, "rb");
	dst = fopen(objPath, "wb");
	
	if(!src || !dst){
		if(src){
			fclose(src);
		}
		
		if(dst){
			fclose(dst);
		}
		return 0;
	}
	
	int c;
	while((c = fgetc(src)) != EOF){
		fputc(c, dst);
	}
	
	fclose(src);
	fclose(dst);
	
	return 1;
}

int restore_file_object(const char* hexHash, const char* outFilename){
	char objPath[128];
	sprintf(objPath, ".git\\objects\\%.2s\\%s", hexHash, hexHash + 2);
	
	FILE *src, *dst;
	src = fopen(objPath, "rb");
	dst = fopen(outFilename, "wb");
	
	if(!src || !dst){
		if(src){
			fclose(src);
		}
		
		if(dst){
			fclose(dst);
		}
		return 0;
	}
	
	int c;
	while((c = fgetc(src)) != EOF){
		fputc(c, dst);
	}
	
	fclose(src);
	fclose(dst);
	
	return 1;
}