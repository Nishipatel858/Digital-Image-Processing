/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 4
    Program: Mosaic two images
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
void main()
{

int *fp1,*fp2,*fp3;
int pix,scan,npix,i,nscan,mosaicline;
unsigned char *A,*B,*C;
char input1[100],input2[100],output[100];

printf("Enter input image1:");
scanf("%s",&input1);

printf("Enter input image2:");
scanf("%s",&input2);

printf("Enter output image:");
scanf("%s",&output);

printf("Enter npix:");
scanf("%d",&npix);

printf("Enter nscan:");
scanf("%d",&nscan);

printf("Enter from which scan line you want to mosaic(starting from 0):");
scanf("%d",&mosaicline);

printf("new npix nscan is: %d %d\n",2*npix,mosaicline+nscan);

A=(unsigned char*)calloc(npix,sizeof(unsigned char));   //allocate input image1
B=(unsigned char*)calloc(npix,sizeof(unsigned char));   //allocate input image2
C=(unsigned char*)calloc(2*npix,sizeof(unsigned char)); //allocate output image

fp1=open(input1,O_RDONLY);  //open input image1
if(fp1<0)
	printf("Error");

fp2=open(input2,O_RDONLY);  //open input image2
if(fp2<0)
	printf("Error");

fp3=creat(output,0667); //create output image

//Logic for mosaic two images from any scan value
for(scan=0;scan<(mosaicline+nscan);scan++)
{
	if(scan>nscan)
	{
		for(pix=0;pix<npix;pix++)
			C[pix]=0;
	}
	else
	{
		read(fp1,A,npix*sizeof(unsigned char));
		for(pix=0;pix<npix;pix++)
			C[pix]=A[pix];
	}

	if(mosaicline>scan)
	{
		for(pix=npix,i=0;pix<2*npix;pix++)
			C[pix]=0;
	}
	else
	{
		read(fp2,B,npix*sizeof(unsigned char));
		for(pix=npix,i=0;pix<2*npix;pix++)
		{
			C[pix]=B[i];
			i++;
		}
	}
	write(fp3,C,2*npix*sizeof(unsigned char));
}

free(A);
free(B);
free(C);
close(fp1);
close(fp2);
close(fp3);

}





