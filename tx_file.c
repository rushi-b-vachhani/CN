#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h" 
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"

int main()
{
    int i = 0,
        cport_nr = 0,  /* /dev/ttyS0 (COM1 on windows) */
        bdrate = 9600; /* 9600 baud */

    char mode[] = {'8', 'N', '1', 0};

    if (RS232_OpenComport(cport_nr, bdrate, mode))
    {
        printf("Can not open comport\n");

        return (0);
    }

    char filepath[] = "gpl.txt";
    printf("Sending %s\n", filepath);
    FILE *fp = fopen("gpl.txt", "r+");
    if (fp == NULL)
        printf("Error in opening a file\n");
    i=0;
    char c = fgetc(fp); 
    while (c != EOF) 
    {  
        int fail = RS232_SendByte(cport_nr,c);
        if(fail == -1)
            printf("Error");
        c = fgetc(fp);
        i++;
        if(i==2048)
        {
            // fflush(0);
            #ifdef _WIN32
                Sleep(1000);
            #else
                usleep(1000000);  /* sleep for 1 Second */
            #endif
            i=0;
        } 
    } 
    RS232_SendByte(cport_nr,EOF);
    i++;
    return (0);
}
