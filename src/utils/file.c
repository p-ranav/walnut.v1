#include <file.h>
#include <macros.h>

long read_file(const char *file_path, char **buffer)
{
  FILE *file;
  long file_size;

  file = fopen(file_path, "rb"); // Open the file in binary mode
  fseek(file, 0, SEEK_END);      // Jump to the end of the file
  file_size = ftell(file);       // Get the current byte offset in the file
  rewind(file);                  // Jump back to the beginning of the file

  *buffer = (char *)malloc((file_size + 1) * sizeof(char)); // Enough memory for file + \0
  size_t bytes = fread(*buffer, file_size, 1, file);        // Read in the entire file
  fclose(file);                                             // Close the file

  return file_size;
}