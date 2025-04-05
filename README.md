# Minishell

A minimal shell written in C, it can manage error codes, pipes, redirections and environment variables.

## builtins
- cd
- env
- pwd
- export
- unset
- exit
- echo with the -n option

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
