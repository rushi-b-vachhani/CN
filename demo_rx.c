
/**************************************************

file: demo_rx.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_rx.c rs232.c -Wall -Wextra -o2 -o test_rx

**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "checksum_algo.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"

int main()
{
	int i, n,
		cport_nr = 0,  /* /dev/ttyS0 (COM1 on windows) */
		bdrate = 9600; /* 9600 baud */

	unsigned char buf[4096];
	int check;
	char mode[] = {'8', 'N', '1', 0};
	char str2[512];

	if (RS232_OpenComport(cport_nr, bdrate, mode))
	{
		printf("Can not open comport\n");

		return (0);
	}

	while (1)
	{
		n = RS232_PollComport(cport_nr, buf, 4095);

		if (n > 0)
		{
			buf[n] = 0; /* always put a "null" at the end of a string! */

			strcpy(str2, buf);
			check = check_xor(str2);
			if (check != 0)
			{
				RS232_cputs(cport_nr, "t");
			}
			else
			{
				RS232_cputs(cport_nr, "f");
				printf("***Failed***");
			}
			
			printf("received %i bytes: %s\n", n, (char *)buf);
		}

#ifdef _WIN32
		Sleep(100);
#else
		usleep(100000); /* sleep for 100 milliSeconds */
#endif
	}

	return (0);
}
