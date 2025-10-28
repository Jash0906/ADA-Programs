import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from collections import Counter

# Create question bank Q1 to Q100
questions = np.array([f"Q{i}" for i in range(1, 101)])

# 1. Simulate Question Selection
def select_with_replacement():
    return np.random.choice(questions, size=5, replace=True)

def select_without_replacement():
    return np.random.choice(questions, size=5, replace=False)

# 2. Run Simulations
def run_simulations(n=10000, replacement=True):
    selections = []
    for _ in range(n):
        if replacement:
            selections.append(select_with_replacement())
        else:
            selections.append(select_without_replacement())
    return np.array(selections)

with_replacement = run_simulations(10000, replacement=True)
without_replacement = run_simulations(10000, replacement=False)

# Count frequency of each question
freq_with = Counter(with_replacement.flatten())
freq_without = Counter(without_replacement.flatten())

# 3. Compute Expected Unique Questions
def expected_unique_replacement(trials=10000):
    unique_counts = []
    for _ in range(trials):
        selected = select_with_replacement()
        unique_counts.append(len(set(selected)))
    return np.mean(unique_counts)

mean_unique_with = expected_unique_replacement()
print("Expected unique questions (with replacement):", mean_unique_with)
print("Expected unique questions (without replacement):", 5)

# 4. Simulate Conditional Probability
def conditional_probability(trials=100000):
    count_Q1 = 0
    count_Q1_Q2 = 0
    for _ in range(trials):
        selected = select_with_replacement()
        if "Q1" in selected:
            count_Q1 += 1
            if "Q2" in selected:
                count_Q1_Q2 += 1
    return count_Q1_Q2 / count_Q1 if count_Q1 > 0 else 0

cond_prob = conditional_probability()
print("Conditional Probability P(Q2|Q1 selected):", cond_prob)
print("Theoretical value:", 1 - (99/100)**5)  # approximation

# 5. Bayes Theorem Example
# P(E) = 30/100 = 0.3 , P(H) = 0.7
# P(C|E) = 0.8 , P(C|H) = 0.4
# P(C) = P(C|E)*P(E) + P(C|H)*P(H)
P_E, P_H = 0.3, 0.7
P_C_E, P_C_H = 0.8, 0.4
P_C = P_C_E*P_E + P_C_H*P_H
P_E_C = (P_C_E * P_E) / P_C
print("Bayesian probability P(Easy|Correct):", P_E_C)

# 6. Group tests & boxplot
def group_tests():
    group_avgs = []
    for _ in range(10):  # 10 groups
        tests = run_simulations(1000, replacement=True)
        distinct_counts = [len(set(test)) for test in tests]
        group_avgs.append(np.mean(distinct_counts))
    return group_avgs

group_results = group_tests()
plt.boxplot(group_results)
plt.title("Boxplot of Average Number of Distinct Questions per Group")
plt.ylabel("Avg Distinct Questions")
plt.show()

# 7. Co-selection Heatmap
def co_selection_heatmap(trials=10000):
    matrix = np.zeros((100,100))
    for _ in range(trials):
        test = select_without_replacement()
        for i in range(len(test)):
            for j in range(i+1, len(test)):
                qi = int(test[i][1:]) - 1
                qj = int(test[j][1:]) - 1
                matrix[qi][qj] += 1
                matrix[qj][qi] += 1
    plt.figure(figsize=(12,10))
    sns.heatmap(matrix, cmap="viridis")
    plt.title("100x100 Co-selection Frequency Heatmap")
    plt.show()

co_selection_heatmap()

# 8. Biased Sampling
def biased_selection():
    probs = np.ones(100)
    probs[:20] = 3   # bias Q1-Q20
    probs = probs / probs.sum()
    return np.random.choice(questions, size=5, replace=True, p=probs)

def biased_simulation(trials=10000):
    selections = []
    for _ in range(trials):
        selections.extend(biased_selection())
    return Counter(selections)

biased_freq = biased_simulation()
plt.bar(biased_freq.keys(), biased_freq.values())
plt.xticks(rotation=90)
plt.title("Frequency Histogram with Biased Sampling (Q1-Q20 more likely)")
plt.show()