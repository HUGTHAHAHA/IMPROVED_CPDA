#include"myExtraceCPDA.h"

using namespace std;
using namespace cv;


//点弦距离
double DisPointsToLine(cv::Point2f&p0, cv::Point2f&p1, cv::Point2f&p2)
{
	double Dis = 0;
	double A = 0;
	double B = 0;
	double C = 0;
	double s1, s2;
	A = -(p1.y - p2.y);
	B = (p1.x - p2.x);
	C = (p2.x*p1.y - p2.x*p2.y);
	s1 = abs(A*p0.x + B*p0.y + C);
	s2 = sqrt(pow(A, 2) + pow(B, 2));
	if (s2 != 0)
	{
		Dis = s1 / s2;
	}
	return Dis;
}

//点弦距离与弦长的累加值
std::vector<double> DisSerialNum(std::vector<cv::Point2f>& centerPints, std::vector<double>& DisSerial,int& C)
{
	int len = centerPints.size();
	Point2f p1, p2;
	double Dis = 0;
	
	for (int i = C - 1; i < len - C + 1; i++)
	{
		double h = 0;
		for (int j = i - (C - 1); j < i; j++)
		{
			p1 = centerPints[j];
			p2= centerPints[j+C];
			h += (DisPointsToLine(centerPints[i], p1, p2) / C);  //点弦距离与弦长的比值
		}
		DisSerial.push_back(h);
	}
	return DisSerial;
}

/*******对每个点的点弦距离与弦长的比值进行归一化******/
void Normalization(std::vector<double>& DisSerial)
{
	int len = DisSerial.size();
	double Max = 0;
	double Min = 0;
	for (int i = 0; i < len; i++)
	{
		if (DisSerial[i] > Max)
		{
			Max = DisSerial[i];
		}
		if (DisSerial[i] < Min)
		{
			Min = DisSerial[i];
		}
	}
	for (int j = 0; j < len; j++)
	{
		DisSerial[j] = (DisSerial[j] - Min) / (Max - Min);
	}
}

/***************求局部极大值************************/
//void LocalMax(cv::Mat& gray, std::vector<cv::Point2f>& centerPints, std::vector<double>& DisSerialNum, std::vector<cv::Point2f>& MaxiMum, double thresh, /*double& Athresh,*/ int R)
std::vector<cv::Point2f> LocalMax(/*cv::Mat& gray, */std::vector<cv::Point2f>& centerPints, std::vector<double>& DisSerialNum, std::vector<cv::Point2f>& MaxiMum, double thresh, /*double& Athresh,*/int R)
{
	int nR = DisSerialNum.size();
	double t = 0;
	double s = 0;
	double x1, x2, y1, y2;
	for (int i = R; i < nR - R; i++)
	{
		if (DisSerialNum[i] <= thresh)
		{
			continue;
		}
		bool isLocalMax = true;
		for (int j = i - R; j < i + R; j++)
		{
			if (DisSerialNum[i] < DisSerialNum[j])
			{
				isLocalMax = false;
				break;
			}
		}
		if (isLocalMax)
		{
			MaxiMum.push_back(centerPints[i]);
			////circle(gray, centerPints[i], 5, Scalar(0, 0, 0), -1);
			////计算角度阈值
			///*a = TowPointDis(centerPints[i], centerPints[i + R]);
			//b= TowPointDis(centerPints[i-R], centerPints[i]);
			//c=TowPointDis(centerPints[i-R], centerPints[i + R]);
			//A = acos((a*a + b*b - c * c) / (2 * a*b)) * 180 / 3.141592653;*/
			//x1 = centerPints[i].x - centerPints[i - R].x;
			//y1 = centerPints[i].y - centerPints[i - R].y;
			//x2 = centerPints[i].x - centerPints[i + R].x;
			//y2 = centerPints[i].y - centerPints[i + R].y;
			//t = ((x1*x2) + (y1*y2)) / (sqrt(pow(x1, 2) + pow(y1, 2))*sqrt(pow(x2, 2) + pow(y2, 2)));
			//s = acos(t)*(180 / 3.141592654);
			////cout << "A=" << s << endl;
			//if (s <= 175)
			//{
			//	//Athresh = A;
			//	MaxiMum.push_back(centerPints[i]);
			//	//circle(gray, centerPints[i], 5, Scalar(0, 0, 0), -1);
			//}
			i = i + R;
		}
		
	}
	return MaxiMum;
}

/***********************多边形逼近*****************/
void solveMax(cv::Mat&gray,std::vector<cv::Point2f>& MaxiMum, std::vector<cv::Point2f>& MaxMum)
{
	double Dis=0 ;
	double Max=0 ;
	int len = MaxiMum.size();
	Point2f p1 = MaxiMum[0];
	Point2f p2 = MaxiMum[len-1];
	for (int i = 1; i < len-1; i++)
	{
		Dis=DisPointsToLine(MaxiMum[i], p1, p2);
		if (Dis> Max)
		{
			Max = Dis;
			MaxMum.push_back(MaxiMum[i]);
			circle(gray, MaxiMum[i], 5, Scalar(0, 0, 0), -1);
		}
	}
	
}

void solveMax2(cv::Mat& gray, std::vector<cv::Point2f>& MaxiMum, std::vector<cv::Point2f>& MaxMum, int Thresh)
{
	double t = 0;
	double s = 0;
	double x1, x2,y1,y2;
	int len = MaxiMum.size();
	for (int i = 1; i < len-1; i++)
	{
		x1 = MaxiMum[i].x - MaxiMum[i - 1].x;
		y1= MaxiMum[i].y - MaxiMum[i - 1].y;
		x2 = MaxiMum[i].x - MaxiMum[i + 1].x;
		y2 = MaxiMum[i].y - MaxiMum[i + 1].y;
		t = ((x1*x2) + (y1*y2)) / (sqrt(pow(x1, 2) + pow(y1, 2))*sqrt(pow(x2, 2) + pow(y2, 2)));
		s = acos(t)*(180 / 3.141592654);
		cout << "s=" << s << endl;
		if (s < Thresh)
		{
			MaxMum.push_back(MaxiMum[i]);
			circle(gray, MaxiMum[i], 5, Scalar(0, 0, 0), -1);
		}
	}
	
}
