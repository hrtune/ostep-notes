# To make stats about scheduling windows.

import subprocess

cmd = 'python3 disk.py -A 1000,-1,0 -p SATF -w 1 -c'.split()


for i in range(1, 1001):
    cmd[-2] = str(i)
    proc = subprocess.Popen(cmd,stdout=subprocess.PIPE)
    for line in proc.stdout:
        line = line.decode()
        if line[0] == 'T':
            line_totals = line.split()
            total = line_totals[-1]
            total = total[total.find(':') + 1 :]
            print(i,total)
