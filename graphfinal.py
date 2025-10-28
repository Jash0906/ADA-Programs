import matplotlib.pyplot as plt
import time
import random

def fractional_knapsack(values, weights, capacity):
    ratio = [(v / w, v, w) for v, w in zip(values, weights)]
    ratio.sort(reverse=True)
    total_value = 0.0
    for r, v, w in ratio:
        if capacity >= w:
            capacity -= w
            total_value += v
        else:
            total_value += v * (capacity / w)
            break
    return total_value

def knapsack_01(values, weights, W):
    n = len(values)
    dp = [[0 for _ in range(W + 1)] for _ in range(n + 1)]
    for i in range(1, n + 1):
        for w in range(W + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                )
            else:
                dp[i][w] = dp[i - 1][w]
    return dp[n][W]

def test_fractional(n):
    values = [random.randint(10, 100) for _ in range(n)]
    weights = [random.randint(1, 50) for _ in range(n)]
    capacity = n * 10
    start = time.time()
    fractional_knapsack(values, weights, capacity)
    return time.time() - start

def test_knapsack_01(n, W):
    values = [random.randint(10, 100) for _ in range(n)]
    weights = [random.randint(1, 50) for _ in range(n)]
    start = time.time()
    knapsack_01(values, weights, W)
    return time.time() - start

sizes = [5, 10, 15, 20, 25]
frac_times = [test_fractional(n) for n in sizes]
dp_times = [test_knapsack_01(n, 100) for n in sizes]

plt.plot(sizes, frac_times, 'o-', color='orange', label='Fractional Knapsack (Greedy)')
plt.plot(sizes, dp_times, 's-', color='skyblue', label='0/1 Knapsack (Dynamic Programming)')
plt.xlabel('Number of Items (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Time Complexity Comparison: Fractional vs 0/1 Knapsack')
plt.legend()
plt.grid(True)
plt.show()
