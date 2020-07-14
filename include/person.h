#ifndef _PERSON_H_
#define _PERSON_H_

#include <memory>
#include <string>

class Person final {
public:
    Person(const std::string& name = "Vassily Poupkine");
    ~Person();

    auto getPartner() const -> const std::shared_ptr<Person>;
    std::string getName() const;

    friend bool partnerUp(std::shared_ptr<Person> p1, std::shared_ptr<Person> p2);

private:
    std::string mName;
    //std::shared_ptr<Person> mPartner; // use this to have a cross dependency between shared pointers
    std::weak_ptr<Person> mPartner; // use this for correct work
};

#endif
