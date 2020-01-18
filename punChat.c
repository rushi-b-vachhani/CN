#include <stdlib.h>
#include <stdio.h>
#include "rs232.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main()
{
	int cport_nr = 0;  /* /dev/ttyS0 (COM1 on windows) */
	int bdrate = 9600; /* 9600 baud */

	char mode[] = {'8', 'N', '1', 0};

	if (RS232_OpenComport(cport_nr, bdrate, mode))
	{
		printf("Can not open comport\n");
		return (0);
	}

	char str1[4096];
	int i = 0, n;

	unsigned char buf[4096];

	int pid = fork();

	// Tx Side
	if (pid == 0)
	{
		while (1)
		{
			printf("\nMessage to be sent: ");
			int x=0;
			int count=0;
			char ch;
			while(1)
			{
				scanf("%c",&ch);
				if(ch=='*')count++;
				else count=0;

				str1[x++] = ch;
				if(count==3)break;
			}
			str1[x-3] = '\0';
			//printf("String is :%s\n",str1);
			fflush(0);
			RS232_cputs(cport_nr, str1);
			
			#ifdef _WIN32
			Sleep(100);
			#else
			usleep(100000); /* sleep for 100 milliSeconds */
			#endif
		}
	}

	// Rx Side
	else
	{
		while (1)
		{
			n = RS232_PollComport(cport_nr, buf, 4095);

			if (n > 0)
			{
				buf[n] = 0; /* always put a "null" at the end of a string! */

				printf("\n\t\t\tReceived : %s\n",(char *)buf);
			}
			
			// Increased the sleep time to allow long strings
			#ifdef _WIN32
			Sleep(500);
			#else
			usleep(500000); /* sleep for 500 milliSeconds */
			#endif
			
		}
	}

	return 0;
}
