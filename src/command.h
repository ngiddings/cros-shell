#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <vector>

/**
 * The entire line parsed is a "Command"
 * Each process with arguments included are an "Instruction"
 * The Command class stores each instruction as a vector and will pipe between
 * each instruction in the vector.
 */
class Command
{
public:
  /**
   * Parse each input by the pipe deliminator.
   * Setup the command with each parsed input.
   * @return 0 if successful
   * @return not 0 otherwise
   */
  int parse(std::string command);

  /**
   * Fork and exec the command.
   * Pipe to the next command if applicable.
   */
  int run();

private:
  std::vector<std::vector<std::string>> instructions;

  /**
   * Loops through every parsed input in a vector
   * Separates each segment o f a command by spaces
   * Embeds each segment of a command as an "instruction"
   * Each "instruction" is added to a vector called "instructions"
   * @param parsed_input a vector of commands separated by a vertical pipe "|"
   */
  int setup_command(std::vector<std::string> &instructions);

  /**
   * Executes the command
   * @param curr_command
   * @return
   */
  int exec_instruction(std::vector<std::string> &instruction);
};

#endif // !_COMMAND_H_
