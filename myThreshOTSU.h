#pragma once
//�����ֵ������

#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

//ͼ����ֵ�ָ�
int myThresh(cv::Mat &img, cv::Mat &dst);

//����Ƶ��ͳ�Ʊ�����OTSU��ֵ,����ľ�ֵ
//p ΪƵ��ͳ�ƣ�����Ϊ����ֵ��p[i]Ϊ����ֵ��ͳ����
int myThresh(const std::vector<int>& p, float& avg1, float& avg2);

//�����еķ���
double deviation(std::vector<int>& x);