#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){
    FILE *fp_src, *fp_csum;
    uint8_t byte;
    uint8_t csum = 0;
    char line[16];
    int flag = 1;
    
    // if there are not enough arguments (source and csum file)
    if(!(argc == 3)){
        printf("Usage: ./check-csum [source] [csum file]\n");
        return 1;
    }

    // open files
    fp_src = fopen(argv[1], "rb");
    fp_csum = fopen(argv[2], "r");
    
    int i;
    while(flag){
        csum = 0;
        for(i = 0; i < 4096; i++){ // calculate 4KB block check sum
            if(fread(&byte, 1, 1, fp_src)) 
                csum ^= byte;
            else{  // if fread() reads no more byte, then done
                flag = 0;
                break;
            }
        }
        
        if((fgets(line, 16, fp_csum) != NULL)){
            byte = 0;
            byte = atoi(line);
            if(byte != csum){
                printf("The file is corrupted!\n");
                fclose(fp_src);
                fclose(fp_csum);
                return 0;
            }
        }

        //printf("matched!\n");

    }

    printf("The file matches with the checksum.\n");

    //close files
    fclose(fp_src);
    fclose(fp_csum);

    return 0;
}