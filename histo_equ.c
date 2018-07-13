/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 25/3/2018
    Assignment: 5
    Program: histogram equalization

*/

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <malloc.h>

void main()
{
	char input_file[100], output_file[100];
	unsigned char *image, *image1, *image2;
	unsigned char *temp;
	FILE *input,*inputimage;
	int pix,npix,scan,nscan,fp1,fp2,fp3,k,fp4,i;

	int hist[256], tt[256], hist1[256];

	float a[256], t[256];

	float sum=0;

	printf("Enter npix nscan: ");		//size of input image
	scanf("%d%d",&npix,&nscan);

	image=(unsigned char *)calloc(npix,sizeof(unsigned char));  //allocate memory to input image
	image1=(unsigned char *)calloc(npix,sizeof(unsigned char)); //allocate memory to output image

	printf("Enter input file name: ");
	scanf("%s",input_file);

	printf("Enter output file name: ");
	scanf("%s",output_file);

	fp1= open(input_file,O_RDONLY); //open input image pointer to read image
	fp2= creat(output_file,0677);   //create output image pointer to write into it

	if(fp1<0)
	{
		printf("error in opening %s \n",input_file);
		exit(1);
	}

	if(fp2<0)
	{
		printf("error in opening %s \n",output_file);
		exit(1);
	}

    for(k=0;k<256;k++)
	{
		hist[k]=0;
		t[k]=0;
		a[k]=0;
		tt[k]=0;
		hist1[k]=0;
	}

    for(scan=0;scan<nscan;scan++)
	{
		read(fp1,&image[0],npix*sizeof(unsigned char));

			for(pix=0;pix<npix;pix++)
			{
				hist[image[pix]]++;		//finding histogram of input image
			}
	}

	for (i = 0; i < 256; ++i)
	{
		sum = hist[i] + sum;
        t[i] = sum;
	}

	for (i = 0; i < 256; ++i)
	{
        t[i] = t[i]/t[255];
        t[i] = t[i] * 255;
		t[i] = round(t[i]);
		tt[i] = (int)t[i];
	}

	inputimage = fopen("old_histogram.txt","w");		//opening old histogram.txt file in write mode
	if(inputimage == NULL)
        printf("Error while opening \n");

	for(k=0;k<256;k++)
	{
		fprintf(inputimage,"%d \n",hist[k]);	//writing data to text file to generate histogram using GNU plot
	}

	close(fp1); //close input image

	fp4= open(input_file,O_RDONLY); //again open input image

    if(fp4<0)
	{
		printf("error in opening %s \n",input_file);
		exit(1);
	}

	for(scan=0;scan<nscan;scan++)
	{
		read(fp4,&image[0],npix*sizeof(unsigned char));

		for (pix = 0; pix < npix; ++pix)
		{
			image1[pix] = tt[image[pix]];   //assign new gray values to output image
		}

		write(fp2,image1,npix*sizeof(unsigned char));
	}

	free(image1);
	free(image);
	close(fp2);

	image2=(unsigned char *)calloc(npix,sizeof(unsigned char));
	fp3= open(output_file,O_RDONLY);
	if(fp3<0)
	{
		printf("error in opening %s \n",output_file);
		exit(1);
	}
	for(scan=0;scan<nscan;scan++)
	{
		read(fp3,&image2[0],npix*sizeof(unsigned char));

			for(pix=0;pix<npix;pix++)
			{
				hist1[image2[pix]]++;		//finding histogram of output image
			}
	}

    input = fopen("new_histogram.txt","w");		//opening new histogram.txt file in write mode
	if(input == NULL)
		printf("Error while opening \n");

	for(k=0;k<256;k++)
	{
		fprintf(input,"%d \n",hist1[k]);	//writing data to text file to generate histogram using GNU plot
    }

	close(fp4);
    free(image2);
	close(fp3);
}
