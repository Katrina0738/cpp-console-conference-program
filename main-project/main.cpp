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
    cout << "\nСписок докладов:\n";

    for (int i = 0; i < count; i++)
    {
        cout << i + 1 << ". ";
        cout << reports[i].surname << " "
            << reports[i].name << " "
            << reports[i].patronymic << " | ";

        int duration = reports[i].endMinutes - reports[i].startMinutes;
        cout << "Длительность: " << duration << " мин | ";
        cout << "Тема: " << reports[i].topic << endl;
    }
    cout << "\nДоклады Иванова Ивана Ивановича:\n";

    bool foundIvanov = false;

    for (int i = 0; i < count; i++)
    {
        if (reports[i].surname == "Иванов" &&
            reports[i].name == "Иван" &&
            reports[i].patronymic == "Иванович")
        {
            cout << reports[i].surname << " "
                << reports[i].name << " "
                << reports[i].patronymic << " | ";

            int duration = reports[i].endMinutes - reports[i].startMinutes;
            cout << "Длительность: " << duration << " мин | ";
            cout << "Тема: " << reports[i].topic << endl;

            foundIvanov = true;
        }
    }

    if (!foundIvanov)
    {
        cout << "Доклады не найдены.\n";
    }

    cout << "\nДоклады длительностью больше 15 минут:\n";

    bool foundLong = false;

    for (int i = 0; i < count; i++)
    {
        int duration = reports[i].endMinutes - reports[i].startMinutes;

        if (duration > 15)
        {
            cout << reports[i].surname << " "
                << reports[i].name << " "
                << reports[i].patronymic << " | ";
            cout << "Длительность: " << duration << " мин | ";
            cout << "Тема: " << reports[i].topic << endl;

            foundLong = true;
        }
    }

    if (!foundLong)
    {
        cout << "Доклады не найдены.\n";
    }



    file.close();
    return 0;
}
