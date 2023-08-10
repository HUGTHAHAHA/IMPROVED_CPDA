#pragma once
//棋盘格背景下光条中心提取
//逐列提取光条中心
#pragma once
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include"myThreshOTSU.h"

#ifndef THRESH_TYPE
#define  THRESH_TYPE
enum threshType
{
	CENTER_NOTHRESH,		//不做阈值化
	CENTER_TOTALTHRESH,	//全局阈值化
	CENTER_COLTHRESH		//逐列阈值化
};
#endif // !THRESH_TYPE

//************************************
// Method:    getThreshInCol
// FullName:  getThreshInCol
// Access:    public 
// Returns:   int 返回OTSU阈值
// Qualifier:求某一列的OTSU阈值
// Parameter: cv::Mat & lightGray 输入灰度图
// Parameter: int col 灰度图列索引
//************************************
int getThreshInCol(cv::Mat& lightGray, int col);

//************************************
// Method:    myThreshCol
// FullName:  myThreshCol
// Access:    public 
// Returns:   void
// Qualifier:逐列OTSU对图像阈值化，小于阈值的设置为0
// Parameter: cv::Mat & lightGray 输入输出灰度图
//************************************
void myThreshCol(cv::Mat& lightGray);

//************************************
// Method:    getCenterYCol
// FullName:  getCenterYCol
// Access:    public 
// Returns:   bool
// Qualifier: 求某一列的重心Y坐标
// Parameter: const cv::Mat & gray  输入灰度图
// Parameter: int col 图像列索引
// Parameter: double & centerY 重心Y坐标
// Parameter: int thresh 阈值
//************************************
bool getCenterInCol(const cv::Mat& gray, int col, double& centerY, int thresh = 0);

//************************************
// Method:    grayCenterByCol
// FullName:  grayCenterByCol
// Access:    public 
// Returns:   void
// Qualifier: 逐列提取图片的灰度重心
// Parameter: cv::Mat & gray 输入灰度图
// Parameter: std::vector<cv::Point2f> & centerPoints 提取得到的中心点坐标
// Parameter: int threshFlag 阈值类型
//************************************
void grayCenterByCol(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag = CENTER_TOTALTHRESH);

//************************************
// Method:    drawCenterPoints
// FullName:  drawCenterPoints
// Access:    public 
// Returns:   cv::Mat&
// Qualifier: 在图像上绘制中心点
// Parameter: cv::Mat & src 输入图片
// Parameter: std::vector<cv::Point2f> & centerPoints 中心点坐标序列
//************************************
cv::Mat& drawCenterPoints(cv::Mat& src, std::vector<cv::Point2f>& centerPoints, const cv::Scalar& color = cv::Scalar(0, 0, 255));

cv::Mat& drawCenterPoints(cv::Mat& src, const  std::vector<cv::Point2f>& centerPoints, const cv::Scalar& color = cv::Scalar(0, 0, 255));

cv::Mat& drawCenterPoints(cv::Mat& src, const  std::vector<std::vector<cv::Point2f>>& vCenterPoints, const cv::Scalar& color = cv::Scalar(0, 0, 255));


//************************************
// Method:    detectStripe
// FullName:  detectStripe
// Access:    public 
// Returns:   bool 是否检测到条纹
// Qualifier:检测阈值图，或灰度图 某一列的条纹宽度，条纹起点，终点
// Parameter: const cv::Mat & lightGray 输入，灰度图需要指定阈值
// Parameter: int col 图像列索引
// Parameter: cv::Vec3i& wPos 输出，宽度，条纹起点，终点尾后位置
// Parameter: int thresh = 0 指定阈值
//************************************
bool detectStripe(const cv::Mat& lightGray, int col, cv::Vec3i& wPos, int thresh = 0);

//************************************
// Method:    getCenterInCol
// FullName:  getCenterInCol
// Access:    public 
// Returns:   bool
// Qualifier: 根据检测到的条纹位置计算灰度重心
// Parameter: const cv::Mat & lightGray 输入灰度图 或 阈值化后的图
// Parameter: int col 列索引
// Parameter: cv::Vec3i & wPos  检测到的条纹位置
// Parameter: cv::Point2f & centerPoint  计算得到的灰度重心
// Parameter: int thresh = 0 指若输入为灰度图要指定阈值
//************************************
bool getCenterInCol(const cv::Mat& lightGray, int col, cv::Point2f& centerPoint, int thresh = 0);

//************************************
// Method:    grayCenterWidthCol
// FullName:  grayCenterWidthCol
// Access:    public 
// Returns:   void
// Qualifier: 通过检测条纹宽度 提取灰度重心，能滤除一定的椒盐噪声
// Parameter: cv::Mat & gray 输入灰度图或阈值后的图
// Parameter: std::vector<cv::Point2f> & centerPoints  提取的中心点序列
// Parameter: int threshFlag 阈值方法
//************************************
void grayCenterWidthCol(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag);

//在光条中心处 沿纵向检测条纹宽度
int getWidthInCenterCol(cv::Mat& imgGray, cv::Point2f& centerPoint);

//求初始中心点 邻域条纹列方向宽度方差
double getDeviationInCols(cv::Mat& imgGray, cv::Point2f& centerPoint);

