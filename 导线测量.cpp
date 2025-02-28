#include "processing.hpp"

using namespace std;

int main2() {
    cout << setprecision(15);
    // ������ʼ��������
    cout << "������ʼ�����N E���꣬����˳��ע�����н����򱣳�һ��" << endl;
    double ori_n_2, ori_e_2, ori_n_1, ori_e_1;  //��ʼ��1��2����
    cin >> ori_n_1 >> ori_e_1 >> ori_n_2 >> ori_e_2;
    double origin;  // ��ʼ��λ��
    origin = atan2((ori_e_2 - ori_e_1) , (ori_n_2 - ori_n_1));
    //��ʼ��λ����atan(E(��-ǰ)/N(��-ǰ))
    DMS originDMS = radians_to_DMS(origin); // ���������ʼ��λ�ǵ�DMS
    // ori_n_2, ori_e_2�����������
    
    cout << "�պϵ��߻��߸��͵��������յ������N E���꣬����˳��ע�����н����򱣳�һ��" << endl;
    double end_n_1, end_e_1, end_n_2, end_e_2;
    cin >> end_n_1 >> end_e_1 >> end_n_2 >> end_e_2;
    double end;
    end = atan2((end_e_2 - end_e_1) , (end_n_2 - end_n_1)); // �ձ߷�λ��
    DMS endDMS = radians_to_DMS(end); // ������ձ߷�λ��
    //double end_n_2, end_e_2;

    vector<DMS> gcj_data; // ʹ��vector��̬���飬�۲������
    int count = 0;  //��¼�������˶��ٸ���ǣ����ǲ��˶���վ��վ��վ��վ������ �㣡��
    cout << "�����������ǣ�����2227ʱ˵���������\n\n��������ƽ�����ģ������ûƽ�������á��Ƕȴ���ѡ��" << endl;
    while (1) { //������ǵĺ�������������ƽ�����ģ������ûƽ�������á��Ƕȴ���ѡ��
        int a, b, c;
        cin >> a;
        if (a == 2227) { // ʹ��2227��Ϊ��������ı��
            break;
        }
        cin >> b >> c;
        gcj_data.push_back(DMS(a, b, c)); // ʹ��push_back���Ԫ��
        count++;
    }

    // ��Ҫ���Զ����������
    DMS sum(0, 0, 0);   //�Ƕ��ܺ�
    for (int i = 0; i < count; i++) {
        sum = addDMS(gcj_data[i], sum);
    } // �����
    
    
    int bhc;    // ����պϲ�
    bhc = subtractS(sum, DMS(((count - 2) * 180), 0, 0)) + subtractS(originDMS, endDMS);
    // ��Ȼ�Ҳ����������Ϊʲô��(�۲�Ǹ���-2)�������㹫ʽȷʵ������
    // ���������ʱ������substract��������Ϊ-4�����59��56�룬Ctrl+������鿴subtractS�Ķ���
    cout << "�ȸ���������պϲ������û�г���" << endl;
    cout << "���Ǳպϲ�" << endl;
    cout << bhc << endl;

    cout << "���м�վ��" << count << endl;
    cout << "ȫ�����" << endl;
    output(sum);
    // �պϲ����ˣ���ʼ������������������������
    vector<int> gaizhengshu(count); // ʹ��vector��̬����


#pragma region �պϲ����д��һ�磬�����������漣
    if (bhc > 0) {
        int v1, v2;
        v1 = bhc / count; // �Ȱ���������������
        v2 = bhc % count; // �ٷ�������
        for (int i1 = 0; i1 < count; i1++) {
            gcj_data[i1] = subtractDMS(gcj_data[i1], DMS(0, 0, v1));
        }
        // Ϊ�˱ȴ�С��ȫ���Ѷȷ���ת��Ϊ�����ƣ�Ȼ���ҳ�����v2�����±�
        vector<double> select(count); // ʹ��vector��̬����
        for (int i1 = 0; i1 < count; i1++) {
            select[i1] = change(gcj_data[i1]);
        }
        // �ҳ�v2�����������±꣬������һ������
        vector<double> arr(count); // ʹ��vector��̬����
        for (int i1 = 0; i1 < count; i1++) {
            arr[i1] = select[i1];
        }
        vector<int> indices(v2); // ʹ��vector��̬����
        for (int i = 0; i < v2; ++i) {
            indices[i] = -1;
        }
        for (int i = 0; i < count; ++i) {
            bool replaced = false; // ����Ƿ��滻��indices�е�Ԫ��
            for (int j = 0; j < v2; ++j) {
                // ���indices[j]�ǿյģ����ߵ�ǰԪ�ر�indices[j]ָ���Ԫ�ش�
                if (indices[j] == -1 || arr[i] > arr[indices[j]]) {
                    // ��indices�����е�Ԫ������ƶ�һλ�������Ҫ�Ļ���
                    for (int k = v2 - 1; k > j; --k) {
                        indices[k] = indices[k - 1];
                    }
                    indices[j] = i;
                    replaced = true;
                    break;
                }
            }
        }
        // дһ�������������滹Ҫ���
        for (int i2 = 0; i2 < count; i2++) {
            gaizhengshu[i2] = -v1;
            for (int i3 = 0; i3 < v2; i3++) {
                if (i2 == indices[i3]) {
                    gaizhengshu[i2] = -(v1 + 1);
                    break;
                }
            }
        }

        for (int i1 = 0; i1 < v2; i1++) { // �ҳ�������v2���ǣ�Ȼ��������������
            gcj_data[indices[i1]] = subtractDMS(gcj_data[indices[i1]], DMS(0, 0, 1));
        }
    }

    // д������������ȰѸ����ĳ����ģ�Ȼ��ӱ�ɼ�
    else {
        bhc = -bhc;
        int v1, v2;
        v1 = bhc / count; // �Ȱ���������������
        v2 = bhc % count; // �ٷ�������
        for (int i1 = 0; i1 < count; i1++) {
            gcj_data[i1] = addDMS(gcj_data[i1], DMS(0, 0, v1));
        }
        // Ϊ�˱ȴ�С��ȫ���Ѷȷ���ת��Ϊ�����ƣ�Ȼ���ҳ�����v2�����±�
        vector<double> select(count); // ʹ��vector��̬����
        for (int i1 = 0; i1 < count; i1++) {
            select[i1] = change(gcj_data[i1]);
        }
        // �ҳ�v2�����������±꣬������һ������
        vector<double> arr(count); // ʹ��vector��̬����
        for (int i1 = 0; i1 < count; i1++) {
            arr[i1] = select[i1];
        }
        vector<int> indices(v2); // ʹ��vector��̬����
        for (int i = 0; i < v2; ++i) {
            indices[i] = -1;
        }
        for (int i = 0; i < count; ++i) {
            bool replaced = false; // ����Ƿ��滻��indices�е�Ԫ��
            for (int j = 0; j < v2; ++j) {
                // ���indices[j]�ǿյģ����ߵ�ǰԪ�ر�indices[j]ָ���Ԫ�ش�
                if (indices[j] == -1 || arr[i] > arr[indices[j]]) {
                    // ��indices�����е�Ԫ������ƶ�һλ�������Ҫ�Ļ���
                    for (int k = v2 - 1; k > j; --k) {
                        indices[k] = indices[k - 1];
                    }
                    indices[j] = i;
                    replaced = true;
                    break;
                }
            }
        }
        // дһ�������������滹Ҫ���
        for (int i2 = 0; i2 < count; i2++) {
            gaizhengshu[i2] = v1;
            for (int i3 = 0; i3 < v2; i3++) {
                if (i2 == indices[i3]) {
                    gaizhengshu[i2] = v1 + 1;
                    // ���ԣ���Ȼ����д�ĺ��ң������Ѿ��������if�ж������˱պϲ����������
                    break;
                }
            }
        }
        for (int i1 = 0; i1 < v2; i1++) { // �ҳ�������v2���ǣ�Ȼ��������������
            gcj_data[indices[i1]] = addDMS(gcj_data[indices[i1]], DMS(0, 0, 1));
        }
    }
#pragma endregion


    cout << "����������߳�" << endl;
    vector<double> length(count);       // ʹ��vector��̬����
    for (int i = 0; i < count-1; i++)   // ע����count-1
        cin >> length[i];
    cout << "������ʼ��λ��" << endl;
    output(originDMS);
    cout << "�����ձ߷�λ��" << endl;
    output(endDMS);
    // �������������
    cout << "�������������" << endl;
    for (int i = 0; i < count; i++) {
        output(gcj_data[i]);
        cout << endl;
    }

    vector<DMS> fwj(count + 1); // ʹ��vector��̬����
    fwj[0] = originDMS;
    cout << "���Ƿ�λ��" << endl;
    for (int i = 0; i < count; i++) {
        fwj[i + 1] = subtractDMS(addDMS(fwj[i], gcj_data[i]), DMS(180, 0, 0));
        output(fwj[i + 1]);
        cout << endl; // ��ΪExcel�кϲ���Ԫ�������
    }
    // ���������
    cout << "���������" << endl;
    for (int i = 0; i < count; i++) {
        cout << gaizhengshu[i] << endl << endl;
    }

    // �ȷ���ת����
    vector<double> hd(count); // ʹ��vector��̬����
    for (int i = 0; i < count; i++) {
        hd[i] = change(fwj[i + 1]);
    }

    double lengthsum = 0;// �����ܳ�
    for (int i = 0; i < count-1; i++) {
        lengthsum += length[i];
    }
    cout << "���ǵ���ȫ�� " << endl;
    cout << lengthsum << endl;

    // ����������
    cout << "����N��������" << endl;
    for (int i = 0; i < count-1; i++) {
        cout << cos(hd[i]) * length[i] << endl << endl;
    }
    double nsum = 0;
    for (int i = 0; i < count-1; i++) {
        nsum += cos(hd[i]) * length[i];
        //TODO �����һ������nsum�պϲ��㷨�ǲ���������ѽ��
        //������ +��ʼ-ĩ��= �պϲ�
        //������ - �պϲ� =��ĩ-ʼ��
    }
    nsum += ori_n_2 - end_n_1;
    cout << "����N����պϲ� " << endl;
    cout << nsum << endl;
    // ���������
    cout << "���ŷ���պϲ�" << endl;
    for (int i = 0; i < count-1; i++) {
        cout << -(length[i] / lengthsum) * nsum << endl << endl;
        //TODO : ���ܲ��Ǹ��ݳ���ֱ�Ӽ�Ȩ���䣬���Ǹ���������������
    }
    cout << "���Ǹ������N��������" << endl;

    for (int i = 0; i < count-1; i++) {
        cout << cos(hd[i]) * length[i] - (length[i] / lengthsum) * nsum << endl << endl;
        //TODO : ���ܲ��Ǹ��ݳ���ֱ�Ӽ�Ȩ���䣬���Ǹ���������������
    }
    cout << "���ǳ���������N����" << endl;
    double newn = ori_n_2;
    for (int i = 0; i < count-1; i++) {
        newn += cos(hd[i]) * length[i] - (length[i] / lengthsum) * nsum;
        cout << newn << endl << endl;
    }

    cout << "����E��������" << endl;
    for (int i = 0; i < count-1; i++) {
        cout << sin(hd[i]) * length[i] << endl << endl;
    }
    double esum = 0;
    for (int i = 0; i < count-1; i++) {
        esum += sin(hd[i]) * length[i];
        // TODO ����������
    }
    esum += ori_e_2 - end_e_1;
    cout << "����E����պϲ� " << endl << endl;
    cout << esum << endl;
    // ���������
    cout << "���ŷ���պϲ�" << endl;
    for (int i = 0; i < count-1; i++) {
        cout << -(length[i] / lengthsum) * esum << endl << endl;
        //TODO : ���ܲ��Ǹ��ݳ���ֱ�Ӽ�Ȩ���䣬���Ǹ���������������
    }
    cout << "���Ǹ������E��������" << endl;

    for (int i = 0; i < count-1; i++) {
        cout << sin(hd[i]) * length[i] - (length[i] / lengthsum) * esum << endl << endl;
        //TODO : ���ܲ��Ǹ��ݳ���ֱ�Ӽ�Ȩ���䣬���Ǹ���������������
    }
    cout << "���ǳ���������E����" << endl;
    double newe = ori_e_2;
    for (int i = 0; i < count-1; i++) {
        newe += sin(hd[i]) * length[i] - (length[i] / lengthsum) * esum;
        cout << newe << endl << endl;
    }
    
    return 0;
}
