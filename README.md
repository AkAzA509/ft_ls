# ft_ls

A basic reimplementation of the Unix `ls` command in C.

This project lists files and directories, supports common options, and reproduces a small subset of the behavior of `ls`.

## Features

- `-a` : show hidden files and directories
- `-l` : long format output
- `-R` : recursive listing
- `-t` : sort by modification time
- `-r` : reverse sort order
- `-h` : display help

If no path is given, the program lists the current directory.

## Usage

```bash
./ft_ls
./ft_ls -l
./ft_ls -a
./ft_ls -R .
./ft_ls -ltr
./ft_ls /tmp /var
```

## Build

```bash
make
```

Run it with:

```bash
./ft_ls
```

Clean artifacts:

```bash
make clean
make fclean
```

## Project structure

```text
.
├── include/
│   └── ft_ls.h
├── src/
│   ├── listing.c
│   ├── main.c
│   ├── parser.c
│   ├── print.c
│   └── libft/
│       └── ...
├── Makefile
├── LICENSE
├── README.md
```
