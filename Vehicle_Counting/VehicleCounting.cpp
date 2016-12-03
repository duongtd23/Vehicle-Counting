// main.cpp
#pragma once
#include"VehicleCounting.h"

#include<iostream>
#include<conio.h>           // it may be necessary to change or remove this line if not using Windows

#include "Blob.h"

//implement function
///////////////////////////////////////////////////////////////////////////////////////////////////
MyVehicleCounting::MyVehicleCounting(std::string input, int count_type){
	this->input = input;
	this->count_type = count_type;
}

//main function - call this from C#
/**
 * output: file path to write video output
 * writeVideoOutput: true to write
 */
int MyVehicleCounting::functionMain(std::string ouput, bool writeVideoOutput){
	isCounting = true;
	cv::VideoWriter video;
	cv::Size video_size = cv::Size(640, 360);
	if(writeVideoOutput)
		video = cv::VideoWriter(ouput, CV_FOURCC('M', 'J', 'P', 'G'), 10, video_size, true);
	capVideo.open(input);

	if (!capVideo.isOpened()) {                                                 // if unable to open video file
		std::cout << "error reading video file" << std::endl << std::endl;      // show error message
		_getch();                   // it may be necessary to change or remove this line if not using Windows
		return(0);                                                              // and exit program
	}

	if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 2) {
		std::cout << "error: video file must have at least two frames";
		_getch();                   // it may be necessary to change or remove this line if not using Windows
		return(0);
	}

	//cv::Mat tempImg1, tempImg2;
	capVideo.read(imgFrame1);
	capVideo.read(imgFrame2);

	int intHorizontalLinePosition = (int)std::round((double)imgFrame1.rows * linePos);

	crossingLine[0].x = 0;
	crossingLine[0].y = intHorizontalLinePosition;

	crossingLine[1].x = imgFrame1.cols - 1;
	crossingLine[1].y = intHorizontalLinePosition;

	char chCheckForEscKey = 0;

	bool blnFirstFrame = true;

	int frameCount = 2;

	while (capVideo.isOpened() && chCheckForEscKey != 27 && isCounting) {

		std::vector<Blob> currentFrameBlobs;

		cv::Mat imgFrame1Copy = imgFrame1.clone();
		cv::Mat imgFrame2Copy = imgFrame2.clone();

		cv::Mat imgDifference;
		cv::Mat imgThresh;

		cv::cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
		cv::cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);

		cv::GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
		cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);

		cv::absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);

		cv::threshold(imgDifference, imgThresh, 30, 255.0, CV_THRESH_BINARY);

		//		cv::imshow("imgThresh", imgThresh);

		cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
		cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
		cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
		cv::Mat structuringElement15x15 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));

		for (unsigned int i = 0; i < 2; i++) {
			cv::dilate(imgThresh, imgThresh, structuringElement5x5);
			cv::dilate(imgThresh, imgThresh, structuringElement5x5);
			cv::erode(imgThresh, imgThresh, structuringElement5x5);
		}

		cv::Mat imgThreshCopy = imgThresh.clone();

		std::vector<std::vector<cv::Point> > contours;

		cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		//		drawAndShowContours(imgThresh.size(), contours, "imgContours");

		std::vector<std::vector<cv::Point>> convexHulls(contours.size());

		for (unsigned int i = 0; i < contours.size(); i++) {
			cv::convexHull(contours[i], convexHulls[i]);
		}

		//		drawAndShowContours(imgThresh.size(), convexHulls, "imgConvexHulls");

		for (auto &convexHull : convexHulls) {
			Blob possibleBlob(convexHull);

			if (possibleBlob.currentBoundingRect.area() > minArea &&
				possibleBlob.dblCurrentAspectRatio > minRatio &&
				possibleBlob.dblCurrentAspectRatio < maxRatio &&
				possibleBlob.currentBoundingRect.width > minWidth &&
				possibleBlob.currentBoundingRect.height > minHeight &&
				possibleBlob.dblCurrentDiagonalSize > minDiagonalSize &&
				(cv::contourArea(possibleBlob.currentContour) / (double)possibleBlob.currentBoundingRect.area()) > minDistanceToCheckMatch) {
				currentFrameBlobs.push_back(possibleBlob);
			}
		}

		//		drawAndShowContours(imgThresh.size(), currentFrameBlobs, "imgCurrentFrameBlobs");

		if (blnFirstFrame == true) {
			for (auto &currentFrameBlob : currentFrameBlobs) {
				blobs.push_back(currentFrameBlob);
			}
		}
		else {
			matchCurrentFrameBlobsToExistingBlobs(blobs, currentFrameBlobs);
		}

		//		drawAndShowContours(imgThresh.size(), blobs, "imgBlobs");

		imgFrame2Copy = imgFrame2.clone();          // get another copy of frame 2 since we changed the previous frame 2 copy in the processing above

		drawBlobInfoOnImage(blobs, imgFrame2Copy);

		bool blnAtLeastOneBlobCrossedTheLine;
		if (count_type == COUNT_DOWN_TO_TOP)
			blnAtLeastOneBlobCrossedTheLine = checkIfBlobsCrossedTheLineDTT(blobs, intHorizontalLinePosition, carCountDTT, motorCountDTT);
		else if (count_type == COUNT_TOP_TO_DOWN)
			blnAtLeastOneBlobCrossedTheLine = checkIfBlobsCrossedTheLineTTD(blobs, intHorizontalLinePosition, carCountTTD, motorCountTTD);
		if (blnAtLeastOneBlobCrossedTheLine == true) {
			cv::line(imgFrame2Copy, crossingLine[0], crossingLine[1], SCALAR_GREEN, 2);
		}
		else {
			cv::line(imgFrame2Copy, crossingLine[0], crossingLine[1], SCALAR_RED, 2);
		}

		if (count_type == COUNT_TOP_TO_DOWN)
			drawCarCountOnImage(carCountTTD, motorCountTTD, imgFrame2Copy);
		else if (count_type == COUNT_DOWN_TO_TOP)
			drawCarCountOnImage(carCountDTT, motorCountDTT, imgFrame2Copy);

		cv::imshow("Output", imgFrame2Copy);

		//cv::waitKey(0);                 // uncomment this line to go frame by frame for debugging

		// now we prepare for the next iteration

		currentFrameBlobs.clear();

		imgFrame1 = imgFrame2.clone();           // move frame 1 up to where frame 2 is

		if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) {
			capVideo.read(imgFrame2);
		}
		else {
			std::cout << "end of video\n";
			break;
		}

		//ghi video
		if (writeVideoOutput)
			video.write(imgFrame2Copy);

		blnFirstFrame = false;
		frameCount++;
		chCheckForEscKey = cv::waitKey(1);
	}



	if (chCheckForEscKey != 27) {               // if the user did not press esc (i.e. we reached the end of the video)
		cv::waitKey(33);                         // hold the windows open to allow the "end of video" message to show
	}
	// note that if the user did press esc, we don't need to hold the windows open, we can simply let the program end which will close the windows

	return(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MyVehicleCounting::matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, 
						std::vector<Blob> &currentFrameBlobs) {

	for (auto &existingBlob : existingBlobs) {

		existingBlob.blnCurrentMatchFoundOrNewBlob = false;

		existingBlob.predictNextPosition();
	}

	for (auto &currentFrameBlob : currentFrameBlobs) {

		int intIndexOfLeastDistance = 0;
		double dblLeastDistance = 100000.0;

		for (unsigned int i = 0; i < existingBlobs.size(); i++) {

			if (existingBlobs[i].blnStillBeingTracked == true) {

				double dblDistance = distanceBetweenPoints(currentFrameBlob.centerPositions.back(), existingBlobs[i].predictedNextPosition);

				if (dblDistance < dblLeastDistance) {
					dblLeastDistance = dblDistance;
					intIndexOfLeastDistance = i;
				}
			}
		}

		if (dblLeastDistance < currentFrameBlob.dblCurrentDiagonalSize * minDistanceToCheckMatch) {
			addBlobToExistingBlobs(currentFrameBlob, existingBlobs, intIndexOfLeastDistance);
		}
		else {
			addNewBlob(currentFrameBlob, existingBlobs);
		}

	}

	for (auto &existingBlob : existingBlobs) {

		if (existingBlob.blnCurrentMatchFoundOrNewBlob == false) {
			existingBlob.intNumOfConsecutiveFramesWithoutAMatch++;
		}

		if (existingBlob.intNumOfConsecutiveFramesWithoutAMatch >= 5) {
			existingBlob.blnStillBeingTracked = false;
		}

	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MyVehicleCounting::addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex) {

	existingBlobs[intIndex].currentContour = currentFrameBlob.currentContour;
	existingBlobs[intIndex].currentBoundingRect = currentFrameBlob.currentBoundingRect;

	existingBlobs[intIndex].centerPositions.push_back(currentFrameBlob.centerPositions.back());

	existingBlobs[intIndex].dblCurrentDiagonalSize = currentFrameBlob.dblCurrentDiagonalSize;
	existingBlobs[intIndex].dblCurrentAspectRatio = currentFrameBlob.dblCurrentAspectRatio;

	existingBlobs[intIndex].blnStillBeingTracked = true;
	existingBlobs[intIndex].blnCurrentMatchFoundOrNewBlob = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MyVehicleCounting::addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs) {

	currentFrameBlob.blnCurrentMatchFoundOrNewBlob = true;

	existingBlobs.push_back(currentFrameBlob);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
double MyVehicleCounting::distanceBetweenPoints(cv::Point point1, cv::Point point2) {

	int intX = abs(point1.x - point2.x);
	int intY = abs(point1.y - point2.y);

	return(sqrt(pow(intX, 2) + pow(intY, 2)));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MyVehicleCounting::drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName) {
	cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);

	cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);

	cv::imshow(strImageName, image);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MyVehicleCounting::drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName) {

	cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);

	std::vector<std::vector<cv::Point> > contours;

	for (auto &blob : blobs) {
		if (blob.blnStillBeingTracked == true) {
			contours.push_back(blob.currentContour);
		}
	}

	cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);

	cv::imshow(strImageName, image);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool MyVehicleCounting::checkIfBlobsCrossedTheLineDTT(std::vector<Blob> &blobs, int &intHorizontalLinePosition, int &carCount, int &motorCount) {
	bool blnAtLeastOneBlobCrossedTheLine = false;

	for (auto blob : blobs) {

		if (blob.blnStillBeingTracked == true && blob.centerPositions.size() >= 2) {
			int prevFrameIndex = (int)blob.centerPositions.size() - 2;
			int currFrameIndex = (int)blob.centerPositions.size() - 1;
			//bool check = true;
			//
			//int minLop = (blob.centerPositions.size() > 10) ? (blob.centerPositions.size() - 10) : 1;
			////minLop = blob.centerPositions.size() - 1;
			//for (int fi = blob.centerPositions.size() - 2; fi >= minLop; fi--) {
			//	cv::Point point = blob.centerPositions[fi];
			//	if (point.y > intHorizontalLinePosition) {
			//		check = false;
			//		break;
			//	}
			//}

			if (blob.centerPositions[prevFrameIndex].y > intHorizontalLinePosition && 
				blob.centerPositions[currFrameIndex].y <= intHorizontalLinePosition) {
				if (blob.currentBoundingRect.width * blob.currentBoundingRect.height > MIN_AREA)
					carCount++;
				else
					motorCount++;
				blnAtLeastOneBlobCrossedTheLine = true;
			}
		}

	}

	return blnAtLeastOneBlobCrossedTheLine;
}

