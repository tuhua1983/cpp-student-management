// Project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//学生成绩管理系统
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sstream>
using namespace std;

//类声明
class Student;

//函数声明
void processCommand(vector<string>&, vector<Student>&);
void insertStudent(vector<string>&, vector<Student>&);
void insertScores(vector<string>&, vector<Student>&);
void listStudents(vector<Student>&);
void deleteStudent(vector<string>&, vector<Student>&);
vector<vector<Student>::iterator> searchStudent(vector<string>&, vector<Student>&);

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

	//插入成绩函数
	void insertScores(const vector<float>& newScores) {
		//scores.insert(scores.end(), newScores.begin(), newScores.end());
		scores = newScores;		//直接覆盖
		calculateAverage();
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
	//获取成绩
	vector<float> getScores() const {
		return scores;
	}

	//序列化
	string serialize() const {
		ostringstream os;
		os << id << "," << name << ",";
		for (int i = 0; i < scores.size(); i++)
		{
			os << scores[i];
			if (i + 1 < scores.size())
				os << " ";
		}
		os << "\n";
		return os.str();
	}

	//反序列化
	static Student deserialize(const string& line) {
		stringstream ss(line);
		string token;

		getline(ss, token, ',');
		int id = stoi(token);

		string name;
		getline(ss, name, ',');

		vector<float> scores;
		getline(ss, token);
		stringstream ss2(token);
		float x;
		while (ss2 >> x)
			scores.push_back(x);

		return Student(id, name, scores);
	}

};

//主函数
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "请通过终端操作,或输入正确的参数\n";
		return 0;
	}

	vector<Student> students;	//创建学生对象数组

	//读取文件中的学生信息
	ifstream inFile("students.txt", ios::binary);	//以二进制方式打开文件
	string line;
	if (inFile.is_open()) {							//文件成功打开
		//读取文件内容
		while (getline(inFile, line)) {
			students.push_back(Student::deserialize(line));
		}
		inFile.close();
	}
	else {											//文件打开失败
		cout << "无法打开文件进行读取" << endl;
	}

	vector<string> args(argv, argv + argc);
	processCommand(args, students);
	return 0;
}

