# Minishell
Minishell is a simple shell implementation with basic functionalities.

## Features**Prompt and Command Execution**
- Display a prompt when waiting for a new command - :white_check_mark:
- Have a working history - :white_check_mark:
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path) - :x:

**Signal Handling**
- Avoid using more than one global variable to indicate a received signal - :white_check_mark:

**Quote Handling**
- Handle ' (single quote) - :x:
- Handle " (double quote) - :x:

**Redirections**
- Implement '<' to redirect input - :x:
- Implement '>' to redirect output - :x:
- Implement '<<' with a delimiter to read input - :x:
- Implement '>>' to redirect output in append mode - :x:

**Pipes**
- Implement pipes (| character) - :x:

**Environment Variables**
- Handle environment variables ($) - :x:
- Handle $? to expand to the exit status of the most recently executed foreground pipeline - :x:

**Interactive Mode**
- Handle ctrl-C, ctrl-D and ctrl-\ like in bash - :white_check_mark:
- ctrl-C displays a new prompt on a new line - :white_check_mark:
- ctrl-D exits the shell - :white_check_mark:
- ctrl-\ does nothing - :white_check_mark:

**Builtins**
- echo with option -n - :white_check_mark:
- cd with only a relative or absolute path - :white_check_mark:
- pwd with no options - :white_check_mark:
- export with no options - :x:
- unset with no options - :x:
- env with no options or arguments - :white_check_mark:
- exit with no options - :white_check_mark:

## Bonus Features
- Implement '&&' and '||' with parenthesis for priorities - :x:
- Wildcards '*' should work for the current working directory - :x: