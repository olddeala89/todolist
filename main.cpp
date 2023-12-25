#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <fstream>
#include "nlohmann/single_include/nlohmann/json.hpp"

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
                nowActive = 4;
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

//Редактирование задачи
void editTask(std::vector<Task>& vect);

//Удаление задачи
void dropTask(std::vector<Task>& vect);

//Запись в файл
void fileWrite(std::vector<Task>& vect);

//Чтение из файла
void fileRead(std::vector<Task>& vect, int& count);

//Точка входа
int main() {
    int choose = -1, count = 0;
    system("chcp 65001");
    test();
    std::vector<Task> tasks;
    fileRead(tasks ,count);
    while (true) {
        menu(choose);
        if (choose == 0) {
            addTask(tasks, count);
            choose = -1;
        }
        else if (choose == 1) {
            listTasks(tasks);
            choose = -1;
        } else if (choose == 2) {
            editTask(tasks);
            choose = -1;
        } else if (choose == 3) {
            dropTask(tasks);
            choose = -1;
        } else if (choose == 4) {
            fileWrite(tasks);
            std::cout << "Программа завершила работу.";
            system("pause");
            break;
        }
    }
    return 0;
}

//Создание новой задачи
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
    std::cout << "Задача успешно добавленна!" << std::endl;
    system("pause");
}

//Вывод списка задач
void listTasks(std::vector<Task>& vect) {
    system("cls");
    std::cout << "Ваши задачи: " << std::endl;
    for (int i = 0; i < vect.size(); i++) {
        std::cout << i+1 << "." << vect[i].getName() << std::endl << vect[i].getDescription()
        << std::endl << "Приоретет: " << vect[i].getPriority() << " ID: " <<vect[i].getId() << std::endl << std::endl;
    }
    system("pause");
}

//Редактирование задачи
void editTask(std::vector<Task>& vect) {
    system("cls");
    listTasks(vect);
    int point;
    std::cout << "Какую задачу хотите отрадактировать (ID): ";
    std::cin >> point;
    std::cin.ignore(1, '\n');
    std::cout << "\nВведите новую задачу:\n";
    std::string task;
    std::getline(std::cin, task);
    std::cout << "Введите новое описание: \n";
    std::string desc;
    std::getline(std::cin, desc);
    std::cout << "Введите новый приоритет задачи (0 - малый, 1 - средний, 2 - высокий): ";
    int prio;
    std::cin >> prio;
    std::cin.ignore(1, '\n');
    vect.at(point).setName(task);
    vect.at(point).setDescription(desc);
    vect.at(point).setPriority(prio);
    std::cout << "\nЗадача изменена!\n";
    system("pause");
}

//Удаление задачи
void dropTask(std::vector<Task>& vect) {
    system("cls");
    listTasks(vect);
    int point;
    size_t indexToRemove = 0;
    std::cout << "Какую задачу хотите удалить (ID): ";
    std::cin >> point;
    std::cin.ignore(1, '\n');
    for (int i = 0; i < vect.size(); i++) {
        if (vect[i].getId() == point) {
            indexToRemove = i;
        }
    }
    if (indexToRemove < vect.size()) {
        vect.erase(vect.begin() + indexToRemove);
    }
    std::cout << "Задача удалена!\n";
    system("pause");
}

//Запись в файл
void fileWrite(std::vector<Task>& vect) {
    std::ofstream ass;
    ass.open("C:/Users/Nakon_yw29/CLionProjects/todolist/tasks.txt");
    if (!ass.is_open()) {
        std::cout << "File error" << std::endl;
        system("pause");
    }
    for (int i = 0; i < vect.size(); i++) {
        nlohmann::json obj;
        obj["id"] = vect.at(i).getId();
        obj["name"] = vect.at(i).getName();
        obj["desc"] = vect.at(i).getDescription();
        obj["prio"] = vect.at(i).getPriority();
        std::string jsonStr = obj.dump();
        ass << jsonStr << "\n";
    }
    ass.close();
}

//Чтение из файла
void fileRead(std::vector<Task>& vect, int& count) {
    std::string name, desc, s_id, s_prio;
    int max_id = 0;
    std::ifstream ass("C:/Users/Nakon_yw29/CLionProjects/todolist/tasks.txt");
    if (ass.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "File is empty" << std::endl;
    } else {
            std::string line;
            while (!ass.eof() && std::getline(ass, line, '\n'))
            {
                nlohmann::json obj;
                obj = nlohmann::json::parse(line);
                vect.push_back(Task(obj["id"], obj["name"], obj["desc"], obj["prio"]));
                if (obj["id"] > max_id) {
                    max_id = obj["id"];
                }
            }
    }
    ass.close();
    count = (max_id + 1);
}

//Вниз 115
//Вверх 119
//Энтер 13
//Esc 27