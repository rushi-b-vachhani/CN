


/**************************************************

file: demo_rx.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_rx.c rs232.c -Wall -Wextra -o2 -o test_rx

**************************************************/

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
  int  n,
      cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600,
      abc[50];      /* 9600 baud */

  unsigned char buf[1];

  char mode[]={'8','N','1',0};
int Cport[38];
    
    char comports[38][16]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
                       "/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
                       "/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyUSB0",
                       "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5",
                       "/dev/ttyAMA0","/dev/ttyAMA1","/dev/ttyACM0","/dev/ttyACM1",
                       "/dev/rfcomm0","/dev/rfcomm1","/dev/ircomm0","/dev/ircomm1",
                       "/dev/cuau0","/dev/cuau1","/dev/cuau2","/dev/cuau3",
                       "/dev/cuaU0","/dev/cuaU1","/dev/cuaU2","/dev/cuaU3"};


  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");

    return(0);
  }
    Cport[cport_nr] = open(comports[cport_nr], O_RDWR | O_NOCTTY | O_NDELAY);
  while(1)
  {
    //n = RS232_PollComport(cport_nr, buf, 1);

    n=read(Cport[cport_nr], buf, 1);

    if(n > 0)
    {
      
      printf("received %d bytes: %c\n", n,buf[0]);
    }

#ifdef _WIN32
    //Sleep(100);
#else
    //usleep(100000);  /* sleep for 100 milliSeconds */
#endif
  }

  return(0);
}

