#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <ctime>

#define w 400
#define alpha_slider_max 100
using namespace cv;

int alpha_slider = 0;
Mat src1, src2;
  

void MyLine(Mat img, cv::Point start, cv::Point end)
{
  srand(time(0));
  int thickness = rand()%10 + 1;
  int linetype = LINE_8;
  cv::line(img, start, end, cv::Scalar(rand()%256, rand()%256, rand()%256), thickness, linetype);
  cv::namedWindow("Line added", WINDOW_AUTOSIZE);
  cv::imshow("Line added", img);
  cv::waitKey(0);
}

void MyEllipse(cv::Mat img, double angle)
{
  srand(time(0));
  int thickness = rand()%10 + 1;
  int linetype = LINE_8;

  ellipse(img,
      Point( w/15, w/15 ),
      Size( w/30, w/50 ),
      angle,
      0,
      360,
      Scalar(rand()%256, rand()%256, rand()%256),
      thickness,
      linetype );

  cv::namedWindow("ellipse added", WINDOW_AUTOSIZE);
  cv::imshow("ellipse added", img);
  cv::waitKey(0);
}

void MyFilledCircle(Mat img, Point center)
{
  circle(img, center, 40 ,Scalar(rand()%256, rand()%256, rand()%256), FILLED);
  cv::destroyAllWindows();
  cv::imshow("ellipse added", img);
  cv::waitKey(0);
}

void trackbarcallback(int, void*)
{
  double alpha = alpha_slider/alpha_slider_max;
  double beta = 1- alpha;
  Mat dst;
  cv::addWeighted(src1, alpha, src2, beta, 0.0, dst);
  cv::imshow("Linear blend", dst);
}
void addTrackbar(Mat src1, Mat src2)
{
  cv::namedWindow("Linear blend", cv::WINDOW_AUTOSIZE);
  char trackbarname[50];
  std::sprintf(trackbarname, "Alpha x %d", alpha_slider);
  cv::createTrackbar(trackbarname, "Linear blend", &alpha_slider, alpha_slider_max, trackbarcallback/* [&alpha_slider, &src1, &src2](int val, void* ptr){
      double alpha = alpha_slider/alpha_slider_max;
      double beta = 1- alpha;
      Mat dst;
      cv::addWeighted(src1, alpha, src2, beta, 0.0, dst);
      cv::imshow("Linear blend", dst);
      cv::waitKey(0); 
      }*/); 
  trackbarcallback(alpha_slider, 0);
  cv::waitKey(0); 
}
int editAndsave(char* imageName, char *destFile, int transformation)
{
  Mat image;
  image = imread( imageName, IMREAD_COLOR );
  if(!imageName || !destFile)
  {
    printf( " No image data \n " );
    return -1;
  }

  /*Mat gray_image;
  cvtColor( image, gray_image, transformation);
  imwrite( destFile, gray_image );
  namedWindow( imageName, WINDOW_AUTOSIZE );
  namedWindow( "Gray image", WINDOW_AUTOSIZE );
  imshow( imageName, image );
  imshow( "Gray image", gray_image );
  waitKey(0);*/

  Mat img = cv::imread( imageName, IMREAD_COLOR);
  namedWindow( imageName, WINDOW_AUTOSIZE );
  cv::imshow(imageName, img);
  cv::waitKey(0);

  cv::Point start(1, 1);
  cv::Point end(90, 90);
  MyLine(img, start, end);
  MyEllipse(img, 90);
  MyFilledCircle( img, Point(40,40));
  /*char selection;
  std::cout << "Lets draw some geometry: press q to exit anytime" << std::endl;
  std::cout << "For Line : press 1" << std::endl;
  std::cin >> selection;
  std::cout << "You have entered : "<< selection << std::endl;
  
  while(selection != 'q')
  {
    switch (selection)
    {
    case '1':
      std::cout << "enter starting x-cordinate : " << std::endl;
      std::cin >> start.x;
      std::cout << "enter starting y-cordinate : " << std::endl;
      std::cin >> start.y;
      
      std::cout << "enter starting x-cordinate : " << std::endl;
      std::cin >> end.x;
      std::cout << "enter starting y-cordinate : " << std::endl;
      std::cin >> end.y;

      MyLine(img, start, end);
      cv::namedWindow("Line added", WINDOW_AUTOSIZE);
      cv::imshow("Line added", img);
      cv::waitKey(0);

      std::cout << "For Line : press 1" << std::endl;
      std::cin >> selection;
      std::cout << "You have entered : "<< selection << std::endl;
      break;
    
    default:
      break;
    }

  }*/

  return 0;
}

int main(int argc, char** argv )
{
  if ( argc < 2 )
  {
    printf("usage: DisplayImage.out <Image_Path>\n");
    return -1;
  }

  Mat image;
  switch(argc)
  {
    case 2:
      image = imread( argv[1], 1 );
      if ( !image.data )
      {
        printf("No image data \n");
        return -1;
      }
      namedWindow("Display Image", WINDOW_AUTOSIZE );
      imshow("Display Image", image);
      waitKey(0);
      break;

    case 3:
      // editAndsave(argv[1], argv[2], COLOR_BGR2GRAY);
      src1 = cv::imread(argv[1]);
      src2 = cv::imread(argv[2]);
      if(src1.empty() || src2.empty())
      {
        std::cout << "invalid input. No image file loaded. about to exit" << std::endl;
        return -1;      
      }
      addTrackbar(src1, src2);
      break;
    default:
      printf("No match found...");
      break;
  }
  return 0;
}
