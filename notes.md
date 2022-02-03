< file.txt cat | wc -w > file1.txt | cat << hello > file2.txt

## Lexing

'< file.txt' 
[IN : 'file1']

'cat'
[CMD : 'cat']

'|'
[PIPE]

'wc -w'
[CMD : 'wc -w']

'> file1.txt'
[OUT: 'file1.txt']

'|'
[PIPE]

'cat << hello'
[CMD : 'cat << hello']

'> file2.txt'
[OUTPUT: 'file2.txt']

## Parsing

SimpleComman
[
	PIPE	:	[CMD: 'ls -l']
				[CMD: 'wc -w']
				[CMD: 'cat << hello']
	IN		:	'file1'
	OUT		:	'file2.txt'
]

<	: at the beginning of a command
>	: at the end of a command
<<	: parsed after in command exec
| : between command (so after a command)

plan :	s_command → char* command, char* input = NULL(0), char* outfile = NULL(1);
