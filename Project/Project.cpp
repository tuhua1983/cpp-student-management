// Project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//学生成绩管理系统
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
	int id;					//学号
	string name;			//姓名
	vector<float> scores;	//各科成绩
	float average;			//平均分
public:
	Student(int id, string name, vector<float> scores)
		: id(id), name(name), scores(scores) {
		calculateAverage();
	}
	void calculateAverage() {
		float sum = 0;
		for (float score : scores) {
			sum += score;
		}
		average = sum / scores.size();
	}
};

int main(int argc,char* argv[])
{
    
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
