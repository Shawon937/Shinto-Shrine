img = imread('wwod.jpg');

figure;
imshow(img);

disp(size(img));



img1 = imresize(img , 128 / 1024);

imwrite(img1, 'wwod.bmp');

figure;
imshow(img1);

disp(size(img1));
