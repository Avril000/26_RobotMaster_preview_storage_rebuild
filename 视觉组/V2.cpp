#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

vector<vector<int>> newPoints;
 
vector<vector<int>> myColors{
    {24, 44, 0, 58, 133, 255},     // Yellow (黄色)
    {173, 87, 0, 179, 163, 255}    // Red (红色)
    //待调整
};

vector<Scalar> myColorValues{
    {0, 255, 255}, // Yellow
    {0, 0, 255}    // Red
};

// 【关键修改】寻找轮廓并判断灯效状态
Point getContours(Mat imgDil, Mat& img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    Point myPoint(0, 0);

    int lightCount = 0; // 【新增】用来统计找到了几根灯条

    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);

        // 为了更容易识别灯条，把面积阈值从 1000 降到 200
        if (area > 200) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            boundRect[i] = boundingRect(conPoly[i]);

            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;

            // 画框
            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 3);

            lightCount++; // 找到一根，数量 +1
        }
    }

    // 【新增】根据找到的灯条数量，在屏幕上打字
    if (lightCount >= 4) {
        // 找到4根及以上，认为是待激活
        putText(img, "Status: ACTIVE (Ready to hit)", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
    }
    else if (lightCount == 2) {
        // 找到2根，认为是已激活
        putText(img, "Status: ACTIVATED (Already hit)", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
    }

    return myPoint;
}

vector<vector<int>> findColor(Mat img, Mat& originalImg) {
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    newPoints.clear();

    for (int i = 0; i < myColors.size(); i++) {
        Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
        Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);

        Mat mask;
        inRange(imgHSV, lower, upper, mask);

        imshow(to_string(i), mask);

        Point myPoint = getContours(mask, originalImg);

        if ((myPoint.x != 0) && (myPoint.y != 0)) {
            newPoints.push_back({ myPoint.x, myPoint.y, i });
        }
    }
    return newPoints;
}

void drawoncanvas(Mat& img, vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{
    for (int i = 0; i < newPoints.size(); i++)
    {
        circle(img, Point(newPoints[i][0], newPoints[i][1]), 8, myColorValues[newPoints[i][2]], -1);
    }
}

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "摄像头打不开！" << endl;
        return -1;
    }

    Mat img;

    while (true) {
        cap.read(img);
        if (img.empty()) break;

        newPoints = findColor(img, img);
        drawoncanvas(img, newPoints, myColorValues);

        imshow("Image", img);

        if (waitKey(1) == 27) break;
    }

    return 0;
}