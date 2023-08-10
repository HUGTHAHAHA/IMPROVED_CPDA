#pragma once
//���̸񱳾��¹���������ȡ
//������ȡ��������
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
	CENTER_NOTHRESH,		//������ֵ��
	CENTER_TOTALTHRESH,	//ȫ����ֵ��
	CENTER_COLTHRESH		//������ֵ��
};
#endif // !THRESH_TYPE

//************************************
// Method:    getThreshInCol
// FullName:  getThreshInCol
// Access:    public 
// Returns:   int ����OTSU��ֵ
// Qualifier:��ĳһ�е�OTSU��ֵ
// Parameter: cv::Mat & lightGray ����Ҷ�ͼ
// Parameter: int col �Ҷ�ͼ������
//************************************
int getThreshInCol(cv::Mat& lightGray, int col);

//************************************
// Method:    myThreshCol
// FullName:  myThreshCol
// Access:    public 
// Returns:   void
// Qualifier:����OTSU��ͼ����ֵ����С����ֵ������Ϊ0
// Parameter: cv::Mat & lightGray ��������Ҷ�ͼ
//************************************
void myThreshCol(cv::Mat& lightGray);

//************************************
// Method:    getCenterYCol
// FullName:  getCenterYCol
// Access:    public 
// Returns:   bool
// Qualifier: ��ĳһ�е�����Y����
// Parameter: const cv::Mat & gray  ����Ҷ�ͼ
// Parameter: int col ͼ��������
// Parameter: double & centerY ����Y����
// Parameter: int thresh ��ֵ
//************************************
bool getCenterInCol(const cv::Mat& gray, int col, double& centerY, int thresh = 0);

//************************************
// Method:    grayCenterByCol
// FullName:  grayCenterByCol
// Access:    public 
// Returns:   void
// Qualifier: ������ȡͼƬ�ĻҶ�����
// Parameter: cv::Mat & gray ����Ҷ�ͼ
// Parameter: std::vector<cv::Point2f> & centerPoints ��ȡ�õ������ĵ�����
// Parameter: int threshFlag ��ֵ����
//************************************
void grayCenterByCol(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag = CENTER_TOTALTHRESH);

//************************************
// Method:    drawCenterPoints
// FullName:  drawCenterPoints
// Access:    public 
// Returns:   cv::Mat&
// Qualifier: ��ͼ���ϻ������ĵ�
// Parameter: cv::Mat & src ����ͼƬ
// Parameter: std::vector<cv::Point2f> & centerPoints ���ĵ���������
//************************************
cv::Mat& drawCenterPoints(cv::Mat& src, std::vector<cv::Point2f>& centerPoints, const cv::Scalar& color = cv::Scalar(0, 0, 255));

cv::Mat& drawCenterPoints(cv::Mat& src, const  std::vector<cv::Point2f>& centerPoints, const cv::Scalar& color = cv::Scalar(0, 0, 255));

cv::Mat& drawCenterPoints(cv::Mat& src, const  std::vector<std::vector<cv::Point2f>>& vCenterPoints, const cv::Scalar& color = cv::Scalar(0, 0, 255));


//************************************
// Method:    detectStripe
// FullName:  detectStripe
// Access:    public 
// Returns:   bool �Ƿ��⵽����
// Qualifier:�����ֵͼ����Ҷ�ͼ ĳһ�е����ƿ��ȣ�������㣬�յ�
// Parameter: const cv::Mat & lightGray ���룬�Ҷ�ͼ��Ҫָ����ֵ
// Parameter: int col ͼ��������
// Parameter: cv::Vec3i& wPos ��������ȣ�������㣬�յ�β��λ��
// Parameter: int thresh = 0 ָ����ֵ
//************************************
bool detectStripe(const cv::Mat& lightGray, int col, cv::Vec3i& wPos, int thresh = 0);

//************************************
// Method:    getCenterInCol
// FullName:  getCenterInCol
// Access:    public 
// Returns:   bool
// Qualifier: ���ݼ�⵽������λ�ü���Ҷ�����
// Parameter: const cv::Mat & lightGray ����Ҷ�ͼ �� ��ֵ�����ͼ
// Parameter: int col ������
// Parameter: cv::Vec3i & wPos  ��⵽������λ��
// Parameter: cv::Point2f & centerPoint  ����õ��ĻҶ�����
// Parameter: int thresh = 0 ָ������Ϊ�Ҷ�ͼҪָ����ֵ
//************************************
bool getCenterInCol(const cv::Mat& lightGray, int col, cv::Point2f& centerPoint, int thresh = 0);

//************************************
// Method:    grayCenterWidthCol
// FullName:  grayCenterWidthCol
// Access:    public 
// Returns:   void
// Qualifier: ͨ��������ƿ��� ��ȡ�Ҷ����ģ����˳�һ���Ľ�������
// Parameter: cv::Mat & gray ����Ҷ�ͼ����ֵ���ͼ
// Parameter: std::vector<cv::Point2f> & centerPoints  ��ȡ�����ĵ�����
// Parameter: int threshFlag ��ֵ����
//************************************
void grayCenterWidthCol(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag);

//�ڹ������Ĵ� �����������ƿ���
int getWidthInCenterCol(cv::Mat& imgGray, cv::Point2f& centerPoint);

//���ʼ���ĵ� ���������з�����ȷ���
double getDeviationInCols(cv::Mat& imgGray, cv::Point2f& centerPoint);
