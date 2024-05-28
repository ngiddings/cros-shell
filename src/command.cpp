#include "command.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utility.h"
#include <sys/syscall.h>

void spawn_command(char **args)
{
  execvp(args[0], args);
  terminate();
}

int Command::parse(std::string input)
{
  // if input has \n appended to the end, remove it
  if (input[input.size() - 1] == '\n')
  {
    input = input.substr(0, input.size() - 1);
  }

  std::string pipe_delim = "|";
  std::vector<std::string> parsed_input = split_string(input, pipe_delim);

  if (Command::setup_command(parsed_input) < 0)
  {
    return -1;
  }

  return 0;
}

int Command::run()
{
  int i, j, pid;
  int num_instructions = instructions.size();

  // If there is no pipe, just fork and execute the first command
  if (num_instructions == 1)
  {

    // Check for built-in commands
    if (instructions[0][0] == "cd")
    {
      if (instructions[0].size() > 1)
      {
        return cd(instructions[0][1].c_str());
      }
      return cd("/");
    }
    else if (instructions[0][0] == "clear")
    {
      clear();
      return 0;
    }

    // No built-ins, execute elsewhere
    exec_instruction(instructions[0]);
    wait(NULL);
    return 0;
  }
  //////////////////////////////////

  // Piping logic:
  // Initialize file descriptors for some piping
  int fd[num_instructions][2];

  // Init the pipes
  int result = -1;
  for (i = 0; i < num_instructions; i++)
  {
    pipe(fd[i]);
  }

  // Fork every instruction
  for (i = 0; i < num_instructions; i++)
  {
    pid = fork();

    if (pid == 0)
    {

      // If this is not the first instruction
      if (i > 0)
      {

        if (fd[i - 1][0] != 0)
        {
          dup2(fd[i - 1][0], 0);
        }
      }

      // If this is not the last instruction
      if (i < num_instructions - 1)
      {
        if (fd[i][1] != 1)
        {
          dup2(fd[i][1], 1);
        }
      }

      // Close all descriptors
      for (j = 0; j < num_instructions; j++)
      {
        close(fd[j][0]);
        close(fd[j][1]);
      }

      // Execute instruction
      exec_instruction(instructions[i]);
    }
  }

  // Close parent file descriptors
  for (i = 0; i < num_instructions; i++)
  {
    close(fd[i][0]);
    close(fd[i][1]);
  }

  // Wait for all processes to finish
  for (int i = 0; i < num_instructions; i++)
  {
    wait(NULL);
  }

  return 0;
}

int Command::setup_command(std::vector<std::string> &parsed_input)
{
  std::string space_delim = " ";
  while (!parsed_input.empty())
  {
    std::string input = parsed_input.front();
    std::vector<std::string> instruction = split_string(input, space_delim);
    // terminate setup if input error
    if (instruction.empty())
    {
      return -1;
    }

    instructions.push_back(instruction);
    parsed_input.remove(0);
  }

  return 0;
}

int Command::exec_instruction(std::vector<std::string> &instruction)
{
  int num_args = instruction.size();
  char **arg = new char *[num_args + 1];
  for (size_t i = 0; i < num_args; i++)
  {
    arg[i] = new char[instruction[i].size() + 1];
    strcpy(arg[i], instruction[i].c_str());
  }
  arg[num_args] = nullptr;
  void *stack = malloc(1024);
  clone(spawn_command, stack + 1024, (void *)arg, 0);
  return 0;
}
