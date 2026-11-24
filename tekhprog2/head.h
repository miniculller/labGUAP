#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class STUDENT {
private:
    string name;
    string sname;
    int    gnum;
    float  usp[5] = {0};

public:
    STUDENT();
    STUDENT(class STUDENT& s);
    ~STUDENT();

    void set_name  (char n[]);
    void set_sname (char sn[]);
    void set_gnum  (int gn);
    void set_usp   (float u[5]);
    
    string get_name  (void);
    string get_sname (void);
    int    get_gnum  (void);
    void   get_usp   (float u[5]);

    void operator>> (STUDENT& s);
    void operator<< (STUDENT& s);

    void disp(char s[]);
};

class GROUP {
private:
    STUDENT** g;
    int       size;
    float     average;
    int       gnum;
    string    subj[6];
public:
    GROUP(int size, int gnum);
    ~GROUP();
    int get_size() const { return size; }
    int get_gnum() const { return gnum; }
    void qsort(int left, int right);
    void swp  (int i, int j);
    void disp(void);
    void avgt40(void);
};

#endif