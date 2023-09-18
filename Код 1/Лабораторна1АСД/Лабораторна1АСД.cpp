#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;

struct MathAnalysis // Структура Пара з матаналізу
{
    char profName[15];
    int classNum, attend;
};

struct DynamicArray // Структура динамічного масиву
{
    DynamicArray(int sizeNum = 6) // Конструктор
    {
        size = sizeNum;
        array = new MathAnalysis[size];
        currSize = 0;
    }

    ~DynamicArray() // Деструктор
    {
        delete[] array;
    }

    MathAnalysis* array;
    int currSize, size;

    void relocMem() // Перевиділення пам'яті
    {
        size *= 2;
        MathAnalysis *newArray = new MathAnalysis[size]; // Виділення більшої кількості пам'яті

        memmove(newArray, array, currSize * sizeof(MathAnalysis)); // Перенесення елементів

        delete[] array; // Видалення старого масиву
        array = newArray; // Зміна масиву, з яким пов'язаний вказівник
    }

    void push_back(MathAnalysis obj) // Додавання елементу в кінець
    {
        if (currSize == size) // Якщо масив заповнений
            relocMem();
        array[currSize] = obj;
        currSize++;
    }

    MathAnalysis pop_back() // Зчитування та видалення елементу з кінця
    {
        if (currSize == 0) // Якщо масив пустий
        { 
            cout << "The array is already empty.\n";
            return { "null", -1, -1 };
        }
        else
        {
            MathAnalysis obj = array[currSize - 1];
            currSize--;
            return obj;
        }
    }

    MathAnalysis get(int id) // Зчитування елементу за індексом
    {
        if (id >= 0 && id < currSize)
            return array[id];
        else if (currSize == 0) // Якщо масив пустий
            cout << "The array is empty.\n";
        else // Якщо вказано неправильний індекс
            cout << "Element with such id wasn't found.\n";
        return { "null", -1, -1 };
    }

    int arrSize() // Кількість елементів
    {
        return currSize;
    }

    void print() // Виведення всіх даних
    {
        if(currSize == 0) // Якщо масив пустий
            cout << "There weren't any classes yet.\n";
        for (int i = 0; i < currSize; i++)
            cout << "| " << array[i].classNum << " class | professor's name: " << array[i].profName << " | students' attendance: " << array[i].attend << " |\n";
    }

    void clear() // Видалення елементів та очищення пам'яті
    {
        delete[] array;
        size = 6;
        currSize = 0;
        array = new MathAnalysis[size];
    }

    void push_front(MathAnalysis obj) // Додавання елементу на початок
    {
        if (currSize == size) // Якщо недостатньо пам'яті
            relocMem();

        memmove(array + 1, array, currSize * sizeof(MathAnalysis)); // Перенесення елементів праворуч

        currSize++;
        array[0] = obj;
    }

    MathAnalysis pop_front() // Зчитування та видалення елементу на початку
    {
        if (currSize == 0) // Якщо масив пустий
        {
            cout << "The array is already empty.\n";
            return { "null", -1, -1 };
        }
        else
        {
            MathAnalysis obj = array[0];
            currSize--;

            memmove(array, array + 1, currSize * sizeof(MathAnalysis)); // Перенесення елементів ліворуч

            return obj;
        }
    }

    void insert(MathAnalysis obj, int id) // Додавання елементу у певне місце
    {
        if (id >= 0 && id <= currSize) // Якщо вказано правильний індекс
        {
            if (currSize == size) // Якщо недостатньо пам'яті
                relocMem();

            memmove(array + (id + 1), array + id, (currSize - id) * sizeof(MathAnalysis)); // Перенесення елементів праворуч від вказаного місця

            array[id] = obj;
            currSize++;
        }
        else // Якщо введено неправильний індекс
            cout << "You can't insert the element in the array's cell with such id.\n";
    }

    void remove(int id) // Видалення певного елементу
    {
        if (id >= 0 && id < currSize) // Якщо вказано правильний індекс
        {
            memmove(array + (id + 1), array + id, (currSize - id) * sizeof(MathAnalysis)); // Перенесення елементів ліворуч

            currSize--;
        }
        else if(currSize == 0) // Якщо масив пустий
            cout << "The array is already empty.\n";
        else // Якщо вказано неправильний індекс
            cout << "Element with such id wasn't found.\n";
    }
};

