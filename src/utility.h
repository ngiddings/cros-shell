//
// Created by connor on 2/21/24.
//

#ifndef EOS_UTILITY_H
#define EOS_UTILITY_H

#include <string>
#include <vector>

/*
 * split up a string into a vector of strings based on the given delimiter
 */
std::vector<std::string> split_string(std::string &str,
                                      const std::string &delimiter);

/*
 * change directory
 */
int cd(const char *str);

/*
 * Prints a banner.
 */
void PRINT_BANNER();

/*
 * Clears the screen.
 */
void clear();

#endif // EOS_UTILITY_H
