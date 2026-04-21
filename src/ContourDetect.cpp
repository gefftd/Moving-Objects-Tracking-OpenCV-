#include"ClassInclude.h"
using namespace std;

ContourDetector::ContourDetector(double areaThreshold):minArea(areaThreshold){}

vector<Rect> ContourDetector::getBoundingBoxes(const Mat&mask){
    vector<vector<Point>> contours;//这是一帧的数据，是闭合轮廓的点集
    vector<Rect> boxes;
    findContours(mask,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    for(auto& c:contours){
        double area=contourArea(c);
        if(area<minArea) continue;
        boxes.push_back(boundingRect(c));
    }
    return boxes;
}
/*
void ContourDetector::detect(const Mat& mask,Mat &frame){
    //不使用引用的话是有开销的，会复制header,引用计数增加
    vector<Rect> boxes=getBoundingBoxes(mask);
    for(auto & box:boxes){
        rectangle(frame,box,Scalar(0,255,0),2);
    }
}*/