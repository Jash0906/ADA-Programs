#include <stdio.h>
#include <time.h>

int fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter n: ");
    scanf("%d", &n);

    start = clock();

    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib_recursive(i));
    }
    printf("\n");

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
