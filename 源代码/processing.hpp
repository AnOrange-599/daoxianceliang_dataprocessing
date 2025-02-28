#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

// ����Բ���ʳ���
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ����ȷ�����
class DMS {
public:
    int degree; // ��
    int minute; // ��
    int second; // ��

    // Ĭ�Ϲ��캯��
    DMS() : degree(0), minute(0), second(0) {}

    // ���ι��캯��
    DMS(int a, int b, int c);

    // ������ת��ΪDMS
    DMS(double radians);

    // �������
    void output() const;
};

// �����������
void output(const DMS& a);

// �ӷ�����
DMS addDMS(const DMS& a, const DMS& b);

// ����������������Ϊ�����������360��
DMS subtractDMS(const DMS& a, const DMS& b);

// ����պϲ��󷵻ص�����Ĳ�ֵ�����Ҳ����Զ�ת��Ϊ��ֵ 
int subtractS(DMS a, DMS b);

// ����ǶȻ���ת���ĺ���
double change(DMS a);

// ����ת�Ƕ�
DMS radians_to_DMS(double radians);

// ����Ƕ�ƽ��ֵ�ĺ���
DMS averageDMS(DMS a, DMS b);

