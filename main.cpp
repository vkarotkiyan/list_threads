#include "list.h"
using namespace  std;

int main(int argc, char* argv[]) {
    FineGrainedQueue* list = new FineGrainedQueue(); // инициализация

    list->insertIntoMiddle(1111, 14); // вставка в пустой список

    for (int i = 0; i < 10; i++){ // заполнение списка псевдослучайными числами
        list->push_back(rand() % 100);
    }
    list->show();

    thread t1([&](){ list->remove(69); });
    thread t3([&]() { list->insertIntoMiddle(333, 3); });
    thread t2([&]() { list->remove(78); });
    thread t4([&]() { list->insertIntoMiddle(555, 7); });
    thread t5([&]() { list->insertIntoMiddle(777, 23); }); // вставка в конец, pos > list.size
    thread t6([&]() { list->remove(1111); }); // удаление из начала списка
    thread t7([&]() { list->insertIntoMiddle(999, 0); }); // вставка в начало
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    list->show();

    delete list;
    return 0;
}
