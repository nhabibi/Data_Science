prompt = {'Enter the path of original image: '}; 
title = 'File Path';
location = inputdlg(prompt, title); 
location1 = char(location); % type conversion from cellstring to string

% if (strcmp(location1,'')==1)
%     location1 = 'HWdefualt.bmp'; 
% end

HWoriginalImage = imread(location1);

[r c p] = size(HWoriginalImage);
if (p>1)
    tempImg = rgb2gray(HWoriginalImage);
    HWoriginalImage = tempImg;
end
figure(200);
subplot(1,1,1),imshow(HWoriginalImage); 
