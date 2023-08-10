#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\calib3d.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\core.hpp>
#include<string>
#include<fstream>
#include"myExtraceCPDA.h"
#include"grayCenterColumn.h"
#include"grayCenterRow.h"

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
 	    int C = 16; //弦长
		double Athresh = 0;
		vector<double> DisSerial;
		vector<Point2f> centerPoints;
		vector<Point2f> MaxiMum; //极大值点
		vector<Point2f> MaxMum;
		Scalar color;

		Mat image = imread("E:/picture/jiaojie_welding/12/jiaojie_001.BMP", 0);
		if (image.empty())
		{
			cout << "图片输入有误" << endl;
			return -1;
		}
		//myThresh(image, image);
		blur(image, image, Size(5, 5), Point(-1,-1));
		grayCenterByRow(image, centerPoints, CENTER_TOTALTHRESH);
		//grayCenterByRowSquare(gray, centerPoints, CENTER_COLTHRESH);
		//grayCenterWidthRow(gray, centerPoints, CENTER_COLTHRESH);
		//weightCenter(gray, centerPoints);
		drawCenterPoints(image, centerPoints, color);
		DisSerial = DisSerialNum(centerPoints, DisSerial, C);
		Normalization(DisSerial);
		////LocalMax(gray, centerPoints, DisSerial, MaxiMum, 0.8, /*Athresh,*/ 40);
		MaxiMum = LocalMax(/*gray, */centerPoints, DisSerial, MaxiMum, 0.1, /*Athresh,*/ 80);
		solveMax2(image, MaxiMum, MaxMum,179); //多边形逼近
	imwrite("E:/picture/jiaojie_welding/result_jiaojie/jiaojie_2_4.BMP", image);
	namedWindow("output", WINDOW_FREERATIO);
	imshow("output", image);
	waitKey(0);
	return 0;
}
