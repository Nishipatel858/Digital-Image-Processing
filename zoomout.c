/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 2
    Program: Reduce image dimensions(Zoomout an image)
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <fcntl.h>

void main()
{
unsigned char *A,*B;
int zoom_out_factor;
char inputimage[100],outputimage[100];
int npix,scan,nscan,*fp1,*fp2,i,j,l,k,h,b;
float *sum,*average;

printf("Enter input image:");
scanf("%s",&inputimage);
printf("Enter output image:");
scanf("%s",&outputimage);

printf("Enter npix:");
scanf("%d",&npix);
printf("Enter zoom out factor:");
scanf("%d",&zoom_out_factor);

nscan=npix;

printf("New npix nscan are:%d %d\n",npix/zoom_out_factor,nscan/zoom_out_factor);

A=(unsigned char*)malloc(npix*sizeof(unsigned char));
B=(unsigned char*)malloc(npix/zoom_out_factor*sizeof(unsigned char));

//for concept of averaging pixel values
sum=(float *)malloc(npix/zoom_out_factor*sizeof(float));
average=(float *)malloc(npix/zoom_out_factor*sizeof(float));

fp1=open(inputimage,O_RDONLY);  //open to read
fp2=creat(outputimage,0777);    //create output file

//Logic for zoom out by averaging pixel values
for(scan=0;scan<nscan/zoom_out_factor;scan++)
{
	for(b=0;b<npix/zoom_out_factor;b++)
		sum[b]=0;
	for(i=0;i<zoom_out_factor;i++)
	{
		read(fp1,A,npix*sizeof(unsigned char));
		h=0;
		for(j=0;j<npix/zoom_out_factor;j++)
		{
			for(l=0;l<zoom_out_factor;l++)
			{
				sum[j]=sum[j]+A[h];
				h++;
			}
		}
	}
	for(k=0;k<npix/zoom_out_factor;k++)
	{
		average[k]=sum[k]/(zoom_out_factor*zoom_out_factor);
		B[k]=average[k];
	}
	write(fp2,B,npix/zoom_out_factor*sizeof(unsigned char));    //write an image
}

free(A);
free(B);
close(fp1);
close(fp2);
}
