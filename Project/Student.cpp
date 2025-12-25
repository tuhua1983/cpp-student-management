#include "Student.h"

/*构造函数*/
	//默认构造
Student::Student() : id(0), name(""), average(0.0) {}
	//赋值构造
Student::Student(int id, std::string name, std::vector<float> scores)
	: id(id), name(name), scores(scores) {
	calculateAverage();
}