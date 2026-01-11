#constants
src = "seed1.txt"
jobs = [
    (8,75),
    (4,25)
]

fh = open(src, "r")

for line in fh:
    line = line.strip()
    int(line)
    

fh.close()