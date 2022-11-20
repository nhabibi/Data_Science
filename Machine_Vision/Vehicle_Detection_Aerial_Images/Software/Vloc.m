prompt = {'Enter the path of original image: '}; 
title = 'File Path';
location = inputdlg(prompt, title); 
location1 = char(location); % type conversion from cellstring to string

% if (location1 == '')
%     location1 = 'Vdefualt.bmp'; 
% end

VoriginalImage = imread(location1);

[r c p] = size(VoriginalImage);
if (p>1)
    tempImg = rgb2gray(VoriginalImage);
    VoriginalImage = tempImg;
end
figure(100);
subplot(1,1,1),imshow(VoriginalImage); 
