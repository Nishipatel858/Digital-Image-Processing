/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 1
    Program: Create chessboard image
*/

#include<stdio.h>
#include<math.h>
void main()
{
	unsigned char *image;   //output image variable
	char out_file[100];
	int pix,npix,scan,nscan,*fp1,i,k,j;

	printf("enter npix & nscan:");
	scanf("%d%d",&npix,&nscan);
	printf("npix nscan are %d %d \n",npix,nscan);

	image=(unsigned char *)calloc(npix,sizeof(unsigned char));  //dynamically allocate size to output image

	printf("enter output file\n");
	scanf("%s",out_file);
	printf("output file is %s\n",out_file);

	fp1=creat(out_file,0666);   //create file to write into it

	if(fp1<0)   //if some error in creating a file
	{
	 printf("Error");
	 exit(1);
	}

	/* Logic of a chessboard */
	for(j=0;j<4;j++)
	{
		for(scan=0;scan<nscan/4;scan++)
		{
			i=0;
			k=0;
			if(scan<=nscan/8)
			{

				while(i!=4)
				{
					for(pix=0;pix<(npix/8);pix++)
					{
						image[k]=255;
						k++;
					}
					for(pix=0;pix<(npix/8);pix++)
					{
						image[k]=0;
						k++;
					}
					i++;
				}
				write(fp1,&image[0],npix*sizeof(unsigned char));    //write as white,black and so on...
			}
			else
			{
				while(i!=4)
				{
					for(pix=0;pix<(npix/8);pix++)
					{
						image[k]=0;
						k++;
					}
					for(pix=0;pix<(npix/8);pix++)
					{
						image[k]=255;
						k++;
					}
					i++;
				}
				write(fp1,&image[0],npix*sizeof(unsigned char));    //write as black,white and so on...
			}
		}
	}

	free(image);    //free image space
	close(fp1); //close image pointer
}
