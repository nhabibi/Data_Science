%Detect bright cars with Multiple Thresholding methods:
[r c p] = size(VROIImage);
%p
temp1 = VROIImage';
temp2 = max(temp1);
temp3 = temp2';
T1 = mean(temp3);
T2 = min(temp3);
% T3 = mean2(T1,T2);
T3 = (T1 + T2) / 2;
% T1
% T2
% T3
image1 = VROIImage;
image2 = VROIImage;
image3 = VROIImage;
%image1:T1
for i=1:1:r
    for j=1:1:c
        if (VROIImage(i,j) <= T1)
            image1(i,j) = 0;
        else
            image1(i,j) = 255;
        end
    end
end
%image2:T2
for i=1:1:r
    for j=1:1:c
        if (VROIImage(i,j) <= T2)
            image2(i,j) = 0;
        else
            image2(i,j) = 255;
        end
    end
end
%image3:T3
for i=1:1:r
    for j=1:1:c
        if (VROIImage(i,j) <= T3)
            image3(i,j) = 0;
        else
            image3(i,j) = 255;
        end
    end
end
% figure(1);
% imshow(image1);
% figure(2);
% imshow(image2);
% figure(3);
% imshow(image3);

% r
% c
% p

%Detect bright cars with Otsu Thresholding methods:
preprocessBright = inline('max(x(:))');
filteredImageBright = nlfilter(VROIImage,[3 3],preprocessBright);
% figure(5);
% imshow(filteredImageBright);
OtsuLevelBright = graythresh(filteredImageBright);
image4 = im2bw(filteredImageBright,OtsuLevelBright);
figure(6);
imshow(image4);

%Detect dark cars with Otsu Thresholding methods:
preprocessDark = inline('min(x(:))');
filteredImageDark = nlfilter(VROIImage,[3 3],preprocessDark);
% figure(7);
% imshow(filteredImageDark);
OtsuLevelDark = graythresh(filteredImageDark);
image5 = im2bw(filteredImageDark,OtsuLevelDark);
%complement image5
for i=1:1:r
    for j=1:1:c
        if (image5(i,j) == 1)
            image5(i,j) = 0;
        else 
            image5(i,j) = 1;
        end
    end
end
figure(8);
imshow(image5);

%Adding Brights & Darks together:
image6 = or(image4,image5);
figure(97);
imshow(image6);

[M,NumberOfCars] = bwlabel(image6,8);
%M
NumberOfCars


























