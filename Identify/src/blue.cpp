#include "blue.h"

bool testBlue(){
        // 打开视频捕捉设备（0为默认摄像头）
    VideoCapture cap("blue.avi");
    if (!cap.isOpened()) {
        cout << "无法打开视频" << endl;
        return -1;
    }

    Mat frame, hsv, mask;
    // 定义要检测的颜色范围
    Scalar lower_blue(100, 125, 40);
    Scalar upper_blue(110, 180, 255);

    while (true) {
        // 读取帧
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        // 转换到 HSV 颜色空间
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        
        // 创建掩码
        inRange(hsv, lower_blue, upper_blue, mask);

        // 找到轮廓
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // 绘制轮廓
        for (const auto& contour : contours) {
            Rect boundingBox = boundingRect(contour);
            double area = contourArea(contour);
            if (area > 2500) {
                rectangle( frame, boundingBox, Scalar(255, 0, 0), 2 ); 
            }
        }

        // 显示结果
        imshow( "Video", frame );
        //imshow( "Mask", mask );

        waitKey(30);
    }

    // 释放视频捕捉设备
    cap.release();
    destroyAllWindows();
    return 0;
}