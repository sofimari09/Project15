#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>

using namespace std;
enum Spec { PhIT, ME, �S };
string strSpec[] = { "�i���� ", "����������","I����������" };
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
        cout << "�������:" << endl;
        cout << "[1] - ������ ���;" << endl;
        cout << "[2] - ������� �� ����� ���;" << endl;
        cout << "[3] - ���� �� ����� ��������;" << endl;
        cout << "[0] - �����." << endl << endl;
        cout << "��� ����: "; cin >> ch;
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "������ ����� �����: "; cin.getline(fname,
                sizeof(fname));
            enter_save(fname);
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "������ ����� �����: "; cin.getline(fname,
                sizeof(fname));
            load_print(fname);
            break;
        case '3':
            cout << endl;
            cout << "������ ����� �����: "; cin >> fname;
            cout << "cep���: "; Average(fname);
            cout << endl;
            cout << "����� : " << Bilshe(fname) << endl;
            break;
        default:
            cout << "������� ! ";
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
        cerr << "������� �������� ����� '" << fname << "'" << endl;
        return;
    }
    Student worker;
    char ch;
    do
    {
        cout << endl;
        cout << "�������: "; cin.sync();
        cin >> worker.lname;
        cout << "����: "; cin >> worker.kurs;
        cout << "����i����i��� (0 - �i���� , 1 - ����������, 2 - I����������): ";
        cin >> sp;
        worker.spec = static_cast<Spec>(sp);
        cout << "��i��� � �i����: "; cin >> worker.physics;
        cout << "��i��� � ����������: "; cin >> worker.math;
        cout << "������ � �����������: "; cin >> worker.comscience;
        if (!f.write((char*)&worker, sizeof(Student)))
        {
            cerr << "������� �������� �����." << endl;
        }
        cout << "����������? (�/�) "; cin >> ch;
    } while (ch == '�' || ch == '�');
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
        cerr << "������� �������� ����� '" << fname << "'" << endl;
        return;
    }
    cout <<
        "========================================================================================="
        << endl;
    cout << "| � | ��i����� | ���� |     ����i����i���    | �i���� | ���������� | ����������� | " << endl;
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