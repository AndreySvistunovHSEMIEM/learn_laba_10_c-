#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct FIO{
    string name;
    string surname;
    string patronmic;
};

struct Progress{
    float mean_mark;
    int marks[5];
};

class Student{
public:
    string group;
    FIO* full_name;
    Progress* progress;
    Student(){
        full_name = new FIO();
        progress = new Progress();
    }
    Student(FIO* fl_nm, string grp, Progress* prgrss){
        //full_name = new FIO();
        full_name = fl_nm;
        //progress = new Progress();
        progress = prgrss;
        group = grp;
    }
    ~Student(){
    }
    void display_student(){
        cout << "ФИО студнета: " << full_name->name << ' ' <<  full_name->surname << ' ' << full_name->patronmic << endl;
        cout << "Группа: " << group << endl;
        cout << "Успеваемость студента: " << endl;
        cout << "\tОценки студента (оценка - количество оценок): " << endl;
        for (int i = 0; i < 5; i++){
            cout << "\t\t" << i + 1 << " - " << progress->marks[i] << endl;
        }
        cout << "\tСредний балл: " << progress->mean_mark << endl << endl;
    }
};


class Node {
public:
    Student* data;
    Node* next;

    Node(Student* data) {
        this->data = data;
        next = nullptr;
    }
};


class Queue {
private:
    Node* head;
    Node* tail;
    int size;
public:
    Queue() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    ~Queue(){
    }
    void enqueue(Student* data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            head->next = tail;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
            
        }
        size++;
    }

    Student* dequeue() {
        if (head == nullptr) {
            cerr << "Очередь пуста" << endl;
            exit(1);
        }
        Node* temp = head;
        Student* data = temp->data;
        head = head->next;
        tail->next = head;
        delete temp;
        size--;

        return data;
    }

    void displayQueue() {
        Node* temp = head;
        while (temp->next != head) {
            temp->data->display_student();
            temp = temp->next;
        }
        temp->data->display_student();
        cout << endl;
    }
    int getSize() {
        return size;
    }
};

Queue read_file(){
    cout << "Введите имя файла (вместе с расширением)...\n";
    string filename;
    cin >> filename;
    Queue a;
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Ошибка открытия файла" << endl;
        exit(1);
    }
    while (!file.eof()){
        FIO* full = new FIO();
        file >> full->name;
        if (file.eof()){
            cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
            break;
        }
        file >> full->surname;
        if (file.eof()){
            cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
            break;
        }
        file >> full->patronmic;
        if (file.eof()){
            cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
            break;
        }
        string* group = new string();
        file >> *group;
        if (file.eof()){
            cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
            break;
        }
        Progress* progress = new Progress();
        float mn = 0.0f;
        int cnt = 0;
        for (int i = 0; i < 5; i++){
            file >> progress->marks[i];
            mn += progress->marks[i] * (i + 1);
            cnt += progress->marks[i];
            if (i < 4 && file.eof()){
                cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
                break;
            }
            progress->mean_mark = mn / cnt;
        }
        Student* student = new Student(full, *group, progress);
        a.enqueue(student);
    }
    file.close();
    return a;
}

