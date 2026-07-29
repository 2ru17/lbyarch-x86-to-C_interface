#!/bin/bash
# Build script for LBYARCH x86-64/C Machine Project
# Assemble, compile, link, and run

set -e

echo "[1/3] Assembling imgCvtGrayIntToDouble.asm..."
nasm -f elf64 imgCvtGrayIntToDouble.asm -o imgCvtGrayIntToDouble.o

echo "[2/3] Compiling and linking main.c..."
gcc -o main main.c imgCvtGrayIntToDouble.o -lm -no-pie

echo "[3/3] Build complete! Run with: ./main"
