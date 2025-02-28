#include "processing.hpp"

using namespace std;

int main2() {
    cout << setprecision(15);
    // 输入起始两点坐标
    cout << "输入起始两点的N E坐标，输入顺序注意与行进方向保持一致" << endl;
    double ori_n_2, ori_e_2, ori_n_1, ori_e_1;  //起始点1、2坐标
    cin >> ori_n_1 >> ori_e_1 >> ori_n_2 >> ori_e_2;
    double origin;  // 起始方位角
    origin = atan2((ori_e_2 - ori_e_1) , (ori_n_2 - ori_n_1));
    //起始方位角是atan(E(后-前)/N(后-前))
    DMS originDMS = radians_to_DMS(origin); // 这个就是起始方位角的DMS
    // ori_n_2, ori_e_2是起算点坐标
    
    cout << "闭合导线或者附和导线输入终点两点的N E坐标，输入顺序注意与行进方向保持一致" << endl;
    double end_n_1, end_e_1, end_n_2, end_e_2;
    cin >> end_n_1 >> end_e_1 >> end_n_2 >> end_e_2;
    double end;
    end = atan2((end_e_2 - end_e_1) , (end_n_2 - end_n_1)); // 终边方位角
    DMS endDMS = radians_to_DMS(end); // 这个是终边方位角
    //double end_n_2, end_e_2;

    vector<DMS> gcj_data; // 使用vector动态数组，观测角数据
    int count = 0;  //记录下输入了多少个左角，就是测了多少站（站！站！站！不是 点！）
    cout << "输入所测的左角，输入2227时说明输入结束\n\n这个左角是平均过的，如果还没平均，先用“角度处理”选项" << endl;
    while (1) { //输入左角的函数，这个左角是平均过的，如果还没平均，先用“角度处理”选项
        int a, b, c;
        cin >> a;
        if (a == 2227) { // 使用2227作为输入结束的标记
            break;
        }
        cin >> b >> c;
        gcj_data.push_back(DMS(a, b, c)); // 使用push_back添加元素
        count++;
    }

    // 需要有自动分配改正数
    DMS sum(0, 0, 0);   //角度总和
    for (int i = 0; i < count; i++) {
        sum = addDMS(gcj_data[i], sum);
    } // 先求和
    
    
    int bhc;    // 计算闭合差
    bhc = subtractS(sum, DMS(((count - 2) * 180), 0, 0)) + subtractS(originDMS, endDMS);
    // 虽然我不能理解这里为什么是(观测角个数-2)，但计算公式确实是这样
    // 分配改正数时不能用substract函数，因为-4秒会变成59分56秒，Ctrl+点击，查看subtractS的定义
    cout << "先给你输出个闭合差，看看有没有超限" << endl;
    cout << "这是闭合差" << endl;
    cout << bhc << endl;

    cout << "共有几站：" << count << endl;
    cout << "全部相加" << endl;
    output(sum);
    // 闭合差有了，开始分配改正数，分正负两种情况
    vector<int> gaizhengshu(count); // 使用vector动态数组


#pragma region 闭合差分配写的一坨，能运行真是奇迹
    if (bhc > 0) {
        int v1, v2;
        v1 = bhc / count; // 先把整数都给分配了
        v2 = bhc % count; // 再分配余数
        for (int i1 = 0; i1 < count; i1++) {
            gcj_data[i1] = subtractDMS(gcj_data[i1], DMS(0, 0, v1));
        }
        // 为了比大小，全部把度分秒转化为弧度制，然后找出最大的v2个的下标
        vector<double> select(count); // 使用vector动态数组
        for (int i1 = 0; i1 < count; i1++) {
            select[i1] = change(gcj_data[i1]);
        }
        // 找出v2个最大的数的下标，并存在一个数组
        vector<double> arr(count); // 使用vector动态数组
        for (int i1 = 0; i1 < count; i1++) {
            arr[i1] = select[i1];
        }
        vector<int> indices(v2); // 使用vector动态数组
        for (int i = 0; i < v2; ++i) {
            indices[i] = -1;
        }
        for (int i = 0; i < count; ++i) {
            bool replaced = false; // 标记是否替换了indices中的元素
            for (int j = 0; j < v2; ++j) {
                // 如果indices[j]是空的，或者当前元素比indices[j]指向的元素大
                if (indices[j] == -1 || arr[i] > arr[indices[j]]) {
                    // 将indices数组中的元素向后移动一位（如果需要的话）
                    for (int k = v2 - 1; k > j; --k) {
                        indices[k] = indices[k - 1];
                    }
                    indices[j] = i;
                    replaced = true;
                    break;
                }
            }
        }
        // 写一个改正数，后面还要输出
        for (int i2 = 0; i2 < count; i2++) {
            gaizhengshu[i2] = -v1;
            for (int i3 = 0; i3 < v2; i3++) {
                if (i2 == indices[i3]) {
                    gaizhengshu[i2] = -(v1 + 1);
                    break;
                }
            }
        }

        for (int i1 = 0; i1 < v2; i1++) { // 找出最大的这v2个角，然后分配除不尽的秒
            gcj_data[indices[i1]] = subtractDMS(gcj_data[indices[i1]], DMS(0, 0, 1));
        }
    }

    // 写负数的情况，先把负数改成正的，然后加变成减
    else {
        bhc = -bhc;
        int v1, v2;
        v1 = bhc / count; // 先把整数都给分配了
        v2 = bhc % count; // 再分配余数
        for (int i1 = 0; i1 < count; i1++) {
            gcj_data[i1] = addDMS(gcj_data[i1], DMS(0, 0, v1));
        }
        // 为了比大小，全部把度分秒转化为弧度制，然后找出最大的v2个的下标
        vector<double> select(count); // 使用vector动态数组
        for (int i1 = 0; i1 < count; i1++) {
            select[i1] = change(gcj_data[i1]);
        }
        // 找出v2个最大的数的下标，并存在一个数组
        vector<double> arr(count); // 使用vector动态数组
        for (int i1 = 0; i1 < count; i1++) {
            arr[i1] = select[i1];
        }
        vector<int> indices(v2); // 使用vector动态数组
        for (int i = 0; i < v2; ++i) {
            indices[i] = -1;
        }
        for (int i = 0; i < count; ++i) {
            bool replaced = false; // 标记是否替换了indices中的元素
            for (int j = 0; j < v2; ++j) {
                // 如果indices[j]是空的，或者当前元素比indices[j]指向的元素大
                if (indices[j] == -1 || arr[i] > arr[indices[j]]) {
                    // 将indices数组中的元素向后移动一位（如果需要的话）
                    for (int k = v2 - 1; k > j; --k) {
                        indices[k] = indices[k - 1];
                    }
                    indices[j] = i;
                    replaced = true;
                    break;
                }
            }
        }
        // 写一个改正数，后面还要输出
        for (int i2 = 0; i2 < count; i2++) {
            gaizhengshu[i2] = v1;
            for (int i3 = 0; i3 < v2; i3++) {
                if (i2 == indices[i3]) {
                    gaizhengshu[i2] = v1 + 1;
                    // 不对，虽然这里写的很乱，但是已经在上面的if判断区分了闭合差正负的情况
                    break;
                }
            }
        }
        for (int i1 = 0; i1 < v2; i1++) { // 找出最大的这v2个角，然后分配除不尽的秒
            gcj_data[indices[i1]] = addDMS(gcj_data[indices[i1]], DMS(0, 0, 1));
        }
    }
#pragma endregion


    cout << "接下来输入边长" << endl;
    vector<double> length(count);       // 使用vector动态数组
    for (int i = 0; i < count-1; i++)   // 注意是count-1
        cin >> length[i];
    cout << "这是起始方位角" << endl;
    output(originDMS);
    cout << "这是终边方位角" << endl;
    output(endDMS);
    // 输出改正后的左角
    cout << "输出改正后的左角" << endl;
    for (int i = 0; i < count; i++) {
        output(gcj_data[i]);
        cout << endl;
    }

    vector<DMS> fwj(count + 1); // 使用vector动态数组
    fwj[0] = originDMS;
    cout << "这是方位角" << endl;
    for (int i = 0; i < count; i++) {
        fwj[i + 1] = subtractDMS(addDMS(fwj[i], gcj_data[i]), DMS(180, 0, 0));
        output(fwj[i + 1]);
        cout << endl; // 因为Excel中合并单元格的问题
    }
    // 输出改正数
    cout << "输出改正数" << endl;
    for (int i = 0; i < count; i++) {
        cout << gaizhengshu[i] << endl << endl;
    }

    // 度分秒转弧度
    vector<double> hd(count); // 使用vector动态数组
    for (int i = 0; i < count; i++) {
        hd[i] = change(fwj[i + 1]);
    }

    double lengthsum = 0;// 导线总长
    for (int i = 0; i < count-1; i++) {
        lengthsum += length[i];
    }
    cout << "这是导线全长 " << endl;
    cout << lengthsum << endl;

    // 横坐标增量
    cout << "这是N坐标增量" << endl;
    for (int i = 0; i < count-1; i++) {
        cout << cos(hd[i]) * length[i] << endl << endl;
    }
    double nsum = 0;
    for (int i = 0; i < count-1; i++) {
        nsum += cos(hd[i]) * length[i];
        //TODO ：检查一下这里nsum闭合差算法是不是有问题呀？
        //总增量 +（始-末）= 闭合差
        //总增量 - 闭合差 =（末-始）
    }
    nsum += ori_n_2 - end_n_1;
    cout << "这是N坐标闭合差 " << endl;
    cout << nsum << endl;
    // 分配改正数
    cout << "反号分配闭合差" << endl;
    for (int i = 0; i < count-1; i++) {
        cout << -(length[i] / lengthsum) * nsum << endl << endl;
        //TODO : 可能不是根据长度直接加权分配，而是根据增量比例分配
    }
    cout << "这是改正后的N坐标增量" << endl;

    for (int i = 0; i < count-1; i++) {
        cout << cos(hd[i]) * length[i] - (length[i] / lengthsum) * nsum << endl << endl;
        //TODO : 可能不是根据长度直接加权分配，而是根据增量比例分配
    }
    cout << "这是除起算点外的N坐标" << endl;
    double newn = ori_n_2;
    for (int i = 0; i < count-1; i++) {
        newn += cos(hd[i]) * length[i] - (length[i] / lengthsum) * nsum;
        cout << newn << endl << endl;
    }

    cout << "这是E坐标增量" << endl;
    for (int i = 0; i < count-1; i++) {
        cout << sin(hd[i]) * length[i] << endl << endl;
    }
    double esum = 0;
    for (int i = 0; i < count-1; i++) {
        esum += sin(hd[i]) * length[i];
        // TODO ：还有这里
    }
    esum += ori_e_2 - end_e_1;
    cout << "这是E坐标闭合差 " << endl << endl;
    cout << esum << endl;
    // 分配改正数
    cout << "反号分配闭合差" << endl;
    for (int i = 0; i < count-1; i++) {
        cout << -(length[i] / lengthsum) * esum << endl << endl;
        //TODO : 可能不是根据长度直接加权分配，而是根据增量比例分配
    }
    cout << "这是改正后的E坐标增量" << endl;

    for (int i = 0; i < count-1; i++) {
        cout << sin(hd[i]) * length[i] - (length[i] / lengthsum) * esum << endl << endl;
        //TODO : 可能不是根据长度直接加权分配，而是根据增量比例分配
    }
    cout << "这是除起算点外的E坐标" << endl;
    double newe = ori_e_2;
    for (int i = 0; i < count-1; i++) {
        newe += sin(hd[i]) * length[i] - (length[i] / lengthsum) * esum;
        cout << newe << endl << endl;
    }
    
    return 0;
}