//指令识别函数
void processCommand(vector<string>& args, vector<Student>& students) {
	cout << "指令识别函数调用" << endl;
	string command = args[1];
	//"-add" 插入学生信息
	if (command == "-add") {
		insertStudent(args, students);
		return;
	}
	//"-i"插入学生成绩
	else if (command == "-i") {
		insertScores(args, students);
	}
	//"-d" 删除学生信息
	else if (command == "-d") {
		deleteStudent(args, students);
		return;
	}
	//"-u" 更新学生信息
	else if (command == "-u") {
		//updateStudent();
		return;
	}
	//"-s" 查询学生信息
	else if (command == "-s") {
		vector<vector<Student>::iterator> its = searchStudent(args, students);
		cout << "--------------------------\n";
		for ( vector<Student>::iterator it: its )
		{
			cout << "学号:" << it->getId() << "\t姓名:" << it->getName() << "\t平均分:" << it->getAverage() << "\n";
			cout << "成绩:";
			for (float scores : it->getScores() ) {
				cout << scores << "\t";
			}
			cout << "\n\n";
		}
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
	ofstream outFile("students.txt", ios::app);
	if (outFile.is_open()) {
		outFile << newStudent.serialize();
		outFile.close();
	}
	else {
		cout << "无法打开文件进行写入" << endl;
	}
}

void listStudents(vector<Student>& students) {
	cout << "列出所有学生信息函数调用" << endl;
	for (const Student& student : students) {
		//输出学生信息
		cout << "学号：" << student.getId() << ", 姓名：" << student.getName() << ", 平均分：" << student.getAverage() << endl;
	}
}

//插入学生成绩函数
void insertScores(vector<string>& args, vector<Student>& students) {
	cout << "插入学生成绩函数调用\n";

	//判断参数是否足够
	if (args.size() < 3) {
		cout << "参数缺少\n";
		return;
	}

	vector<float> scores;
	cout << "创建成绩暂存容器完毕\n";
	cout << "args.size()=" << args.size() << "\n";
	for (int i = 3; i < args.size(); i++)
	{
		scores.push_back(stof(args[i]));
		cout << "插入成绩：" << args[i] << "\n";
	}

	//查找学生并插入成绩
	bool found = false;
	for (Student& student : students)
	{
		if (student.getName() == args[2])
		{
			student.insertScores(scores);
			found = true;
		}
	}
	if (found == false)
	{
		cout << "未找到该学生，无法插入成绩\n";
		return;
	}

	//保存students到文件
	ofstream outFile("students.txt", ios::trunc);
	if (outFile.is_open()) {
		for (const Student& student : students)
		{
			outFile << student.serialize();
		}
		outFile.close();
	}
	else {
		cout << "无法打开文件进行写入" << endl;
	}
}

// 删除学生信息函数
void deleteStudent(vector<string>& args, vector<Student>& students) {
	cout << "删除学生信息函数调用" << endl;

	bool found = false;

	//校验参数
	if (args.size() < 3) {
		cout << "参数缺少(--id/--name)\n";
		return;
	}

	//判断以什么方式删除
	if (args[2] == "--id") {

		//二次校验参数
		if (args.size() < 4) {
			cout << "参数缺少\n";
			return;
		}

		int idToDelete = stoi(args[3]);

		auto it = students.begin();
		while (it != students.end()) {
			if (it->getId() == idToDelete) {
				it = students.erase(it);//it已被删除，所以要让it接收erase()返回的下一个迭代器。
				cout << "已删除学号为 " << idToDelete << " 的学生信息。" << endl;
				found = true;
			}
			else {
				++it;
			}
		}

	}
	else if (args[2] == "--name") {

		//二次校验参数
		if (args.size() < 4) {
			cout << "参数缺少\n";
			return;
		}

		string nameToDelete = args[3];

		auto it = students.begin();
		while (it != students.end()) {
			if (it->getName() == nameToDelete) {
				it = students.erase(it);
				cout << "已删除姓名为 " << nameToDelete << " 的学生信息。" << endl;
				found = true;
			}
			else {
				++it;
			}
		}

	}
	else
	{
		cout << "无效的删除方式参数(--id/--name)\n";
	}

	//未找到学生
	if (found == false) {
		cout << "未找到该学生，无法删除\n";
		return;
	}

	//保存students到文件
	ofstream outFile("students.txt", ios::trunc);
	if (outFile.is_open()) {
		for (const Student& student : students)
		{
			outFile << student.serialize();
		}
		outFile.close();
	}
	else {
		cout << "无法打开文件进行写入" << endl;
	}
}

//查询学生信息函数
vector<vector<Student>::iterator> searchStudent(vector<string>& args, vector<Student>& students) {
	cout << "查询学生信息函数调用" << endl;

	vector<vector<Student>::iterator> its;

	//校验参数
	if (args.size() < 4) {
		cout << "参数缺少(--id/--name)\n";
		return its;
	}

	bool found = false;

	if (args[2] == "--id") {
		int id = stoi(args[3]);

		auto it = students.begin();
		while (it != students.end()) {
			if (it->getId() == id)
			{
				its.push_back(it);
				found = true;
			}
			++it;
		}
	}
	else if (args[2] == "--name")
	{
		string name = args[3];

		auto it = students.begin();
		while (it != students.end()) {
			if (it->getName() == name)
			{
				its.push_back(it);
				found = true;
			}
			++it;
		}
	}
	else {
		cout << "无效的查询方式(--id/--name)\n";
	}

	if (!found) {
		cout << "未找到相关数据\n";
	}

	return its;
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
