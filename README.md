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

## The Tiny BASIC Language

Supported Features:

1. Line comment "REM"

   ```bash
   REM This is a comment
   ```

1. Variant assignment "LET" or without "LET"

   ```bash
   LET a = 12
   LET b = 12 + 3.04
   c = 13
   ```

1. Console display function "PRINT"

   ```bash
   PRINT "Hello, world!"
   ```

1. Program ending mark "END"
1. Label definition and GOTO

   ```bash
   THIS_IS_A_LABEL:
   PRINT "Infinite looping..."
   GOTO THIS_IS_A_LABEL
   ```
