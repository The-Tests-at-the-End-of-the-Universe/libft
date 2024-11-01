lol

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://m.media-amazon.com/images/M/MV5BMzJjZDJlNTQtYTEyZC00YTNkLTg0N2EtZTQyYjgzNTAwNzE4XkEyXkFqcGdeQXVyMTIwODk1NTQ@._V1_.jpg">
    <img src="https://m.media-amazon.com/images/M/MV5BMzJjZDJlNTQtYTEyZC00YTNkLTg0N2EtZTQyYjgzNTAwNzE4XkEyXkFqcGdeQXVyMTIwODk1NTQ@._V1_.jpg" alt="Logo" width="225" height="150">
  </a>
  <h3 align="center">libft_tester</h3>

  <p align="center">
    What are unit tests?
    <br />
    <br />
    <a href="https://github.com/The-Tests-at-the-End-of-the-Universe/libft_tester/issues">Report Bug</a>
    ·
    <a href="https://github.com/The-Tests-at-the-End-of-the-Universe/libft_tester/issues">Request Feature</a>
  </p>
</div>


# About The Project

  
libft is the first project at Codam. This is a tester to test out all the functions for edge cases or memory violations.


# Installation
1. Clone the repo in libft folder, --recursive flag is for submodules, and is necessary otherwise some tests may not run.


```sh

cd libft
git clone git@github.com:The-Tests-at-the-End-of-the-Universe/libft_tester.git --recursive

```
2. cd into directory

```sh

cd libft_tester

```

3. run bash script 

```sh

bash tester.sh

```

# Usage

- run help flag with script to see all options

```sh

bash tester.sh --help

```

- run tests without norminette

```sh
bash tester.sh -nn
```

- run tests without forbidden function test

```sh
bash tester.sh -nf
```

- run tests without memory tests

```sh
bash tester.sh -nm
```

- run tests with strict (fail tests)

```sh
bash tester.sh -s
```


# Contributing

To contribute, a pull request can be made to add changes that you want to add. Look at the open issues to 
see how you could contribute. 

## General structure of tester

1. run tester.sh
2. compile unit tests in c together with libft
3. script runs norminette test
4. script runs forbidden function test
5. script run tests per function together with valgrind
6. unit tests are all in one file per function, tests in c print out fail or success and returns exit code + prints errors out in stderr
7. script catches unit tests errors and valgrind errors and redirections them to log files.

# License

Distributed under the MIT License. See `LICENSE.txt` for more information.
