#include "processing.hpp"

// 带参构造函数的定义
DMS::DMS(int a, int b, int c) {
    second = c % 60;
    minute = b + c / 60;
    degree = a + minute / 60;
}

// 输出函数的定义
void DMS::output() const {
    std::cout << degree << " " << minute << " " << second << " " << std::endl;
}

// 将弧度转化为DMS
DMS::DMS(double radians) {
    if (radians < 0)
        radians += 2 * M_PI;
    second = 3600 * 180 * radians / M_PI;
    degree = second / 3600;
    minute = (second % 3600) / 60;
    second = second % 60;
}

// 重载输出函数的定义
void output(const DMS& a) {
    std::cout << a.degree << " " << a.minute << " " << a.second << " " << std::endl;
}

// 加法函数的定义
DMS addDMS(const DMS& a, const DMS& b) {
    int totalSeconds = (a.degree + b.degree) * 3600 + (a.minute + b.minute) * 60 + (a.second + b.second);
    int degrees = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;
    return DMS(degrees, minutes, seconds);
}

// 减法函数的定义
DMS subtractDMS(const DMS& a, const DMS& b) {
    int totalSecondsA = a.degree * 3600 + a.minute * 60 + a.second;
    int totalSecondsB = b.degree * 3600 + b.minute * 60 + b.second;
    int diffSeconds = totalSecondsA - totalSecondsB;
    if (diffSeconds < 0) diffSeconds += 360 * 3600; // 加上360度
    int degrees = diffSeconds / 3600;
    int minutes = (diffSeconds % 3600) / 60;
    int seconds = diffSeconds % 60;
    return DMS(degrees, minutes, seconds);
}

// 计算闭合差的定义，这是专门计算闭合差的减法函数
int subtractS(DMS a, DMS b) {
    int aTotalSec = a.degree * 3600 + a.minute * 60 + a.second;
    int bTotalSec = b.degree * 3600 + b.minute * 60 + b.second;

    // 计算差值
    int diffSec = aTotalSec - bTotalSec;
    return diffSec;
}

// 计算角度弧度转化的定义
double change(DMS a) {
    return (a.degree + a.minute / 60.0 + a.second / 3600.0) * M_PI / 180.0;
}

// 弧度转角度的定义
DMS radians_to_DMS(double radians) {
    if (radians < 0)
        radians += 2 * M_PI;
    double degrees = radians * 180.0 / M_PI;
    double minutes = (degrees - floor(degrees)) * 60.0;
    double seconds = (minutes - floor(minutes)) * 60.0;
    return DMS(floor(degrees), floor(minutes), floor(seconds));
}

// 计算角度平均值的定义
DMS averageDMS(DMS a, DMS b) {
    int totalSecondsA = a.degree * 3600 + a.minute * 60 + a.second;
    int totalSecondsB = b.degree * 3600 + b.minute * 60 + b.second;
    int totalSeconds = (totalSecondsA + totalSecondsB); // 不除以2，先计算总和

    // 计算平均秒数，并处理奇数进位偶数舍去    
    int averageSeconds = totalSeconds / 2; // 现在除以2得到平均秒数
    int asecond = (totalSeconds / 2) % 2; // 如果平均秒的整数部分是奇数
    // 则asecond为1，否则为0
    if (asecond != 0) { // 如果是奇数，且有余数，则进位；偶不进
        averageSeconds = averageSeconds + totalSeconds % 2;
    }
    // 将平均秒数转换为度、分、秒
    int adegree = averageSeconds / 3600;
    int remainder = averageSeconds % 3600;
    int aminute = remainder / 60;
    asecond = remainder % 60;

    DMS result(adegree, aminute, asecond);
    return result;
}

