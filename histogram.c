/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 4
    Program: find histogram of an image
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
void main()
{

int *fp1,scan,pix,nscan,npix,i,cn[256];
unsigned char *A;
char input[100];
FILE *output;

printf("Enter input image:");
scanf("%s",&input);

printf("Enter npix:");
scanf("%d",&npix);

printf("Enter nscan:");
scanf("%d",&nscan);

A=(unsigned char*)calloc(npix,sizeof(unsigned char));   //allocate input image

fp1=open(input,O_RDONLY);   //open to read
if(fp1<0)
	printf("Error");

//Logic for creating histogram
for(i=0;i<=255;i++)
	cn[i]=0;

for(scan=0;scan<nscan;scan++)
{
	read(fp1,A,npix*sizeof(unsigned char));
	for(i=0;i<=255;i++)
	{
		for(pix=0;pix<npix;pix++)
		{
			if(A[pix]==i)
				cn[i]=cn[i]+1;
		}
	}
}

output = fopen("histogram.txt","w");    //make txt file to write frequency of pixels of an image
if(output == NULL)
	printf("Error while opening \n");
for(i=0;i<=255;i++)
	fprintf(output,"%d \n",cn[i]);  //write histogram values to output file

free(A);
close(fp1);

}
