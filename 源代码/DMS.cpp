#include "processing.hpp"

// ���ι��캯���Ķ���
DMS::DMS(int a, int b, int c) {
    second = c % 60;
    minute = b + c / 60;
    degree = a + minute / 60;
}

// ��������Ķ���
void DMS::output() const {
    std::cout << degree << " " << minute << " " << second << " " << std::endl;
}

// ������ת��ΪDMS
DMS::DMS(double radians) {
    if (radians < 0)
        radians += 2 * M_PI;
    second = 3600 * 180 * radians / M_PI;
    degree = second / 3600;
    minute = (second % 3600) / 60;
    second = second % 60;
}

// ������������Ķ���
void output(const DMS& a) {
    std::cout << a.degree << " " << a.minute << " " << a.second << " " << std::endl;
}

// �ӷ������Ķ���
DMS addDMS(const DMS& a, const DMS& b) {
    int totalSeconds = (a.degree + b.degree) * 3600 + (a.minute + b.minute) * 60 + (a.second + b.second);
    int degrees = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;
    return DMS(degrees, minutes, seconds);
}

// ���������Ķ���
DMS subtractDMS(const DMS& a, const DMS& b) {
    int totalSecondsA = a.degree * 3600 + a.minute * 60 + a.second;
    int totalSecondsB = b.degree * 3600 + b.minute * 60 + b.second;
    int diffSeconds = totalSecondsA - totalSecondsB;
    if (diffSeconds < 0) diffSeconds += 360 * 3600; // ����360��
    int degrees = diffSeconds / 3600;
    int minutes = (diffSeconds % 3600) / 60;
    int seconds = diffSeconds % 60;
    return DMS(degrees, minutes, seconds);
}

// ����պϲ�Ķ��壬����ר�ż���պϲ�ļ�������
int subtractS(DMS a, DMS b) {
    int aTotalSec = a.degree * 3600 + a.minute * 60 + a.second;
    int bTotalSec = b.degree * 3600 + b.minute * 60 + b.second;

    // �����ֵ
    int diffSec = aTotalSec - bTotalSec;
    return diffSec;
}

// ����ǶȻ���ת���Ķ���
double change(DMS a) {
    return (a.degree + a.minute / 60.0 + a.second / 3600.0) * M_PI / 180.0;
}

// ����ת�ǶȵĶ���
DMS radians_to_DMS(double radians) {
    if (radians < 0)
        radians += 2 * M_PI;
    double degrees = radians * 180.0 / M_PI;
    double minutes = (degrees - floor(degrees)) * 60.0;
    double seconds = (minutes - floor(minutes)) * 60.0;
    return DMS(floor(degrees), floor(minutes), floor(seconds));
}

// ����Ƕ�ƽ��ֵ�Ķ���
DMS averageDMS(DMS a, DMS b) {
    int totalSecondsA = a.degree * 3600 + a.minute * 60 + a.second;
    int totalSecondsB = b.degree * 3600 + b.minute * 60 + b.second;
    int totalSeconds = (totalSecondsA + totalSecondsB); // ������2���ȼ����ܺ�

    // ����ƽ��������������������λż����ȥ    
    int averageSeconds = totalSeconds / 2; // ���ڳ���2�õ�ƽ������
    int asecond = (totalSeconds / 2) % 2; // ���ƽ�������������������
    // ��asecondΪ1������Ϊ0
    if (asecond != 0) { // ������������������������λ��ż����
        averageSeconds = averageSeconds + totalSeconds % 2;
    }
    // ��ƽ������ת��Ϊ�ȡ��֡���
    int adegree = averageSeconds / 3600;
    int remainder = averageSeconds % 3600;
    int aminute = remainder / 60;
    asecond = remainder % 60;

    DMS result(adegree, aminute, asecond);
    return result;
}

