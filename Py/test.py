import numpy as np
import matplotlib.pyplot as plt

# 两数之和
nums = (2,7,11,15)
target = 9

def fun1(nums, target):
    hashmap = {}
    for ind,num in enumerate(nums):
        hashmap[num] = ind

    for i,num in enumerate(nums):
        j = hashmap.get(target - num)
        if j is not None and i!=j:
            return [i,j]

def fun2(nums, target):
    lens = len(nums)
    for i in range(lens):
        for j in range(i+1,lens):
            if nums[i] == target- nums[j] and i!=j:
                return [i,j]


#sigmod函数
def sigmod(z):
    return 1/(1+np.exp(-z))

def fun3():
    x = np.linspace(-10,10,100)
    y = sigmod(x)
    plt.plot(x,y)
    plt.show()

# test
x = 2 * np.random.rand(100, 1)
y = 4 + 3 * x + np.random.randn(100, 1)
plt.plot(x,y,"ro")
#plt.show()
#print(x)
################################################
sum = 0
for i in range(1,10):
  sum += (1.045**i)-1

sum = 10*(1.045**23)+0.22*23
print("%f"%sum)








