#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp> //selectROI is part of this
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
  cv::Mat img;
  if(argc >= 2)
    img = cv::imread(argv[1]);
  else
    img = cv::imread(../cat.jpg");

  cv::
  return 0;
}
