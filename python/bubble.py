a=[2,4,5,1,6,3,7]
l=len(a)
j=l
print("before sort ",a)
while (j>1):
    for i in range(l-1):
        if a[i]>a[i+1]:
            a[i],a[i+1]=a[i+1],a[i]
    j=j-1
print("after sort ",a)
# print(a)