#define INCL_DOSFILEMGR
#include <os2.h>
#include <iostream.h>
#include <stdio.h>
#include "init.hpp"

int cmd_init(){
	cout << "Init command!" << endl;
	
	DosCreateDir((PSZ)".git", NULL);
	DosCreateDir((PSZ)".git\\objects", NULL);
	DosCreateDir((PSZ)".git\\refs", NULL);
	DosCreateDir((PSZ)".git\\refs\\heads", NULL);
	
	FILE* f;
	f = fopen(".git\\HEAD", "wb");
	
	if(f != NULL){
		fprintf(f, "ref: refs/heads/master\n");
		fclose(f);
	}
	
	cout << "OS/2 repository succesfully created!" << endl;
	
	return 0;
}