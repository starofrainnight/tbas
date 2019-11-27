# TBAS (Tiny BASIC compiler/executor)

A small example of tiny BASIC language compiler/executor written with
flex/bison.

Just use for demonstrate how to write a simple BASIC compiler/executor.

## How to compile

Under the source directory, run commands below to build the projec:

    cmake .
    make

It will generate a program `tbas` under `src` directory.

You could test this program by:

    ./src/tbas ./tests/sample.bas
