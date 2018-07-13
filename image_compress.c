/*   Name: Nishi R. Patel
     Roll no: 201501076
     Date: 11/4/2018
     Assignment: 6
     Program: JPG compression using DCT and IDCT
*/


#include<stdio.h>
#include<math.h>
#include<fcntl.h>
#include<stdlib.h>
#include<malloc.h>
#define pi 3.142857

int row, col;
row=0;
col=0;
int cnt;
cnt=0;
double arr[512][512];
int img[512][512];


void main()
{
	unsigned char *rimage, *tmpimg;
	char input_name[100], output_name[100];
	int npix, nscan, pix, scan;
	int fp1, fp2, i, j;
	int count, no_blocks, comp_scan, comp_pix, val_scan, val_pix, order, i1, j1;
	float dct_f[order][order];

	printf("Enter input image: \n");
	scanf("%s", input_name);

	printf("Enter npix : \n");
	scanf("%d", &npix);

	printf("Enter nscan: \n");
	scanf("%d", &nscan);

	unsigned char tempimage[nscan][npix];
	int temp[8][8];

	fp1=open(input_name, O_RDONLY); //open for reading image
	fp2=creat("comp_out.raw", 0667);

	tmpimg=(unsigned char *)calloc(npix, sizeof(unsigned char));

	if(fp1<0)
	{
		printf("Error opening image \n");
		exit(1);
	}

	if(fp2<0)
	{
		printf("Error creating image \n");
		exit(1);
	}

	for(scan=0;scan<nscan;scan++)
	{
		read(fp1, &tmpimg[0], npix*sizeof(unsigned char));

		for(pix=0;pix<npix;pix++)
		{
			tempimage[scan][pix]=tmpimg[pix];
		}
	}

	//make 8*8 blocks from image
	comp_scan = nscan/8;
	comp_pix = npix/8;

	no_blocks = comp_scan*comp_pix;
	count = 0;
	i=0;
	j=0;
	order=8;

    while(count<no_blocks)
	{
		val_scan = i*order;
		val_pix = j*order;
		i1=0;
		j1=0;

        for(scan=val_scan;scan<(val_scan+order);scan++)
		{

			for(pix=val_pix;pix<(val_pix+order);pix++)
			{
				temp[i1][j1]=tempimage[scan][pix];
				temp[i1][j1]=temp[i1][j1]-128;
				j1++;
			}
			i1++;
			j1=0;
		}

		dct(temp, order, no_blocks);    //do dct of each block

		if(val_pix == npix-order)
		{
			i++;
			j=0;
		}

		else
		{
			j++;
		}

		count++;

	}
}

