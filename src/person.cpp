#include "person.h"

#include <iostream>

Person::Person(const std::string &name)
    : mName{name}
    , mPartner{} {
    std::cout << "Creating a new person with name: " << mName << std::endl;
}

Person::~Person() {
    std::cout << "Person with name: " << mName << " is destroyed" << std::endl;
}

auto Person::getPartner() const -> const std::shared_ptr<Person> {
    return mPartner.lock(); // convert weak_ptr to shared
}

std::string Person::getName() const {
    return mName;
}


