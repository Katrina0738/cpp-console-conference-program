#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Report
{
    int startMinutes;   // время начала в минутах
    int endMinutes;     // время окончания в минутах
    string surname;
    string name;
    string patronymic;
    string topic;
};

// перевод времени чч:мм в минуты
int timeToMinutes(const string& timeStr)
{
    int hours = stoi(timeStr.substr(0, 2));
    int minutes = stoi(timeStr.substr(3, 2));
    return hours * 60 + minutes;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    ifstream file("data.txt");
    if (!file.is_open())
    {
        cout << "Не удалось открыть файл data.txt\n";
        return 1;
    }

    Report reports[100];
    int count = 0;

    // чтение данных из файла
    while (!file.eof())
    {
        string startTime, endTime;
        file >> startTime >> endTime
            >> reports[count].surname
            >> reports[count].name
            >> reports[count].patronymic;

        file.ignore(); // пропускаем пробел перед темой
        getline(file, reports[count].topic);

        reports[count].startMinutes = timeToMinutes(startTime);
        reports[count].endMinutes = timeToMinutes(endTime);

        count++;
    }

    file.close();

    int choice;
    do
    {
        cout << "\nМеню:\n";
        cout << "1 — Показать все доклады\n";
        cout << "2 — Показать доклады Иванова Ивана Ивановича\n";
        cout << "3 — Показать доклады длительностью больше 15 минут\n";
        cout << "0 — Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nВсе доклады:\n";
            for (int i = 0; i < count; i++)
            {
                int duration = reports[i].endMinutes - reports[i].startMinutes;
                cout << reports[i].surname << " "
                    << reports[i].name << " "
                    << reports[i].patronymic << " | "
                    << "Длительность: " << duration << " мин | "
                    << "Тема: " << reports[i].topic << endl;
            }
            break;

        case 2:
            cout << "\nДоклады Иванова Ивана Ивановича:\n";
            for (int i = 0; i < count; i++)
            {
                if (reports[i].surname == "Иванов" &&
                    reports[i].name == "Иван" &&
                    reports[i].patronymic == "Иванович")
                {
                    int duration = reports[i].endMinutes - reports[i].startMinutes;
                    cout << reports[i].surname << " "
                        << reports[i].name << " "
                        << reports[i].patronymic << " | "
                        << "Длительность: " << duration << " мин | "
                        << "Тема: " << reports[i].topic << endl;
                }
            }
            break;

        case 3:
            cout << "\nДоклады длительностью больше 15 минут:\n";
            for (int i = 0; i < count; i++)
            {
                int duration = reports[i].endMinutes - reports[i].startMinutes;
                if (duration > 15)
                {
                    cout << reports[i].surname << " "
                        << reports[i].name << " "
                        << reports[i].patronymic << " | "
                        << "Длительность: " << duration << " мин | "
                        << "Тема: " << reports[i].topic << endl;
                }
            }
            break;

        case 0:
            cout << "Выход из программы.\n";
            break;

        default:
            cout << "Неверный выбор.\n";
        }

    } while (choice != 0);

    return 0;
}
