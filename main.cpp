#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include "Commands\add.hpp"
#include "Commands\init.hpp"
#include "Core\hash.hpp"

int main(int argc, char* argv[]){
	if(argc < 2){
		cout << "Enter your command!" << endl;
		return 0;
	}
	
	const char* cmd = argv[1];
	
	if(strcmp(cmd, "init") == 0){
		return cmd_init();
	}else if(strcmp(cmd, "hash-object") == 0){
		if(argc < 3){
			cout << "Usage: os2git hash-object <file>" << endl;
			return 1;
		}
		
	char hexBuf[48];
	if(calc_file_hash(argv[2], hexBuf) != 0){
		cout << hexBuf << endl;
		return 0;
	}else{
		cout << "Fatal: cannot open file!" << endl;
		return 1;
	}
		
	}else if(strcmp(cmd, "add") == 0){
		if(argc < 3){
			cout << "Usage: os2git add <file>" << endl;
			return 1;
		}else{
			return cmd_add(argv[2]);
		}
	}else{
		cout << "Unknown command!" << endl;
		return 1;
	}
	
	return 0;
}