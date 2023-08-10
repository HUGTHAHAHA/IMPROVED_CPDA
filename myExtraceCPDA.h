#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\calib3d.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\core.hpp>

//���Ҿ���
double DisPointsToLine(cv::Point2f&p0, cv::Point2f&p1, cv::Point2f&p2);


//����֮��ľ���
inline double TowPointDis(cv::Point2f& p1, cv::Point2f& p2)
{
	double value = 0;
	value = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	return value;
}

/****************************************************/
/****************���Ҿ������ҳ����ۼ�ֵ***************/
/****************centerPints         ���ĵ�**********/
/*************** DisSerial           �����ۼ�ֵ******/
/*************** C                   �ҳ�ֵ**********/
/****************************************************/
std::vector<double> DisSerialNum(std::vector<cv::Point2f>& centerPints,std::vector<double>& DisSerial,int& C);

/***************************************************/
/*******��ÿ����ĵ��Ҿ������ҳ��ı�ֵ���й�һ��******/
/***** std::vector<double>& DisSerial  �����ۼ�ֵ****/
/***************************************************/
void Normalization(std::vector<double>& DisSerial);


/***************************************************/
/******************��ֲ�����ֵ**********************/
/***************Mat& gray      ����ͼ��*************/
/*************** centerPints   ���ĵ�***************/
/*************** DisSerialNum  �����ۼ�ֵ***********/
/*************** MaxiMum       �洢����ֵ��*********/
/*************** thresh        ��ֵ*****************/
/*************** Athresh       �Ƕ���ֵ*************/
/*************** R             �ֲ��뾶*************/
/***************************************************/
void LocalMax(cv::Mat& gray,std::vector<cv::Point2f>& centerPints, std::vector<double>& DisSerialNum, std::vector<cv::Point2f>& MaxiMum, double thresh, /*double& Athresh,*/ int R);
std::vector<cv::Point2f> LocalMax(/*cv::Mat& gray,*/ std::vector<cv::Point2f>& centerPints, std::vector<double>& DisSerialNum, std::vector<cv::Point2f>& MaxiMum, double thresh, /*double& Athresh,*/int R);

/**************************************************/
/***********************����αƽ�*****************/
/*************** MaxiMum       �洢����ֵ��*********/
/*************** thresh        ��ֵ*****************/
/***************************************************/
void solveMax(cv::Mat&gray,std::vector<cv::Point2f>& MaxiMum, std::vector<cv::Point2f>& MaxMum);
void solveMax2(cv::Mat& gray, std::vector<cv::Point2f>& MaxiMum, std::vector<cv::Point2f>& MaxMum, int Thresh);