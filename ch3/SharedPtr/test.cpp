#include <iostream>
#include <memory>



#define COMBINAISON 4
#if(COMBINAISON == 1) // not ok
#define smart_ptr std::unique_ptr
#define val_ptr std::unique_ptr

#elif(COMBINAISON == 2) // not ok
#define smart_ptr std::unique_ptr
#define val_ptr std::shared_ptr

#elif(COMBINAISON == 3) // ok mit MY_PTR_CHOICE == 1 und MY_PTR_CHOICE ungleich 1
#define smart_ptr std::shared_ptr
#define val_ptr std::shared_ptr

#else // ok mit MY_PTR_CHOICE == 1 und MY_PTR_CHOICE ungleich 1
#define smart_ptr std::shared_ptr
#define val_ptr std::unique_ptr

#endif

struct MyVector {
  int mNum = 0;
  val_ptr<int[]> mValues = nullptr;
};


#define MY_PTR_CHOICE 1
#if(MY_PTR_CHOICE == 1)
template< typename T>
class MySmartPtr : public smart_ptr<T>{
public:
    MySmartPtr():smart_ptr<T>{new T}{}
    ~MySmartPtr() {std::cout << "Destructor!" << std::endl;}
};
#define mypointer MySmartPtr<MyVector>

#else
class MySmartPtr : public smart_ptr<MyVector>{
public:
    MySmartPtr():smart_ptr<MyVector>{new MyVector}{}
    ~MySmartPtr() {std::cout << "Destructor!" << std::endl;}
};
#define mypointer MySmartPtr
#endif


//#define mypointer MySmartPtr

mypointer readValues()
{
    auto pMyVec = MySmartPtr<MyVector>(); // MY_PTR_CHOICE == 1

    //auto pMyVec = MySmartPtr{}; // MY_PTR_CHOICE ungleich 1

    int num = 0;

    std::cout << "Wieviele Elemente brauchen Sie? ";
    std::cin >> num;

    pMyVec->mNum = num;
    pMyVec->mValues.reset(new int [pMyVec->mNum]);

    for(int i=0 ; i<pMyVec->mNum ; i++) {
        std::cout << "Element " << i << " hat folgenden Wert: ";
        std::cin >> pMyVec->mValues[i];
    }

    return pMyVec;
}

void printValues(mypointer pMyVec)
{
    std::cout << "Eingebene Werte sind wie folgt:" << std::endl;

    int sum = 0;
    for(int i=0 ; i<pMyVec->mNum ; i++) {
        std::cout << pMyVec->mValues[i] << std::endl;
        sum += pMyVec->mValues[i];
    }

    std::cout << "Die Summe ist: " << sum << std::endl;
}


int main()
{
    auto pMyVec = readValues();
    printValues(pMyVec);

    return 0;
}
