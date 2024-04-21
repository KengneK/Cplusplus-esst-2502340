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
    CreditCardState mState = CreditCardState::New;
    int mBalance = 100;
};

struct Customer {
    CustomerState mState = CustomerState::New;
    CreditCard mCreditcard;
};

bool verifyStatus(const Customer &cust)
{
	// TODO: Alle Karten müssen gültig (valid) sein.
    if(cust.mCreditcard.mState != CreditCardState::Valid) return false;
	// TODO: Premium-Kunden dürften sich weiterhin verschulden, Standard-Kunden nicht
    if(cust.mState == CustomerState::Premium) return true;

    if(cust.mCreditcard.mBalance < 0) return false;  // Reihenfolgen von if-Anweisugen ist Wichtig. Ohne diese if-Anweisung muss in withdrawMoney der kommentierte Code betrachtet werden

    return true;
}

void withdrawMoney(Customer &cust, const int amnt)
{
	// TODO: Prüfen ob Kunde überhaupt Geld abheben darf; Fehler melden, falls nicht.
    if( verifyStatus(cust) == false){
        std::cout << "withdraw Money impossible!!" << std::endl;
        return;
    }

    /*if(cust.mState != CustomerState::Premium){
        if(cust.mCreditcard.mBalance < 0){
            std::cout << "withdraw Money impossible because not enought Money!!" << std::endl;
            return;
        }

    }*/
    
	
	// TODO: Dann Geld abheben  
    cust.mCreditcard.mBalance -= amnt;  
}

void showBalance(const CreditCard &card)
{
	// TODO: Anzeigen wieviel Geld noch auf der Kreditkarte ist
    std::cout<< "Actualy balance is: "<< card.mBalance << std::endl;
}

int main()
{
    Customer peter;
    Customer john;

	// TODO: Erkläre Peter zu Premium-Kunde, John zu Standard-Kunde
    peter.mState = CustomerState::Premium;
    peter.mCreditcard.mState = CreditCardState::Valid;

    john.mState = CustomerState::Standard;
    john.mCreditcard.mState = CreditCardState::Valid;

	// TODO: Zeige hier an, wieviel Geld Sie zur Verfügung haben
    std::cout << "Peter: ";
    showBalance(peter.mCreditcard);
    std::cout << "John: ";
    showBalance(john.mCreditcard);

    std::cout << "Each is going to withdraw some Money: First 50, then 100 and finally 200."  << std::endl;
    
    withdrawMoney(john, 50);
    withdrawMoney(peter, 50);

    withdrawMoney(john, 100);
    withdrawMoney(peter, 100);

    withdrawMoney(john, 200);
    withdrawMoney(peter, 200);

	// TODO: Zeige hier an, wieviel Geld beide jetzt zur Verfügung haben
    std::cout << "Peter: ";
    showBalance(peter.mCreditcard);
    std::cout << "John: ";
    showBalance(john.mCreditcard);

    return 0;
}
