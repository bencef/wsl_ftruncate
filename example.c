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
  char *filename = mktemp("/tmp/wsl_ftruncate.XXXXXX");
  int fd = open(filename, O_WRONLY|O_CREAT, 0644);
  if(fd == -1) {
    int error = errno;
    fprintf(stderr, "Couldn't create %s with size %d: %s\n",
            filename,
            size,
            strerror(error));
  }
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
