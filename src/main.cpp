#include <algorithm>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "person.h"
#include "resource.h"

void takeOwnership(std::unique_ptr<Resource> ptr) {
    if (ptr) {
        std::cout << "Unique pointer is valid" << std::endl;
    }
}

bool partnerUp(std::shared_ptr<Person> p1, std::shared_ptr<Person> p2) {
    if (!p1 || !p2) {
        return false;
    }

    p1->mPartner = p2;
    p2->mPartner = p1;

    std::cout << p1->mName << " is now partner of " << p2->mName << std::endl;
    return true;
}

auto makeFunction(int& x) {
    return [&]() { std::cout << "x = " << x << std::endl; };
}

//auto* getX() {} // error: nothing to return as a pointer

decltype(auto) getInt() { return 4; }

template<class T, class U>
auto multiply(T a, U b) -> decltype(a*b) {
    return (a*b);
}

int main(int argc, char** argv) {
    // unique ptr example
    auto uniqueResource{std::make_unique<Resource>()};
    takeOwnership(std::move(uniqueResource)); // no copies allowed, only moving is possible
    if (uniqueResource == nullptr) {
        std::cout << "Unique pointer isn't valid any more" << std::endl;
    }

    // shared_ptr example #1
    auto sharedResource{std::make_shared<Resource>()};
    {
        auto ptr{sharedResource};
        std::cout << "Killing one of the shared pointers" << std::endl;
    }

    {
        std::shared_ptr<Resource> ptr1{new Resource, [](Resource* r) {
                if (r) {
                    std::cout << "This is a custom deleter for resource" << std::endl;
                    delete r;
                    r = nullptr;
                }
            }};
        std::shared_ptr<Resource> ptr2{ptr1};
    }

    // shared_ptr example #2
    const auto lucy{std::make_shared<Person>("Lucy")};
    const auto ricky{std::make_shared<Person>("Ricky")};
    partnerUp(lucy, ricky); // there's a problem if we use shared_ptr
    const auto partner{lucy->getPartner()}; // here we can safely get new shared_ptr

    // lambda example #1
    int x{0};
    const auto function{makeFunction(x)};
    x = 10;
    function();

    // lambda example #2
    bool flag{true};
    std::thread t{[&] {
            while(flag) {
                std::cout << "Thread is running" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            std::cout << "Thread now stops, flag is " << flag << std::endl;
                  }};
    t.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    flag = false;

    // lambda example #3
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i{5};
    const auto sort{[i](int n) { return (n < i); }};
    vec.erase(std::remove_if(vec.begin(), vec.end(), sort), vec.end());
    std::cout << "vector: ";
    std::for_each(vec.begin(), vec.end(), [](int value) { std::cout << " " << value; });
    std::cout << std::endl;

    // decltype example
    decltype (getInt) funcType;
    decltype (getInt()) intType;
    std::cout << "Type id # 1: " << typeid(funcType).name() << std::endl;
    std::cout << "Type id # 1: " << typeid(intType).name() << std::endl;

    unsigned char a{255};
    int b{255}; // you can use uchar here safely too: result type will be deducted automatically
    auto result = multiply(a, b);
    std::cout << "multiplication result: " << result
              << ", type: " << typeid(result).name() <<  std::endl;

    std::cout << "This is the point where all valid smart pointers cease to be" << std::endl;
    return 0;
}
