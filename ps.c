#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int
main(int argc, char *argv[]){
    char * addr = sbrk(0);
    sbrk(PGSIZE);
    *addr = 100;
    mprotect(addr,1);
    int num = fork();
    if(num == 0){
        printf(1,"Protect: %d \n", *addr);
        munprotect(addr,1);
        *addr = 5;
        printf(1, "Unprotect: %d \n", *addr);
        exit();
    }
    else if(num>0){
        wait();
        printf(1, "trap \n");
        *addr = 5;
        exit();
    }
    exit();
}
