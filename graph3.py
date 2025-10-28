import matplotlib.pyplot as plt
n = [50,300,2500,5000,7700]
time = [0.000000, 0.000016, 0.000022, 0.000040,0.000057]  
plt.plot(n, time, marker='o')
plt.xlabel("Input size (n)")
plt.ylabel("Time taken (seconds)")
plt.title("Linear Search: Time vs n")
plt.grid(True)
plt.show()