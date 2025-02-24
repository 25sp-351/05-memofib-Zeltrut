/*
    Assignment 5: Memoized Fibonacci
    CPSC 351 Spring 2025
    Justin Lam
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMO 91
#define CACHE_SIZE 100
#define BUFFER_SIZE 50

typedef struct {
    int key;
    long long value;
} MemoEntry;

static MemoEntry cache[CACHE_SIZE];

// Initializes the memoization cache
void memoize_init(void) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].key = -1;  // Indicates an empty slot
        cache[i].value = 0;
    }
}

// Stores a computed Fibonacci number in the cache
void memoize_set(int key, long long value) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].key == -1 || cache[i].key == key) {
            cache[i].key = key;
            cache[i].value = value;
            return;
        }
    }
}

// Retrieves a computed Fibonacci number from the cache
long long *memoize_get(int key) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].key == key) {
            return &cache[i].value;
        }
    }
    return NULL;
}

// Computes the Fibonacci number at index n
long long fibonacci(int n) {
    if (n < 0 || n > MAX_MEMO) {
        printf("Error: Input is outside of the supported range (0-91)\n");
        return -1;
    }

    // Check cache
    long long *cached_value = memoize_get(n);
    if (cached_value) {
        return *cached_value;
    }

    // Compute Fibonacci number
    long long result;
    if (n == 0) result = 0;
    else if (n == 1) result = 1;
    else result = fibonacci(n - 1) + fibonacci(n - 2);

    // Store computed value in cache
    memoize_set(n, result);
    return result;
}

// Converts a number to a string
void number_to_string(long long num, char *buffer, size_t size) {
    if (snprintf(buffer, size, "%lld", num) < 0) {
        buffer[0] = '\0';  // Ensure safe fallback
    }
}

int main(void) {
    memoize_init();
    
    int n;
    char buffer[BUFFER_SIZE];

    printf("Enter Fibonacci numbers (0-91). Press Ctrl+D (EOF) to exit.\n");

    while (scanf("%d", &n) != EOF) {
        long long result = fibonacci(n);
        if (result != -1) {
            number_to_string(result, buffer, BUFFER_SIZE);
            printf("Memoized Fibonacci(%d) = %s\n", n, buffer);
        }
    }

    printf("\nEnd of file.\n");
    
    return 0;
}
