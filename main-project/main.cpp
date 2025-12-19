#include <iostream>
#include <fstream>
#include <string>

#include "constants.h"
#include "conference_report.h"

using namespace std;

int timeToMinutes(const string& timeStr)
{
    int hours = stoi(timeStr.substr(0, 2));
    int minutes = stoi(timeStr.substr(3, 2));
    return hours * 60 + minutes;
}
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

    Report reports[MAX_RECORDS];
    int count = 0;

    while (!file.eof() && count < MAX_RECORDS)
    {
        string startTime, endTime;
        Report r;

        file >> startTime >> endTime;
        file >> r.surname >> r.name >> r.patronymic;

        getline(file, r.topic);
        if (!r.topic.empty() && r.topic[0] == ' ')
            r.topic.erase(0, 1);

        r.startMinutes = timeToMinutes(startTime);
        r.endMinutes = timeToMinutes(endTime);

        reports[count] = r;
        count++;
    }

    cout << "Считано записей: " << count << endl;


    file.close();
    return 0;
}
