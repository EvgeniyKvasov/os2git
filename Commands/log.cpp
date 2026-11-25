#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log.hpp"

int cmd_log(){
	FILE* fLog;
	fLog = fopen(".git\\refs\\heads\\master", "rb");
	if(fLog == NULL){
		cout << "User has not done any commits yet!" << endl;
		return 0;
	}
	
	char currentHex[48];
	if(fLog != NULL){
		fgets(currentHex, 48, fLog);
		*(currentHex + strcspn(currentHex, "\r\n")) = 0;
		fclose(fLog);
	}
	
	while (currentHex[0] != 0){
		char objPath[128];
		sprintf(objPath, ".git\\objects\\%.2s\\%s", currentHex, currentHex + 2);
		FILE* fObj;
		fObj = fopen(objPath, "rb");
		if(!fObj){
			cout << "Error reading file!" << endl;
			break;
		}
		
		cout << "commit " << currentHex << endl;
		
		char nextHex[48];
		nextHex[0] = 0;
		
		char line[512];
		
		while (fgets(line, 512, fObj)){
			*(line + strcspn(line, "\r\n")) = 0;
			if(line[0] == 0){
				break;
			}
			
			if(strncmp(line, "parent ", 7) == 0){
				strcpy(nextHex, line + 7);
			}
			
			if(strncmp(line, "date ", 5) == 0) {
				time_t rawtime = (time_t)atol(line + 5);
				struct tm *timeinfo = localtime(&rawtime);
				
				char dateBuf[64];
				strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d %H:%M:%S", timeinfo);
				cout << "Date and time:   " << dateBuf << endl;
			}
		}
		
		fclose(fObj);
		
		strcpy(currentHex, nextHex);
	}
	
	return 0;
}