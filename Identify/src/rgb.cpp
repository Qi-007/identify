#include "rgb.h"

void Find(Scalar lower_colors, Scalar upper_colors, Mat m_hsv, Mat m_frame){
    Mat mask;
        
    // 创建掩码
    inRange(m_hsv, lower_colors, upper_colors, mask);

    // 找到轮廓
    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 绘制轮廓
    for (const auto& contour : contours) {
        Rect boundingBox = boundingRect(contour);
        double area = contourArea(contour);
        if (area > 1500) {
            rectangle( m_frame, boundingBox, Scalar(255, 255, 255), 2 ); 
        }
    }

}

bool testRGB(){
    // 打开视频捕捉设备
    VideoCapture cap("rgb.avi");
    if (!cap.isOpened()) {
        cout << "无法打开视频" << endl;
        return -1;
    }

    Mat frame, hsv;
    // 定义要检测的颜色范围
    Scalar lower_blue(95, 115, 30);
    Scalar upper_blue(110, 180, 260);

    Scalar lower_red(0, 80, 40);
    Scalar upper_red(12, 185, 160);

    Scalar lower_green(45, 60, 30);
    Scalar upper_green(85, 150, 130);


    while (true) {
        // 读取帧
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        // 转换到 HSV 颜色空间
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        
        Find(lower_blue, upper_blue, hsv, frame);        
        Find(lower_red, upper_red, hsv, frame);        
        Find(lower_green, upper_green, hsv, frame);


        // 显示结果
        imshow( "GBR", frame );
        waitKey(30);
    }

    // 释放视频捕捉设备
    cap.release();
    destroyAllWindows();
    return 0;
}

