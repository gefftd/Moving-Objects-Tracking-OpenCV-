#include"Track.h"
#include<cmath>
using namespace std;
using namespace cv;

Track::Track(double distThresh):threshold(distThresh),nextID(0){}

Point Track::getCenter(const Rect& r){
  return Point(r.x+r.width/2,r.y+r.height/2);
}

void Track::update(const vector<Rect>& boxes){
    vector<bool> matched(boxes.size(),false);
    //1.先标记所有的旧目标为未更新,这个有必要吗？
    for(auto &obj:objects){
        obj.missedFrames++;
    }
    //2.遍历当前检测框
    for(int i=0;i<boxes.size();i++){
        Point c=getCenter(boxes[i]);
        double minDist=1e9;
        int bestID=-1;
        //3.找最近目标
        for(int j=0;j<objects.size();j++){
            double d=norm(c-objects[j].center);
            if(d<minDist&&d<threshold){
                minDist=d;
                bestID=j;
            }
        }
        //4.如果匹配成功
        if(bestID!=-1){
            objects[bestID].box=boxes[i];
            objects[bestID].center=c;
            objects[bestID].missedFrames=0;
        }
        else{
            //5.新目标
            TrackObject obj;//会自动归入objects吗？会，因为objects创建的时候就是结构体的集和
            obj.id=nextID++;
            obj.box=boxes[i];
            obj.center=c;
            obj.missedFrames=0;
            objects.push_back(obj);//好吧不能
        }
    }
    //6.删除丢失太久的目标
    objects.erase(
        remove_if(
            objects.begin(),
            objects.end(),
            [](TrackObject &o){return o.missedFrames>5;}
        ),
        objects.end()
    );
}

void Track::Draw(Mat &frame){
  for(auto &obj:objects){
    rectangle(frame,obj.box,Scalar(0,255,0),2);
    putText(
        frame,
        "ID:"+to_string(obj.id),
        obj.box.tl(),
        FONT_HERSHEY_SIMPLEX,
        0.6,
        Scalar(0,255,0),
        2
    );
  }
}