#include<stdio.h>
#include<stddef.h>

typedef struct address{
    char varable1[100];
    int varable2;
    long varable3;
} address;

address addr1, addr2;

int main(int argc, char const *argv[])
{
    /* code */
    extern address addr1,addr2;
    address* poniter = (typeof(&addr1))((void*)(char*)&addr1.varable2-offsetof(address, varable2));
    printf("%d\n", poniter->varable2);
    return 0;
}
