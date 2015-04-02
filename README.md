# BING Objectness

BING Objectness proposal estimator Matlab (mex-c) wrapper, runs at 250
FPS at a i7 CPU (2.93Hz) with Linux 12.04 64-bit and Matlab R2013a.

## Introduction

This is the matlab wrapper of BING Objectness for efficient
objectness proposal estimator following the CVPR 2014 paper BING, please
consider to cite and refer to this paper.

@inproceedings{BingObj2014,
  title={{BING}: Binarized Normed Gradients for Objectness Estimation at
300fps},
  author={Ming-Ming Cheng and Ziming Zhang and Wen-Yan Lin and Philip H.
S. Torr},
  booktitle={IEEE CVPR},
  year={2014},
}

The original author Ming-Ming Cheng has already released the source code
for windows 64-bit platform, and Shuai Zheng has provided the code for
the linux/mac/windows users.
In this library, I intend to provide some simple functions so that some
users can easily reproduce the results in the paper or use BING for some
other applications.

## Requirements

In order to make the code running, you need to download the
images/annotations PASCAL VOC 2007 data from the link:
[VOC2007](http://pascallin.ecs.soton.ac.uk/challenges/VOC/voc2007/#testdata).

Please refer to the FAQs #2 in
[http://mmcheng.net/bing/](http://mmcheng.net/bing/) for more details
about how to prepare VOC2007 dataset.

## HowTo in Matlab

I have written three mex-c fuctions:

* trainBING.cpp - For training BING Objectness
* BINGMultiple.cpp - For reproducing the results of the original paper
* BINGSingle.cpp - For users to use BING on a single image

Also, I have written three matlab scripts to show how to use it in
Matlab (Name Convention: Example\_ + function name ).

Note that the function _trainBING_ is a bit needless because 
_BINGMultiple_ and _BINGSINGLE_ will learn the models if they do not
exists. 

You can run Example\_BINGMultiple.m to reproduce the results in the
origin paper, and a script called _PerImgAll.m_ will be generated in
your VOC2007 folder. 
You can use the script and _PlotsCVPR14.m_ to plot the Figure 3 in the
paper.

I have tested the code in Ubuntu 12.04 64-bit (8G Memory) and Matlab R2013a,
 and it produces the same accuarcy results as the
original windows version, except that in my PC, it runs at 250 FPS
compared to 300 FPS reported in the paper. 

If you intend to use the codes in other system version, please run
_compile.m_ to re-compile the files.

Please contact me (removethisifyouarehuman-tfzhou@bit.edu.cn) or create an issue if you have problems to run the
codes. 

## Other Source Code Repos

* [http://mmcheng.net/bing/](http://mmcheng.net/bing/) -- The original
  code / FAQ / Paper by Ming-Ming Cheng.
* [https://github.com/bittnt/Objectness](https://github.com/bittnt/Objectness) -- The Linux version library by Shuai Zheng.
