#pragma once
#include <string>
#include <vector>
#include <sstream>

class Student {
private:
	int id;					//学号
	std::string name;			//姓名
	std::vector<float> scores;	//各科成绩
	float average;			//平均分
public:

	Student();
	Student(int, std::string, std::vector<float>);
	Student(const Student&);

	void initialize(int,std::string);

	//插入成绩函数
	void insertScores(const std::vector<float>&);

	//计算平均分函数
	void calculateAverage();

	//获取学号
	int getId() const;
	//获取姓名
	std::string getName() const;
	//获取平均分
	float getAverage() const;
	//获取成绩
	std::vector<float> getScores() const;

	//序列化
	std::string serialize() const;

	//反序列化
	static Student deserialize(const std::string&);

	//重载小于运算符(按id排序)
	bool operator<(const Student& other) const;
};