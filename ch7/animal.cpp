#include "animal.h"

Animal::Animal()
{}

std::unique_ptr<Zookeeper> && Animal::releaseZooKeeper()
{
    // TODO: Code for moving the zookeeper instance    
    return std::move(mCurZookeeper);
}

// TODO: Put the catchFoodFrom Methods of Elefant, Giraffe and Lion here
void Elefant::catchFoodFrom(std::unique_ptr<Zookeeper> &&zk) {
    mCurZookeeper = std::move(zk);
    mCurZookeeper->takeFood(10);
}

void Giraffe::catchFoodFrom(std::unique_ptr<Zookeeper> &&zk) {
    mCurZookeeper = std::move(zk);
    mCurZookeeper->takeFood(5);  
}

void Lion::catchFoodFrom(std::unique_ptr<Zookeeper> &&zk) {
    mCurZookeeper = std::move(zk);
    mCurZookeeper->takeFood(6);  
}
