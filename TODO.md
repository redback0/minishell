
# Minishell todo

## Commands to implement -- beth

- echo
- cd
- pwd
- export // in bash, running with no args prints the whole environment, this doesn't appear to be a requirement in the evaluation sheet
- unset
- env
- exit // needs to be changed to run as other builtins, correct the exit status + error message if argument is non-numeric

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
- check how redirects act with builtins // builtins do not fork with redirects, pass fds instead
