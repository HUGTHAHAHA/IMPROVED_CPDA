#include"myThreshOTSU.h"

using namespace cv;
using namespace std;

//传入频数统计表，求OTSU阈值,两类的均值
//p 为频数统计，索引为数据值，p[i]为数据值的统计数
int myThresh(const vector<int>& p, float& avg1, float& avg2)
{
	//求全局均值
	const int len = p.size();
	double mG{ 0 };//全局均值
	double convSum{ 0 };//值*数目 的累加
	double countSum = 0;//数目累加
	for (int j = 0;j < len;++j)
	{
		convSum += j*p[j];
		countSum += p[j];
	}
	mG = convSum / countSum;

	
	double p1=0;//阈值为k时，第一类的频率
	double m=0;//阈值为k时，第一类的 值*频率 累加
	double sigma=0;//类间方差
	int thresh = 0;//阈值
	double maxSigma = 0;
	for (int k = 0;k < len;++k)
	{
		p1 +=  (p[k] / countSum);//背景频率
		m +=  (k*p[k] / countSum);//背景灰度值*频率 的累加
		if (p1 == 0)
		{
			continue;//继续下一次循环
		}
		else if(p1 == 1)
		{
			break;
		}
		sigma = pow((mG*p1 - m), 2) / p1 / (1 - p1);
		if (sigma>maxSigma)
		{
			thresh = k;
			maxSigma = sigma;
			//第一类的均值
			avg1 = m / p1;
			//第二类的均值
			avg2 = (mG - m) / (1 - p1);
		}
	}
	return thresh;
}

int myThresh(Mat &img, Mat &dst)
{
	double mG{ 0 };//全局均值
				   //每一个灰度值的频数
	vector<int> p(256, 0.0);

	for (int i = 0;i < img.rows;++i)
	{
		for (int j = 0;j < img.cols;++j)
		{
			uchar val = img.at<uchar>(i, j);
			//灰度均值
			mG += val;
			//频数统计
			++p[val];
		}
	}
	mG /= (img.rows * img.cols);
	cout << "mG=" << mG << endl;

	float avg1 = 0;
	float avg2 = 0;
	float thresh = myThresh(p, avg1, avg2);

	//阈值化
	for (int i = 0;i < dst.rows;++i)
	{
		for (int j = 0;j < dst.cols;++j)
		{
			if (img.at<uchar>(i, j) <= thresh)
			{
				dst.at<uchar>(i, j) = 0;
			}
			else
			{
				dst.at<uchar>(i, j) = 255;
			}
		}
	}
	return thresh;
}

//求序列的方差
double deviation(vector<int>& x)
{
	double avg = 0;
	double s = 0;
	for (auto item = x.begin(); item != x.end(); ++item)
	{
		s += *item;
	}
	avg = s / x.size();

	double d = 0;
	for (auto item = x.begin(); item != x.end(); ++item)
	{
		d += pow((*item - avg), 2);
	}
	d /= x.size();
	return d;
}