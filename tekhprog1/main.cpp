#include"vuz.h"
#include <vector>
#include <limits>

// ================= утилиты ввода =================

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& p) {
    int x;
    while (true) {
        cout << p;
        if (cin >> x) return x;
        cout << "\033[1;31mОшибка: введите число\033[0m\n";
        clearInput();
    }
}

string readStr(const string& p) {
    string s;
    cout << p;
    cin >> s;
    return s;
}

void pause() {
    cout << "\n\033[1;36mНажмите Enter...\033[0m";
    clearInput();
    cin.get();
}

// ================= обёртка над keeper<T> =================

enum class GroupType { STUDENT, TEACHER, ADPER };

string typeName(GroupType t) {
    switch (t) {
        case GroupType::STUDENT: return "студенты";
        case GroupType::TEACHER: return "преподаватели";
        case GroupType::ADPER:   return "адперсонал";
    }
    return "?";
}

class AnyGroup {
private:
    GroupType type;
    keeper<student>* s = nullptr;
    keeper<teacher>* t = nullptr;
    keeper<adper>*   a = nullptr;
    string name;

public:
    AnyGroup(const string& name, int n, const string& flag, GroupType type)
        : type(type), name(name)
    {
        char f[8];
        strncpy(f, flag.c_str(), 7);
        f[7] = 0;
        switch (type) {
            case GroupType::STUDENT: s = new keeper<student>(n, f); break;
            case GroupType::TEACHER: t = new keeper<teacher>(n, f); break;
            case GroupType::ADPER:   a = new keeper<adper>(n, f);   break;
        }
    }

    AnyGroup(const AnyGroup& other) : type(other.type), name(other.name) {
        if (other.s) s = new keeper<student>(*other.s);
        if (other.t) t = new keeper<teacher>(*other.t);
        if (other.a) a = new keeper<adper>(*other.a);
    }

    ~AnyGroup() {
        delete s;
        delete t;
        delete a;
    }

    GroupType getType() const { return type; }
    string getName() const { return name; }

    int getsize() const {
        if (s) return s->getsize();
        if (t) return t->getsize();
        if (a) return a->getsize();
        return 0;
    }

    void printall() const {
        if (s) s->printall();
        if (t) t->printall();
        if (a) a->printall();
    }

    void set(int idx, string data[5]) {
        if (s) s->set(idx, data);
        else if (t) t->set(idx, data);
        else if (a) a->set(idx, data);
    }

    void getInfo(int idx) {
        if (s) { s->get(idx).info(); return; }
        if (t) { t->get(idx).info(); return; }
        if (a) { a->get(idx).info(); return; }
    }

    void writefile(const string& fname) {
        if (s) s->writefile(fname);
        if (t) t->writefile(fname);
        if (a) a->writefile(fname);
    }

    void readfile(const string& fname) {
        if (s) s->readfile(fname);
        if (t) t->readfile(fname);
        if (a) a->readfile(fname);
    }

    AnyGroup* concat(const AnyGroup& other) {
        if (type != other.type) {
            cout << "\033[1;31mНельзя объединять разные типы.\033[0m\n";
            return nullptr;
        }
        AnyGroup* res = new AnyGroup(other);
        res->name = name + "+" + other.name;

        switch (type) {
            case GroupType::STUDENT: {
                keeper<student> merged(*s, *other.s);
                delete res->s;
                res->s = new keeper<student>(merged);
                break;
            }
            case GroupType::TEACHER: {
                keeper<teacher> merged(*t, *other.t);
                delete res->t;
                res->t = new keeper<teacher>(merged);
                break;
            }
            case GroupType::ADPER: {
                keeper<adper> merged(*a, *other.a);
                delete res->a;
                res->a = new keeper<adper>(merged);
                break;
            }
        }
        return res;
    }
};

// ================= список групп =================

vector<AnyGroup*> groups;

int pickGroup() {
    if (groups.empty()) {
        cout << "\033[1;31mСписок групп пуст.\033[0m\n";
        return -1;
    }
    cout << "\nДоступные группы:\n";
    for (size_t i = 0; i < groups.size(); i++) {
        cout << i << ") " << groups[i]->getName()
             << " [" << typeName(groups[i]->getType())
             << ", size=" << groups[i]->getsize() << "]\n";
    }
    int idx = readInt("Индекс группы (-1 - отмена): ");
    if (idx < 0 || idx >= (int)groups.size()) return -1;
    return idx;
}

// ================= пункты меню =================

