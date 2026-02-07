#include "Student.h"

/*构造函数*/
	//默认构造
Student::Student() : id(0), name(""), average(0.0) {}
	//有参构造
Student::Student(int id, std::string name, std::vector<float> scores)
	: id(id), name(name), scores(scores) {
	calculateAverage();
}
	//拷贝构造
Student::Student(const Student& other) :id(other.id), name(other.name), scores(other.scores), average(other.average) {}

//学生基本信息初始化函数（不包含成绩）
void Student::initialize(int id, std::string name) {
	this->id = id;
	this->name = name;
}

//插入成绩函数
void Student::insertScores(const std::vector<float>& newScores) {
	//scores.insert(scores.end(), newScores.begin(), newScores.end());
	scores = newScores;		//直接覆盖
	calculateAverage();
}

//计算平均分函数
void Student::calculateAverage() {
	float sum = 0;
	for (float score : scores) {
		sum += score;
	}
	average = sum / scores.size();
}

//获取学号
int Student::getId() const {
	return id;
}
//获取姓名
std::string Student::getName() const {
	return name;
}
//获取平均分
float Student::getAverage() const {
	return average;
}
//获取成绩
std::vector<float> Student::getScores() const {
	return scores;
}

//序列化
std::string Student::serialize() const {
	std::ostringstream os;
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
Student Student::deserialize(const std::string& line) {
	std::stringstream ss(line);
	std::string token;

	getline(ss, token, ',');
	int id = stoi(token);

	std::string name;
	getline(ss, name, ',');

	std::vector<float> scores;
	getline(ss, token);
	std::stringstream ss2(token);
	float x;
	while (ss2 >> x)
		scores.push_back(x);

	return Student(id, name, scores);
}

//重载小于运算符(按id排序)
bool Student::operator<(const Student& other) const {
	return this->id < other.id;
}