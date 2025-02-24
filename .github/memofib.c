#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMO 91

/*
    Assignment 5: memoized Fibonacci
    CPSC 351 Spring 2025
    Justin Lam
*/

// Entry for storing Fibonacci numbers in the cache
typedef struct {
    int key;
    long long value;
} MemoEntry;

// Cache for storing Fibonacci numbers
#define CACHE_SIZE 100
static MemoEntry cache[CACHE_SIZE];

// Initialize the cache
void memoize_init() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].key = -1;
        cache[i].value = 0;
    }
}

// Store a Fibonacci number in the cache
void memoize_set(int key, long long value) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].key == -1 || cache[i].key == key) {
            cache[i].key = key;
            cache[i].value = value;
            return;
        }
    }
}

// Retrieve a Fibonacci number from the cache
long long *memoize_get(int key) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].key == key) {
            return &cache[i].value;
        }
    }
    return NULL;
}

// Recursive Fibonacci function with memoization
long long fibonacci(int n) {
    if (n < 0 || n > MAX_MEMO) {
        printf("Outside of the supported range (0-91)\n");
        return -1;
    }

    long long *cached_value = memoize_get(n);
    if (cached_value) {
        return *cached_value;
    }

    long long result;
    if (n == 0) result = 0;
    else if (n == 1) result = 1;
    else result = fibonacci(n - 1) + fibonacci(n - 2);

    // Store in cache
    memoize_set(n, result);
    return result;
}

int main() {
    memoize_init();

    int n;
    printf("Enter Fibonacci numbers (0-91). Press Ctrl+D (EOF) to exit the program.\n");
    
    while (scanf("%d", &n) != EOF) {
        long long result = fibonacci(n);
        if (result != -1) {
            printf("Memoized Fibonacci(%d) = %lld\n", n, result);
        }
    }

    printf("\nEnd of file\n");

    return 0;
}
