#include "head.h"
#include <vector>
#include <limits>

static void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static int read_int(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) { clear_input(); return x; }
        cout << "  ошибка: нужно целое число\n";
        clear_input();
    }
}

// ---------- меню активной группы ----------
static void group_menu(GROUP* grp, int size) {
    bool back = false;
    while (!back) {
        cout << "\n--- ГРУППА " << grp->get_gnum() << " ---\n"
             << " 1. Показать всех (disp)\n"
             << " 2. Средний балл > 4.0 (avgt40)\n"
             << " 3. Отсортировать по номеру группы (qsort)\n"
             << " 4. Поменять двух студентов (swp)\n"
             << " 0. Назад к списку групп\n"
             << "Выбор: ";
        int cmd = read_int("");
        switch (cmd) {
        case 1:
            grp->disp();
            break;
        case 2:
            cout << "\nСтуденты со средним баллом > 4.0:\n";
            grp->avgt40();
            cout << '\n';
            break;
        case 3:
            grp->qsort(0, size);
            cout << "  сортировка выполнена\n";
            grp->disp();
            break;
        case 4: {
            int i = read_int("Индекс первого: ");
            int j = read_int("Индекс второго: ");
            if (i < 0 || i >= size || j < 0 || j >= size || i == j) {
                cout << "  неверные индексы\n";
            } else {
                grp->swp(i, j);
                cout << "  обмен выполнен\n";
                grp->disp();
            }
            break;
        }
        case 0:
            back = true;
            break;
        default:
            cout << "  неизвестная команда\n";
        }
    }
}

// ---------- верхний уровень ----------
int main() {
    vector<GROUP*> groups;
    int active = -1;

    bool running = true;
    while (running) {
        cout << "\n===== ГРУППЫ =====\n";
        if (groups.empty()) {
            cout << "  (список пуст)\n";
        } else {
            for (size_t i = 0; i < groups.size(); ++i) {
                cout << "  группа " << groups[i]->get_gnum()
                     << " (индекс " << i << ")"
                     << (static_cast<int>(i) == active ? " *активна*" : "")
                     << "\n";
            }
        }
        cout << " 1. Создать группу\n"
             << " 2. Удалить группу\n"
             << " 3. Выбрать активную (по номеру)\n"
             << " 4. Показать все группы (disp)\n"
             << " 5. avgt40 для всех групп\n"
             << " 6. Работа с группой (по номеру)\n"
             << " 0. Выход\n"
             << "Выбор: ";
        int cmd = read_int("");

        switch (cmd) {
        case 1: {
            int size = read_int("Размер группы: ");
            int gnum = read_int("Номер группы:   ");
            if (size <= 0) { cout << "  размер должен быть > 0\n"; break; }
            groups.push_back(new GROUP(size, gnum));
            active = static_cast<int>(groups.size()) - 1;
            cout << "  группа создана и выбрана активной\n";
            break;
        }

        case 2: {
            if (groups.empty()) { cout << "  список пуст\n"; break; }
            int want = read_int("Номер группы для удаления: ");
            int idx = -1;
            for (size_t i = 0; i < groups.size(); ++i)
                if (groups[i]->get_gnum() == want) { idx = static_cast<int>(i); break; }
            if (idx < 0) { cout << "  нет такой группы\n"; break; }
            delete groups[idx];
            groups.erase(groups.begin() + idx);
            if (active == idx)          active = groups.empty() ? -1 : 0;
            else if (active > idx)      --active;
            cout << "  группа удалена\n";
            break;
        }

        case 3: {
            if (groups.empty()) { cout << "  список пуст\n"; break; }
            int want = read_int("Номер группы: ");
            int idx = -1;
            for (size_t i = 0; i < groups.size(); ++i)
                if (groups[i]->get_gnum() == want) { idx = static_cast<int>(i); break; }
            if (idx < 0) { cout << "  нет такой группы\n"; break; }
            active = idx;
            cout << "  активная группа: " << want << '\n';
            break;
        }

        case 4:
            if (groups.empty()) { cout << "  список пуст\n"; break; }
            for (size_t i = 0; i < groups.size(); ++i) {
                cout << "\n[группа " << groups[i]->get_gnum()
                     << (static_cast<int>(i) == active ? ", активна" : "") << "]\n";
                groups[i]->disp();
            }
            break;

        case 5:
            if (groups.empty()) { cout << "  список пуст\n"; break; }
            for (size_t i = 0; i < groups.size(); ++i) {
                cout << "\n[группа " << groups[i]->get_gnum() << "]\n";
                groups[i]->avgt40();
            }
            break;

        case 6: {
            if (groups.empty()) { cout << "  список пуст\n"; break; }
            int want = read_int("Номер группы: ");
            int idx = -1;
            for (size_t i = 0; i < groups.size(); ++i)
                if (groups[i]->get_gnum() == want) { idx = static_cast<int>(i); break; }
            if (idx < 0) { cout << "  группы с таким номером нет\n"; break; }
            active = idx;
            group_menu(groups[active], groups[active]->get_size());
            break;
        }

        case 0:
            running = false;
            break;

        default:
            cout << "  неизвестная команда\n";
        }
    }

    for (GROUP* g : groups) delete g;
    return 0;
}