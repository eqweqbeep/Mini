Minishell
A simple Unix shell implementation written in C that mimics the behavior of bash with essential features and built-in commands.
Features
Core Functionality

Command Execution: Execute system commands with arguments
Built-in Commands: Implementation of essential shell built-ins
Input/Output Redirection: Support for <, >, and >> operators
Pipes: Command chaining with | operator
Environment Variables: Variable expansion and manipulation
Signal Handling: Proper handling of Ctrl+C, Ctrl+D, and Ctrl+\
Command History: Navigation through previous commands
Quote Handling: Support for single and double quotes

Built-in Commands

echo - Display text with -n option support
cd - Change directory with relative and absolute paths
pwd - Print working directory
export - Set environment variables
unset - Remove environment variables
env - Display environment variables
exit - Exit the shell with optional exit code

Advanced Features

Wildcards: Basic glob pattern matching (*)
Logical Operators: Support for && and ||
Subshells: Command grouping with parentheses
Here Documents: << operator implementation
Job Control: Background process handling with &

Installation
Prerequisites

GCC compiler
GNU Make
GNU Readline library

Building
bash git clone https://github.com/crouns1/minishell.git
cd minishell
make
Running
bash./minishell
Usage
Basic Commands
bashminishell$ ls -la
minishell$ echo "Hello World"
minishell$ pwd
minishell$ cd /path/to/directory
Redirection
bashminishell$ echo "Hello" > output.txt
minishell$ cat < input.txt
minishell$ ls >> log.txt
Pipes
bashminishell$ ls -la | grep ".c"
minishell$ cat file.txt | wc -l
minishell$ ps aux | grep minishell
Environment Variables
bashminishell$ export MY_VAR="Hello World"
minishell$ echo $MY_VAR
minishell$ unset MY_VAR
Quote Handling
bashminishell$ echo 'Single quotes preserve everything literally'
minishell$ echo "Double quotes allow $variable expansion"
minish