bool MyVehicleCounting::checkIfBlobsCrossedTheLineTTD(std::vector<Blob> &blobs, int &intHorizontalLinePosition, int &carCount, int &motorCount) {
	bool blnAtLeastOneBlobCrossedTheLine = false;

	for (auto blob : blobs) {

		if (blob.blnStillBeingTracked == true && blob.centerPositions.size() >= 2) {
			int prevFrameIndex = (int)blob.centerPositions.size() - 2;
			int currFrameIndex = (int)blob.centerPositions.size() - 1;

			if (blob.centerPositions[prevFrameIndex].y < intHorizontalLinePosition &&
				blob.centerPositions[currFrameIndex].y >= intHorizontalLinePosition) {
				if (blob.currentBoundingRect.width * blob.currentBoundingRect.height > MIN_AREA)
					carCount++;
				else
					motorCount++;
				blnAtLeastOneBlobCrossedTheLine = true;
			}
		}

	}

	return blnAtLeastOneBlobCrossedTheLine;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void MyVehicleCounting::drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy) {

	for (unsigned int i = 0; i < blobs.size(); i++) {

		if (blobs[i].blnStillBeingTracked == true) {
			//drawExtract(blobs[i].currentBoundingRect, imgFrame2Copy, i);

			if (blobs[i].currentBoundingRect.area() > 0) {
				cv::rectangle(imgFrame2Copy, blobs[i].currentBoundingRect, SCALAR_RED, 1);

				int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
				double dblFontScale = blobs[i].dblCurrentDiagonalSize / 300.0;
				int intFontThickness = (int)std::round(dblFontScale * 0.6);

				cv::putText(imgFrame2Copy, std::to_string(i), blobs[i].centerPositions.back(), intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void MyVehicleCounting::drawCarCountOnImage(int &carCount, int &motorCount, cv::Mat &imgFrame2Copy) {

	int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
	double dblFontScale = (imgFrame2Copy.rows * imgFrame2Copy.cols) / 200000.0;
	int intFontThickness = (int)std::round(dblFontScale * 1.5);

	cv::Size textSize = cv::getTextSize(std::to_string(carCount), intFontFace, dblFontScale, intFontThickness, 0);

	cv::Point ptTextBottomLeftPosition;

	ptTextBottomLeftPosition.x = imgFrame2Copy.cols - 1 - (int)((double)textSize.width * 1.25);
	ptTextBottomLeftPosition.y = (int)((double)textSize.height * 1.25);

	cv::copyMakeBorder(imgFrame2Copy, imgFrame2Copy, 80, 0, 0, 0, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0, 0));
	
	cv::putText(imgFrame2Copy, std::to_string(carCount), ptTextBottomLeftPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
	cv::putText(imgFrame2Copy, std::to_string(motorCount), cv::Point(10,50), intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
}

int MyVehicleCounting::getMotorCountDTT(){
	return motorCountDTT;
}
int MyVehicleCounting::getCarCountDTT(){
	return carCountDTT;
}
int MyVehicleCounting::getMotorCountTTD(){
	return motorCountTTD;
}
int MyVehicleCounting::getCarCountTTD(){
	return carCountTTD;
}

//destroy
void MyVehicleCounting::destroy(){
	carCountDTT = 0;
	carCountTTD = 0;
	motorCountDTT = 0;
	motorCountTTD = 0;
	isCounting = false;
}
