#include <iostream.h>
#include <string.h>
#include "Commands\init.hpp"

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "Enter your command!" << endl;
		return 0;
	}
	
	const char* cmd = argv[1];
	
	if (strcmp(cmd, "init") == 0){
		return cmd_init();
	} else {
		cout << "Unknown command!" << endl;
		return 1;
	}
	
	return 0;
}