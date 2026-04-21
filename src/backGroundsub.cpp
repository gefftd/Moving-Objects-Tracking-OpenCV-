#include"ClassInclude.h"
using namespace cv;

BackGroundSub::BackGroundSub(double a):alpha(a),isInitialized(false){}


//running average模型 Background = α * 当前帧 + (1-α) * 旧背景
void BackGroundSub::apply(const Mat& frame,Mat& fgMask){
    Mat gray;
    cvtColor(frame,gray,COLOR_BGR2GRAY);
    gray.convertTo(gray,CV_8U);
    if (!isInitialized) {
        background = gray.clone();
        isInitialized = true;
        fgMask = Mat::zeros(gray.size(), CV_8U);
        return;
    }

    // 更新背景
    background = (1 - alpha) * background + alpha * gray;

    Mat bg8u;
    background.convertTo(bg8u, CV_8U);

    // 差分
    Mat diff;
    absdiff(gray, bg8u, diff);  //当前帧与背景做差=运动区域

    threshold(diff, fgMask, 25, 255, THRESH_BINARY);//二值化
}