class Stack{
private:
    Node* head;
public:
    Stack(){
        head = nullptr;
    }
    ~Stack(){
    }
    void add_element(Student* data){
        if (head == nullptr){
            Node* newNode = new Node(data);
            head = newNode;
        }
        else{
            Node* newNode = new Node(data);
            newNode->next = head;
            head = newNode;
        }
    }
    Student* pop_element(){
        if (head == nullptr){
            cerr << "Стэк пустой" << endl;
            exit(1);
        }
        Node* prev = head;
        Student* ans = head->data;
        head = head->next;
        delete prev;
        return ans;
    }
    void show(){
        if (head == nullptr){
            cout << "Стэк пуст" << endl;
            return;
        }
        Node* current = head;
        while (current){
            current->data->display_student();
            current = current->next;
        }
    }
    void del_element(Node* element){
        if (head == nullptr){
            cout << "Нечего удалять\nСтэк пуст" << endl << endl;
        }
        else if(element == nullptr){
            cout << "Нечего удалять\nЕлемент указывает на ничего" << endl << endl;
        }
        else if (element == head){
            Node* prev = head;
            head = head->next;
            delete prev;
        }
        else if (element != head){
            Node* current = head;
            while (current){
                if (current->next == element){
                    Node* prev = current->next;
                    current->next = current->next->next;
                    delete prev;
                    return;
                }
                current = current->next;
            }
            cout << "Элемент не содержится в стэке" << endl;
        }
    }
    void filter_students(){
        cout <<  endl << endl << endl << "Происходит фильтрация..." << endl << endl;
        Node* current = head;
        while (current){
            bool flag = false;
            for (int i = 0; i < 3; i++){
                if (current->data->progress->marks[i] > 0){
                    flag = true;
                    break;
                }
            }
            if (!flag)
                current = current->next;
            else{
                Node* prev = current;
                current = current->next;
                this->del_element(prev);
            }
        }
        cout << "Фильтрация проведена" << endl;
    }
    void stack_in_file(){
        cout << "Введите имя файла (вместе с расширением)...\n";
        string filename;
        cin >> filename;
        ofstream out_file(filename);
        if (!out_file){
            cout << "Что-то пошло не так...\n";
            exit(1);
        }
        Node* current = head;
        while (current){
            out_file << current->data->full_name->name << endl;
            out_file << current->data->full_name->surname << endl;
            out_file << current->data->full_name->patronmic << endl;
            out_file << current->data->group << endl;
            for (int i = 0; i < 5; i ++)
                out_file << current->data->progress->marks[i] << endl;
            out_file << current->data->progress->mean_mark << endl;
            current = current->next;
        }
        cout << "Запись завершена" << endl;
        out_file.close();
    }
    void add_element_sorted(Student* data){
        if (head == nullptr){
            Node* newNode = new Node(data);
            head = newNode;
        }
        else if (data->progress->mean_mark <= head->data->progress->mean_mark) {
            Node* newNode = new Node(data);
            newNode->next = head;
            head = newNode;
        }
        else{
            Node* newNode = new Node(data);
            Node* prev = head;
            Node* current = head->next;
            while (current){
                if (current->data->progress->mean_mark >= newNode->data->progress->mean_mark){
                    prev->next = newNode;
                    newNode->next = current;
                    return;
                }
                prev = prev->next;
                current = current->next;
            }
            prev->next = newNode;
        }
    }
};

Stack read_file_stack(){
    cout << "Введите имя файла (вместе с расширением)...\n";
    string filename;
    cin >> filename;
    Stack a;
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Ошибка открытия файла" << endl;
        exit(1);
    }
    while (!file.eof()){
        FIO* full = new FIO();
        file >> full->name;
        if (file.eof()){
            cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
            break;
        }
        file >> full->surname;
        if (file.eof()){
            cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
            break;
        }
        file >> full->patronmic;
        if (file.eof()){
            cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
            break;
        }
        string* group = new string();
        file >> *group;
        if (file.eof()){
            cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
            break;
        }
        Progress* progress = new Progress();
        float mn = 0.0f;
        int cnt = 0;
        for (int i = 0; i < 5; i++){
            file >> progress->marks[i];
            mn += progress->marks[i] * (i + 1);
            cnt += progress->marks[i];
            if (i < 4 && file.eof()){
                cout << "Неудалось заполнить данные о студенте, так как количество строк неполное" << endl;
                break;
            }
            progress->mean_mark = mn / cnt;
        }
        Student* student = new Student(full, *group, progress);
        a.add_element(student);
    }
    file.close();
    return a;
}

int main() {
    /*
    cout << "Лабораторная работа №10\nВыполнил ученик группы БИВ234\nСвистунов Андрей\n";
    cout << "Задание 1" << endl;
    cout << endl;
    Queue bam;
    bam = read_file();
    bam.displayQueue();
    cout << "\n\nЗадание 2\n";
    Stack bambam;
    while (bam.getSize() > 0){
        bambam.add_element(bam.dequeue());
    }
    bambam.filter_students();
    //bambam.show();
    bambam.stack_in_file();
     
    */
    Stack bambambam;
    bambambam = read_file_stack();
    bambambam.show();
    Student* newNode = new Student();
    newNode->full_name->name = "BAMA";
    newNode->full_name->name = newNode->full_name->name;
    newNode->full_name->surname = "BAMA";
    newNode->full_name->patronmic = "BAMA";
    newNode->group = "BIVVV";
    float mn = 0.0f;
    int cnt = 0;
    for (int i = 0; i < 5; i ++){
        int cur; cin >> cur;
        newNode->progress->marks[i] = cur;
        mn += cur * (i + 1);
        cnt += cur;
    }
    newNode->progress->mean_mark = mn / cnt;
    bambambam.add_element_sorted(newNode);
    bambambam.show();
    
    
}

/*
 Student(FIO* fl_nm, string grp, Progress* prgrss){
     //full_name = new FIO();
     full_name = fl_nm;
     //progress = new Progress();
     progress = prgrss;
     group = grp;
 }
 */

