import matplotlib.pyplot as plt
n = [700,5000,9000,15000,55000]
time = [ 0.000028, 0.000074, 0.000082,0.000127,0.000433 ]  
plt.plot(n, time, marker='o')
plt.xlabel("Input size (n)")
plt.ylabel("Time taken (seconds)")
plt.title("Binary Search: Time vs n")
plt.grid(True)
plt.show()