void menuCreate() {
    cout << "\n--- Создать группу ---\n";
    cout << "1. Студенты\n2. Преподаватели\n3. Адперсонал\n";
    int type = readInt("Тип: ");
    int n    = readInt("Размер: ");
    if (n <= 0) { cout << "Отмена.\n"; return; }

    int manual = readInt("Заполнять вручную? (1/0): ");
    string name = readStr("Имя группы: ");

    GroupType gt;
    switch (type) {
        case 1: gt = GroupType::STUDENT; break;
        case 2: gt = GroupType::TEACHER; break;
        case 3: gt = GroupType::ADPER;   break;
        default: cout << "Неверный тип.\n"; return;
    }
    groups.push_back(new AnyGroup(name, n, manual ? "manual" : "empty", gt));
    cout << "\033[1;32mГотово.\033[0m\n";
}

void menuSet() {
    cout << "\n--- Записать по индексу ---\n";
    int g = pickGroup();
    if (g < 0) return;

    int idx = readInt("Индекс записи: ");
    if (idx < 0 || idx >= groups[g]->getsize()) {
        cout << "Индекс вне диапазона.\n"; return;
    }

    string data[5] = {"", "", "", "", ""};
    int manual = readInt("Заполнять вручную? (1/0): ");
    if (manual) {
        cout << "Поле 1 (имя): "; cin >> data[0];
        cout << "Поле 2: ";       cin >> data[1];
        cout << "Поле 3: ";       cin >> data[2];
        cout << "Поле 4: ";       cin >> data[3];
        cout << "Поле 5: ";       cin >> data[4];
    }
    groups[g]->set(idx, data);
    cout << "\033[1;32mЗаписано.\033[0m\n";
}

void menuGet() {
    cout << "\n--- Прочитать по индексу ---\n";
    int g = pickGroup();
    if (g < 0) return;
    int idx = readInt("Индекс записи: ");
    if (idx < 0 || idx >= groups[g]->getsize()) {
        cout << "Индекс вне диапазона.\n"; return;
    }
    groups[g]->getInfo(idx);
}

void menuShow() {
    cout << "\n--- Показать группы ---\n";
    if (groups.empty()) { cout << "Пусто.\n"; return; }
    for (auto* gr : groups) {
        cout << "\n\033[1;35m" << gr->getName()
             << " [" << typeName(gr->getType()) << "]:\033[0m\n";
        gr->printall();
    }
}

void menuSave() {
    int g = pickGroup();
    if (g < 0) return;
    string f = readStr("Имя файла: ");
    groups[g]->writefile(f);
    cout << "\033[1;32mСохранено.\033[0m\n";
}

void menuLoad() {
    int g = pickGroup();
    if (g < 0) return;
    string f = readStr("Имя файла: ");
    groups[g]->readfile(f);
    cout << "\033[1;32mЗагружено.\033[0m\n";
}

void menuConcat() {
    cout << "\n--- Объединить две группы ---\n";
    cout << "Первая:\n";  int a = pickGroup(); if (a < 0) return;
    cout << "Вторая:\n";  int b = pickGroup(); if (b < 0) return;
    if (a == b) { cout << "Нельзя объединять группу с самой собой.\n"; return; }

    AnyGroup* merged = groups[a]->concat(*groups[b]);
    if (merged) {
        groups.push_back(merged);
        cout << "\033[1;32mСоздана группа '" << merged->getName() << "'.\033[0m\n";
    }
}

void menuDelete() {
    int g = pickGroup();
    if (g < 0) return;
    delete groups[g];
    groups.erase(groups.begin() + g);
    cout << "\033[1;32mУдалено.\033[0m\n";
}

// ================= main =================

int main() {
    // стартовая демо-группа студентов
    groups.push_back(new AnyGroup("group1", 2, "manual", GroupType::STUDENT));

    while (true) {
        cout << "\n\033[1;35m========= МЕНЮ =========\033[0m\n";
        cout << "1. Создать группу (студенты/преподаватели/адперсонал)\n";
        cout << "2. Записать по индексу (set)\n";
        cout << "3. Прочитать по индексу (get)\n";
        cout << "4. Показать все группы\n";
        cout << "5. Сохранить группу в файл\n";
        cout << "6. Загрузить группу из файла\n";
        cout << "7. Объединить две группы\n";
        cout << "8. Удалить группу\n";
        cout << "0. Выход\n";

        int c = readInt("Выбор: ");
        switch (c) {
            case 1: menuCreate(); break;
            case 2: menuSet();    break;
            case 3: menuGet();    break;
            case 4: menuShow();   break;
            case 5: menuSave();   break;
            case 6: menuLoad();   break;
            case 7: menuConcat(); break;
            case 8: menuDelete(); break;
            case 0:
                for (auto* g : groups) delete g;
                cout << "Пока.\n";
                return 0;
            default: cout << "Нет такого пункта.\n";
        }
        pause();
    }
}
