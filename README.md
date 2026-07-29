# lbyarch-x86-to-C_interface
LBYARCH Machine Project - Grayscale Int-to-Double Converter

## Group Members - S25E
* Neil Jr. Gutang
* Allisha Kate Wong

## Project Description
This project implements a hybrid C and x86-64 assembly program to convert grayscale images represented as 8-bit unsigned integers (0-255) to a double precision floating-point representation (0.0 to 1.0). The C program handles memory allocation, correctness checking, benchmarking, and result output, while the core conversion calculation `imgCvtGrayIntToDouble()` is performed in x86-64 NASM assembly utilizing functional scalar SIMD registers and instructions.

## How to Build & Run
A build script is provided to simplify compilation and linking. 

```bash
chmod +x build.sh
./build.sh
./main
```

## Performance Benchmarks
The program runs the conversion algorithm 30 times for different image sizes to calculate the average execution time.

| Image Size | Total Pixels | Average Execution Time (seconds) |
| --- | --- | --- |
| 10 x 10 | 100 | [Time] |
| 100 x 100 | 10,000 | [Time] |
| 1000 x 1000 | 1,000,000 | [Time] |

### Performance Analysis
*(Write your short analysis of the execution time here)*

## Output and Correctness
*(Insert Screenshot of output verifying correctness here)*

## Demo Video
*(Insert Link to 5-10 minute Youtube/Gdrive demo video here)*
