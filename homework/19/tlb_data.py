import subprocess

i = 1

output = ""

while(i <= 4096):

    print(i)
    
    proc = subprocess.Popen(['./tlb', str(i)],stdout=subprocess.PIPE)

    #print(proc.stdout.readline().decode())

    output += proc.stdout.readline().decode()

    i *= 2


f = open("data.txt", "w")

f.write(output)

f.close()