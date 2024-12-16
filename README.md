# Minishell

Welcome to **Minishell**, a project from 42 School aimed at recreating a minimalist command-line interpreter inspired by bash. This project implements many features of a standard shell while respecting the constraints imposed by 42 School.

## Description

Minishell is a functional command-line interpreter developed in C. It supports a wide range of standard commands, complex redirections, pipes, and signal handling. This project is designed to provide a deep understanding of how a shell works internally while adhering to UNIX philosophy.

### Main Features

- Execution of simple and compound commands
- Redirection management (`<`, `>`, `>>`, `<<`)
- Pipe management (`|`)
- Environment variables
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Variable expansions (`$VARIABLE`)
- Error handling and edge cases (e.g., nested redirections)

### Limitations

- No support for wildcards (`*`)
- No support for logical operators (`&&`, `||`)

## Installation

To compile and use Minishell:

```bash
# Clone the repository
$ git clone https://github.com/youraccount/minishell.git

# Navigate to the directory
$ cd minishell

# Compile the project
$ make

# Run Minishell
$ ./minishell
```

## Usage

Here are some examples to explore Minishell's features.

### Simple Commands

```bash
# List files in the current directory
$ ls

# Display a message
$ echo "Welcome to Minishell!"
```

### Pipes

```bash
# Combine multiple commands with pipes
$ ls | grep minishell | wc -l
```

### Redirections

#### Output Redirections

```bash
# Redirect standard output to a file
$ echo "Hello, world!" > output.txt

# Append to an existing file
$ echo "Another line" >> output.txt
```

#### Input Redirections

```bash
# Read input from a file
$ cat < input.txt

# Combine redirection and pipes
$ grep "word" < input.txt | sort
```

#### Combined Redirections

```bash
# Complex commands with nested redirections
$ < input.txt grep "word" > output.txt

# Redirection with multiple commands
$ < file1 cat | grep "pattern" > file2
```

### Expansions

```bash
# Use environment variables
$ export NAME=42
$ echo "Welcome to $NAME!"

# Invalid command with error handling
$ invalidcmd
Minishell: command not found: invalidcmd
```

### Signals

- `Ctrl+C`: Interrupts the current command
- `Ctrl+D`: Exits Minishell (EOF)
- `Ctrl+\`: Ignored (no effect)

## Code Structure

The code is organized to clearly separate responsibilities:

- **Parsing**: Command analysis and splitting
- **Execution**: Command execution management
- **Redirections**: Implementation of redirections and pipes
- **Builtins**: Management of internal commands (e.g., `cd`, `export`, `unset`)
- **Signals**: Signal handling

## Contributing

Contributions are welcome! If you have suggestions or want to report bugs, open an issue or submit a pull request.
