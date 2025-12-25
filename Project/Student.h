#pragma once
#include <string>
#include <vector>

class Student {
private:
	int id;					//学号
	std::string name;			//姓名
	std::vector<float> scores;	//各科成绩
	float average;			//平均分
public:

	Student();
	Student(int, std::string, std::vector<float>);

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

	//重载小于运算符(按id排序)
	bool operator<(const Student& other) const {
		return this->id < other.id;
	}
};