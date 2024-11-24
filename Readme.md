# minishell

# Allowed functions

    the new:

    readline, rl_clear_history, rl_on_new_line,
    rl_replace_line, rl_redisplay, add_history,
    printf, malloc, free, write, access, open, read,
    close, fork, wait, waitpid, wait3, wait4, signal,
    sigaction, sigemptyset, sigaddset, kill, exit,
    getcwd, chdir, stat, lstat, fstat, unlink, execve,
    dup, dup2, pipe, opendir, readdir, closedir,
    strerror, perror, isatty, ttyname, ttyslot, ioctl,
    getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
    tgetnum, tgetstr, tgoto, tputs

    the old:

    readline, rl_clear_history, rl_on_new_line,
    rl_replace_line, rl_redisplay, add_history,
    printf, malloc, free, write, access, open, read,
    close, fork, wait, waitpid, wait3, wait4, signal,
    sigaction, sigemptyset, sigaddset, kill, exit,
    getcwd, chdir, stat, lstat, fstat, unlink, execve,
    dup, dup2, pipe, opendir, readdir, closedir,
    strerror, perror, isatty, ttyname, ttyslot, ioctl,
    getenv, tcsetattr, tcgetattr, tgetent, tgetflag,

# Mandatory TODOs

- [x] Display a prompt when waiting for a new command.
  - [ ] make it nicer
- [x] Have a working history.
  - [ ] does it really work correctly in all cases? especially the heredoc case?
  - [ ] Search and launch the right executable (based on the PATH variable or
      using a relative or an absolute path).
- [ ] Not interpret unclosed quotes or special characters which are not required
  by the subject such as \ (backslash) or ; (semicolon).
- [ ] Handle ’ (single quote) which should prevent the shell from interpreting
  the meta- characters in the quoted sequence.
- [ ] Handle " (double quote) which should prevent the shell from interpreting
  the meta- characters in the quoted sequence except for $ (dollar sign).
- [ ] Implement redirections:
  - [ ] < should redirect input.
  - [ ] > should redirect output.
  - [ ] << should be given a delimiter, then read the input until a line
    containing the delimiter is seen. However, it doesn’t have to update the
    history!
  - [ ] >> should redirect output in append mode.
- [ ] Implement pipes (| character). The output of each command in the pipeline
  is connected to the input of the next command via a pipe.
- [ ] Handle environment variables ($ followed by a sequence of characters)
  which should expand to their values.
- [ ] Avoid using more than one global variable to indicate a received signal.
  Consider the implications: this approach ensures that your signal handler will
  not access your main data structures
- [ ] Handle $? which should expand to the exit status of the most recently
  executed foreground pipeline.
- [x] Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
  + [ ] idk know. ctrl-d behaves different for bash's built with lib-readline.
    sometimes ctrl-d on an non-empty prompt is completly ignored sometimes it
    isn't. clarify
- [ ] In interactive mode:
  - [x] ctrl-C displays a new prompt on a new line.
  - [x] ctrl-D exits the shell.
    + [ ] clarify different behavior from readline man-page.
  - [x] ctrl-\ does nothing.
- [ ] Your shell must implement the following builtins:
  - [ ] echo with option -n
  - [ ] cd with only a relative or absolute path
  - [ ] pwd with no options
  - [ ] export with no options
  - [ ] unset with no options
  - [ ] env with no options or arguments
  - [ ] exit with no options
- [ ] The readline() function can cause memory leaks. You don’t have to fix
  them. But that doesn’t mean your own code, yes the code you wrote, can have
  memory leaks.

## Parsing / Lexing TODOs

