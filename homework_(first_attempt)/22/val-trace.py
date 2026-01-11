import subprocess
import random

def get_addr(line):
    comma = line.find(',')
    hex_addr = '0x' + line[:comma]
    
    return int(hex_addr, 16)

def opt_hitrate(addrs, len_addrs, buff_size):
    buffer = []
    hit = 0
    
    for i in range(len_addrs):

        if addrs[i] in buffer:
            hit += 1
        
        elif len(buffer) < buff_size:
            buffer.append(addrs[i])
        
        else:
            max = 0
            max_index = 0
            for j in range(buff_size):
                count = addrs[i + 1:].count(buffer[j])
                if count > max:
                    max = count
                    max_index = j
                
            buffer.pop(max_index)

            buffer.append(addrs[i])
    
    hitrate = hit / len_addrs * 100
    return hitrate

def fifo_hitrate(addrs, len_addrs, buff_size):
    buffer = []
    hit = 0
    
    for i in range(len_addrs):

        if addrs[i] in buffer:
            hit += 1
        
        elif len(buffer) < buff_size:
            buffer.append(addrs[i])
        
        else:
            buffer.pop(0)
            buffer.append(addrs[i])

    hitrate = hit / len_addrs * 100
    return hitrate

def rand_hitrate(addrs, len_addrs, buff_size):
    buffer = []
    hit = 0
    
    for i in range(len_addrs):

        if addrs[i] in buffer:
            hit += 1
        
        elif len(buffer) < buff_size:
            buffer.append(addrs[i])
        
        else:
            evictee = random.randint(0, buff_size - 1)
            buffer.pop(evictee)
            buffer.append(addrs[i])

    hitrate = hit / len_addrs * 100
    return hitrate

def lru_hitrate(addrs, len_addrs, buff_size):

    buffer = []
    hit = 0
    
    for i in range(len_addrs):

        if addrs[i] in buffer:
            temp = buffer.pop(buffer.index(addrs[i]))
            buffer.append(temp)
            hit += 1
        
        elif len(buffer) < buff_size:
            buffer.append(addrs[i])
        
        else:
            buffer.pop(0)
            buffer.append(addrs[i])

    hitrate = hit / len_addrs * 100
    return hitrate


buffer = []
addresses = []
len_addrs = 0

log_file = 'val_output.txt'

f = open('val_output.txt', 'r')

for line in f:
    line = line.split()
    if line[0] in ['I', 'L', 'S', 'M']:
        addr = get_addr(line[1])
        addr = (addr & int('0xFFFFF000', 16)) >> 12
        addresses.append(addr)
print('Loaded.')

f.close()

len_addrs = len(addresses)
print(len_addrs)

fifo_data = []
lru_data = []
rand_data = []
opt_data = []
output = '|  FIFO  |  LRU  |  RAND  |  OPT  |\n'

for i in range(1, 101, 1):
    hitrate = fifo_hitrate(addresses, len_addrs, i)
    print('FIFO : Done')
    fifo_data.append(hitrate)
    output += '|{:.3f}'.format(hitrate)
    hitrate = lru_hitrate(addresses, len_addrs, i)
    print('LRU : Done')
    lru_data.append(hitrate)
    output += '|{:.3f}'.format(hitrate)
    hitrate = rand_hitrate(addresses, len_addrs, i)
    print('RANDOM : Done')
    rand_data.append(hitrate)
    output += '|{:.3f}'.format(hitrate)
    hitrate = opt_hitrate(addresses, len_addrs, i)
    print('OPT : Done')
    opt_data.append(hitrate)
    output += '|{:.3f}|\n'.format(hitrate)


    
    
with open('data_sheet.txt', 'w') as f:
    f.write(output)


    










