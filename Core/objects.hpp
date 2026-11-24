#ifndef CORE_OBJECTS_HPP
#define CORE_OBJECTS_HPP

int save_file_object(const char* filename, const char* hexHash);
int restore_file_object(const char* hexHash, const char* outFilename);

#endif