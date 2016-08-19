%% Example to call BINGSingle.mexa64

clc; clear;

imPath = '000001.jpg';
vocPath = '/home/tfzhou/Research/data/VOC/VOC2007/';

im = imread( imPath );

BBs = BINGSingle( im, vocPath, 2, 8, 2, 130 );
BBs(~any(BBs, 2), :) = [];


gt = [48 240 195 371];

overlaps = zeros(size(BBs, 1), 1);
for(it_n = 1 : size(BBs, 1))
  bb = BBs(it_n, :);
  
  minX = double(max(bb(1), gt(1)));
  minY = double(max(bb(2), gt(2)));
  maxX = double(min(bb(3), gt(3)));
  maxY = double(min(bb(4), gt(4)));
  
  iw = maxX - minX + 1;
  ih = maxY - minY + 1;
  
  if( iw > 0 && ih > 0 )
    ua = prod(bb(3:4)-bb(1:2)) + prod(gt(3:4)-gt(1:2)) - iw * ih;
    overlaps(it_n) = iw * ih / ua;
  else
    overlaps(it_n) = -1;
  end
  
end

% Plot BB
figure('position',[0 0 400 300]); clf;
imshow(im);
[val, idx] = max(overlaps);
hold on, rectangle('Position', [gt(1:2), gt(3:4)-gt(1:2)], 'EdgeColor', 'r');

bb = BBs(idx,:);
hold on, rectangle('Position', [bb(1:2), bb(3:4)-bb(1:2)], 'EdgeColor', 'g');

