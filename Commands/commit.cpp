#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "commit.hpp"
#include "..\Core\hash.hpp"
#include "..\Core\objects.hpp"

int cmd_commit(const char* message){
	FILE* fIdx;
	fIdx = fopen(".git\\os2index", "rb");
	if(!fIdx){
		cout << "Nothing to commit!" << endl;
		return 1;
	}
	
	char parentHex[48];
	parentHex[0] = 0;
	
	FILE* fParent;
	fParent = fopen(".git\\refs\\heads\\master", "rb");
	if(fParent != NULL){
		fgets(parentHex, 48, fParent);
		*(parentHex + strcspn(parentHex, "\r\n")) = 0;
		fclose(fParent);
	}
	
	FILE* fTmp;
	fTmp = fopen(".git\\commit_tmp", "wb");
	if(!fTmp){
		fclose(fIdx);
		return 1;
	}
	
	if(parentHex[0] != 0){
		fprintf(fTmp, "parent %s\n", parentHex);
	}
	
	fprintf(fTmp, "date %ld\n", (long)time(NULL));
	fprintf(fTmp, "message %s\n\n", message);
	
	char line[512];
	while(fgets(line, 512, fIdx)){
		fputs(line, fTmp);
	}
	
	fclose(fIdx);
	fclose(fTmp);
	
	char commitHex[48];
	calc_file_hash(".git\\commit_tmp", commitHex);
	save_file_object(".git\\commit_tmp", commitHex);
	remove(".git\\commit_tmp");
	
	FILE* fMaster;
	fMaster = fopen(".git\\refs\\heads\\master", "wb");
	if(fMaster){
		fprintf(fMaster, "%s\n", commitHex);
		fclose(fMaster);
	}
	
	cout << "master " << commitHex << " - " << message << endl;
	
	return 0;
}