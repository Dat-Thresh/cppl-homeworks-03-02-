#include <iostream>
#include <exception>


class smart_array {
private:
    int* arr;
    int logic_size;
    int phys_size;
    smart_array() {};

public:
    //конструктор копирования
    smart_array(const smart_array& other) {
        //создаем новый массив и копируем тогда из объекта other
        int* new_arr = new int[other.phys_size];
        for (int i = 0; i < other.phys_size; i++) {
            new_arr[i] = other.arr[i];
        }
        arr = new_arr;
        logic_size = other.logic_size;
        phys_size = other.phys_size;
    }
    //перегружаем присваивание
   
    smart_array& operator=(const smart_array& other) {
        //если указатели не равны, создаем новый массив под числа, и копируем туда данные из присваемого объекта
        if (this != &other) {
            int* new_arr = new int[other.phys_size];
            for (int i = 0; i < other.phys_size; i++) {
                new_arr[i] = other.arr[i];
            }
            //чистим память на старый массив на указателе, в который потом запишем новый массив
            delete arr;
            //в первый объект в поле массива пишем указатель на свежесозданный массив
            //в остальные поля просто копируем из присваемого объекта
            arr = new_arr;
            logic_size = other.logic_size;
            phys_size = other.phys_size;

        }
        return *this;            
        
    }
    //конструктоp
    smart_array(int size) {
        arr = new int[size];//создает динам массив
        logic_size = 0;//при создании не будет элементов в массиве(поэтому 0)
        phys_size = size;//фактический размер массива
    }

    //добавляет элемент в массив
    void add_element(int number) {
        logic_size++;
        if (logic_size > phys_size) {
            throw std::out_of_range("Превышено допустимое количество элементов массива!");
        }
        arr[logic_size - 1] = number;
    }

    //возвращает элемент по индексу
    int get_element(int num) {
        if (num > logic_size || num < 0) {
            throw std::out_of_range("Указанный индекс вне зоны массива!");
        }
        return arr[num];
    }

    //деструктор
    ~smart_array() {
        delete[] arr;
    }
};

int main() {
    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);

    arr = new_array;
    std::cout << arr.get_element(0) << std::endl;

    smart_array p_arr(3);
    smart_array arr2(p_arr);
    return 0;
}