# SHELL COMMAND DOCUMENTATION:
1. `$ help` provides a quick reference for available commands.
3. `$ echo <(opt) args>` Echos back the provided argument(s). Will include double quote.
4. `$ joke` provides a tasteful joke.
5. `$ ls <(opt) arg>` Provides the files and directories at the provided location. Prints files and directories in current directory if no arg given.
6. `$ cd <arg>` BUILT-IN: Changes current directory to provided file location.
7. `$ pwd` BUILT-IN: Provides an exact location of the current directory.

---
# ./commands/*

Commands created as separate cpp files. Compiled into `./bin` during `make`.

pwd and cd are built-ins.

---
# Compiling and Running

* `make`
* `make install prefix=PATH_TO_INSTALL_DIRECTORY`

* Don't forget `make clean`

Authored by Connor
echo.cpp authored by Kyle
