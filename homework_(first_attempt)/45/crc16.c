#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define POLY 0x8005

void shift(uint16_t *buff){
    if(buff[1] & 0x8000){
        buff[0] = buff[0] << 1 | 1;
        buff[1] = buff[1] << 1;
    }
    else{
        buff[0] = buff[0] << 1;
        buff[1] = buff[1] << 1;
    }
}

size_t read16(uint16_t *buff, FILE *fp){
    uint16_t byte, byte2;
    size_t size;
    if(fread(&byte, 1, 1, fp)){
        if(fread(&byte2, 1, 1, fp)){
            *buff = (byte << 8) | byte2;
            return 2;
        } else{
            *buff = byte << 8;
            return 1;
        }
    }
    return 0;
}

int main(int argc, const char *argv[]){
    uint16_t *buff = malloc(sizeof(uint16_t) * 2);
    unsigned char byte;
    int shift_count = 0;
    size_t size;
    uint32_t rest, poly;
    FILE *fp;

    fp = fopen(argv[1], "rb");
    read16(buff, fp);
    while(1){
        size = read16(buff + 1, fp);
        if(size == 1){
            shift_count = 0;
            while(shift_count < 8){
                if(buff[0] & 0x8000){
                    buff[0] = buff[0] ^ POLY;
                }
                shift(buff);
                shift_count++;
                //printf("%x %x\n", buff[0], buff[1]);
            }
        } else if(size == 0){
            break;
        }
        //printf("%x\n", buff[1]);
        shift_count = 0;
        while(shift_count < 16){
            if(buff[0] & 0x8000){
                buff[0] = buff[0] ^ POLY;
            }
            shift(buff);
            shift_count++;
            //printf("%x %x\n", buff[0], buff[1]);
        }
    }
    
    rest = buff[0] << 16;

    shift_count = 0;
    poly = POLY << 16;
    while(rest > POLY){
        if(rest & (0x80000000 >> shift_count)){
            rest = rest ^ poly;
        }
        poly = poly >> 1;
        shift_count++;
        //printf("%x\n", rest);
    }
    

    printf("%x\n", rest);
    fclose(fp);
}