#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class ERR {
	string errmsg;
	unsigned errcod = 0;
public:
	ERR(string msg, unsigned cod);
	ERR(ERR& other);
	~ERR();

	void printmsg(void);
	void printcod(void);

	unsigned getecod(void) {return errcod;}
	string   getemsg(void) {return errmsg;}
};

class vuz {
public:
	vuz();
	virtual ~vuz();
	virtual void init_const(string[5]) = 0;
	virtual void init_keywo() = 0;
    virtual void info() = 0;
	virtual string** getstptr() = 0;
};

class student : public vuz {
private:
	string name;
    string group;
    string spec;
    string stage;
	string srbal;
	string* stptr[6] = {&name, &group, &spec, &stage, &srbal, nullptr};
public:
	student(char*);
	student(student& st);
	~student();
	void init_const(string[5]);
	void init_keywo();
	void info();
	string** getstptr();
	//get strings
	string getname(void);
	string getgroup(void);
	string getspec(void);
	string getstage(void);
	string getsrbal(void);
};

class teacher : public vuz {
private:
	string name;
	string groups;
	string subjects;
	string* stptr[4] = {&name, &groups, &subjects, nullptr};
public:
	teacher(char*);
	teacher(teacher&);
	~teacher();
	void init_const(string[5]);
	void init_keywo();
	void info();
	string** getstptr();
	//get string
	string getname(void);
	string getgroups(void);
	string getsubjects(void);
};

class adper : public vuz {
private:
	string name;
	string dolzh;
	string phonenumber;
	string oblotvet;
	string* stptr[5] = {&name, &dolzh, &phonenumber, &oblotvet, nullptr};
public:
	adper(char*);
	adper(adper&);
	~adper();
	void init_const(string[5]);
	void init_keywo();
	void info();
	string** getstptr();
	//get string
	string getname(void);
	string getdolzh(void);
	string getphonenumber(void);
	string getoblotvet(void);
};

template<class T> class keeper {
private:
	class vuz** v;
	int size{};
public:
	keeper(int s, char* f) {
		cout << "\033[1;32mkeeper: constructor called\033[0m\n";
		this->size = s;
		v = new vuz*[s];
		if (strcmp(f, "empty") != 0) {
			for (int i = 0 ; i < s ; i++)
				v[i] = (T*) new T("");
		} else {
			for (int i = 0 ; i < s ; i++)
				v[i] = (T*) new T("empty");
		}
	}

	keeper(int s) {
		cout << "\033[1;32mkeeper: constructor called\033[0m\n";
		this->size = s;
		v = new vuz*[s];
		for (int i = 0 ; i < s ; i++)
			v[i] = (T*) new T("");
	}

	keeper(keeper<T>& k) {
		size = k.getsize();
		v = new vuz*[size];
		for (int i = 0 ; i < size ; i++) {
			v[i] = (T*) new T( *(T*)(k.getv()[i]) );
		}
	}

	keeper(keeper<T>& l, keeper<T>& r) {
		int sl = l.getsize();
		int sr = r.getsize();
		this->size = sl + sr;
		v = new vuz*[sl+sr];
		for (int i = 0 ; i < sl ; i++) {
			cout << i << '\n';
			v[i] = (T*) new T( *(T*)(l.getv()[i]) );
		}
		for (int i = 0 ; i < sr ; i++) {
			cout << i << '\n';
			v[i+sl] = (T*) new T( *(T*)(r.getv()[i]) );
		}
	}

	~keeper() {
		cout << "\033[1;32mkeeper: destructor called\033[0m\n";
		for (int i = 0 ; i < size ; i ++)
			delete v[i];
		delete [] v;
	}
	vuz** getv() { return this->v; }
	int getsize() { return this->size; }
	void printall(void);
	void set(int idx, string s[5]);
	T get(int idx);
	void writefile(string filename);
	void readfile(string filename);
	T operator[] (int);
};

template<class T> void keeper<T>::set(int idx, string s[5]) {
	if (idx >= size) throw ERR("idx out of range", 1);
	v[idx]->init_const(s);
}

template<class T> T keeper<T>::get(int idx) {
	if (idx >= size) throw ERR("idx out of range", 1);
	return *(T*)v[idx];
}

template<class T> void keeper<T>::printall(void) {
	for (int i = 0 ; i < size ; v[i++]->info());
}

template<class T> T keeper<T>::operator[] (int idx) {
	if (idx >= size) throw ERR("idx out of range", 1);
	return *(T*)v[idx];
}

template<class T> void keeper<T>::writefile(string filename) {
	ofstream out;
	out.open(filename);
	string** curst;
	for (int i = 0; i < size ; i++) {
		curst = v[i]->getstptr();
		while ( *curst != nullptr )
			out << **(curst++) << ' ';
		out << '\n';
	}
	out.close();
}

template<class T> void keeper<T>::readfile(string filename) {
	ifstream in;
	in.open(filename, ios::in);
	string** curst;
	for (int i = 0; i < size ; i++) {
		curst = v[i]->getstptr();
		while ( *curst != nullptr )
			in >> **(curst++);
	}
	in.close();
}
