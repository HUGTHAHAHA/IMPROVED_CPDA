#include"grayCenterRow.h"
//利用两张图，棋盘格中心提取
using namespace cv;
using namespace std;

//求某一行的OTSU阈值
int getThreshInRow(Mat& lightGray, int r)
{
	vector<int> rPoints(256, 0);
	for (int j = 0; j < lightGray.cols; ++j)
	{
		++rPoints[lightGray.at<uchar>(r, j)];
	}
	float avg1, avg2;
	int thresh = myThresh(rPoints, avg1, avg2);
	return thresh;
}
//逐行OTSU,效果不好
void myThreshRow(Mat& lightGray)
{
	for (int i = 0; i < lightGray.rows; ++i)
	{
		int thresh = getThreshInRow(lightGray, i);
		//if (thresh <140)
		//{
		//	thresh *= 1.2;
		//}
		//else
		//{
		//	thresh = 220;
		//}

		for (int j = 0; j < lightGray.cols; ++j)
		{
			if (lightGray.at<uchar>(i, j) <= thresh)
			{
				lightGray.at<uchar>(i, j) = 0;
			}
		}
	}
}

bool getCenterInRow(const cv::Mat& gray, int row, double& centerX, int thresh)
{
	double sum = 0;
	double count = 0;
	const uchar * grayRow = gray.ptr<uchar>(row);
	for (int c = 0; c < gray.cols; ++c)
	{
		int val = grayRow[c];
		if (val > thresh)
		{
			sum += (c*val);
			count += val;
		}
	}
	if (count > 0)
	{
		centerX = sum / count;
		return true;
	}
	return false;
}

bool getCenterInRowSquare(const cv::Mat& gray, int row, double& centerX, int thresh /*= 0*/)
{
	double sum = 0;
	double count = 0;
	const uchar * grayRow = gray.ptr<uchar>(row);
	for (int c = 0; c < gray.cols; ++c)
	{
		int val = grayRow[c];
		if (val > thresh)
		{
			sum += (c*val*val);
			count += val * val;
		}
	}
	if (count > 0)
	{
		centerX = sum / count;
		return true;
	}
	return false;
}

void grayCenterByRow(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag)
{
	if (threshFlag == CENTER_TOTALTHRESH)
	{
		threshold(gray, gray, 0, 255, THRESH_TOZERO + THRESH_OTSU);
		//imshow("gray", gray);
		//waitKey(0);
	}
	if (threshFlag == CENTER_TOTALTHRESH || threshFlag == CENTER_NOTHRESH)
	{
		//阈值后的图求重心
		for (int r = 0; r < gray.rows; ++r)
		{
			double x = 0;
			if (getCenterInRow(gray, r, x))
			{
				//求重心Y坐标
				centerPoints.push_back(Point2f(x, r));
			}
		}
	}
	//逐列阈值
	else if (threshFlag == CENTER_COLTHRESH)
	{
		for (int r = 0; r < gray.rows; ++r)
		{
			//求阈值
			int thresh = getThreshInRow(gray, r);
			double x = 0;
			if (getCenterInRow(gray, r, x, thresh))
			{
				//求重心Y坐标
				centerPoints.push_back(Point2f(x, r));
			}
		}
	}
}

void grayCenterByRowSquare(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag)
{
	if (threshFlag == CENTER_TOTALTHRESH)
	{
		threshold(gray, gray, 0, 255, THRESH_TOZERO + THRESH_OTSU);
		//imshow("gray", gray);
		//waitKey(0);
	}
	if (threshFlag == CENTER_TOTALTHRESH || threshFlag == CENTER_NOTHRESH)
	{
		//阈值后的图求重心
		for (int r = 0; r < gray.rows; ++r)
		{
			double x = 0;
			if (getCenterInRowSquare(gray, r, x))
			{
				//求重心Y坐标
				centerPoints.push_back(Point2f(x, r));
			}
		}
	}
	//逐列阈值
	else if (threshFlag == CENTER_COLTHRESH)
	{
		for (int r = 0; r < gray.rows; ++r)
		{
			//求阈值
			int thresh = getThreshInRow(gray, r);
			double x = 0;
			if (getCenterInRowSquare(gray, r, x, thresh))
			{
				//求重心Y坐标
				centerPoints.push_back(Point2f(x, r));
			}
		}
	}
}

bool detectStripeInRow(const cv::Mat& lightGray, int row, cv::Vec3i& wPos, int thresh)
{
	int w = 0;
	int maxW = 0;
	int startPos = 0;
	int tmpStartPos = 0;
	int endPos = 0;
	for (int i = 0; i < lightGray.cols;)
	{
		while (i < lightGray.cols && lightGray.at<uchar>(row, i)>thresh)//大于阈值
		{
			//int tmp = lightGray.at<uchar>(row, i);
			if (w == 0)
			{
				tmpStartPos = i;
			}
			++w;
			++i;
		}
		//只检测宽度最大的 光条条纹
		if (w > maxW)
		{
			maxW = w;
			startPos = tmpStartPos;
			endPos = i;//endPos 为尾后元素

		}
		w = 0;
		++i;
	}
	if (maxW >= 3)//条纹宽度阈值
	{
		wPos[0] = maxW;
		wPos[1] = startPos;
		wPos[2] = endPos;
		//(maxW, startPos, endPos);
		return true;
	}
	else
	{
		return false;
	}
}

bool getCenterInRow(const cv::Mat& lightGray, int row, cv::Point2f& centerPoint, int thresh)
{
	Vec3i wPos;
	if (detectStripeInRow(lightGray, row, wPos, thresh))
	{
		double sc = 0;
		double sm = 0;
		for (int j = wPos[1]; j < wPos[2]; ++j)
		{
			sc += lightGray.at<uchar>(row, j);
			sm += j * lightGray.at<uchar>(row, j);
		}
		centerPoint.y = row;
		centerPoint.x = sm / static_cast<float>(sc);
		return true;
	}
	else
	{
		return false;
	}
}

void grayCenterWidthRow(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag)
{
	if (threshFlag == CENTER_TOTALTHRESH)
	{
		threshold(gray, gray, 0, 255, THRESH_TOZERO + THRESH_OTSU);
		//imshow("gray", gray);
		//waitKey(0);
	}
	if (threshFlag == CENTER_TOTALTHRESH || threshFlag == CENTER_NOTHRESH)
	{
		//阈值后的图求重心
		for (int r = 0; r < gray.rows; ++r)
		{
			Point2f cp;
			if (getCenterInRow(gray, r, cp, 0))
			{
				//求重心Y坐标
				centerPoints.push_back(cp);
			}
		}
	}
	//逐行阈值
	else if (threshFlag == CENTER_COLTHRESH)
	{
		for (int r = 0; r < gray.rows; ++r)
		{
			//求阈值
			int thresh0 = getThreshInRow(gray, r);
			Point2f cp;
			if (getCenterInRow(gray, r, cp, thresh0))
			{
				//求重心Y坐标
				centerPoints.push_back(cp);
			}
		}
	}
}

//赵斌 自适应灰度重心
void weightCenter(Mat& srcImage, vector<Point2f>& centerPoints)
{
	vector<Mat> channels;
	split(srcImage, channels);//分离色彩通道
	Mat& imageRedChannel = channels.at(2);
	//阈值化
	Mat threshed;
	double bestThresh = threshold(imageRedChannel, threshed, 0, 255, THRESH_OTSU);
	threshed = threshed - bestThresh;
	imshow("threhed", threshed);
	waitKey(10);
	//平法加权灰度重心
	grayCenterByRowSquare(threshed, centerPoints, CENTER_NOTHRESH);
}