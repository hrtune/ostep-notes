import subprocess

i = 1

while(True):
    print('({})'.format(i))
    subprocess.run(['./vector-deadlock', '-n', '20', '-l', '20', '-d', '-v'])
    i += 1
