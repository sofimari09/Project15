#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>

using namespace std;
enum Spec { PhIT, ME, СS };
string strSpec[] = { "Фiзика ", "Математика","Iнформатика" };
struct Student
{
    char lname[20];
    int kurs;
    Spec spec;
    int physics;
    int math;
    int comscience;
};
void enter_save(char* fname);
void load_print(char* fname);
double Bilshe(char* fname);
void Average(char* fname);
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[61];
    char ch;
    do
    {
        cout << endl;
        cout << "Вибрати:" << endl;
        cout << "[1] - введіть дані;" << endl;
        cout << "[2] - вивести на екран дані;" << endl;
        cout << "[3] - вивід на екран завдання;" << endl;
        cout << "[0] - вийти." << endl << endl;
        cout << "Ваш вибір: "; cin >> ch;
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу: "; cin.getline(fname,
                sizeof(fname));
            enter_save(fname);
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу: "; cin.getline(fname,
                sizeof(fname));
            load_print(fname);
            break;
        case '3':
            cout << endl;
            cout << "Введіть назву файла: "; cin >> fname;
            cout << "cepеднє: "; Average(fname);
            cout << endl;
            cout << "більше : " << Bilshe(fname) << endl;
            break;
        default:
            cout << "Помилка ! ";
        }
    } while (ch != '0');
    return 0;
}
void enter_save(char* fname)
{
    int sp;
    ofstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "Помилка відкриття файла '" << fname << "'" << endl;
        return;
    }
    Student worker;
    char ch;
    do
    {
        cout << endl;
        cout << "Прізвище: "; cin.sync();
        cin >> worker.lname;
        cout << "Курс: "; cin >> worker.kurs;
        cout << "Спецiальнiсть (0 - Фiзика , 1 - Математика, 2 - Iнформатика): ";
        cin >> sp;
        worker.spec = static_cast<Spec>(sp);
        cout << "Оцiнка з фiзики: "; cin >> worker.physics;
        cout << "Оцiнка з математики: "; cin >> worker.math;
        cout << "Оцінка з інформатики: "; cin >> worker.comscience;
        if (!f.write((char*)&worker, sizeof(Student)))
        {
            cerr << "Помилка відкриття файлу." << endl;
        }
        cout << "Продовжити? (Т/т) "; cin >> ch;
    } while (ch == 'Т' || ch == 'т');
}

double Bilshe(char* fname) {
    ifstream f(fname, ios::binary);
    int i = 0;
    Student worker;
    double average;
    while (f.read((char*)&worker, sizeof(Student)))
    {
        average = (worker.physics + worker.math + worker.comscience) / 3.0;
        if (average > 4.5)
            i++;
    }
    return i;
}

void Average(char* fname) {
    ifstream f(fname, ios::binary);
    int i = 0;
    Student worker;
    double maths = 0;
    double comscience = 0;
    double physics = 0;
    int Counter = 0;
    while (f.read((char*)&worker, sizeof(Student)))
    {
        Counter++;
        maths += worker.math;
        physics += worker.physics;
        comscience += worker.comscience;
    }
    if (maths > comscience && maths > physics) {
        cout << strSpec[1];
    }
    else if (maths < comscience && comscience > physics) {
        cout << strSpec[2];
    }
    else if (maths < physics && comscience < physics) {
        cout << strSpec[0];
    }
}
void load_print(char* fname)
{
    int i = 0;
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
        return;
    }
    cout <<
        "========================================================================================="
        << endl;
    cout << "| № | Прiзвище | Курс |     Спецiальнiсть    | Фiзика | Математика | Інформатика | " << endl;
    cout <<
        "-----------------------------------------------------------------------------------------"
        << endl;
    Student worker;
    while (f.read((char*)&worker, sizeof(Student)))
    {
        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(9) << left << worker.lname
            << "| " << setw(5) << right << worker.kurs
            << "| " << setw(20) << left << strSpec[worker.spec]
            << "| " << setw(7) << worker.physics
            << "| " << setw(11) << right << worker.math
            << "| " << setw(12) << left << worker.comscience << "| " <<
            endl;
        ++i;
    }
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
}