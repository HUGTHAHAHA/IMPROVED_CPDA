
#include"grayCenterColumn.h"

using namespace cv;
using namespace std;

int getThreshInCol(Mat& lightGray, int col)
{
	vector<int> rPoints(256, 0);
	for (int j = 0; j < lightGray.rows; ++j)
	{
		++rPoints[lightGray.at<uchar>(j, col)];
	}
	float avg1, avg2;
	int thresh = myThresh(rPoints, avg1, avg2);
	return thresh;
}

void myThreshCol(Mat& lightGray)
{
	for (int i = 0; i < lightGray.cols; ++i)
	{
		int thresh = getThreshInCol(lightGray, i);
		for (int j = 0; j < lightGray.rows; ++j)
		{
			if (lightGray.at<uchar>(j, i) <= thresh)
			{
				lightGray.at<uchar>(j, i) = 0;
			}
		}
	}
}

bool getCenterInCol(const Mat& gray, int col, double& centerY, int thresh)
{
	double sum = 0;
	double count = 0;
	//const uchar* grayCol = gray.ptr<uchar>();
	for (int r = 0; r < gray.rows; ++r)
	{
		int val = gray.at<uchar>(r, col);
		if (val > thresh)
		{
			sum += (r*val);
			count += val;
		}
	}
	if (count > 0)
	{
		centerY = sum / count;
		return true;
	}
	return false;
}

void grayCenterByCol(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag)
{

	if (threshFlag == CENTER_TOTALTHRESH)
	{
		double thresh = threshold(gray, gray, 0, 255, THRESH_TOZERO + THRESH_OTSU);
		cout << "�����ֵ" << thresh << endl;
		//imshow("gray", gray);
		//waitKey(0);
	}
	if (threshFlag == CENTER_TOTALTHRESH || threshFlag == CENTER_NOTHRESH)
	{
		//��ֵ���ͼ������
		for (int c = 0; c < gray.cols; ++c)
		{
			double y = 0;
			if (getCenterInCol(gray, c, y))
			{
				//������Y����
				centerPoints.push_back(Point2f(c, y));
			}
		}
	}
	//������ֵ
	else if (threshFlag == CENTER_COLTHRESH)
	{
		for (int c = 0; c < gray.cols; ++c)
		{
			//����ֵ
			int thresh = getThreshInCol(gray, c);
			double y = 0;
			if (getCenterInCol(gray, c, y, thresh))
			{
				//������Y����
				centerPoints.push_back(Point2f(c, y));
			}
		}
	}
}


cv::Mat& drawCenterPoints(cv::Mat& src, std::vector <cv::Point2f>& centerPoints, const cv::Scalar& color)
{
	if (src.channels() == 1)
	{
		if (src.depth() == CV_8U)
		{
			for (auto& point : centerPoints)
			{
				int r(point.y);
				int c(point.x);
				if (r >= 0 && r < src.rows&& c >= 0 && c < src.cols)
				{
					src.at<uchar>(r, c) = color[0];
				}
			}
		}
		else if (src.depth() == CV_32F)
		{
			for (auto& point : centerPoints)
			{
				int r(point.y);
				int c(point.x);
				if (r >= 0 && r < src.rows&& c >= 0 && c < src.cols)
				{
					src.at<float>(r, c) = color[0];
				}
			}
		}
	}
	else if (src.channels() == 3)
	{
		if (src.depth() == CV_8U)
		{
			for (auto& point : centerPoints)
			{
				int r(point.y);
				int c(point.x);
				if (r >= 0 && r < src.rows&& c >= 0 && c < src.cols)
				{
					src.at<Vec3b>(r, c) = Vec3b(color[0], color[1], color[2]);
				}
			}
		}
		else if (src.depth() == CV_32F)
		{
			for (auto& point : centerPoints)
			{
				int r(point.y);
				int c(point.x);
				if (r >= 0 && r < src.rows&& c >= 0 && c < src.cols)
				{
					src.at<Vec3f>(r, c) = Vec3b(color[0], color[1], color[2]);
				}
			}
		}
	}
	return src;
}

