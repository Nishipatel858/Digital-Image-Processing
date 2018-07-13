/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 4
    Program: Shear an image
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>

#define PI 3.14

void main(){
	int input_file, output_file;
	unsigned char *input_image, *output_image;
	int npix, nscan, scan, pix, pix1, rotation,npix1;
	char input[100], output[100];

	printf("Enter values of npix and nscan\n");
	scanf("%d %d", &npix, &nscan);

	printf("Enter Input file\n");
	scanf("%s", input);

	printf("Enter Output file\n");
	scanf("%s", output);

	input_file=open(input, O_RDONLY);   //open to read

	if(input_file<0){
		printf("Error Opening file!\n");
		exit(1);
	}

	output_file=creat(output, 0666);    //create for writing

	if(output_file<0){
		printf("Error Creating file!\n");
		exit(1);
	}

	printf("Enter Shear angle:\n");   //shear angle
	scanf("%d", &rotation);

	printf("After rotation");

	float angel=(rotation*PI)/180;  //angle in radian for less than 90 degree
	float angel1=((180-rotation)*PI)/180;   //angle in radian for greater than 90 degree
	int space[nscan];
	int i=0;
	int nscan1=nscan;
	int nscan2=0;

	//Logic for shearing an image
	if(rotation<=90)
	{
		for(i=0; i<nscan; i++)
		{
			space[i]=round(nscan1/tan(angel));
			nscan1--;
		}
		npix1=npix+space[0];
	}
	else
	{
		for(i=0; i<nscan; i++)
		{
			space[i]=round(nscan2/tan(angel1));
			nscan2++;
		}
		npix1=npix+space[nscan-1];
	}


	input_image=(unsigned char*)malloc(npix*sizeof(unsigned char)); //allocate input image
	output_image=(unsigned char*)malloc(npix1*sizeof(unsigned char));   //allocate output image using new npix

	printf("New Size of Image is %d %d", npix1, nscan);

	for(scan=0; scan<nscan; scan++){
		read(input_file, input_image, npix*sizeof(unsigned char));

		for(pix=0; pix<npix1; pix++){
			if(pix<space[scan] || pix>npix+space[scan]){
				output_image[pix]=0;
			}
			else{
				output_image[pix]=input_image[pix-space[scan]];
			}
		}
		write(output_file, output_image, npix1*sizeof(unsigned char));
	}
}