struct Node // Структура вузла
{
    MathAnalysis value;
    Node* next = nullptr;
};

struct LinkedList // Структура однозв'язного списку
{
    Node* head;
    Node* tail;
    int count;

    LinkedList() // Конструктор
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~LinkedList() // Деструктор
    {
        while (head) // Видалення пам'яті списку
        {
            Node* obj = head;
            head = head->next;
            delete obj;
        }
    }

    void push_front(MathAnalysis obj) // Додавання елементу на початок
    {
        Node* node = new Node; // Створення нового вузлу
        node->value = obj;
        node->next = head; // Присвоєння вказівнику адреси першого елемента списку
        head = node; // Зміна вказівника передньої частини

        if (tail == nullptr) // Якщо до операції список був пустий
            tail = head;

        count++;
    }

    void push_back(MathAnalysis obj) // Додавання елементу в кінець
    {
        Node* node = new Node; // Створення нового вузлу
        node->value = obj;
        node->next = nullptr; // Присвоєння вказівнику пустої адреси

        if(tail != nullptr) // Якщо список був не пустий
            tail->next = node; // Присвоєння вказівнику адреси передостаннього елемента списку

        tail = node; // Присвоєння вказівнику адреси останнього елемента списку

        if (head == nullptr) // Якщо список був пустий
            head = tail;

        count++;
    }

    MathAnalysis get(int objNum) // Зчитування елементу за індексом
    {
        if (objNum < 1 || objNum > count) // Якщо вказано неправильний індекс
        {
            cout << "Element with such id wasn't found.\n";
            return { "null", -1, -1 };
        }
        Node* obj = head; // Присвоєння вказівнику адреси першого елемента списку

        for (int i = 1; i < objNum; i++) // Пошук потрібного елемента за індексом
            obj = obj->next;
        return obj->value;
    }

    MathAnalysis pop_front() // Зчитування та видалення елементу на початку
    {
        if (head == nullptr) // Якщо список пустий
        {
            cout << "The list is already empty.\n";
            return { "null", -1, -1 };
        }

        Node* nodeObj = head; // Присвоєння вказівнику адреси першого елемента списку
        MathAnalysis obj = nodeObj->value; // Визначення результату

        head = head->next; // Зміна першого елементу
        count--;

        delete nodeObj; // Видалення вузлу

        if (head == nullptr) // Якщо тепер список пустий
            tail == nullptr;
        
        return obj;
    }

    MathAnalysis pop_back() // Зчитування та видалення елементу в кінці
    {
        if (tail == nullptr) // Якщо список пустий
        {
            cout << "The list is already empty.\n";
            return { "null", -1, -1 };
        }

        MathAnalysis obj = tail->value; // Визначення результату
        count--;

        if (head == tail) // Якщо список складається з одного елементу
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            return obj;
        }

        Node* nodeObj = head; // Присвоєння вказівнику адреси першого елемента списку

        while (nodeObj->next != tail) // Пошук передостаннього елементу
            nodeObj = nodeObj->next;

