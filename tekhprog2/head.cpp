#include "head.h"

STUDENT::STUDENT() {
    cout << "введите имя и фамилию: ";
    cin >> this->name >> this->sname;
    cout << "введите номер группы: ";
    cin >> this->gnum;
    cout << "введите успеваемость: ";
    cin >> usp[0] >> usp[1] >> usp[2] >> usp[3] >> usp[4];
    cout << endl;
}
STUDENT::STUDENT(STUDENT& s) {
    this->name  = s.name;
    this->sname = s.sname;
    this->gnum  = s.gnum;
    for (int i = 0; i < 5 ; i++)
        this->usp[i] = s.usp[i];
}
STUDENT::~STUDENT() {}

void STUDENT::set_name(char n[]) {name = n;}
void STUDENT::set_sname(char sn[]) {sname = sn;}
void STUDENT::set_gnum(int gn) {gnum = gn;}
void STUDENT::set_usp(float u[5]) {
    for (int i = 0 ; i < 5 ; i++) 
        usp[i] = u[i];
}

string STUDENT::get_name  (void) {return name;}
string STUDENT::get_sname (void) {return sname;}
int    STUDENT::get_gnum  (void) {return gnum;}
void   STUDENT::get_usp   (float u[5]) {
    for (int i = 0 ; i < 5 ; i++)
        u[i] = usp[i];
}

void STUDENT::operator >> (STUDENT& s) {
    s.name  = this->name; 
    s.sname = this->sname;
    s.gnum  = this->gnum;
    for (int i = 0 ; i < 5 ; i++) s.usp[i] = this->usp[i];
}
void STUDENT::operator << (STUDENT& s) {
    this->name  = s.name; 
    this->sname = s.sname;
    this->gnum  = s.gnum;
    for (int i = 0 ; i < 5 ; i++) this->usp[i] = s.usp[i];
}

void STUDENT::disp(char s[]) {
    if (strcmp(s, "std") == 0) {
        cout << name  << " "; 
        cout << sname << " ";
        cout << gnum  << " ";
        cout << "[ ";
        for (int i = 0 ; i < 5 ; i++) cout << usp[i] << " ";
        cout << "]";
    } else if (strcmp(s, "srt") == 0) {
        cout << gnum << "  " << sname;
    } else cout << "invalid mode for disp";

    cout << endl;
}

GROUP::GROUP(int size, int gnum) :
size(size), 
gnum(gnum)
{
    float usp[5];
    float sm = 0;
    string s;

    cout << "введите названия предметов через \\n\n";
    for (int i = 0 ; i < 6 ; i++) {
        cout << "предмет " << i+1 << " : ";
        cin >> s;
        subj[i] = s;
    }
    cout << endl;

    g = (STUDENT**) new STUDENT*[size];
    for (int i = 0; i < size ; i++) {
        g[i] = (STUDENT*) new STUDENT();
        g[i]->get_usp(usp);
        for (int i = 0 ; i < 5 ; i++) sm += usp[i];
    }
    average = sm / (size * 5);

    qsort(0, size);
}

GROUP::~GROUP() {
    for (int i = 0 ; i < size ; i++)
        delete g[i];
    delete [] g;
}

void GROUP::qsort(int left, int right) {
    int last;
    if (left >= right)
        return;
    last = left;
    for (int i = left+1 ; i < right ; i++)
        if (g[i]->get_gnum() < g[left]->get_gnum())
            swp(++last, i);
    swp(left, last);

    qsort(left, last-1);
    qsort(last+1, right);
}

void GROUP::swp(int i, int j) {
    STUDENT* temp;
    temp = g[i];
    g[i] = g[j];
    g[j] = temp;
}

void GROUP::disp(void) {
    cout << "средний бал группы " << gnum << ": " << average << endl;
    cout << "студенты группы " << gnum << ":" << endl; 
    for (int i = 0 ; i < size ; i++)
        g[i]->disp("std");
    
}

void GROUP::avgt40(void) {
    for (int i = 0 ; i < size ; i++) {
        float usp[5];
        g[i]->get_usp(usp);
        float av = 0;
        for (int j = 0 ; j < 5 ; j++) av+=usp[j];
        if (av / 5 > 4.0) g[i]->disp("srt");
    }
}