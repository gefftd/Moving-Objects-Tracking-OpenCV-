#ifndef TRACK_H
#define TRACK_H
#include<opencv2/opencv.hpp>

struct TrackObject{
    cv::Point center;
    int id;
    cv::Rect box;
    int missedFrames;
};
class Track{
   public:
   Track(double distThresh);
   void update(const std::vector<cv::Rect>& boxes);
   void Draw(cv::Mat& frame);

   private:
   double threshold;
   int nextID;
   std::vector<TrackObject> objects;//类的成员对象，包含若干个结构体
   cv::Point getCenter(const cv::Rect& r);

};

#endif