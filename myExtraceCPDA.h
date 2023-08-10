#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\calib3d.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\core.hpp>

//点弦距离
double DisPointsToLine(cv::Point2f&p0, cv::Point2f&p1, cv::Point2f&p2);


//两点之间的距离
inline double TowPointDis(cv::Point2f& p1, cv::Point2f& p2)
{
	double value = 0;
	value = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	return value;
}

/****************************************************/
/****************点弦距离与弦长的累加值***************/
/****************centerPints         中心点**********/
/*************** DisSerial           返回累加值******/
/*************** C                   弦长值**********/
/****************************************************/
std::vector<double> DisSerialNum(std::vector<cv::Point2f>& centerPints,std::vector<double>& DisSerial,int& C);

/***************************************************/
/*******对每个点的点弦距离与弦长的比值进行归一化******/
/***** std::vector<double>& DisSerial  返回累加值****/
/***************************************************/
void Normalization(std::vector<double>& DisSerial);


/***************************************************/
/******************求局部极大值**********************/
/***************Mat& gray      输入图像*************/
/*************** centerPints   中心点***************/
/*************** DisSerialNum  距离累加值***********/
/*************** MaxiMum       存储极大值点*********/
/*************** thresh        阈值*****************/
/*************** Athresh       角度阈值*************/
/*************** R             局部半径*************/
/***************************************************/
void LocalMax(cv::Mat& gray,std::vector<cv::Point2f>& centerPints, std::vector<double>& DisSerialNum, std::vector<cv::Point2f>& MaxiMum, double thresh, /*double& Athresh,*/ int R);
std::vector<cv::Point2f> LocalMax(/*cv::Mat& gray,*/ std::vector<cv::Point2f>& centerPints, std::vector<double>& DisSerialNum, std::vector<cv::Point2f>& MaxiMum, double thresh, /*double& Athresh,*/int R);

/**************************************************/
/***********************多边形逼近*****************/
/*************** MaxiMum       存储极大值点*********/
/*************** thresh        阈值*****************/
/***************************************************/
void solveMax(cv::Mat&gray,std::vector<cv::Point2f>& MaxiMum, std::vector<cv::Point2f>& MaxMum);
void solveMax2(cv::Mat& gray, std::vector<cv::Point2f>& MaxiMum, std::vector<cv::Point2f>& MaxMum, int Thresh);