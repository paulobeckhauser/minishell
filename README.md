# Minishell
Minishell is a simple shell implementation with basic functionalities.

## Features**Prompt and Command Execution**
- Display a prompt when waiting for a new command - ✅
- Have a working history - ✅
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path) - ❌

**Signal Handling**
- Avoid using more than one global variable to indicate a received signal - ❌

**Quote Handling**
- Handle ' (single quote) - ❌
- Handle " (double quote) - ❌

**Redirections**
- Implement '<' to redirect input - ❌
- Implement '>' to redirect output - ❌
- Implement '<<' with a delimiter to read input - ❌
- Implement '>>' to redirect output in append mode - ❌

**Pipes**
- Implement pipes (| character) - ❌

**Environment Variables**
- Handle environment variables ($) - ❌
- Handle $? to expand to the exit status of the most recently executed foreground pipeline - ❌

**Interactive Mode**
- Handle ctrl-C, ctrl-D and ctrl-\ like in bash - ❌
- ctrl-C displays a new prompt on a new line - ❌
- ctrl-D exits the shell - ❌
- ctrl-\ does nothing - ❌

**Builtins**
- echo with option -n - ❌
- cd with only a relative or absolute path - ✅
- pwd with no options - ❌
- export with no options - ❌
- unset with no options - ❌
- env with no options or arguments - ❌
- exit with no options - ❌

## Bonus Features
- Implement '&&' and '||' with parenthesis for priorities - ❌
- Wildcards '*' should work for the current working directory - ❌