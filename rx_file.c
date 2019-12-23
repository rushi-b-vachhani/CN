
/**************************************************

file: demo_rx.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_rx.c rs232.c -Wall -Wextra -o2 -o rx_file

**************************************************/

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"
#include <stdio.h>

int main()
{
    int i = 0, n,
        cport_nr = 0,  /* /dev/ttyS0 (COM1 on windows) */
        bdrate = 9600; /* 9600 baud */

    unsigned char buf[4096];

    char mode[] = {'8', 'N', '1', 0};
    char data[500];
    FILE *fp;
    fp = fopen("received1.txt", "w");

    if (RS232_OpenComport(cport_nr, bdrate, mode))
    {
        printf("Can not open comport\n");
        return (0);
    }

    char c;
    while (1)
    {
        n = RS232_PollComport(cport_nr, buf, 1);
        if (n != 1)
        {
            continue;
        }

        c = buf[0];
        if (c == EOF)
        {
            break;
        }

        fputc(buf[0], fp);
        printf("%c", buf[0]);
        i++;
        // if (i == 1024)
        // {
        //     #ifdef _WIN32
        //         Sleep(100);
        //     #else
        //         usleep(100000); /* sleep for 100 milliSeconds */
        //     #endif
        //     i=0;
        // }
    }

    fclose(fp);
    return (0);
}