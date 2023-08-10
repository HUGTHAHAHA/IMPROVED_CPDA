#pragma once
//���̸񱳾��¹���������ȡ
//����������ȡ��غ���
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
// Qualifier: ��ĳһ�е�OTSU��ֵ
// Parameter: cv::Mat & lightGray ����Ҷ�ͼ
// Parameter: int r ������
//************************************
int getThreshInRow(cv::Mat& lightGray, int r);

//************************************
// Method:    myThreshRow
// FullName:  myThreshRow
// Access:    public 
// Returns:   void
// Qualifier: ����OTSU��ֵ��
// Parameter: cv::Mat & lightGray ����Ҷ�ͼ
//************************************
void myThreshRow(cv::Mat& lightGray);

//************************************
// Method:    getCenterInRow
// FullName:  getCenterInRow
// Access:    public 
// Returns:   bool
// Qualifier: ��ĳһ�е�����X����
// Parameter: const cv::Mat & gray ����Ҷ�ͼ
// Parameter: int row ������
// Parameter: double & centerX ���ĵ�X����
// Parameter: int thresh ��ֵ
//************************************
bool getCenterInRow(const cv::Mat& gray, int row, double& centerX, int thresh = 0);

bool getCenterInRowSquare(const cv::Mat& gray, int row, double& centerX, int thresh = 0);

//************************************
// Method:    grayCenterByRow
// FullName:  grayCenterByRow
// Access:    public 
// Returns:   void
// Qualifier: ������ȡͼƬ�ĻҶ�����
// Parameter: cv::Mat & gray ����Ҷ�ͼ
// Parameter: std::vector<cv::Point2f> & centerPoints ������������
// Parameter: int threshFlag ��ֵ����
//************************************
void grayCenterByRow(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag);
void grayCenterByRowSquare(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag);

//************************************
// Method:    detectStripeInRow
// FullName:  detectStripeInRow
// Access:    public 
// Returns:   bool �����Ƿ��⵽����
// Qualifier: ���ĳһ�����ƿ��ȣ�λ�õ�
// Parameter: const cv::Mat & lightGray ����Ҷ�ͼ
// Parameter: int row ������
// Parameter: cv::Vec3i & wPos  ��������ȣ�������㣬�յ�β��λ��
// Parameter: int thresh ָ����ֵ
//************************************
bool detectStripeInRow(const cv::Mat& lightGray, int row, cv::Vec3i& wPos, int thresh = 0);

//************************************
// Method:    getCenterInRow
// FullName:  getCenterInRow
// Access:    public 
// Returns:   bool
// Qualifier: ���ݼ�⵽������λ�ü���Ҷ�����
// Parameter: const cv::Mat & lightGray ����Ҷ�ͼ �� ��ֵ�����ͼ
// Parameter: int row ������
// Parameter: cv::Vec3i & wPos  ��⵽������λ��
// Parameter: cv::Point2f & centerPoint  ����õ��ĻҶ�����
// Parameter: int thresh = 0 ָ������Ϊ�Ҷ�ͼҪָ����ֵ
//************************************
bool getCenterInRow(const cv::Mat& lightGray, int row, cv::Point2f& centerPoint, int thresh = 0);

//************************************
// Method:    grayCenterWidthRow
// FullName:  grayCenterWidthRow
// Access:    public 
// Returns:   void
// Qualifier: ͨ��������ƿ��� ��ȡ�Ҷ����ģ����˳�һ���Ľ�������
// Parameter: cv::Mat & gray ����Ҷ�ͼ����ֵ���ͼ
// Parameter: std::vector<cv::Point2f> & centerPoints  ��ȡ�����ĵ�����
// Parameter: int threshFlag ��ֵ����
//************************************
void grayCenterWidthRow(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag);



//�Ա� ����Ӧ�Ҷ�����
void weightCenter(cv::Mat& srcImage, std::vector<cv::Point2f>& centerPoints);