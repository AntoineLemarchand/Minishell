# Minishell

A minimal shell written in C, it can manage error codes, pipes, redirections and environment variables.

## builtins
1. cd
1. pwd
1. export
1. unset
1. exit
1. echo

## Usage
```
make
./minishell 
MrdShll> echo "hello"  $USER
hello antoine
MrdShll> ls > test
MrdShll> cat test
includes
libft
Makefile
minishell
README.md
srcs
test
MrdShll> rm test
MrdShll> exit 123
exit
```
