#include <stdio.h>
#include <time.h>

void fib_bottomup(int n) {
    if (n <= 0) return;

    long long fib[n];  // Use long long for larger numbers
    fib[0] = 0;

    if (n > 1)
        fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++) {
        printf("%lld ", fib[i]);
    }
    printf("\n");
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter n: ");
    scanf("%d", &n);

    start = clock();
    fib_bottomup(n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
