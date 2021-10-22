import subprocess

page = []
valist = []
seed = 0
cmd = ['python3', 'paging-multilevel-translate.py', '-s', str(seed)]
stdout = subprocess.check_output(cmd).decode()
stdout = stdout.split("\n")
page_index = 0

def vatopa(va, pdbr, page):
    # PD(5bit) | PT(5bit) | offset(5bit)
    pd = (va & 31744) >> 10
    pt = (va & 992) >> 5
    offset = (va & 31)

    pde = page[pdbr][pd]
    pd_valid = (pde & 128) >> 7

    if(not pd_valid):
        return 'Fault'

    ptbr = pde & 127

    pte = page[ptbr][pt]
    pt_valid = (pte & 128) >> 7

    if(not pt_valid):
        return 'Fault'
    
    pfn = pte & 127

    page_address = (pfn << 5) | offset 
    value = page[pfn][offset]
    
    return hex(page_address), hex(value)


for line in stdout:
    
    if(line and line[0] == 'p'):
        colon = line.find(':')
        base = colon + 1
        values = []
        
        for i in range(0, 64, 2):
            byte = int('0x' + line[base + i] + line[base + i + 1], 16)
            values.append(byte)
        
        page.append(values)
        page_index += 1

    if(line and line[0] == 'P'):
        colon = line.find(':')
        left_paren = line.find('(')
        
        pdbr = int(line[colon + 1:left_paren].strip())
    
    if(line and line[0] == 'V'):
        line = line.split()
        valist.append(int('0x' + line[2][:4], 16))

for va in valist:
    print(vatopa(va, pdbr, page))




