import subprocess

#alist = ['0','6','30', '7,30,8', '10,11,12,13']
alist = ['7,30,8']
slist = ['2', '4', '8', '10', '40', '0.1']
rlist = ['0.1', '0.5', '0.01']


output = ''

for a in alist:
    for s in slist:
        for r in rlist:
            output += '( -a {} -S {} -R {})\n'.format(a,s,r)
            output += subprocess.check_output(['python3', 'disk.py', '-a', a, '-S', s, '-R', r, '-c']).decode()
            output += '\n'

f = open('q3.txt', 'w')
f.write(output)
f.close()