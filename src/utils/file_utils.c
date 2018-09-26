#include <file_utils.h>

long read_file(const char *filename, char *buffer)
{
  FILE *file;
  long file_length;

  file = fopen(filename, "rb"); // Open the file in binary mode
  fseek(file, 0, SEEK_END);     // Jump to the end of the file
  file_length = ftell(file);    // Get the current byte offset in the file
  rewind(file);                 // Jump back to the beginning of the file

  buffer = (char *)malloc((file_length + 1) * sizeof(char)); // Enough memory for file + \0
  fread(buffer, file_length, 1, file);                       // Read in the entire file
  fclose(file);                                              // Close the file

  return file_length;
}