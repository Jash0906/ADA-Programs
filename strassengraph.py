import matplotlib.pyplot as plt

sizes = [99, 143, 365]
times = [0.052, 0.345, 2.280]

plt.plot(sizes, times, marker='o')
plt.xlabel("Input size (n)")
plt.ylabel("Time taken (seconds)")
plt.title("Strassen’s Matrix Multiplication: Time vs n")
plt.grid(True)
plt.show()
