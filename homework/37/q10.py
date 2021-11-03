import subprocess

out = '35,'

for i in range(7, 100):
   out += str(i % 12) + ','

out = out[:-1]

subprocess.run(['python3', 'disk.py', '-p', 'SATF', '-a', out, '-G'])