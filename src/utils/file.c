#include <file.h>
#include <macros.h>

long read_file(const char *file_path, char **buffer)
{
  FILE *file;
  long file_size;
  size_t bytes;

  file = fopen(file_path, "rb"); /* open the file in binary mode */
  if (!file)
  {
    fprintf(stderr, "failed to open file: %s\n", file_path);
    exit(EXIT_FAILURE);
  }
  fseek(file, 0, SEEK_END); /* jump to the end of the file */
  file_size = ftell(file);  /* get the current byte offset in the file */
  rewind(file);             /* jump back to the beginning of the file */

  *buffer = (char *)malloc((file_size + 1) * sizeof(char)); /* enough memory for file + \0 */
  bytes = fread(*buffer, file_size, 1, file);               /* read in the entire file */
  printf("%s (%ld bytes)\n", file_path, bytes * file_size);
  fclose(file); /* close the file */

  return file_size;
}