/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 2
    Program: Zoom an image
*/

#include<stdio.h>
#include<fcntl.h>
#include<math.h>
#include <malloc.h>

void main()
{
	int kount;
	float zoom_factor;
	int *fp1,*fp2,kj,l;
	int i,j,npix,nscan,scan,pix,npix_new,nscan_new,x,y;
	unsigned char *A;
	char inputimage[100],outputimage[100];
	kount=0;

	printf("Given an Input Image: \n");
	scanf("%s",&inputimage);

	printf("Give npix nscan of input image: \n");
	scanf("%d%d",&npix,&nscan);

	printf("Give an Output Image: \n");
	scanf("%s",&outputimage);

	printf("Zoom factor: \n");
	scanf("%f",&zoom_factor);

	printf("npix:%d nscan:%d will be size of %s image\n",(npix),(nscan),inputimage);
	nscan_new=nscan*zoom_factor;
	npix_new=npix*zoom_factor;
	printf("npix:%d nscan:%d will be size of %s image\n",npix_new,nscan_new,outputimage);

	A=(unsigned char*)malloc(npix*sizeof(unsigned char));   //input image allocation

	fp1=open(inputimage,O_RDONLY);  //open file to read input image

	if(fp1<0)
	{
		printf("Error in opening %s \n",inputimage);
		exit(1);
	}

	fp2=creat(outputimage,0777);    //create file for writing output

	kount = 0;
	 unsigned char input[nscan][npix];
	 for(scan=0;scan<nscan;scan++)
	 {

	     read(fp1,A,npix*sizeof(unsigned char));
	     for(pix=0;pix<npix;pix++)
	     {
	       input[scan][pix] = A[pix];   //read input image and put into 2D output array
	     }

	 }
	 unsigned char output[nscan_new][npix_new];
	 //From output image see which point correspond to input image's point
	for(i=0;i<nscan_new;i++)
	{
			for (j=0;j<npix_new;j++)
			{
				x = i/zoom_factor;
				y = j/zoom_factor;
				output[i][j]=input[x][y];
			}
	}
    write(fp2,&output,nscan_new*npix_new*sizeof(unsigned char));    //write whole image

	free(A);    //free input image
    close(fp1); //close image pointer
	close(fp2); //close image pointer
}

