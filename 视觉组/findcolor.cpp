#include<vector>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
vector<vector<int>>mycolors{ {140,195,88,204,75,255},{23,36,55,147,149,233} };
vector<Scalar>mycolorvalues{ {},{} };
int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        //cout << "����ͷ��ռ���˻���û��ã�" << endl;
        return -1;
    }
    //140 195 88 204 75 255//red
    //23 36 55 147 149 223//yellow
    Mat img;
    Mat imgHSV, mask;
    int hmin = 140, smin = 88, vmin = 46;
    int hmax = 195, smax = 204, vmax = 255;
    //ʶ����ɫ����תHSV���ٻ���,Hɫ����S���Ͷȣ�V����
    namedWindow("trackbars", WINDOW_NORMAL);
    createTrackbar("hmin", "trackbars", &hmin, 255);
    createTrackbar("hmax", "trackbars", &hmax, 255);
    createTrackbar("smin", "trackbars", &smin, 255);
    createTrackbar("smax", "trackbars", &smax, 255);
    createTrackbar("vmin", "trackbars", &vmin, 255);
    createTrackbar("vmax", "trackbars", &vmax, 255);

    while (true)
    {
        // 1. ���������ͷ��һ֡��
        cap.read(img);
        if (img.empty()) break; // �����������ֱ������

        // 2. �����ת������ѭ����
        cvtColor(img, imgHSV, COLOR_BGR2HSV);

        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask);

        // 3. ��ԭͼ�� mask ����ʾ����������Ա�
        imshow("Original", img);
        imshow("mask", mask);

        // 4. �Ӹ��� ESC �˳����߼�����Ȼ����ض��ز�����
        int key = waitKey(1);
        if (key == 27) { // 27��ESC���ļ���
            break;
        }
    }
    return 0;
}