#include <iostream>

enum class CustomerState {
    New,
    Standard,
    Premium
};

enum CreditCardState {
    New,
    Valid,
    TransferInProgress,
    Invalid,
    Error
};


struct CreditCard {

public:
    CreditCard();
    CreditCard(CreditCardState &State, int &Balance);
    void showBalance() const;
    void set_state(CreditCardState const & state);
    CreditCardState const & get_state() const;
    int get_balance() const;
    void set_balance(int value);
    void update_balance(int value, bool withdraw = true); // withdraw = true -> Auszahlung


private:
    CreditCardState mState = CreditCardState::New;
    int mBalance = 100;
};

CreditCard::CreditCard(): mState{CreditCardState::New}, mBalance{100}
{}
CreditCard::CreditCard(CreditCardState &state, int &balance):mState{state}, mBalance{balance}
{}
void CreditCard::showBalance() const{
    std::cout << "Balance: " << mBalance << std::endl;
}
void  CreditCard::set_state(CreditCardState const & state){
    mState = state;
}
CreditCardState const & CreditCard::get_state() const{
    return mState;
}
int CreditCard::get_balance() const{
    return mBalance;
}
void CreditCard::set_balance(int value){
    mBalance = value;
}
void CreditCard::update_balance(int value, bool withdraw ){
    if(withdraw){  mBalance -= value;}
    else{ mBalance += value;}
}


struct Customer {
public:
    Customer();
    Customer(CustomerState &state, CreditCard &creditcard);
    void set_state(CustomerState const & state);
    void set_CreditCardState( CreditCardState const & state);
    bool verifyStatus() const ;
    void withdrawMoney(const int amnt);
    void showBalance() const;

private:
    CustomerState mState = CustomerState::New;
    CreditCard mCreditcard;
};

Customer::Customer(): mState{CustomerState::New}, mCreditcard{CreditCard()}
{}
Customer::Customer(CustomerState &state, CreditCard &creditcard): mState{state}, mCreditcard{creditcard}
{}
void Customer::set_state(CustomerState const & state){
    mState = state;
}

void Customer::set_CreditCardState(CreditCardState const & state){
    mCreditcard.set_state(state);
}

bool Customer::verifyStatus() const
{
    if(mCreditcard.get_state() != CreditCardState::Valid)
        return false;

    if(mState == CustomerState::Premium)
        return true;

    if(mCreditcard.get_balance() <0)
        return false;

    return true;
}

void Customer::withdrawMoney(const int amnt)
{
    if( !verifyStatus() )
    {
        std::cout << "Die Transaktion kann leider nicht durchgefuehrt werden." << std::endl;
        return;
    }
    mCreditcard.update_balance(amnt);
}
void Customer::showBalance() const{
    mCreditcard.showBalance();
}



int main()
{
    Customer peter{};
    Customer john{};

    peter.set_state(CustomerState::Premium);
    john.set_state(CustomerState::Standard);

    peter.set_CreditCardState(CreditCardState::Valid);
    john.set_CreditCardState(CreditCardState::Valid);

    std::cout << "Peter:";
    peter.showBalance();
    std::cout << "John:" ;
    john.showBalance();

    std::cout << "Each is going to withdraw some Money: First 50, then 100 and finally 200."  << std::endl;
    john.withdrawMoney(50);
    peter.withdrawMoney(50);

    john.withdrawMoney(100);
    peter.withdrawMoney(100);

    john.withdrawMoney(200);
    peter.withdrawMoney(200);

    std::cout << "Balance after withdrawing:" << std::endl;
    std::cout << "Peter:";
    peter.showBalance();
    std::cout << "John:" ;
    john.showBalance();


    return 0;
}
