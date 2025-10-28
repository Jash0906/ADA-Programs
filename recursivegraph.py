import matplotlib.pyplot as plt
n = [99, 143, 365]
time = [0.069, 0.483, 3.616]

plt.plot(n, time, marker='o', linestyle='-')
plt.xlabel("Matrix Size (n)")
plt.ylabel("Time Taken (seconds)")
plt.title("Divide and Conquer Matrix Multiplication")
plt.grid(True)
plt.show()
