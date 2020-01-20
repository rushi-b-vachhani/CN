
/**************************************************

file: demo_tx.c
purpose: simple demo that transmits characters to
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_tx.c rs232.c -Wall -Wextra -o2 -o test_tx

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
  int i=0,
      cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600;       /* 9600 baud */

  char mode[]={'8','N','1',0};

  char userinput[512],transmitted[512];
  scanf("%[^\n]",userinput);

  strcpy(transmitted, userinput);
  xor_gen(transmitted);

  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");
    return(0);
  }

 
  RS232_cputs(cport_nr, transmitted);

  printf("sent: %30s | [%s]\n", transmitted,userinput);
  

  // Acknowledgement Checking
  /*
  char buf[10];
  int n = RS232_PollComport(cport_nr, buf, 4096);
  if(n > 0)
  {
    buf[n] = 0;
  }
  if(buf[0]=='y')
    print("True")
  */
 
  return(0);
}

