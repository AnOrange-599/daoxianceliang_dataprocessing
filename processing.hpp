#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

// 定义圆周率常量
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 定义度分秒类
class DMS {
public:
    int degree; // 度
    int minute; // 分
    int second; // 秒

    // 默认构造函数
    DMS() : degree(0), minute(0), second(0) {}

    // 带参构造函数
    DMS(int a, int b, int c);

    // 将弧度转化为DMS
    DMS(double radians);

    // 输出函数
    void output() const;
};

// 重载输出函数
void output(const DMS& a);

// 加法函数
DMS addDMS(const DMS& a, const DMS& b);

// 减法函数，如果结果为负数，则加上360度
DMS subtractDMS(const DMS& a, const DMS& b);

// 计算闭合差，最后返回的是秒的差值，并且不会自动转化为正值 
int subtractS(DMS a, DMS b);

// 计算角度弧度转化的函数
double change(DMS a);

// 弧度转角度
DMS radians_to_DMS(double radians);

// 计算角度平均值的函数
DMS averageDMS(DMS a, DMS b);