cv::Mat& drawCenterPoints(cv::Mat& src, const std::vector<cv::Point2f>& centerPoints, const cv::Scalar& color /*= cv::Scalar(0, 0, 255)*/)
{
	if (src.channels() == 1)
	{
		if (src.depth() == CV_8U)
		{
			for (auto& point : centerPoints)
			{
				int r(point.y);
				int c(point.x);
				if (r >= 0 && r < src.rows&& c >= 0 && c < src.cols)
				{
					src.at<uchar>(r, c) = color[0];
				}
			}
		}
		else if (src.depth() == CV_32F)
		{
			for (auto& point : centerPoints)
			{
				int r(point.y);
				int c(point.x);
				if (r >= 0 && r < src.rows&& c >= 0 && c < src.cols)
				{
					src.at<float>(r, c) = color[0];
				}
			}
		}
	}
	else if (src.channels() == 3)
	{
		if (src.depth() == CV_8U)
		{
			for (auto& point : centerPoints)
			{
				int r(point.y);
				int c(point.x);
				if (r >= 0 && r < src.rows&& c >= 0 && c < src.cols)
				{
					src.at<Vec3b>(r, c) = Vec3b(color[0], color[1], color[2]);
				}
			}
		}
		else if (src.depth() == CV_32F)
		{
			for (auto& point : centerPoints)
			{
				int r(point.y);
				int c(point.x);
				if (r >= 0 && r < src.rows&& c >= 0 && c < src.cols)
				{
					src.at<Vec3f>(r, c) = Vec3b(color[0], color[1], color[2]);
				}
			}
		}
	}
	return src;
}

cv::Mat& drawCenterPoints(cv::Mat& src, const std::vector<std::vector<cv::Point2f>>& vCenterPoints, const cv::Scalar& color /*= cv::Scalar(0, 0, 255)*/)
{
	for (const auto& item : vCenterPoints)
	{
		drawCenterPoints(src, item, color);
	}
	return src;
}

bool detectStripe(const Mat& lightGray, int col, cv::Vec3i& wPos, int thresh)
{
	int w = 0;
	int maxW = 0;
	int startPos = 0;
	int tmpStartPos = 0;
	int endPos = 0;
	for (int i = 0; i < lightGray.rows;)
	{
		while (i < lightGray.rows && lightGray.at<uchar>(i, col)>thresh)//������ֵ
		{
			int tmp = lightGray.at<uchar>(i, col);
			if (w == 0)
			{
				tmpStartPos = i;
			}
			++w;
			++i;
		}
		//ֻ���������� ��������
		if (w > maxW)
		{
			maxW = w;
			startPos = tmpStartPos;
			endPos = i;//endPos Ϊβ��Ԫ��

		}
		w = 0;
		++i;
	}
	if (maxW >= 3)//���ƿ�����ֵ
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

bool getCenterInCol(const Mat& lightGray, int col, Point2f& centerPoint, int thresh)
{
	Vec3i wPos;
	if (detectStripe(lightGray, col, wPos, thresh))
	{
		double sc = 0;
		double sm = 0;
		for (int j = wPos[1]; j < wPos[2]; ++j)
		{
			sc += lightGray.at<uchar>(j, col);
			sm += j * lightGray.at<uchar>(j, col);
		}
		centerPoint.x = col;
		centerPoint.y = sm / static_cast<float>(sc);
		return true;
	}
	else
	{
		return false;
	}

}

void grayCenterWidthCol(cv::Mat& gray, std::vector<cv::Point2f>& centerPoints, int threshFlag)
{

	if (threshFlag == CENTER_TOTALTHRESH)
	{
		threshold(gray, gray, 0, 255, THRESH_TOZERO + THRESH_OTSU);
		//imshow("gray", gray);
		//waitKey(0);
	}
	if (threshFlag == CENTER_TOTALTHRESH || threshFlag == CENTER_NOTHRESH)
	{
		//��ֵ���ͼ������
		for (int c = 0; c < gray.cols; ++c)
		{
			Point2f cp;
			if (getCenterInCol(gray, c, cp, 0))
			{
				//������Y����
				centerPoints.push_back(cp);
			}
		}
	}
	//������ֵ
	else if (threshFlag == CENTER_COLTHRESH)
	{
		for (int c = 0; c < gray.cols; ++c)
		{
			//����ֵ
			int thresh0 = getThreshInCol(gray, c);
			Point2f cp;
			if (getCenterInCol(gray, c, cp, thresh0))
			{
				//������Y����
				centerPoints.push_back(cp);
			}
		}
	}
}

//�ڹ������Ĵ� �����������ƿ���
int getWidthInCenterCol(Mat& imgGray, Point2f& centerPoint)
{
	int w = 1;
	int x0 = round(centerPoint.x);
	int y0 = round(centerPoint.y);
	//���ϼ���
	int y = y0 - 1;
	while (imgGray.at<uchar>(y, x0) && y >= 0)
	{
		++w;
		--y;//���ϼ���
	}
	y = y0 + 1;
	while (imgGray.at<uchar>(y, x0) && y < imgGray.rows)
	{
		++w;
		++y;//�������
	}
	return w;
}

//���ʼ���ĵ� ���������з�����ȷ���
double getDeviationInCols(Mat& imgGray, Point2f& centerPoint)
{
	vector<int> width;
	for (int i = -4; i <= 4; ++i)
	{
		int x = centerPoint.x + i;//����ĳһ��
		Point2f tmp(x, centerPoint.y);
		int w = getWidthInCenterCol(imgGray, tmp);
		if (w > 2 && w < 40)
		{
			width.push_back(w);
		}
	}
	return deviation(width);
}