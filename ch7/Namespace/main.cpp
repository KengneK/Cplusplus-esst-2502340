#include <iostream>

#include <vector>

namespace lil
{
    class vector
    {
    public:
        vector() {}

        ~vector() { delete [] mData; }

        void push_back(const int val)
        {
            int *tempData = new int[mSize+1];

            for(unsigned int i=0 ; i<mSize ; i++)
            {
                tempData[i] = mData[i];
            }

            tempData[mSize] = val;
            delete mData; // deleting nullptr does not make it crash// Ce delete permet de desallouer la memoire resersé au push_back precedent. sans lui, on obtient dans le for suivant les valeur contenue apres le push_back precedent

            // BLOCK VON MIR
            std::cout << "Dans push_back: les valeur presedente dans mData sont:";
            for(int i {0}; i<mSize; i++){ std::cout << mData[i] << " ";} std::cout << std::endl;
            // FIN BLOCK VON MIR

            mData = tempData;
            mSize++;
        }

        int operator[](const unsigned int idx)
        {
            return mData[idx];
        }

    private:
        int *mData = nullptr;
        int mSize = 0;
    };
};


int main()
{

    const int val = 20;

    std::vector<int> stdVec;
    stdVec.push_back(val);

    std::cout << stdVec[0] << std::endl;

    lil::vector lilVec;
    lilVec.push_back(val);

    std::cout << lilVec[0] << std::endl;

    // von mir
    stdVec.push_back(52);
    lilVec.push_back(63);
    stdVec.push_back(-52);
    lilVec.push_back(610);

    for(int i{0}; i<3; i++){
        std::cout<< "stdVec["<< i << "] = " <<stdVec[i] << std::endl;
    }

    std::cout << std::endl;
    for(int i{0}; i<3; i++){
        std::cout<< "lilVec["<< i << "] = " <<lilVec[i] << std::endl;
    }

    //fin von mir

    return 0;
}
