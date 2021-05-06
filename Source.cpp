#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
	Mat img = imread(argv[1], IMREAD_GRAYSCALE);

	if (!img.data) {
		cout << "Could not find image!" << endl;
		return -1;
	}

	Mat copy = img.clone();

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();

	printf("Height: %d,  width: %d,	width step: %d,	Channels: %d\n", height, width, widthstep, ch);

	//Allocate memory location
	int histogram[256];
	int cNew[256];
	int equalHistogram[256];
	double prob[256];
	double cProb[256];

	// initialize all the gray level values to 0
	for (int i = 0; i < 256; i++) {
		histogram[i] = 0;
		cNew[i] = 0;
		prob[i] = 0.0;
		cProb[i] = 0.0;
		equalHistogram[i] = 0;
	}

	// Calculate pixels for each gray level intensity
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			histogram[img.at<uchar>(y, x)] = histogram[img.at<uchar>(y, x)] + 1;
		}
	}

	// Total no of pixels
	int N = height * width;

	// Calculate the probability of each intensity
	for (int i = 0; i < 256; i++) {
		prob[i] = (double)histogram[i] / N;
	}

	// Generate cumulative probability
	cProb[0] = prob[0];
	for (int i = 1; i < 256; i++) {
		cProb[i] = cProb[i - 1] + prob[i];
	}

	for (int i = 0; i < 256; i++) {
		printf("cummuative Prob for Probility at %d is %f\n", i, cProb[i]);
	}

	for (int i = 0; i < 256; i++) {
		cNew[i] = cvRound(cProb[i] * 255);
	}

	int z = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			z = cNew[(int)img.at<uchar>(y, x)];
			copy.at<uchar>(y, x) = (uchar)z;
		}
	}

	// Calculate pixels for each gray level intensity of Equalized image
	/*for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			equalHistogram[(int)img.at<uchar>(y, x)] = equalHistogram[(int)img.at<uchar>(y, x)] + 1;
		}
	}

	// draw histogram
	int hist_w = 512;
	int hist_h = 400;

	Mat histImg(hist_h, hist_w, CV_8UC1, Scalar(255));
	Mat equalImg(hist_h, hist_w, CV_8UC1, Scalar(255));

	*/
	namedWindow("Image");
	imshow("Image", img);

	namedWindow("Copy");
	imshow("Copy", copy);




	waitKey(0);
	return 0;
}