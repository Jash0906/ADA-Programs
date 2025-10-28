#include <stdio.h>
#include <time.h>
#define MAX 100000

long long memo[MAX];

// Top-Down DP (Memoization)
long long fibonacci_topdown(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibonacci_topdown(n - 1) + fibonacci_topdown(n - 2);
    return memo[n];
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    // Initialize memo array
    for (int i = 0; i <= n; i++)
        memo[i] = -1;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    printf("Fibonacci Series: ");
    for (int i = 0; i <= n; i++) {
        printf("%lld ", fibonacci_topdown(i));
    }
    printf("\n");
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
