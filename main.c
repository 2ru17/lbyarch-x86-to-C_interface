#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

// External assembly function
extern void imgCvtGrayIntToDouble(uint8_t *input, double *output, int width, int height);

// C reference implementation for correctness check
void imgCvtGrayIntToDouble_C(uint8_t *input, double *output, int width, int height) {
    int total = width * height;
    for (int i = 0; i < total; i++) {
        output[i] = (double)input[i] / 255.0;
    }
}

// Run benchmark: 30 iterations, return average time in seconds
double benchmark(uint8_t *input, double *output, int width, int height, int runs) {
    clock_t start, end;
    double total_time = 0.0;

    for (int i = 0; i < runs; i++) {
        start = clock();
        imgCvtGrayIntToDouble(input, output, width, height);
        end = clock();
        total_time += (double)(end - start) / CLOCKS_PER_SEC;
    }

    return total_time / runs;
}

int main() {
    srand(time(NULL));
    int sizes[][2] = {{10, 10}, {100, 100}, {1000, 1000}};
    int num_sizes = 3;
    int runs = 30;

    //vCorrectness check with small manual input
    printf("Correctness Check (4x3 image)\n");
    int test_w = 4, test_h = 3;
    uint8_t test_input[] = {
        64,  89,  114, 84,
        140, 166, 191, 84,
        216, 242, 38,  84
    };
    int test_total = test_w * test_h;
    double *asm_output = (double *)malloc(test_total * sizeof(double));
    double *c_output   = (double *)malloc(test_total * sizeof(double));

    imgCvtGrayIntToDouble(test_input, asm_output, test_w, test_h);
    imgCvtGrayIntToDouble_C(test_input, c_output, test_w, test_h);

    int correct = 1;
    for (int i = 0; i < test_total; i++) {
        printf("Pixel[%2d] = %3d | C: %.6f | ASM: %.6f | %s\n",
               i, test_input[i], c_output[i], asm_output[i],
               (fabs(c_output[i] - asm_output[i]) < 1e-10) ? "PASS" : "FAIL");
        if (fabs(c_output[i] - asm_output[i]) >= 1e-10) correct = 0;
    }
    printf("Correctness: %s\n\n", correct ? "ALL PASSED" : "SOME FAILED");

    free(asm_output);
    free(c_output);

    // Performance benchmarks
    printf("Performance Benchmarks (30 runs each)\n");
    for (int s = 0; s < num_sizes; s++) {
        int w = sizes[s][0];
        int h = sizes[s][1];
        int total = w * h;

        uint8_t *input  = (uint8_t *)malloc(total * sizeof(uint8_t));
        double  *output = (double *)malloc(total * sizeof(double));

        // Fill with random pixel values
        for (int i = 0; i < total; i++) {
            input[i] = rand() % 256;
        }

        double avg_time = benchmark(input, output, w, h, runs);
        printf("Image size %dx%d (%d pixels): avg time = %.6f seconds\n",
               w, h, total, avg_time);

        free(input);
        free(output);
    }

    return 0;
}
