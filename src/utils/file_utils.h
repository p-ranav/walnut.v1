#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>
#include <stdlib.h>

// opens the file pointed to by filename
// reads the entire file into buffer
// returns file size
long read_file(const char *filename, char *buffer);

#endif