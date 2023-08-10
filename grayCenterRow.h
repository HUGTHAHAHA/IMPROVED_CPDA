#pragma once
//棋盘格背景下光条中心提取
//逐行中心提取相关函数
#pragma once
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include"grayCenterColumn.h"

//************************************
// Method:    getThreshInRow
// FullName:  getThreshInRow
// Access:    public 
// Returns:   int
// Qualifier: 求某一行的OTSU阈值
// Parameter: cv::Mat & lightGray 输入灰度图
// Parameter: int r 行索引
//************************************
int getThreshInRow(cv::Mat& lightGray, int r);

//************************************
// Method:    myThreshRow
// FullName:  myThreshRow
// Access:    public 
// Returns:   void
// Qualifier: 逐行OTSU阈值化
// Parameter: cv::Mat & lightGray 输入灰度图
//************************************
void myThreshRow(cv::Mat& lightGray);

//************************************
// Method:    getCenterInRow
// FullName:  getCenterInRow
// Access:    public 
// Returns:   bool
// Qualifier: 求某一行的重心X坐标
// Parameter: const cv::Mat & gray 输入灰度图
// Parameter: int row 行索引
// Parameter: double & centerX 中心点X坐标
// Parameter: int thresh 阈值
//************************************
bool getCenterInRow(const cv::Mat& gray, int row, double& centerX, int thresh = 0);

bool getCenterInRowSquare(const cv::Mat& gray, int row, double& centerX, int thresh = 0);

//************************************
// Method:    grayCenterByRow
// FullName:  grayCenterByRow
// Access:    public 
// Returns:   void
// Qualifier: 逐行提取图片的灰度重心
// Parameter: cv::Mat & gray 输入灰度图
// Parameter: std::vector<cv::Point2f> & centerPoints 中心坐标序列
// Parameter: int threshFlag 阈值类型
//************************************
void grayCenterByRow(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag);
void grayCenterByRowSquare(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag);

//************************************
// Method:    detectStripeInRow
// FullName:  detectStripeInRow
// Access:    public 
// Returns:   bool 返回是否检测到条纹
// Qualifier: 检测某一行条纹宽度，位置等
// Parameter: const cv::Mat & lightGray 输入灰度图
// Parameter: int row 行索引
// Parameter: cv::Vec3i & wPos  输出，宽度，条纹起点，终点尾后位置
// Parameter: int thresh 指定阈值
//************************************
bool detectStripeInRow(const cv::Mat& lightGray, int row, cv::Vec3i& wPos, int thresh = 0);

//************************************
// Method:    getCenterInRow
// FullName:  getCenterInRow
// Access:    public 
// Returns:   bool
// Qualifier: 根据检测到的条纹位置计算灰度重心
// Parameter: const cv::Mat & lightGray 输入灰度图 或 阈值化后的图
// Parameter: int row 行索引
// Parameter: cv::Vec3i & wPos  检测到的条纹位置
// Parameter: cv::Point2f & centerPoint  计算得到的灰度重心
// Parameter: int thresh = 0 指若输入为灰度图要指定阈值
//************************************
bool getCenterInRow(const cv::Mat& lightGray, int row, cv::Point2f& centerPoint, int thresh = 0);

//************************************
// Method:    grayCenterWidthRow
// FullName:  grayCenterWidthRow
// Access:    public 
// Returns:   void
// Qualifier: 通过检测条纹宽度 提取灰度重心，能滤除一定的椒盐噪声
// Parameter: cv::Mat & gray 输入灰度图或阈值后的图
// Parameter: std::vector<cv::Point2f> & centerPoints  提取的中心点序列
// Parameter: int threshFlag 阈值方法
//************************************
void grayCenterWidthRow(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag);



//赵斌 自适应灰度重心
void weightCenter(cv::Mat& srcImage, std::vector<cv::Point2f>& centerPoints);