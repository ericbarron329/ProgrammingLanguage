#include <stdio.h>

extern "C" {
    int add(int a, int b) {
        return a + b;
    }

    void print_message() {
        printf("WebAssembly Test: C++ Code Loaded Successfully!\n");
    }
}
