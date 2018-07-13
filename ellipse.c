/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 3
    Program: Draw and fill ellipse at center of an image
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
void main()
{
	int *fp1,*fp2,npix,nscan,scan,pix,center_x,center_y,a,b,x,y;
	unsigned char *A,*B;
	char inputimage[100],outputimage[100];

	printf("Enter input image:");
	scanf("%s",&inputimage);
	printf("Enter output image:");
	scanf("%s",&outputimage);

	printf("Enter npix:");
	scanf("%d",&npix);

	printf("Enter nscan:");
	scanf("%d",&nscan);

	A=(unsigned char*)calloc(npix,sizeof(unsigned char));   //allocate input image
	B=(unsigned char*)calloc(npix,sizeof(unsigned char));   //allocate output image
	fp1=open(inputimage,O_RDONLY);  //open to read
	fp2=creat(outputimage,0667);    //create for writing

    //find center of image
	center_x=npix/2;
	center_y=nscan/2;

	printf("Enter horizontal radius a:");   //horizontal radius of ellipse
	scanf("%d",&a);

	printf("Enter vertical radius b:"); //vertical radius of ellipse
	scanf("%d",&b);

	//Logic for draw and fill ellipse
	for(scan=0;scan<nscan;scan++)
	{
		read(fp1,A,npix*sizeof(unsigned char));
		y=scan;

		if(scan<=center_y+b && center_y-b<=scan)
		{
		    //equation of an ellipse
			x=(y-center_y)*(y-center_y);
			x=x*(a*a)/(b*b);
			x=(a*a)-x;
			x=sqrt(x);

			for(pix=0;pix<npix;pix++)
			{

				if(center_x-x<=pix && pix<=center_x+x)
				{
					B[pix]=0;
				}
				else
					B[pix]=A[pix];

			}
		}
		else
		{
			for(pix=0;pix<npix;pix++)
			{
				B[pix]=A[pix];
			}
		}
		write(fp2,B,npix*sizeof(unsigned char));
	}

	free(A);
	free(B);
	close(fp1);
	close(fp2);
}


