'''
#调和级数
sum = 0
cnt = 0

while(sum < 5):
    cnt = cnt+1
    sum += 1/(cnt)
    print(sum)

print("cnt = %d" % cnt)
'''
#放麦子
sum = 0
a = 1
for i in range(1,65):
    sum += a
    a = a*2
print(sum)

#放麦子等比数列求和
import math
a = 1
q = 2
n = 64
#sum = (a * (1 - math.pow(q,n)))/(1 - q)
sum = (a * (1 - q**n))/(1 - q)
print(sum)

