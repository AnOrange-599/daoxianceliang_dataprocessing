#include "processing.hpp"
using namespace std;

int main1() {
    cout << "�������ݼ�¼ʱ��ת�ǣ�����2227Ϊ������־" << endl;
    vector<DMS> gcj_data; // ʹ�� vector �洢��������
    int a, b, c;
    while (true) {
        cin >> a;
        if (a == 2227) { // ʹ��2227��Ϊ��������ı��
            break;
        }
        cin >> b >> c;
        gcj_data.push_back(DMS(a, b, c)); // ��������ӵ� vector ��
    }

    int count = gcj_data.size(); // ��ȡ�������ݵ�����
    vector<vector<DMS>> gcj(count / 4, vector<DMS>(4)); // ʹ�� vector ��̬�����ά����

    // ��������䵽 gcj ��
    for (int i1 = 0; i1 < count / 4; i1++) {
        for (int i2 = 0; i2 < 4; i2++) {
            gcj[i1][i2] = gcj_data[i1 * 4 + i2];
        }
    }

    // ���������������ҽ�ֵ
    cout << "�����ǰ��ؽ�ֵ" << endl;
    for (int i1 = 0; i1 < count / 4; i1++) {
        output(subtractDMS(gcj[i1][2], gcj[i1][0]));
        output(subtractDMS(gcj[i1][3], gcj[i1][1]));
    }

    // һ���ƽ����ֵ
    cout << "����һ��ؽ�ֵ" << endl;
    for (int i1 = 0; i1 < count / 4; i1++) {
        output(averageDMS(subtractDMS(gcj[i1][3], gcj[i1][1]), subtractDMS(gcj[i1][2], gcj[i1][0])));
    }
    
    return 0;
}
