#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <iostream>

class Resource final {
public:
    Resource() { std::cout << "Resource aquired" << std::endl; }
    ~Resource() {std::cout << "Resource destroyed" << std::endl;}
};

#endif
