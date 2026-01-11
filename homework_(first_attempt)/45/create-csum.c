#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, const char *argv[]){
    FILE *fp, *fpw;
    uint8_t byte;
    uint8_t csum = 0;
    int flag = 1;
    
    // if there is no file name to read...

    
    // set name of output file to ***.csum
    char ofile[256];
    strcpy(ofile, argv[1]);
    strcat(ofile, ".csum");

    // initialize output file
    fpw = fopen(ofile, "w");
    fclose(fpw);
    
    // open files
    fpw = fopen(ofile, "a");
    fp = fopen(argv[1], "rb");
    
    int i;
    while(flag){
        csum = 0;
        for(i = 0; i < 4096; i++){ // calculate 4KB block check sum
            if(fread(&byte, 1, 1, fp)) 
                csum ^= byte;
            else{  // if fread() reads no more byte, then done
                flag = 0;
                break;
            }
        }

        fprintf(fpw, "%d\n", csum);
        printf("%d\n", csum);
    }

    //close files
    fclose(fp);
    fclose(fpw);

    return 0;
}