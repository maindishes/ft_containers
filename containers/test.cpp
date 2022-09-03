#include <iostream>
#include <string>

template <typename T>
class Vector
{
    T* data;
    int capacity;
    int length;

    public:
        // 어떤 타입을 보관 하는지
        typedef T value_type;
        
        // 생성자
        Vector(int n =1): data(new T[n]), capacity(n), length(0)
        {
        }

        void push_back(T  s)
        {
            if (capacity <= length)
            {
                T * temp = new T [capacity*2];
                for (int i =0; i < length; i++)
                {
                    temp[i] = data[i];
                }
                delete[] data;
                data = temp;
                capacity *= 2;
            }
            data[length] = s;
            length++;
        }
        // 임의의 위치 원소에 접근
        T operator[](int i)
        {
            return data[i];
        }

        void remove(int x)
        {
            
            for (int i = x+1; i < length; i++)
            {
                data[i-1] = data[i];
            }
            length--;
        }
        // swap
        void swap(int i, int j)
        {
            T temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }

        void print()
        {
            for (int i = 0; i < length; i++)
            {
                std::cout << "[ " <<data[i] << " ]" ;
            }
            std::cout << std::endl;
        }
        int size()
        {
            return length;
        }

        virtual ~Vector()
        {
            if (data)
            {
                delete[] data;
            }
        }

};

template <typename Cont>
void bubble_sort(Cont& cont)
{
    for (int i =0; i < cont.size(); i++)
    {
        for (int j= i+1; j<cont.size(); j++)
        {
            if (cont[i] > cont[j])
            {
                cont.swap(i,j);
            }
        }
    }
}


int main()
{
    Vector<int> int_vec;
    int_vec.push_back(3);
    int_vec.push_back(333);
    int_vec.push_back(33);
    int_vec.push_back(3333);
    int_vec.push_back(33333);
    int_vec.push_back(311);

    std::cout << "정렬 이전 ---- " << std::endl;
    int_vec.print();

    std::cout << " 정렬 이후 ---- " << std::endl;
    bubble_sort(int_vec);
    int_vec.print();

}