#include <iostream>
#include <fstream>
#include <string>

#include "constants.h"
#include "conference_report.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8" << endl;
    cout << "Вариант 2. Программа конференции" << endl;
    cout << "Автор: Katrina" << endl << endl;

    ifstream file("data.txt");

    if (!file.is_open())
    {
        cout << "Не удалось открыть файл data.txt" << endl;
        return 1;
    }

    cout << "Файл data.txt успешно открыт." << endl;

    file.close();
    return 0;
}
