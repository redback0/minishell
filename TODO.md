
# Minishell todo

## Commands to implement -- beth

- echo
- cd // fix case with no args; should quit without doing anything
- pwd // done
- export // in bash, running with no args prints the whole environment, this doesn't appear to be a requirement in the evaluation sheet
- unset
- env // done
- exit // needs to be changed to run as other builtins, correct the exit status + error message if argument is non-numeric

## Signals to handle

- ctrl-c // should be done
- ctrl-d // done. also, not a signal
- ctrl-\ // should be done

## Other things

- implement pipes (<, |, >, <<, >>) // done, testing required
- implement environment variables ($VAR) // should work in all cases; further testing should be done
- implement $? // fully implemented, pass to ms_exit
- search the path for commands -- beth // done, testing will happen naturally
- open files for read/write -- beth // done, testing required
- add the single command execute function, in execute.c -- beth // done