        delete tail; // Видалення останнього елементу
        tail = nodeObj;
        tail->next = nullptr;
        return obj;
    }

    int size() // Кількість елементів
    {
        return count;
    }

    void print() // Виведення всіх даних
    {
        Node* obj = head;
        bool anyClass = false;

        cout << "Full list:\n";

        while (obj)
        {
            cout << "| " << obj->value.classNum << " class | professor's name: " << obj->value.profName << " | students' attendance: " << obj->value.attend << " |\n";
            anyClass = true;
            obj = obj->next;
        }

        if (!anyClass) // Якщо список пустий
            cout << "There weren't any classes yet.\n";
    }

    void clear() // Видалення елементів та очищення пам'яті
    {
        while (head) // Поки в списку є пам'ять
        {
            Node* obj = head;
            head = head->next;
            delete obj;
        }

        count = 0;
        tail = nullptr;
    }

    void insert(MathAnalysis obj, int id) // Додавання елементу у певне місце
    {
        if (id >= 1 && id <= (count + 1)) // Якщо вказано правильний індекс
        {
            Node* newNode = new Node; // Створення нового вузла
            newNode->value = obj;
            count++;

            if (id == 1) // Якщо елемент додається у найперше місце
            {
                newNode->next = head;
                head = newNode;
                if (!tail) // Якщо до цього список був пустий
                    tail = head;
                return;
            }

            if (id == count) // Якщо елемент додається на останнє місце
            {
                tail->next = newNode;
                tail = newNode;
                return;
            }

            Node* before = head; // Створення вузлу, що має знаходитися перед необхідним місцем
            for(int i = 1; i < (id - 1); i++) // Пошук потрібного місця
                before = before->next;

            newNode->next = before->next; // Вставка елементу у список
            before->next = newNode;
        }
        else // Якщо вказано неправильний індекс
            cout << "You can't insert the element in the linked list's node with such id.\n";
    }

    void remove(int id) // Видалення певного елементу
    {
        if (id >= 1 && id <= count) // Якщо вказано правильний індекс
        {
            Node* before = head; // Створення вузлу, що має знаходитися перед необхідним місцем
            count--;

            if (id == 1) // Якщо видаляється перший елемент
            {
                head = head->next;
                delete before;
                return;
            }

            for (int i = 1; i < (id - 1); i++) // Пошук потрібного елементу
                before = before->next;

            Node* nodeObj = before->next; // Визначення елементу, що буде видалений
            before->next = nodeObj->next;
            if (nodeObj == tail) // Якщо елемент був останнім
                tail = before;
            delete nodeObj;
        }
        else if (head == nullptr) // Якщо список пустий
            cout << "The list is already empty.\n";
        else // Якщо введено непраивльний індекс
            cout << "Element with such id wasn't found.\n";
    }
};

int main()
{
    DynamicArray array;

    srand(time(NULL));

    cout << "Testing dynamic array structure:\n"; // Тестування всіх кроків для динамічного масиву
    clock_t startTime = clock();
    for (int i = 0; i < 50000; i++)
        array.push_back({ "12345", 67, 89 });
    for (int i = 0; i < 10000; i++)
        array.push_front({ "98765", 43, 21 });
    for (int i = 0; i < 20000; i++)
        array.get(rand() % 60000);
    for (int i = 0; i < 5000; i++)
        array.pop_front();
    for (int i = 0; i < 5000; i++)
        array.pop_back();
    clock_t endTime = clock();
    double seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    array.clear();

    LinkedList list;

    cout << "Testing linked list structure:\n"; // Тестування всіх кроків для однозв'язного списку
    startTime = clock();
    for (int i = 0; i < 50000; i++)
        list.push_back({ "12345", 67, 89 });
    for (int i = 0; i < 10000; i++)
        list.push_front({ "98765", 43, 21 });
    for (int i = 0; i < 20000; i++)
        list.get(rand() % 60000);
    for (int i = 0; i < 5000; i++)
        list.pop_front();
    for (int i = 0; i < 5000; i++)
        list.pop_back();
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    list.clear();

    cout << "\nNow testing each method separately.\n"; // Тестування кожного кроку окремо
    cout << "\nDynamic array:\n";

    cout << "Push back: ";
    startTime = clock();
    for (int i = 0; i < 50000; i++)
        array.push_back({ "12345", 67, 89 });
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    cout << "Push front: ";
    startTime = clock();
    for (int i = 0; i < 10000; i++)
        array.push_front({ "98765", 43, 21 });
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    cout << "Get: ";
    startTime = clock();
    for (int i = 0; i < 20000; i++)
        array.get(rand() % 50000);
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    cout << "Pop front: ";
    startTime = clock();
    for (int i = 0; i < 5000; i++)
        array.pop_front();
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    cout << "Pop back: ";
    startTime = clock();
    for (int i = 0; i < 5000; i++)
        array.pop_back();
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    array.clear();


    cout << "\nLinked list:\n";

    cout << "Push back: ";
    startTime = clock();
    for (int i = 0; i < 50000; i++)
        list.push_back({ "12345", 67, 89 });
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    cout << "Push front: ";
    startTime = clock();
    for (int i = 0; i < 10000; i++)
        list.push_front({ "98765", 43, 21 });
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    cout << "Get: ";
    startTime = clock();
    for (int i = 0; i < 20000; i++)
        list.get(rand() % 50000);
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    cout << "Pop front: ";
    startTime = clock();
    for (int i = 0; i < 5000; i++)
        list.pop_front();
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    cout << "Pop back: ";
    startTime = clock();
    for (int i = 0; i < 5000; i++)
        list.pop_back();
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    cout << seconds << endl;

    list.clear();

}
