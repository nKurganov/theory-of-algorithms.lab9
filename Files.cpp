#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;
//1. Используя ввод - вывод в стиле С создать файл и записать в него структурированные данные.
//2. Вывести созданный файл на экран.
//3. Удалить из файла данные в соответствии с вариантом.
//4. Добавить в файл данные в соответствии с вариантом.
//5. Вывести измененный файл на экран.
//6. Используя ввод - вывод в стиле С++ создать файл и записать в него структурированные данные.
//7. Вывести созданный файл на экран.
//8. Удалить из файла данные в соответствии с вариантом.
//9. Добавить в файл данные в соответствии с вариантом.
//10. Вывести измененный файл на экран.
//Вариант 1
struct Enrollee //структура учиника
{
    string FIO;//ФИО
    string birfDay;//дата рождения
    int marks[3];//оценки
    double avg;//средняя оценку
};
//удалить k-ый элемет из файла
void del_num(const char* filename, int k)
{
    fstream temp("temp", ios::out);//исходный файл
    fstream f(filename, ios::in);//вспомогательный файл
    Enrollee a;//буфер для чтения данных из файла
        //считываем данные из исходного файла в буфер
    int id = 1;
    do {
        f >> a.FIO;
        f >> a.birfDay;
        f >> a.marks[0];
        f >> a.marks[1];
        f >> a.marks[2];
        f >> a.avg;
        if (f.eof())break;
        if (id != k)//если номер записи не равен х
        {
            temp << a.FIO; temp << "\n";
            temp << a.birfDay; temp << "\n";
            temp << a.marks[0]; temp << "\n";
            temp << a.marks[1]; temp << "\n";
            temp << a.marks[2]; temp << "\n";
            temp << a.avg; temp << "\n";
        }
        id++;
    } while (!f.eof());
    f.close();//закрываем исходный файл
    temp.close(); //закрываем временный файл
    remove(filename);//удаляем исходный файл
    rename("temp", filename);//переименовываем временный файл
}
//добавить k данных в файл
void add_in_beginning(const char* filename, struct Enrollee* mas, int n)
{
    fstream temp("temp", ios::out);//исходный файл
    fstream f(filename, ios::in);//вспомогательный файл
    Enrollee a;//буфер для чтения данных из файла
        //считываем данные из исходного файла в буфер
    for (int i = 0; i < n; i++)
    {
        //добавляем данные из массива
        temp << mas[i].FIO; temp << "\n";
        temp << mas[i].birfDay; temp << "\n";
        temp << mas[i].marks[0]; temp << "\n";
        temp << mas[i].marks[1]; temp << "\n";
        temp << mas[i].marks[2]; temp << "\n";
        temp << mas[i].avg; temp << "\n";
    }
    do {
        //читанем данные из файла
        f >> a.FIO;
        f >> a.birfDay;
        f >> a.marks[0];
        f >> a.marks[1];
        f >> a.marks[2];
        f >> a.avg;
        if (f.eof())break;
        //переписываем их в конец файла
        temp << a.FIO; temp << "\n";
        temp << a.birfDay; temp << "\n";
        temp << a.marks[0]; temp << "\n";
        temp << a.marks[1]; temp << "\n";
        temp << a.marks[2]; temp << "\n";
        temp << a.avg; temp << "\n"; 
    } while (!f.eof());
    f.close();//закрываем исходный файл
    temp.close(); //закрываем временный файл
    remove(filename);//удаляем исходный файл
    rename("temp", filename);//переименовываем временный файл
}
// запись в файл массива структур
void save(const char* filename, struct Enrollee* mas, int n)
{
    fstream f(filename, ios::out);//двунаправленный файловый поток
    for (int i = 0; i < n; i++)
    {
        //добавляем данные в файл
        f << mas[i].FIO; f << "\n";
        f << mas[i].birfDay; f << "\n";
        f << mas[i].marks[0]; f << "\n";
        f << mas[i].marks[1]; f << "\n";
        f << mas[i].marks[2]; f << "\n";
        f << mas[i].avg; f << "\n";
    }

    f.close();//закрытие потока
}

// загрузка из файла массива структур
void load(const char* filename)
{
    fstream f;
    Enrollee p;
    f.open(filename, ios::in);//открываем поток для чтения
    int id = 1;//id для вывода номера
    do
    {
        //достаём данные
        f >> p.FIO;
        f >> p.birfDay;
        f >> p.marks[0];
        f >> p.marks[1];
        f >> p.marks[2];
        f >> p.avg;
        if (f.eof())break;
        //выводим их
        cout << id << " " << p.FIO << " " << p.birfDay << " " << p.marks[0] << " " << p.marks[1] << " " << p.marks[2] << " " << p.avg << "\n";
        id++;
    } while (!f.eof());

    f.close();//закрытие потока
}


int main(void)
{
    setlocale(LC_ALL, "Rus");//меняем язык консоли на русский
    const char* filename = "studens.stud";
    Enrollee* mas;//динамический массив
    int n;
    while (true) {
        cout << "Введите кол-во данных:";
        cin >> n;
        mas = new Enrollee[n];//создаем динамический массив
        for (int i = 0; i < n; i++)
        {
            cout << "ФИО: ";
            //ввод одного элемента типа person из стандартного потока cin
            cin >> mas[i].FIO;
            cout << "Дата рождения: ";
            cin >> mas[i].birfDay;
            cout << "Оценка по предмету 1: ";
            cin >> mas[i].marks[0];
            cout << "Оценка по предмету 2: ";
            cin >> mas[i].marks[1];
            cout << "Оценка по предмету 3: ";
            cin >> mas[i].marks[2];
            mas[i].avg = (mas[i].marks[0] + mas[i].marks[1] + mas[i].marks[2]) / 3;
        }
        save(filename, mas, n);
        load(filename);

        cout << "Удалить из файла студента под номером k =";
        cin >> n;
        del_num(filename, n);
        cout << "Введите кол-во добавляемых в файл данных: ";
        cin >> n;
        mas = new Enrollee[n];//создаем динамический массив
        for (int i = 0; i < n; i++)
        {
            cout << "ФИО: ";
            //ввод одного элемента типа person из стандартного потока cin
            cin >> mas[i].FIO;
            cout << "Дата рождения: ";
            cin >> mas[i].birfDay;
            cout << "Оценка по предмету 1: ";
            cin >> mas[i].marks[0];
            cout << "Оценка по предмету 2: ";
            cin >> mas[i].marks[1];
            cout << "Оценка по предмету 3: ";
            cin >> mas[i].marks[2];
            mas[i].avg = (mas[i].marks[0] + mas[i].marks[1] + mas[i].marks[2]) / 3;
        }
        add_in_beginning(filename, mas, n);
        load(filename);
    }
    return 0;
}
