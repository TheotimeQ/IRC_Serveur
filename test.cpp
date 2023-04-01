#include <functional>
#include <iostream>

void sayHello() {
    std::cout << "Hello!" << std::endl;
}

int main() {
    std::function<void()> f = &sayHello;
    f();
    return 0;
}
