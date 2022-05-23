# minishell

# How to Install it

## For Linux based OS

```
make install
```

```
make
```

# Implementation details

## Handling single and double quotes

### Single quotes

Enclosing characters in single quotes (') preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash.

### Double quotes

Enclosing characters in double quotes (") preserves the literal value of all characters within the quotes, with the exception of $, `, \, and, when history expansion is enabled, !. The characters $ and ` retain their special meaning within double quotes

## Signals

About the system signals, we are handling them different depending on which layer of the process are we. Here there are some examples
### Ctrl + c 'SIGINT'

Minishell: create a new line and continue REPL. It won't exit the minishell process. Set exit status to `130`

ChildProcess: exit the process with exit status `130`

### Ctrl + \ 'SIGQUIT'

Minishell: ignore it

ChildProcesss: exit the child process.

### Ctrl + d 'EOF'

Minishell: Close the program
