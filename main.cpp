#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>

//Описываем класс Задача
class Task {
private:
    int id, priority;
    std::string name, description;
    bool done;
public:
    //Базовые сеттеры
    void setPriority(int prio) { priority = prio;}
    void setName(std::string n) { name = n;}
    void setDescription(std::string desc) { description = desc;}
    //Базовые геттеры
    std::string getName() { return name; }
    std::string getDescription() { return description; }
    int getPriority() { return priority; }
    int getId() { return id; }
    //Конструктор без парамертров
    Task() {
        id = -1;
        name = "";
        description = "";
        priority = -1;
    }
    //Конструктор с параметрами
    Task(int Id, std::string Name, std::string Description, int Priority) {
        id = Id;
        name = Name;
        description = Description;
        priority = Priority;
    }

};

//Тестовая функция
void test() {
    std::cout << "Code is running!\n";
}

//Главное меню
void menu(int& choose) {
    int nowActive = 0;
    int pressed = 0;
    do {
        switch (nowActive) {
            case 0:
                system("cls");
                std::cout << ">>1.Новая задача\n2.Список задач\n3.Редактировать.\n4.Удалить задачу\n5.Выход";
                break;
            case 1:
                system("cls");
                std::cout << "1.Новая задача\n>>2.Список задач\n3.Редактировать.\n4.Удалить задачу\n5.Выход";
                break;
            case 2:
                system("cls");
                std::cout << "1.Новая задача\n2.Список задач\n>>3.Редактировать.\n4.Удалить задачу\n5.Выход";
                break;
            case 3:
                system("cls");
                std::cout << "1.Новая задача\n2.Список задач\n3.Редактировать.\n>>4.Удалить задачу\n5.Выход";
                break;
            case 4:
                system("cls");
                std::cout << "1.Новая задача\n2.Список задач\n3.Редактировать.\n4.Удалить задачу\n>>5.Выход";
                break;
        }
        pressed = _getch();
        if (pressed == 115) {
            if (nowActive != 4) {
                nowActive++;
            }
            else {
                nowActive = 0;
            }
        }
        else if (pressed == 119) {
            if (nowActive != 0) {
                nowActive--;
            }
            else {
                nowActive = 5;
            }
        }
        else if (pressed == 13) {
            choose = nowActive;
            break;
        }


    } while (true);
}

//Создание новой задачи
void addTask(std::vector<Task>& vect, int& count);

//Вывод списка задач
void listTasks(std::vector<Task>& vect);

//Точка входа
int main() {
    int choose = -1, count = 0;
    system("chcp 65001");
    test();
    std::vector<Task> tasks;
    menu(choose);
    while (choose != 4) {
        switch (choose) {
            case 0:
                addTask(tasks, count);
                choose = -1;
                break;
            case 1:
                listTasks(tasks);
                choose = -1;
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                std::cout << "Error!" << std::endl;
                break;
        }
    }


    return 0;
    /*int ch = _getch();
    std::cout << ch << std::endl;*/
}

//Создание новой задачи расписываем функцию
void addTask(std::vector<Task>& vect, int& count) {
    system("cls");
    std::cout << "Давайте создадим новую задачу.\nВведите что нужно сделать:\n";
    std::string task;
    std::getline(std::cin, task);
    std::cout << "Добавьте описание: \n";
    std::string desc;
    std::getline(std::cin, desc);
    std::cout << "Введите приоритет задачи (0 - малый, 1 - средний, 2 - высокий): \n";
    int prio;
    std::cin >> prio;
    std::cin.ignore(1, '\n');
    vect.push_back(Task(count, task, desc, prio));
    count++;
}

//Вывод списка задач
void listTasks(std::vector<Task>& vect) {
    std::cout << "Ваши задачи: " << std::endl;
    for (int i = 0; i < vect.size(); i++) {
        std::cout << vect[i].getId() << "." << vect[i].getName() << std::endl << vect[i].getDescription()
        << std::endl << "Приоретет: " << vect[i].getPriority() << std::endl << std::endl;
    }
}

//Вниз 115
//Вверх 119
//Энтер 13