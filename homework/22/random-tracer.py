import subprocess
import random


addresses = []
for i in range(10):
    num = random.randint(0,9)
    addresses.append(num)

buffer = []

stdout = ''
with open('template.txt', 'r') as f:
    stdout = f.read()
stdout = stdout.format(addresses, 10, 'RANDOM', 3, 10, '', 'False')
print(stdout)

hit = 0
miss = 0

for addr in addresses:
    
    hitmiss = 'MISS'
    replaced = '-'

    if addr in buffer:
        hitmiss = 'HIT '
        hit += 1
    
    elif len(buffer) < 3:
        buffer.append(addr)
        miss += 1
    
    else:
        ei = random.randint(0,2)
        replaced = buffer.pop(ei)
        buffer.append(addr)
        miss += 1
    
    num_space = (3 - len(buffer)) * 3
    spacer = ' ' * num_space
    print('Access: {}  {} {} {}Replaced:{} [Hits:{} Misses:{}]'.format(
        addr, hitmiss, buffer, spacer, replaced, hit, miss
    ))

hitrate = hit / 10 * 100
print('\nFINALSTATS hits:{} misses:{} hitrate:{:.2f}'.format(hit, miss, hitrate))



