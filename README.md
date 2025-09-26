## Project Overview

Minishell is a simplified shell built in C as part of the 42 curriculum.
It reproduces basic features of a UNIX shell following bash behvior.


## Project Structure

```md
minishell
├── includes
│   └── *.h
├── libs
│   └── libft
├── srcs
│   └── *.c
├── Makefile
└── README.md
```


## Features

- Full command execution
- Built-in command support
- Input/output redirection
- Multi-pipe support
- Proper error handling
- Signal management
- Custom environment variable expansion


## Installation and Usage

1. Clone the repository:
```bash
git clone https://github.com/matthieugaudin/minishell.git
cd minishell
```
2. Complie the project
```bash
make
```

3. Run the shell
```bash
./minishell
```

4. Use commands like a normal shell
```bash
echo "Hello World"
echo "$PATH"
export VAR=hello then echo $VAR
ls -l | grep minishell > output.txt
export PATH=/usr/bin
cat then Ctrl-C then echo $?
echo hello | nonexistentcmd
```

5. Exit the shell
```bash
exit
```
