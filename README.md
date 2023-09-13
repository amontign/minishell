# Minishell

## Description

Minishell is a simple project aimed at creating a minimalist UNIX command interpreter. This command interpreter, also known as a shell, allows users to execute basic commands in a UNIX environment.

## Features

- Interpretation of basic UNIX commands.
- Managing the working environment with commands like `cd`, `pwd`, `export`, `unset`, etc.
- Execution of external commands with arguments.
- Correct handling of paths.
- Implementation of certain bash shell features such as double and single quotes.

## Installation

To install and compile Minishell, follow the steps below:

```sh
git clone https://github.com/your_username/minishell.git
cd minishell
make
```

## Usage

After compiling the project, you can launch Minishell using:

```sh
./minishell
```

Within the Minishell, you can run commands just as you would in a normal UNIX terminal. For example :

```sh
ls -la
cd /path/to/directory
echo Hello, world!
```
