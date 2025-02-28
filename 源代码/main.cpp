#include "header.hpp"
#include "processing.hpp"
using namespace std;
int main() {
	cout << "输入1或2选择需要的功能\n输入\t1\t角度处理\n输入\t2\t导线测量计算\n";
	int a = 0;
	cin >> a;
	if (a == 1)
		main1();
	else if (a == 2)
		main2();
	else
		cout << "重输" << endl;
	
	system("pause");
	return 0;
}