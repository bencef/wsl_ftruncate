#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct file {
  char *name;
  int  fd;
};

int create_file(size_t);

int create_file(size_t size)
{
  char template[] = "/tmp/wsl_ftruncate.XXXXXX";
  char *filename;
  int fd;
  int error;
  char *content;
  ssize_t written;

  filename = mktemp(template);
  fd = open(filename, O_WRONLY|O_CREAT, 0644);
  if(fd == -1) {
    error = errno;
    fprintf(stderr, "Couldn't create %s with size %d: %s\n",
            filename,
            size,
            strerror(error));
    return fd;
  }
  printf("File created: %s\n", filename);
  if(size > 0) {
    content = malloc(size);
    content = memset(content, 'A', size);
    written = write(fd, content, size);
    if(written == -1) {
      error = errno;
      fprintf(stderr, "Couldn't write into %s: %s\n",
              filename,
              strerror(error));
    }
  }
  unlink(filename); // will delete after close
  return fd;
}

int main(int argc, char *argv[])
{
  struct file files[] = {
    {"Content file", create_file(256)},
    {"Empty file",   create_file(0)}
  };
  return 0;
}
