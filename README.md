## 💻 Project Overview

Minishell is a simplified shell built in C as part of the 42 curriculum.
It reproduces basic features of a UNIX shell following bash behvior, including:

Executing commands with arguments

Handling built-in commands: cd, echo, env, pwd, export, unset, exit

Redirections: >, >>, <

Pipelines using |

Environment variable expansion

Signal handling (Ctrl-C, Ctrl-D, Ctrl-)

This project helped me learn process management, pipes, signals, and command parsing in a low-level C environment.

## ⚡ Features

Full command execution

Built-in command support

Input/output redirection

Multi-pipe support

Proper error handling

Signal management

Custom environment variable expansion

## 🛠️ Tech Stack

Language: C (C99 standard)

OS: Linux / macOS

Tools: gcc, make, readline

## 📂 Project Structure
minishell/
├── src/               # Source files
├── include/           # Header files
├── tests/             # Unit tests
├── Makefile           # Compilation script
├── README.md          # Project documentation
└── .gitignore         # Ignored files

## 🚀 Installation & Usage

Clone the repo:

git clone https://github.com/yourusername/minishell.git
cd minishell


Compile the project:

make


Run the shell:

./minishell


Use commands like a normal shell:

echo "Hello World"
ls -l | grep minishell > output.txt
export PATH=/usr/bin


Exit the shell:

exit

Include example scripts for testing.

Add badges for 42 norms check, libft integration, or any CI/CD setup.
