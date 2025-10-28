import matplotlib.pyplot as plt
n = [1000,3000,5000,7000]
time = [ 0.001023, 0.009351, 0.023740,0.045705]  
plt.plot(n, time, marker='o')
plt.xlabel("Input size (n)")
plt.ylabel("Time taken (seconds)")
plt.title("Bubble sort: Time vs n")
plt.grid(True)
plt.show()