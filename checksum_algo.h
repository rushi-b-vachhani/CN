#include<stdio.h>
#include<stdlib.h>

int xor_gen(char data[])
{
	int i;
	int res = 0;
	for(i=0;data[i]!='\0';i++)
	{
		res = res^data[i];
	}
	data[i] = res;
	data[i+1] = '\0';
	
	return res;	
}


int xor_check(char data[])
{
	int i;
	int res = 0;
	for(i=0;data[i]!='\0';i++)
	{
		res = res^data[i];
	}
	
	return res;
}

/*
int weighted_xor_gen(char data[])
{
	int i;
	int res = 0;
	for(i=0;data[i]!='\0';i++)
	{
		res = res^(data[i]*(i+1));
	}
	data[i] = res*(i+1);
	data[i+1] = '\0';
	
	return res;
}


int weighted_xor_check(char data[])
{
	int i;
	int res = 0;
	for(i=0;data[i]!='\0';i++)
	{
		res = res^(data[i]*(i+1));
	}
	
	if(res==0)
		return 1;
	else
		return 0;
}
*/
