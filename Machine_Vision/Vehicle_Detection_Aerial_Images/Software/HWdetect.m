% %1- apply Thresholding:

%Method 1 : in most cases, produces worse results
% m1 = mean(HWoriginalImage);
% m = mean(m1);
% mid = m/2;
% [r c] = size(HWoriginalImage);
% for i=1:1:r
%     for j=1:1:c
%         if (HWoriginalImage(i,j) >= mid  &  HWoriginalImage(i,j) <= m)
%             thresholdedImage(i,j) = 0;
%         else 
%             thresholdedImage(i,j) = 255;
%         end
%     end
% end
% figure(199);
% imshow(thresholdedImage);

%Method 2 : in most cases, produces better results
temp1 = HWoriginalImage';
temp2 = mean(temp1);
T = min(temp2);
thresholdedImage = HWoriginalImage;
[r c] = size(HWoriginalImage);
for i=1:1:r
    for j=1:1:c
        if (HWoriginalImage(i,j) < T)
            thresholdedImage(i,j) = 0;
        else 
            thresholdedImage(i,j) = 255;
        end
    end
end
figure(199);
imshow(thresholdedImage);

%2- Morphlogical operations:
BthresholdedImage = im2bw(thresholdedImage);
%2-1- clean: Removes isolated pixels (individual 1's that are surrounded by 0's
cleanedBthresholdedImage = bwmorph(BthresholdedImage,'clean');
figure(198);
imshow(cleanedBthresholdedImage);
% if (cleanedBthresholdedImage == cleanedBthresholdedImage)
%     mes = 'equal!';
%     mes
% end;

%2-2- majority: Sets a pixel to 1 if five or more pixels in its 3-by-3 neighborhood are 1's; otherwise, it sets the pixel to 0.
majoredCleanedBthresholdedImage = bwmorph(cleanedBthresholdedImage,'majority');
figure(197);
imshow(majoredCleanedBthresholdedImage);
%2-3- fill: Fills isolated interior pixels (individual 0's that are surrounded by 1's)
filledMajoredCleanedBthresholdedImage = bwmorph(majoredCleanedBthresholdedImage,'fill');
figure(196);
imshow(filledMajoredCleanedBthresholdedImage);
%2-4- erode
erodedFilledMajoredCleanedBthresholdedImage = bwmorph(filledMajoredCleanedBthresholdedImage,'erode');
figure(195);
imshow(erodedFilledMajoredCleanedBthresholdedImage);
%intensity image
mResult = erodedFilledMajoredCleanedBthresholdedImage;
intensityImage = mResult;
for i=1:1:r
    for j=1:1:c
        if (mResult(i,j)== 0)
            intensityImage(i,j) = HWoriginalImage(i,j);
        else 
            intensityImage(i,j) = 0;
        end
    end
end 
figure(194);
imshow(intensityImage);































