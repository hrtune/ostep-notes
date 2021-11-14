d = "104 101 108 108 111 10".split()
d = [int(x) for x in d]
s1 = 0
s2 = 0
a = 0
xor = 0

for e in d:
    a = a + e
    xor = xor ^ e

a = a % 256

for i in range(len(d)):
    s1 = (s1 + d[i]) % 255
    s2 = (s1 + s2) % 255

print("Add:", a)
print("Xor:", xor)
print("Fletcher: {},{}".format(s1,s2))