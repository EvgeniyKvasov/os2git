#include <iostream.h>
#include <stdio.h>
#include "add.hpp"
#include "..\Core\hash.hpp"
#include "..\Core\objects.hpp"

int cmd_add(const char* filename){
	char hexBuf[48];
	if(calc_file_hash(filename, hexBuf) == 0){
		cout << "File not found!" << endl;
		return 1;
	}
	
	if(save_file_object(filename, hexBuf) == 0){
		cout << "Error: " << filename << " folder does not exist!" << endl;
		return 1;
	}
	
	FILE* f;
	f = fopen(".git\\os2index", "ab");
	if(f == NULL){
		cout << "Folder .git not found!" << endl;
		return 1;
	}
	
	fprintf(f, "%s %s\n", hexBuf, filename);
	fclose(f);
	
	cout << "File " << filename << " succesfully added!" << endl;
	
	return 0;
}