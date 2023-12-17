# Simple Shell Project.

## User Guide:
Welcome to MinimalShell – a lightweight, command-line interface for streamlined interactions with your system.
This user guide will walk you through the usage of the MinimalShell software, providing clear instructions on 
how to navigate and leverage its features.

## Requirements:
* Operating System: ``Simple Shell`` is designed for Unix-like operating systems.
* Compiler: Ensure you have a C compiler installed (e.g., GCC).

## Getting Started:
* Clone The Repository:
```bash
git clone https://github.com/NairaMescudi/simple_shell.git
```

* Change Working Directory:
Navigate into the directory that has just been cloned
```bash
cd simple_shell
```

* Build The Project:
The project includes a Makefile for easy compilation.
```bash
make
```

* Run Simple Shell:
Once built, execute the Simple Shell.
```bash
./hsh
```

## Usage:
* Executing Commands:
Enter commands as you would in a regular shell and press Enter to execute.
```bash
$ ls -l
```

* Input/Output Redirection:
Redirect input and output for commands.
$ cat input.txt > output.txt

* Built-in Commands:
Simple Shell supports basic built-in commands.
	* env: Print the environment variables list
	```bash
	$ env
	```
* Signal Handling:
Learn how Simple Shell handles signals.
	* Send a termination signal (Ctrl + D) during command execution.

* Error Handling:
Understand how errors are reported for better troubleshooting.

## Contributing:
Contributions to Simple Shell are welcome! If you have suggestions, improvements, or bug fixes, 
feel free to fork the repository and submit pull requests.

## Acknowledgments:
A special thanks to Julien Barber, Maxwell Nana Forson, and all contributors who
have helped ideate and improve the simple shell.

For more details and customization options, please refer to the full documentation in the repository.

Happy shell scripting! 🚀
