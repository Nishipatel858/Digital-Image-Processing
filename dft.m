
%     Name: Nishi R. Patel
%     Roll no: 201501076
%     Date: 25/3/2018
%     Assignment: 5
%     Program: DFT and swapping of amplitudes of images

clc;

%reading image
img1=imread('subject01.glasses.gif');
img2=imread('subject02.normal');

%dft of image
dft1= fft(img1);
dft2= fft(img2);

%finding amplitude
m1= abs(dft1);
m2= abs(dft2);

%finding phase
p1= angle(dft1);
p2= angle(dft2);

%swapping amplitude
si1= m2.*exp(1j*p1);
si2= m1.*exp(1j*p2);

%inverse dft 
i1= ifft(si1);
i2= ifft(si2);

%inverse dft to image
final1 = uint8(real(i1));
final2 = uint8(real(i2));

%ploting
figure();
imshow(img1);
title('original photo 1');
figure();
imshow(img2);
title('original photo 2');
figure();
imshow(final1);
title('output photo 1(phase of 1,amplitude of 2');
figure();
imshow(final2);
title('output photo 2(phase of 2,amplitude of 1');

