# minishell

# How to Install it

## For Linux based OS

```
make install
```

```
make
```

# Documentation

## Signals

About the system signals, we are handling them different depending on which layer of the process are we. Here there are some examples
### Ctrl + c 'SIGINT'

Minishell: create a new line and continue REPL. It won't exit the minishell process. Set exit status to `130`

ChildProcess: exit the process with exit status 130

### Ctrl + \ 'SIGQUIT'

Minishell: ignore it

ChildProcesss: exit the child process.

### Ctrl + d 'EOF'

Minishell: Close the program
