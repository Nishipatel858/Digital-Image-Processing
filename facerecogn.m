%     Name: Nishi R. Patel
%     Roll no: 201501076
%     Date: 11/4/2018
%     Assignment: 6
%     Program: Face recognition using SVD 

clc;
clear all;

cd 'E:\Nishi_6thsem\DIP\Assignments\facerecognition\yalefaces'; %set current folder
imagefiles = dir('E:\Nishi_6thsem\DIP\Assignments\facerecognition\yalefaces');   
nfiles = length(imagefiles);    % Number of images in yalefaces folder

for l=1:nfiles-2
    for j = 1:6768  %assume raw=72 column=94 for each image  
        L(j,l)=0;
    end
end

k=1;
for ii=3:nfiles
   currentfilename = imagefiles(ii).name;
   currentimage = imread(currentfilename);
   currentimage = imresize(currentimage,[72 94]);   %resize big image into 72*94 size image
   nraw = length(currentimage(:,1));
   ncol = length(currentimage(1,:));
   cnt=1;
   for j=1:ncol
       for i = 1:nraw
           f(cnt) =  currentimage(i,j);
           cnt = cnt+1;
       end
   end
   f_t = transpose(f);  %make each image matrix a column vector
   L(:,k) = f_t(:); %make L matrix as each column represents one image vector
   k = k+1;
 end

[U,S,V]=svd(L); %find svd of L matrix

% input Image name
inputfile = 'nishi.happy';      
currentimage = imread(inputfile);
currentimage = imresize(currentimage,[72 94]);  %resize big input image into 72*94 size image
nraw = length(currentimage(:,1));
ncol = length(currentimage(1,:));
cnt=1;
for j=1:ncol
       for i = 1:nraw
           f(cnt) =  currentimage(i,j);
           cnt = cnt+1;
       end
end
g = transpose(f);   %make input image matrix a column vector
for i=1:ncol
    gu(:,i)=double(g).*double(U(:,i));  %multiply input image to columns of U matrix
end 

imagefiles = dir('E:\Nishi_6thsem\DIP\Assignments\facerecognition\yalefaces');
for ii=3:nfiles
    for i = 1:ncol
         fu(:,i)= double(L(:,ii-2)).*double(U(:,i));    %multiply test images to columns of U matrix
    end
    x  = fu-gu; %find error or difference of input and test image
    nx(ii-2)=norm(x);   %take norm of error

end

%find minimum error
mi=nx(1);
for i=1:length(nx)
    if(nx(i)<=mi)
        mi=nx(i);
        j=i;
    end
end
fprintf('%s is similar to %s ',inputfile,imagefiles(j+2).name);
imshow(inputfile);
title(inputfile);
figure;
imshow(imagefiles(j+2).name);
title(imagefiles(j+2).name);

