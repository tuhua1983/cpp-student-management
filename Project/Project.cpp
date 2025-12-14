// Project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//学生成绩管理系统
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
using namespace std;

//类声明
class Student;

//函数声明
void processCommand(vector<string>&, vector<Student>&);
void insertStudent(vector<string>&, vector<Student>&);
void insertScores(vector<string>&);
void listStudents(vector<Student>&);

//学生类
class Student {
private:
	int id;					//学号
	string name;			//姓名
	vector<float> scores;	//各科成绩
	float average;			//平均分
public:

	//构造函数
	Student() : id(0), name(""), average(0.0) {}
	Student(int id, string name, vector<float> scores)
		: id(id), name(name), scores(scores) {
		calculateAverage();
	}

	//学生基本信息初始化函数（不包含成绩）
	void initialize(int id, string name) {
		this->id = id;
		this->name = name;
	}

	//计算平均分函数
	void calculateAverage() {
		float sum = 0;
		for (float score : scores) {
			sum += score;
		}
		average = sum / scores.size();
	}

	//获取学号
	int getId() const {
		return id;
	}
	//获取姓名
	string getName() const {
		return name;
	}
	//获取平均分
	float getAverage() const {
		return average;
	}

};

//主函数
int main(int argc,char* argv[])
{
	if (argc<2)
	{
		cout <<"请通过终端操作,或输入正确的参数\n";
		return 0;
	}

	//读取文件中的学生信息到students向量
	ifstream inFile("students.txt", ios::binary);
	if (inFile.is_open()) {
		//读取文件内容
		inFile.close();
	}
	else {
		cout << "无法打开文件进行读取" << endl;
	}
	vector<Student> students;
	struct stat buf;
	stat("students.txt", &buf);
	int size = buf.st_size / sizeof(Student);
	cout << size << endl;
	cout << inFile.tellg() << endl;
	inFile.seekg(0, ios::beg);
	for (int i = 0; i < 3; i++)
	{
		Student temp;
		inFile.read((char*)&temp, sizeof(Student));
		cout << temp.getName() << endl;
		students.push_back(temp);
	}

	cout << students.size() << endl;
	//cout << students[1].getName() << endl; 
	inFile.close();

	vector<string> args(argv, argv + argc);
	processCommand(args,students);
	return 0;
}

//指令识别函数
void processCommand(vector<string>& args, vector<Student>& students){
	string command = args[1];
	//"-add" 插入学生信息
	if (command == "-add") {
		insertStudent(args,students);
		return;
	}
	//"-i"插入学生成绩
	else if (command == "-i") {
		insertScores(args);
	}
	//"-d" 删除学生信息
	else if (command == "-d") {
		//deleteStudent();
		return;
	}
	//"-u" 更新学生信息
	else if (command == "-u") {
		//updateStudent();
		return;
	}
	//"-s" 查询学生信息
	else if (command == "-s") {
		//searchStudent();
		return;
	}
	//"-l" 列出所有学生信息
	else if (command == "-l") {
		listStudents(students);
		return;
	}
	else {
		cout << "无效指令" << endl;
		return;
	}
}

//插入学生信息函数
void insertStudent(vector<string>& args, vector<Student>& students) {
	cout << "插入学生信息函数调用" << endl;
	int id;
	string name;
	vector<float> scores;
	cout << "学号：";
	cin >> id;
	cout << "姓名：";
	cin >> name;
	Student newStudent;
	newStudent.initialize(id, name);
	students.push_back(newStudent);

	//保存students到文件
	ofstream outFile("students.txt",ios::binary | ios::app);
	if (outFile.is_open()) {
		outFile << id << " " << name << endl;
		outFile.close();
	}
	else {
		cout << "无法打开文件进行写入" << endl;
	}
	outFile.write((char*)&newStudent, sizeof(Student));
	outFile.close();
}

void listStudents(vector<Student>& students) {
	cout << "列出所有学生信息函数调用" << endl;
	for (const Student& student : students) {
		//输出学生信息
		cout << "学号：" << student.getId() << ", 姓名：" << student.getName() << ", 平均分：" << student.getAverage() << endl;
	}
}

//插入学生成绩函数
void insertScores(vector<string>& args) {
	cout << args[2] << endl;
	cout << args[3] << endl;
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
