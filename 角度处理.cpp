#include "processing.hpp"
using namespace std;

int main1() {
    cout << "输入数据记录时的转角，输入2227为结束标志" << endl;
    vector<DMS> gcj_data; // 使用 vector 存储输入数据
    int a, b, c;
    while (true) {
        cin >> a;
        if (a == 2227) { // 使用2227作为输入结束的标记
            break;
        }
        cin >> b >> c;
        gcj_data.push_back(DMS(a, b, c)); // 将数据添加到 vector 中
    }

    int count = gcj_data.size(); // 获取输入数据的数量
    vector<vector<DMS>> gcj(count / 4, vector<DMS>(4)); // 使用 vector 动态分配二维数组

    // 将数据填充到 gcj 中
    for (int i1 = 0; i1 < count / 4; i1++) {
        for (int i2 = 0; i2 < 4; i2++) {
            gcj[i1][i2] = gcj_data[i1 * 4 + i2];
        }
    }

    // 批量处理盘左盘右角值
    cout << "这里是半测回角值" << endl;
    for (int i1 = 0; i1 < count / 4; i1++) {
        output(subtractDMS(gcj[i1][2], gcj[i1][0]));
        output(subtractDMS(gcj[i1][3], gcj[i1][1]));
    }

    // 一测回平均角值
    cout << "这是一测回角值" << endl;
    for (int i1 = 0; i1 < count / 4; i1++) {
        output(averageDMS(subtractDMS(gcj[i1][3], gcj[i1][1]), subtractDMS(gcj[i1][2], gcj[i1][0])));
    }
    
    return 0;
}
