# Minishell

A simplified version of the good old _Shell_. 

# How to Install it

## For Linux based OS

The library _libreadline_ is required to be installed in your OS. The rule below will be able to install it in Debian based OS.

```
make install
```

```
make
```

# Implementation details

## Parser

We can divide the process into 4 parts. 

### Tokenize

Generate a list of tokens that meet the requirements:
- A substring surrounded by quotes, either single or double
- A substring surrounded by spaces

This process will go from left to right in the string and each requirement excludes the next one. Son once we meet the first requirement (quotes), whatever is inside doesn't matter. Example: `echo 'red blue'` will return two tokens of type `echo` and `red blue`.

Another example will be `echo '"42"'` the tokens will be `echo` and `"42"`. Once we enter a requiremente, we don't care about checking it again.

For each token, the spaces and quotes were removed.

### Evaluate vars

Simply check if any of those tokens requires env vars evaluation. Meaning if the token was surrounded by double quotes and have the `$` before a word.
### Split by pipes

Separate those tokens list into smaller list when a token is found with the following conditions
- There is a token string of a single character and is '|'
- The token was parsed without quotes. 

### Split redirections tokens

Redirection tokens are in the form of `<` `<<` `>>` or `>`.
They must follow the following rule:
- The token was parsed without quotes

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
