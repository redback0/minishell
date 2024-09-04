
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
- ctrl-d // done. also, not a signal
- ctrl-\ // should be done

## Other things

- implement pipes (<, |, >, <<, >>) // requires the 'open files for read/write' part to be done
- implement environment variables ($VAR) // should work in all cases; further testing should be done
- implement $? // fully implemented, pass to ms_exit
- search the path for commands -- beth
- open files for read/write -- beth
- add the single command execute function, in execute.c -- beth
- check how redirects act with builtins // builtins do not fork with redirects, pass fds instead. this will be an easy change
