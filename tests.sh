#!/bin/bash

# Compile the program if not already compiled
if [ ! -f memoizefib ]; then
    echo "Compiling memoizefib..."
    gcc -o memofib memofib.c -I.
fi

echo "Running tests..."

test_cases=(
    "5"    # Expected: Memoized Fibonacci(5) = 5
    "10"   # Expected: Memoized Fibonacci(10) = 55
    "20"   # Expected: Memoized Fibonacci(20) = 6765
    "50"   # Expected: Memoized Fibonacci(50) = 12586269025
    "91"   # Expected: Memoized Fibonacci(91) = 4660046610375530309
    "-1"   # Expected: Out of supported range (0-91)
    "100"  # Expected: Out of supported range (0-91)
)

# Run tests
{
    for case in "${test_cases[@]}"; do
        echo "$case"
    done
} | ./memofib

echo "Tests completed!"
