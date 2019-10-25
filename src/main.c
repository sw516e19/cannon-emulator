#include "stdio.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
 
int main(int argc, char *argv[])
{
    while (1)
    {
        printf("TASK 1\n");
        Sleep(1000);
    }
    return 0;
}