//function which calculate DCT of blocks
int dct(int matrix[][8], int order, int block)
{
	int i, j, k, l, r;

	float ci, cj, dct1, sum;

	float dct[order][order];

	float Q[8][8] = {{ 16, 11, 10, 16, 24, 40, 51, 61 },
                         { 12, 12, 14, 19, 26, 58, 60, 55 },
                         { 14, 13, 16, 24, 40, 57, 69, 56 },
                         { 14, 17, 22, 29, 51, 87, 80, 62 },
                         { 18, 22, 37, 56, 68, 109, 103, 77 },
                         { 24, 35, 55, 64, 81, 104, 113, 92 },
                         { 49, 64, 78, 87, 103, 121, 120, 101 },
                         { 72, 92, 95, 98, 112, 100, 103, 99 }};

    float A_vec[64];
    int A_vec_i[64];

    float A[8][8];

    int count, flag=0;
	count=1;
	r=0;

	int n_block;
	n_block = block;
	int track[64];

	for(i=0;i<64;i++)
	{
		track[i]=0;
	}

	double COS[8][8];
	double C[8];

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			COS[i][j]=0;
		}
	}

	for(i=0;i<8;i++)
	{
		C[i]=0;
	}

	for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++)
      COS[i][j] = cos((2 * i + 1) * j * acos(-1) / 16.0);
    if (i) C[i] = 1;
    else C[i] = 1 / sqrt(2);
	}


	for(i=0;i<order;i++)
	{
		for(j=0;j<order;j++)
		{
			sum = 0;
            for (k = 0; k < order; k++) {
                for (l = 0; l < order; l++) {
                    sum += matrix[k][l] * COS[k][i] * COS[l][j];

                }
            }

            sum *= C[i] * C[j] * 0.25;
            dct[i][j] = sum;
		}
	}

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			A[i][j]=0;
		}

	}

	for(i=0;i<order;i++)
	{
		for(j=0;j<order;j++)
		{

			A[i][j]=round(dct[i][j]/Q[i][j]);   //devide by Q matrix then do round
			A[i][j] = A[i][j]*Q[i][j];

		}
	}

	for(i=0;i<64;i++)
	{
		A_vec[i]=0;

	}

	A_vec[0]=A[0][0];

	i=0;
	j=0;

	while(count<63)
	{
		if(flag==0)
		{
			if((i+j)%2==0)
			{
				if(i>=1)
				{
					i--;
					j++;

					A_vec[count]=A[i][j];
					track[count]=(i*10+j);
					count++;

					if(j==order-1 && i+j>=order)
					{
						i++;
						A_vec[count]=A[i][j];
						track[count]=(i*10+j);
						count++;

					}

				}

				else
				{
					j++;
					A_vec[count]=A[i][j];
					track[count]=(i*10+j);
					count++;
				}

			}

			else
			{
				if(j>=1)
				{
					if(i==order-1 && i+j+1>=order)
					{
						j++;
						A_vec[count]=A[i][j];
						track[count]=(i*10+j);
						count++;
					}

					else
					{
						i++;
						j--;

						A_vec[count]=A[i][j];
						track[count]=(i*10+j);
						count++;

					}

				}

				else
				{
					if(i+j+1>=order && i==order-1)
					{
						j++;
						A_vec[count]=A[i][j];
						track[count]=(i*10+j);
						count++;
					}

                    else
					{

						i++;

						A_vec[count]=A[i][j];
						track[count]=(i*10+j);
						count++;

					}
				}

			}
		}

	}

	A_vec[63]=A[7][7];


	track[0]=0;
	track[63]=77;

	for(i=63;i>=0;i--)
	{
		if(A_vec_i[i]>0)
		{
			r=i;
			break;
		}

	}

	printf("\n%d", r);

	int mat[8][8];

	for(i=0;i<order;i++)
	{
		for(j=0;j<order;j++)
		{
			mat[i][j]=0;
		}

	}


	int count_v;
	count_v=0;
	j=0;
	count=0;
	for(i=0;i<order;i++)
	{
		while(count<64)
		{
			if(track[count]<10 && track[count]!=322)
			{
				mat[i][j]=A_vec[count];
				j++;
				track[count]=322;

				if(j==8)
				{
					count_v++;
					count=1;
					j=0;


				}
			}

			if(i==7 && j==7)
			{
				break;
			}

			count++;
		}
	}
	count=0;
	j=0;

	for(i=1;i<order;i++)
	{
		while(count<64 && count_v<8)
		{
			if(track[count]/10 == i)
			{

				mat[i][j]=A_vec[count];
				j++;

				if(j==8)
				{
					count_v++;
					j=0;
				}
			}


			if(i==8 && j==8)
			{
				break;
			}

			count++;
		}

		count=0;
	}

	idct(mat, n_block); //do idct of each block

}

//IDCT function which calculate inverse dct of block
int idct(int matr[][8], int block)
{

	double COS[8][8];
	double C[8];
	int i, j, x, y;
	double idct[8][8];
	int num_blocks;

	num_blocks = block;

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			COS[i][j]=0;
		}
	}

	for(i=0;i<8;i++)
	{
		C[i]=0;
	}

	for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++)
      COS[i][j] = cos((2 * i + 1) * j * acos(-1) / 16.0);
    if (i) C[i] = 1;
    else C[i] = 1 / sqrt(2);
	}


	for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
          double sum = 0;
          for (x = 0; x < 8; x++)
            for (y = 0; y < 8; y++)
              sum += C[x] * C[y] * matr[x][y] * COS[i][x] * COS[j][y];
          sum *= 0.25;
          sum += 128;
          idct[i][j] = sum;
	}

	recon(idct, num_blocks);    //reconstruct image

}

//function for reconstruction of image
void recon(double blk[][8], int n_blk)
{
	int itr;

	int i,j;
	i=0, j=0;

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			arr[row+i][col+j] = blk[i][j];

		}
	}

	if(col+8==512)
	{
		row=row+8;
		col=0;
	}

	else
	{
		col=col+8;
	}

	cnt++;

	if(cnt==4095)
	{
		for(i=0;i<512;i++)
		{
            for(j=0;j<512;j++)
            {
                img[i][j] = round(arr[i][j]);
            }
		}

		imgwrite(img);
	}

}

//write into a new image
void imgwrite(int fin_img[][512])
{
	int fp2;
	unsigned char final[512][512];

	int i,j;


	fp2=creat("compress_img.raw", 0667);

	for(i=0;i<512;i++)
	{
		for(j=0;j<512;j++)
		{

			final[i][j] = fin_img[i][j];

		}
	}

	write(fp2,&final,512*512*sizeof(unsigned char));
}
