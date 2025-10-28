import matplotlib.pyplot as plt
n = [90,950,2500,6900,7900]
time = [0.000002, 0.000014, 0.000036, 0.000063, 0.000081]  
plt.plot(n, time, marker='o')
plt.xlabel("Input size (n)")
plt.ylabel("Time taken (seconds)")
plt.title("Linear Search: Time vs n")
plt.grid(True)
plt.show(block=True)

