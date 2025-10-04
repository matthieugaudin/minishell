## Project Overview

Minishell is a simplified shell built in C as part of the 42 curriculum.
It reproduces basic features of a UNIX shell following bash behavior.


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

2. Compile the project
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


## How Minishell Works

- Load environment variables (or create a minimal one)
- Show the prompt minishell> and wait for input
- Tokenize and parse the line into commands
- Expand variables and remove quotes
- Create command structures and pipes if needed
- Run builtins directly, or fork/exec for other commands
- Handle signals (Ctrl-C, Ctrl-D, Ctrl-\) like Bash
- Free memory and exit cleanly when the user quits

## Conclusion

This project taught me a lot about how a shell works, including parsing, command execution, redirections, and signal handling. The main challenge was ensuring no memory leaks while handling dynamic data structures and multiple processes. If you have any questions or need more details, feel free to contact me.
