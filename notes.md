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

<	: at the beginning of a command
>	: at the end of a command
>>	: at the end of a command
<<	: parsed after in command exec
| : between command (so after a command)
