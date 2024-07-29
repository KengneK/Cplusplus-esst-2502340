#include <iostream>
#include <memory>



#define COMBINAISON 1
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
    MySmartPtr():smart_ptr<T>{new T}{std::cout << "Constructor!" << std::endl;}
    ~MySmartPtr() {std::cout << "Destructor!" << std::endl;}

    #if(COMBINAISON == 1 || COMBINAISON == 2) 
        MySmartPtr<T>(const MySmartPtr<T>& ori) { std::cout << "copie constructor " <<std::endl; }
        MySmartPtr& operator=( const MySmartPtr& ori) { 
            std::cout << "operator= " << std::endl; 
            return *this; 
        }
        //MySmartPtr<T>& operator=(const MySmartPtr<T>& ori) { std::cout << "operator= " << std::endl; return *this;} 
    #endif

};
#define mypointer MySmartPtr<MyVector>

#else
class MySmartPtr : public smart_ptr<MyVector>{
public:
    MySmartPtr():smart_ptr<MyVector>{new MyVector}{}
    ~MySmartPtr() {std::cout << "Destructor!" << std::endl;}

    #if(COMBINAISON == 1 || COMBINAISON == 2) 
        MySmartPtr(const MySmartPtr& ori) { std::cout << "copie constructor " << std::endl;    }
        MySmartPtr& operator=(const MySmartPtr& ori) { 
            std::cout << "operator= " << std::endl; 
            return *this; 
        }
    #endif

};
#define mypointer MySmartPtr
#endif


//#define mypointer MySmartPtr

mypointer readValues()
{

#if(MY_PTR_CHOICE == 1)

    //auto pMyVec {MySmartPtr<MyVector>()}; //  Für COMBINAISON == 1 oder 2 funktionniert diese Zeile in Visual Studio ohne die deklaration des Kopieconstructors nicht, Kopiekonstructor ist hier leer. Muss erberssert werden
    //auto pMyVec = MySmartPtr<MyVector>(); //  

    MySmartPtr<MyVector> pMyVec;
    pMyVec = MySmartPtr<MyVector>(); // Für COMBINAISON == 1 oder 2 funktionniert in Visual Studio und VSCode funktionniert ohne operator= nicht. Operator= muss verbessert werden 

    //MySmartPtr<MyVector> pMyVec;
    //pMyVec =  std::move(MySmartPtr<MyVector>()); // Für COMBINAISON == 1 oder 2 funktionniert in Visual Studio und VSCode funktionniert ohne operator= nicht. Operator= muss verbessert werden 



#else

    //auto pMyVec = MySmartPtr{}; 
    //auto pMyVec{ MySmartPtr{} }; //  Für COMBINAISON == 1 oder 2 funktionniert diese Zeile in Visual Studio ohne die deklaration des Kopieconstructors nicht, Kopiekonstructor ist hier leer. Muss erberssert werden

    //MySmartPtr pMyVec = MySmartPtr{};  
    //MySmartPtr pMyVec{ MySmartPtr{} };  //  Für COMBINAISON == 1 oder 2 funktionniert diese Zeile in Visual Studio ohne die deklaration des Kopieconstructors nicht, Kopiekonstructor ist hier leer. Muss erberssert werden

    //MySmartPtr pMyVec;     
    //pMyVec = MySmartPtr{}; // Für COMBINAISON == 1 oder 2 funktionniert in Visual Studio und VSCode funktionniert ohne operator= nicht. Operator= muss verbessert werden 

    //MySmartPtr pMyVec;     
    //pMyVec = std::move(MySmartPtr{}); // Für COMBINAISON == 1 oder 2 funktionniert in Visual Studio und VSCode funktionniert ohne operator= nicht. Operator= muss verbessert werden



#endif

    int num = 0;

    std::cout << "Wieviele Elemente brauchen Sie? ";
    std::cin >> num;

    pMyVec->mNum = num;
    pMyVec->mValues.reset(new int [pMyVec->mNum]);

    for(int i=0 ; i<pMyVec->mNum ; i++) {
        std::cout << "Element " << i << " hat folgenden Wert: ";
        std::cin >> pMyVec->mValues[i];
    }

    return pMyVec; // Für COMBINAISON == 1 oder 2 funktionniert in Visual Studio und VSCode funktionniert ohne die deklaration des Kopieconstructors nicht, Kopiekonstructor ist hier leer. Muss erberssert werden
}

#if(COMBINAISON == 1 || COMBINAISON == 2) 
void printValues(mypointer &pMyVec){
#else
void printValues(mypointer pMyVec){
#endif
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
    std::cout << "Enter Main!" << std::endl;
    auto pMyVec = readValues();
    std::cout << "in Main!" << std::endl;
    printValues(pMyVec);
    std::cout << "Exit main!" << std::endl;


    return 0;
}
