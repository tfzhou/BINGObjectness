%% Example to call BINGMultiple.mexa64

clc; clear;

vocPath = '/home/fei/Research/datasets/VOC/VOC2007/';

bboxes = BINGMultiple( vocPath, 2, 8, 2, 130 );
