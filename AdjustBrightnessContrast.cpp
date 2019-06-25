#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
Mat img;
Mat adjusted_img;
int alpha = 1.0;
int beta = 0;
const int max_slider = 25;

void adjustImgCallback(int val, void* ptr)
{
  for(int y = 0; y < img.rows; y++)
    for(int x = 0; x < img.cols; x++)
      for(int z = 0; z < img.channels(); z++)
      {
        adjusted_img.at<Vec3b>(y,x)[z] = saturate_cast<uchar>(alpha * img.at<Vec3b>(y,x)[z] + beta);
      }
  
  cv::imshow("Adjusted Image", adjusted_img);
}
void doAdjustment()
{
  adjusted_img = Mat::zeros(img.size(), img.type());
  cv::namedWindow("Adjusted Image", cv::WINDOW_AUTOSIZE);
  cv::createTrackbar("brightness bar", "Adjusted Image", &alpha, max_slider, adjustImgCallback); 
  cv::createTrackbar("contrast bar", "Adjusted Image", &beta, max_slider, adjustImgCallback); 
}

int main(int argc, char** argv)
{
  /*
  if(argc < 2)
  {
    std::cout<< "No input file found. Run the program again with the imagefile path to process..." << std::endl;
    return -1;
  }
   */
  
  img = cv::imread("/home/bmw-user/VS_Code_Workspace/openCVLearnings/images/sunset.jpg");
  //img = cv::imread(argv[1]);
  if(img.empty())
  {
    std::cout << "failed to laod the image..." << std::endl;
    return -1;
  }

  cv::namedWindow("Actual Image", cv::WINDOW_AUTOSIZE);
  cv::imshow("Actual Image", img);

  doAdjustment();
  cv::waitKey(0);
  cv::destroyAllWindows();
  return 0;
}

