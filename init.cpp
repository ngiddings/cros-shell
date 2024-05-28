#include <stdio.h>
#include <sys/syscall.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

char **envp_global;
int pipefd_stdout[2];
int pipefd_stdin[2];

void shellThread(void *ptr)
{
  fddup(pipefd_stdout[1], 1);
  fddup(pipefd_stdin[0], 0);
  char *args[] = {"/bin/shell", NULL};
  // exec("/bin/shell", args, envp);
  execve("shell", args, envp_global);
  terminate();
}

int main(int argc, char **argv, char **envp)
{
  const int stackSize = 1024;
  printf("%s: Starting shell\n", argv[0]);
  void *stack = malloc(stackSize);
  envp_global = envp;

  printf("%s: Creating pipes\n", argv[0]);
  create_pipe(pipefd_stdout);
  create_pipe(pipefd_stdin);

  printf("%s: Spawning new thread\n", argv[0]);
  clone(shellThread, stack + stackSize, nullptr, 0);

  printf("%s: Entering I/O loop\n", argv[0]);
  char line[1024];
  char buffer[1024];
  int pos = 0;
  while (true)
  {
    // printf("init: I/O loop\n");
    int status = read(0, &buffer[pos], 1);
    // printf("init: Read status: %d\n", status);
    while (status > 0)
    {
      char str[2];
      str[0] = buffer[pos];
      str[1] = '\0';
      printf("%s", str);
      if (str[0] == '\r')
      {
        printf("\n");
      }

      pos += status;
      if (buffer[pos - 1] == '\r')
      {
        buffer[pos - 1] = '\n';
        buffer[pos] = '\0';
        fprintf(&pipefd_stdin[1], "%s", buffer);
        pos = 0;
      }
      else if (pos == 1023)
      {
        buffer[pos] = '\0';
        fprintf(&pipefd_stdin[1], "%s", buffer);
        pos = 0;
      }

      status = read(0, &buffer[pos], 1);
    }

    if (status < 0)
    {
      printf("init: Error reading from UART.\n");
    }

    status = read(pipefd_stdout[0], line, 1023);
    // printf("init: Read2 status: %d\n", status);
    if (status > 0)
    {
      line[status] = '\0';
      printf("%s", line);
    }

    yield();
    // printk("hi");
  }
}
