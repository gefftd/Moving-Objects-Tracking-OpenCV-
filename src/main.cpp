#include <opencv2/opencv.hpp>
#include <iostream>
#include "ClassInclude.h"
#include"Track.h"

using namespace std;
using namespace cv;

void modeSelect(int mode);
VideoCapture cap;
int mode = 1;        // 模式2,画面大小折衷
double alpha = 0.05; // 背景更新速度
int mp_size = 3;     // 形态学处理核的尺寸
int minAera=1000;     //轮廓的最小尺寸
//使用视频数据集的相关参数
bool isCameraUsed = false;
vector<string> files;
int pic_number=0;
double disThresh=50.0;

BackGroundSub bg(alpha);
MorphoProcess mp(mp_size); // 形态学去噪声
ContourDetector cd(minAera);
Track tk(disThresh);  //跟踪并且画框

int main()
{

    if (isCameraUsed)
    {
        modeSelect(mode); // 这里会把相机打开
        if (cap.isOpened())
        {
            cout << "打开相机成功!" << endl;
        }
        else
        {
            cout << "打开相机失败" << endl;
            return -1;
        }
    }
    else{
        
        glob("../../dataset/dynamicBackground/boats/input/*.jpg",files);
        
    }

    Mat orin_frame,frame, mask;
    vector<Rect> boxes;
    while (true)
    {
        if(!isCameraUsed){  //使用数据集的情况
          if(pic_number>=files.size()) pic_number=0;
          orin_frame=imread(files[pic_number++]);
          frame=orin_frame.clone();// 深拷贝，保护原始数据集
          //其实不需要，修改的是内存里的图像，不是磁盘的。
        }
        else{
          cap >> frame;
        }
        
        if (frame.empty())
        {
            cout << "获取帧失败" << endl;
        }

        bg.apply(frame, mask);    //前景检测
        mp.apply(mask);           //形态学去噪声
        boxes=cd.getBoundingBoxes(mask);   //轮廓检测
        tk.update(boxes);
        tk.Draw(frame);

        imshow("Frame", frame);
        imshow("Mask", mask);
        //imshow("orin",orin_frame);

        char c = waitKey(10);
        if (c == 'q')
        {
            cout << "程序被手动退出" << endl;
            break;
        }
    }
    cap.release();
    return 0;
}

// 模式调节函数
void modeSelect(int mode)
{
    cap.release();
    cap.open(2, CAP_V4L2); // 先关再打开才能设置模式
    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    if (mode == 0)
    {
        cap.set(CAP_PROP_FRAME_WIDTH, 320);
        cap.set(CAP_PROP_FRAME_HEIGHT, 240);
        cap.set(CAP_PROP_FPS, 120); // 在ubuntu上不能有这个
        // 帧率不支持，ubuntu自动选择未压缩格式，不能达到这个帧率
    }
    else if (mode == 1)
    {
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 480);
        cap.set(CAP_PROP_FPS, 120);
    }
    else
    {
        cap.set(CAP_PROP_FRAME_WIDTH, 1920);
        cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
        cap.set(CAP_PROP_FPS, 30);
    }
}