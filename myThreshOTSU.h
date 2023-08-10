#pragma once
//大津阈值法测试

#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

//图像阈值分割
int myThresh(cv::Mat &img, cv::Mat &dst);

//传入频数统计表，求OTSU阈值,两类的均值
//p 为频数统计，索引为数据值，p[i]为数据值的统计数
int myThresh(const std::vector<int>& p, float& avg1, float& avg2);

//求序列的方差
double deviation(std::vector<int>& x);