/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 1
    Program: gradient of grayscale intensities
*/

#include<stdio.h>
#include<math.h>
void main()
{
	unsigned char *image;   //output image variable
	char out_file[100];
	int pix,npix,scan,nscan,*fp1,cnt,b;
	float a;

	printf("enter npix & nscan:");
	scanf("%d%d",&npix,&nscan);
	printf("npix nscan are %d %d \n",npix,nscan);

	image=(unsigned char *)calloc(npix,sizeof(unsigned char));  //dynamically allocate size to output image

	printf("enter output file\n");
	scanf("%s",out_file);
	printf("output file is %s\n",out_file);

	fp1=creat(out_file,0666);

	if(fp1<0)
	{
	 printf("Error");
	 exit(1);
	}

	/* Logic for shading from black to white */
	a=(float)nscan/256;
	b=nscan/256;
	if(a>b)     //adjust size of shading if any nscan is given
		b=b+1;

	for(cnt=-1,scan=0;scan<nscan;scan++)
	{
		if((scan%b)==0)
			cnt++;
		for(pix=0;pix<npix;pix++)
		{
			image[pix]=cnt;

		}
		write(fp1,&image[0],npix*sizeof(unsigned char));    //write line by line till nscan
	}
	free(image);    //free image space
	close(fp1); //close image pointer
}
