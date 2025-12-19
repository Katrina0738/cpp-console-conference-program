#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Report
{
    int startMinutes;
    int endMinutes;
    string surname;
    string name;
    string patronymic;
    string topic;
};

int timeToMinutes(const string& timeStr)
{
    int h = stoi(timeStr.substr(0, 2));
    int m = stoi(timeStr.substr(3, 2));
    return h * 60 + m;
}

int duration(const Report& r)
{
    return r.endMinutes - r.startMinutes;
}

/* ===== ФУНКЦИИ СРАВНЕНИЯ ===== */

// по убыванию длительности
int compareByDuration(const Report* a, const Report* b)
{
    return duration(*b) - duration(*a);
}

// по возрастанию фамилии, затем темы
int compareBySurnameAndTopic(const Report* a, const Report* b)
{
    if (a->surname != b->surname)
        return a->surname.compare(b->surname);
    return a->topic.compare(b->topic);
}

/* ===== HEAP SORT ===== */

void heapify(Report* arr[], int n, int i,
    int (*cmp)(const Report*, const Report*))
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && cmp(arr[l], arr[largest]) < 0)
        largest = l;

    if (r < n && cmp(arr[r], arr[largest]) < 0)
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, cmp);
    }
}

void heapSort(Report* arr[], int n,
    int (*cmp)(const Report*, const Report*))
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, cmp);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, cmp);
    }
}

/* ===== MERGE SORT ===== */

void merge(Report* arr[], int l, int m, int r,
    int (*cmp)(const Report*, const Report*))
{
    int n1 = m - l + 1;
    int n2 = r - m;

    Report** L = new Report * [n1];
    Report** R = new Report * [n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (cmp(L[i], R[j]) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(Report* arr[], int l, int r,
    int (*cmp)(const Report*, const Report*))
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(arr, l, m, cmp);
        mergeSort(arr, m + 1, r, cmp);
        merge(arr, l, m, r, cmp);
    }
}

/* ===== MAIN ===== */

int main()
{
    setlocale(LC_ALL, "Russian");

    ifstream file("data.txt");
    if (!file)
    {
        cout << "Ошибка открытия data.txt\n";
        return 1;
    }

    Report reports[100];
    Report* ptrs[100];
    int n = 0;

    while (!file.eof())
    {
        string s, e;
        file >> s >> e
            >> reports[n].surname
            >> reports[n].name
            >> reports[n].patronymic;
        file.ignore();
        getline(file, reports[n].topic);

        reports[n].startMinutes = timeToMinutes(s);
        reports[n].endMinutes = timeToMinutes(e);
        ptrs[n] = &reports[n];
        n++;
    }
    file.close();

    int sortChoice, cmpChoice;
    cout << "\nВыберите метод сортировки:\n";
    cout << "1 — Heap sort\n2 — Merge sort\n";
    cin >> sortChoice;

    cout << "\nВыберите критерий:\n";
    cout << "1 — По убыванию длительности\n";
    cout << "2 — По возрастанию фамилии и темы\n";
    cin >> cmpChoice;

    int (*cmp)(const Report*, const Report*) =
        (cmpChoice == 1) ? compareByDuration : compareBySurnameAndTopic;

    if (sortChoice == 1)
        heapSort(ptrs, n, cmp);
    else
        mergeSort(ptrs, 0, n - 1, cmp);

    cout << "\nОтсортированные доклады:\n";
    for (int i = 0; i < n; i++)
    {
        cout << ptrs[i]->surname << " "
            << ptrs[i]->name << " | "
            << "Длительность: " << duration(*ptrs[i])
            << " | Тема: " << ptrs[i]->topic << endl;
    }

    return 0;
}
