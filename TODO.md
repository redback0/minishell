
# Minishell todo

## Commands to implement -- beth

- echo
- cd
- pwd
- export
- unset
- env
- exit // need argument handling, correct the exit status + error message if argument is non-numeric

## Signals to handle

- ctrl-c // should be done
- ctrl-d // should be done
- ctrl-\ // change back when forked

## Other things

- implement pipes (<, |, >, <<, >>) // should be done, almost
- implement environment variables ($VAR) // broken in case of "'$USER'"
- implement $? // where the status variable is will need to change
- search the path for commands -- beth
- open files for read/write -- beth
- add the single command execute function, in execute.c -- beth
- check how redirects act with builtins
