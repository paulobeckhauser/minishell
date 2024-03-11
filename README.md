# Minishell
Minishell is a simple shell implementation with basic functionalities.

## Features**Prompt and Command Execution**
- Display a prompt when waiting for a new command - :white_check_mark:
- Have a working history - :white_check_mark:
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path) - :x:

**Signal Handling**
- Avoid using more than one global variable to indicate a received signal - :x:

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
- Handle ctrl-C, ctrl-D and ctrl-\ like in bash - :x:
- ctrl-C displays a new prompt on a new line - :x:
- ctrl-D exits the shell - :x:
- ctrl-\ does nothing - :x:

**Builtins**
- echo with option -n - :x:
- cd with only a relative or absolute path - :x:
- pwd with no options - :x:
- export with no options - :x:
- unset with no options - :x:
- env with no options or arguments - :x:
- exit with no options - :x:

## Bonus Features
- Implement '&&' and '||' with parenthesis for priorities - :x:
- Wildcards '*' should work for the current working directory - :x: