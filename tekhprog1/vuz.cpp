#include"vuz.h"

//констукторы и деструкторы

vuz::vuz() { cout << "\033[1;32mvuz: constructor called\033[0m\n"; }
vuz::~vuz() { cout << "\033[1;32mvuz: destructor called\033[0m\n"; }


student::student(char* f) {
	cout << "\033[1;32mstudent: constructor called\033[0m\n";
	if (strcmp(f, "empty") != 0) {
		cout << "введите имя: ";
		cin >> this->name;
		cout << "введите группу: ";
		cin >> this->group;
		cout << "введите специальность: ";
		cin >> this->spec;
		cout << "введите курс: ";
		cin >> this->stage;
		cout << "введите средний балл: ";
		cin >> this->srbal;
	}
}

teacher::teacher(char* f) {
	cout << "\033[1;32mteacher: constructor called\033[0m\n";
	if (strcmp(f, "empty") != 0) {
		cout << "введите имя: ";
		cin >> this->name;
		cout << "введите группы, разделив их знаком ',': ";
		cin >> this->groups;
		cout << "введите предметы, разделив их знаком ',': ";
		cin >> this->subjects;
	}
}

adper::adper(char* f) {
	cout << "\033[1;32madper: constructor called\033[0m\n";
	if (strcmp(f, "empty") != 0) {
		cout << "введите имя: ";
		cin >> this->name;
		cout << "введите должность: ";
		cin >> this->dolzh;
		cout << "введите номер телефона: ";
		cin >> this->phonenumber;
		cout << "введите область ответственности: ";
		cin >> this->oblotvet;
	}
}

student::student(student& st) {
	name = st.getname();
	group = st.getgroup();
	spec = st.getspec();
	stage = st.getstage();
	srbal = st.getsrbal();
}

teacher::teacher(teacher& te) {
	name = te.getname();
	groups = te.getgroups();
	subjects = te.getsubjects();
}

adper::adper(adper& ad) {
	name = ad.getname();
	dolzh = ad.getdolzh();
	phonenumber = ad.getphonenumber();
	oblotvet = ad.getoblotvet();
}

student::~student() {
	cout << "\033[1;32mstudent: destructor called\033[0m\n";
}
teacher::~teacher() {
	cout << "\033[1;32mteacher: destructor called\033[0m\n";
}
adper::~adper() {
	cout << "\033[1;32madper: destructor called\033[0m\n";
}

//методы производных классов

void student::info() {
	cout << "\033[1;33m" << name << "\033[0m" << '\n';
	cout << group << '\n';
	cout << spec << '\n';
	cout << stage << '\n';
	cout << srbal << '\n';
}

void teacher::info() {
	cout << "\033[1;33m" << name << "\033[0m" << '\n';
	cout << groups << '\n';
	cout << subjects << '\n';
}

void adper::info() {
	cout << "\033[1;33m" << name << "\033[0m" << '\n';
	cout << dolzh << '\n';
	cout << phonenumber << '\n';
	cout << oblotvet << '\n';
}

void student::init_const(string s[5]) {
	this->name = s[0];
	this->group = s[1];
	this->spec = s[2];
	this->stage = s[3];
	this->srbal = s[4];
}

void teacher::init_const(string s[5]) {
	this->name = s[0];
	this->groups = s[1];
	this->subjects = s[2];
}

void adper::init_const(string s[5]) {
	this->name = s[0];
	this->dolzh = s[1];
	this->phonenumber = s[2];
	this->oblotvet = s[3];
}

void student::init_keywo() {
	cout << "student\n";
	cout << "введите имя: ";
	cin >> this->name;
	cout << "введите группу: ";
	cin >> this->group;
	cout << "введите специальность: ";
	cin >> this->spec;
	cout << "введите курс: ";
	cin >> this->stage;
	cout << "введите средний балл: ";
	cin >> this->srbal;
}

void teacher::init_keywo() {
	cout << "teacher\n";
	cout << "введите имя: ";
	cin >> this->name;
	cout << "введите группы, разделив их знаком ',': ";
	cin >> this->groups;
	cout << "введите предметы, разделив их знаком ',': ";
	cin >> this->subjects;
}

void adper::init_keywo() {
	cout << "adper\n";
	cout << "введите имя: ";
	cin >> this->name;
	cout << "введите должность: ";
	cin >> this->dolzh;
	cout << "введите номер телефона: ";
	cin >> this->phonenumber;
	cout << "введите область ответственности: ";
	cin >> this->oblotvet;
}

string student::getname(void) {
	return name;
}
string student::getgroup(void) {
	return group;
}
string student::getspec(void) {
	return spec;
}
string student::getstage(void) {
	return stage;
}
string student::getsrbal(void) {
	return srbal;
}


string teacher::getname(void) {
	return name;
}
string teacher::getgroups(void) {
	return groups;
}
string teacher::getsubjects(void) {
	return subjects;
}


string adper::getname(void) {
	return name;
}
string adper::getdolzh(void) {
	return dolzh;
}
string adper::getphonenumber(void) {
	return phonenumber;
}
string adper::getoblotvet(void) {
	return oblotvet;
}

string** student::getstptr() { return stptr; }
string** teacher::getstptr() { return stptr; }
string** adper::getstptr() { return stptr; }

ERR::ERR(std::string msg, unsigned cod) {
	errmsg = msg;
	errcod = cod;
}

ERR::ERR(ERR& other) {
	errmsg = other.getemsg();
	errcod = other.getecod();
}

ERR::~ERR() {

}