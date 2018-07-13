/*
    Name: Nishi R. Patel
    Roll no: 201501076
    Date: 8/2/2018
    Assignment: 2
    Program: Rotate an image
*/

#include<stdio.h>
#include<malloc.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))
void main()
{
  int fp1,fp2,a;
  float theta;
  char input_image_file[100],output_image_file[100];
  unsigned char * image;
  int npix,nscan,pix,scan,i1,i2;
  int nscan_new,npix_new,p1x,p1y,p2x,p2y,p3x,p3y,p4x,p4y,left,right,up,down;

  printf("Give input image name: \n");
  scanf("%s",input_image_file);
  printf("Give size of image(npix nscan): \n");
  scanf("%d%d",&npix,&nscan);

  image=(unsigned char *)calloc(npix,sizeof(unsigned char));    //input image allocation

  printf("Input Image is %s npix nscan %d %d \n",input_image_file,npix,nscan);

  printf("Give output image name: \n");
  scanf("%s",output_image_file);

  printf("Enter the angle(in degrees) by which you want to rotate image in anticlockwise direction: \n");
  scanf("%f",&theta);
  theta=((((float)22.0)/7)*theta)/180;  //convert it to radian

  fp1= open(input_image_file,O_RDONLY); //open file for reading
  if (fp1<0)
  {
    printf("Error in opening %s image \n",input_image_file);
    exit(1);
  }
  fp2=creat(output_image_file,0667);    //create file for writing
  if (fp2<0)
  {
    printf("Error in creating output %s image\n",output_image_file);
    exit(1);
  }


   unsigned char image_in[npix][nscan];
   for(scan=0;scan<nscan;scan++)
   {

     read(fp1,image,npix*sizeof(unsigned char));
     for(pix=0;pix<npix;pix++)
     {
       image_in[scan][pix] = image[pix];    //read input image and put into 2D output array
     }

   }

   //calculate 4 end points
   p1x=((0-(npix/2))*cos(theta)-(0+(nscan/2))*sin(theta));
   p2x=((npix-(npix/2))*cos(theta)-(0+(nscan/2))*sin(theta));
   p3x=((npix-(npix/2))*cos(theta)-(-nscan+(nscan/2))*sin(theta));
   p4x=((0-(npix/2))*cos(theta)-(-nscan+(nscan/2))*sin(theta));

   p1y=(((0-(npix/2))*sin(theta))+(0+(nscan/2))*cos(theta));
   p2y=(((npix-(npix/2))*sin(theta))+(0+(nscan/2))*cos(theta));
   p3y=(((npix-(npix/2))*sin(theta))+(-nscan+(nscan/2))*cos(theta));
   p4y=(((0-(npix/2))*sin(theta))+(-nscan+(nscan/2))*cos(theta));

   left=min(p1x,min(p2x,min(p3x,p4x)));
   right=max(p1x,max(p2x,max(p3x,p4x)));
   npix_new = right-left+1;

   down=min(p1y,min(p2y,min(p3y,p4y)));
   up=max(p1y,max(p2y,max(p3y,p4y)));
   nscan_new=up-down+1;

   unsigned char image_out[npix_new][nscan_new];
   int xnew,ynew,xrot,yrot;
   printf("Size of new image--> nscan=%d npix=%d\n",nscan_new,npix_new );

   //Logic for rotation
   for(scan=(up-(nscan/2));scan>=(down-(nscan/2));scan--)
   {
     for(pix=(left+(npix/2));pix<=(right+(npix/2));pix++)
     {
        xnew=pix-(npix/2);
        ynew=scan+(nscan/2);
        xrot=(xnew*cos(theta)+ynew*sin(theta))+(npix/2);
        yrot=(-(xnew*sin(theta))+ynew*cos(theta))-(nscan/2);

        if(xrot<npix && xrot>=0 && yrot>-nscan && yrot<=0)
        {
          image_out[-scan+(up-(nscan/2))][pix-(left+(npix/2))]=image_in[-yrot][xrot];
        }
        else
        {
          image_out[-scan+(up-(nscan/2))][pix-(left+(npix/2))]=0;
        }
     }
   }

   write(fp2,image_out,(npix_new)*(nscan_new)*sizeof(unsigned char));   //write an output image

   close(fp1);
   close(fp2);


}
