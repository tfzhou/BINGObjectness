%% Example to call BINGMultiple.mexa64

clc; clear;

vocPath = '/home/tfzhou/Research/data/VOC/VOC2007/';

bboxes = BINGMultiple( vocPath, 2, 8, 2, 130 );