- [ ] find a way to make everything obey the norm.
- Tokens to correctly tokenize:
  + [x] command
  + [x] arg
  + [x] pipe
  + [x] "<" redirect in
  + [x] infile
  + [x] ">" redirect out
  + [x] outfile
  + [x] ">>" redirect out append -> outfile stays the same
  + [x] "<<" heredoc -> what? how?
  + [x] heredoc-delimiter
  + [x] "'" single quotes
  + [x] -> single quoted text
  + [x] """ double quotes
  + [x] -> single quoted text (but $variables should be handled)
  + [x] $ variable start
  + [x] -> variable name
  + [x] builtins
  + [x] builtin args for echo, export ("=" + arg), unset, export, cd
  + [ ] ...

  -> -> -> **i need much more tokens!!!**

# Resources

- [https://42-cursus.gitbook.io/guide/rank-03/minishell/functions](https://42-cursus.gitbook.io/guide/rank-03/minishell/functions)
- [https://en.wikipedia.org/wiki/Lexical_analysis](https://en.wikipedia.org/wiki/Lexical_analysis)
- [http://web.mit.edu/gnu/doc/html/rlman_2.html](http://web.mit.edu/gnu/doc/html/rlman_2.html)

# Syntax Notes

Bash syntax errors:

- `cat <` or `cat >` or `cat > |` and the like
- `cat << "<<"` is legit!

# Logbook

- **[2024-11-14 21:59]** Now i really want to start working on this. A first
  checklist:
  + [x] display the prompt
  + [ ] implement signal handling, 
    + [ ] handle Ctrl-D like bash
    + [x] that is handle Ctrl-C in a correct way

- **[2024-11-19 01:39]** Well.. the main output of todays.. "coding": there are
  version of bash (on nix bash_interactive) which are build with and linked
  against readline. With those hitting ctrl-d on a non-empty input line does
  nothing. For those bash versions which are not linked against readline ctrl-d
  behaves different. More like explained in the readline-manpage. needs some
  more: 🤔 ... but not too much. next: parsing!

- **[2024-11-20 12:00]** Some observations relevant for syntax checking /
  parsing:
  + `echo "blabla" | < bindvoutside.log wc -w` is the same as `echo "blabla" |
    wc -w < bindvoutside.log`. so '|' followed by '<' is allowed. The same holds
    for '>'
  + Something like `echo "blabal" | | cat` is not allowed -> *bash: syntax error
    near unexpected token `|'*
  
  So. That said how to parse a prompt like: `< infile cat | wc -w > out`?
  **RULE**: every word after a '<' is considered to be a input_file to cmd.

  + another special case: parsing something like `< a cat | < b wc -w > c`.
    During parsing, after the pipe symbol we would have to allocate a new
    cmdlst-member an then read in redirection first.

- **[2024-11-21 00:12]** Alright parsing of commands, <, >, and | seems to
  working so far. what about >> and << ??? at least << is a very special thing
  as it changes the whole program execution flow.
  Major TODO: somehow make the whole parsing process more elegant and shorter.

- **[2024-11-23 11:24]** I wrote this as a comment to my `get_next_token()`
  yesterday:

  ```c
  /* Get next token from input...
  *
  * This function should return (and increment cl->position accordingly):
  * - the VALUE of the token it found (f.ex. '<', for a word the whole word ->
  *   read until there is some new token)
  * - the position of the token in cmdline
  * 
  * This means the whole classification thing happens in the tokenizing function.
  * Maybe i need to add some flags to the cmdline struct:
  * - for squot / dquot
  * - for var name
  * - for if / of
  * - for heredoc
  * - for pipe
  * - forgot somethin ?!?!
  *
  * then i can really read token-symbol by token-symbol, word by word from the
  * input string using get_next_token(), if it ecounters f.ex. '<' it sets the
  * if_flag inside cmdline-struct, returns to tokenize(), which handles the
  * addition to toklst (and maybe stuff like finding out wether we have a builtin
  * or not?!?!)
  *
  * Example tokenization-flow: find '<' -> return just "<" -> in tokenize() there
  * is handle_redirect_token(): checks if quot-flags are set, checks if already
  * inside a redirection (actually waiting for the file name), if yes, throw
  * error.... AAAHHHH, maybe this is too much for a tokenizer. This would be the
  * job of my parser!
  *
  * Maybe words should just be TOK_WORD and only during parsing the decision is
  * made that they should be TOK_IF, TOK_CMD, TOK_ARG, ...
  *
  */
  ```

  Today my view on this is as follows. I will have several tokenization and
  parsing steps:

  1) Tokenize very low-level with only as little as possible grammar. I think
     that "as-little" is interpreting quots because in this case all text
     between the quots **will need to be tokenized as-is**, that is with all
     whitespaces and stuff.
  2) My hypothesis: for everything else 1st level of tokenization / parsing can
     happen by simply assigning f.ex. `TOK_RIN` to '<' and `TOK_WORD` to stuff
     like "cat" and "-w".
  3) 2nd level: Iterate over tokenlist. For something like TOK_RIN followed by
     TOK_WORD set token->type of TOK_WORD token to TOK_IF. One very special case
     is the heredoc. If i find this and next toke is TOK_WORD, make it
     TOK_HERE_DLIM (*Error handling ?!?!?!* perhaps in this very step).
  4) 3rd Level: the real parsing starts. Until here couple of errors have been
     ruled out. Time to fill the Command-struct.
  5) maybe 4th Level: Check filenames, permissions etc.
  6) Execution: forks(), run builtins, run heredoc (*TODO: how to implement
     this?!*).
  

