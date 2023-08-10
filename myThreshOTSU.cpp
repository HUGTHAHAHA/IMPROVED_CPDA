#include"myThreshOTSU.h"

using namespace cv;
using namespace std;

//����Ƶ��ͳ�Ʊ�����OTSU��ֵ,����ľ�ֵ
//p ΪƵ��ͳ�ƣ�����Ϊ����ֵ��p[i]Ϊ����ֵ��ͳ����
int myThresh(const vector<int>& p, float& avg1, float& avg2)
{
	//��ȫ�־�ֵ
	const int len = p.size();
	double mG{ 0 };//ȫ�־�ֵ
	double convSum{ 0 };//ֵ*��Ŀ ���ۼ�
	double countSum = 0;//��Ŀ�ۼ�
	for (int j = 0;j < len;++j)
	{
		convSum += j*p[j];
		countSum += p[j];
	}
	mG = convSum / countSum;

	
	double p1=0;//��ֵΪkʱ����һ���Ƶ��
	double m=0;//��ֵΪkʱ����һ��� ֵ*Ƶ�� �ۼ�
	double sigma=0;//��䷽��
	int thresh = 0;//��ֵ
	double maxSigma = 0;
	for (int k = 0;k < len;++k)
	{
		p1 +=  (p[k] / countSum);//����Ƶ��
		m +=  (k*p[k] / countSum);//�����Ҷ�ֵ*Ƶ�� ���ۼ�
		if (p1 == 0)
		{
			continue;//������һ��ѭ��
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
			//��һ��ľ�ֵ
			avg1 = m / p1;
			//�ڶ���ľ�ֵ
			avg2 = (mG - m) / (1 - p1);
		}
	}
	return thresh;
}

int myThresh(Mat &img, Mat &dst)
{
	double mG{ 0 };//ȫ�־�ֵ
				   //ÿһ���Ҷ�ֵ��Ƶ��
	vector<int> p(256, 0.0);

	for (int i = 0;i < img.rows;++i)
	{
		for (int j = 0;j < img.cols;++j)
		{
			uchar val = img.at<uchar>(i, j);
			//�ҶȾ�ֵ
			mG += val;
			//Ƶ��ͳ��
			++p[val];
		}
	}
	mG /= (img.rows * img.cols);
	cout << "mG=" << mG << endl;

	float avg1 = 0;
	float avg2 = 0;
	float thresh = myThresh(p, avg1, avg2);

	//��ֵ��
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

//�����еķ���
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