#ifndef CLASSINCLUDE_H
#define CLASSINCLUDE_H

#include<opencv2/opencv.hpp>
using namespace cv;
//减去背景
class BackGroundSub{
    public:
    BackGroundSub(double alpha); 
    void apply(const cv::Mat& frame, cv::Mat& fgMask);
    private:
    double alpha;
    cv::Mat background;
    bool isInitialized;
};
//形态学去除噪声
class MorphoProcess{
   private:
    cv::Mat kernel;
   public:
   MorphoProcess(int size):kernel(cv::getStructuringElement(cv::MORPH_RECT,cv::Size(size,size))){}
   void apply(cv::Mat &Mask){
     morphologyEx(Mask,Mask,cv::MORPH_OPEN,kernel);//开运算，先腐蚀后膨胀
    morphologyEx(Mask,Mask,cv::MORPH_CLOSE,kernel);//开运算去除小噪点，闭运算填补空隙
   }
};
//轮廓检测
class ContourDetector{
   private:
   double minArea;
   public:
   ContourDetector(double areaThreshold);
   //void detect(const Mat&mask, Mat&frame);
   std::vector<Rect> getBoundingBoxes(const Mat&mask);
};

#endif