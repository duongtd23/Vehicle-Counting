#pragma once

#include <stdexcept>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "Blob.h"

class MyVehicleCounting{
public:
	// global variables ///////////////////////////////////////////////////////////////////////////////
	cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
	cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
	cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
	cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
	cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);

	//bigger is car and smaller is motor
	int MIN_AREA = 13000;

	//line position to check pass and counting
	double linePos = 0.6;

	//min distance of 2 blob to track the same id
	double minDistanceToCheckMatch = 0.5;

	int minArea = 500;
	int minWidth = 30;
	int minHeight = 50;
	int minRatio = 0.3;
	int maxRatio = 1.5;
	int minDiagonalSize = 60;

	int VIDEO_WIDTH = 360;

	//file path video input - must use absolute path
	std::string input;
	cv::VideoCapture capVideo;

	//mat to use for image subtraction
	cv::Mat imgFrame1;
	cv::Mat imgFrame2;

	//list blobs - vehicles
	std::vector<Blob> blobs;
	cv::Point crossingLine[2];

	//save number of car and motor
	int carCountDTT = 0;
	int motorCountDTT = 0;
	int carCountTTD = 0;
	int motorCountTTD = 0;

	const int COUNT_TOP_TO_DOWN = 0;
	const int COUNT_DOWN_TO_TOP = 1;
	const int COUNT_COMBINE = 2;

	int count_type = 0;

	bool isCounting = false;

	// function prototypes ////////////////////////////////////////////////////////////////////////////
	MyVehicleCounting(std::string input, int count_type);
	void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
	void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
	void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
	double distanceBetweenPoints(cv::Point point1, cv::Point point2);
	void drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName);
	void drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName);
	bool checkIfBlobsCrossedTheLineDTT(std::vector<Blob> &blobs, int &intHorizontalLinePosition, int &carCount, int &motorCount);
	bool checkIfBlobsCrossedTheLineTTD(std::vector<Blob> &blobs, int &intHorizontalLinePosition, int &carCount, int &motorCount);
	void drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy);
	void drawCarCountOnImage(int &carCount, int &motorCount, cv::Mat &imgFrame2Copy);
	int functionMain(std::string ouput, bool writeVideoOutput);

	int getMotorCountDTT();
	int getCarCountDTT();
	int getMotorCountTTD();
	int getCarCountTTD();

	void destroy();
};