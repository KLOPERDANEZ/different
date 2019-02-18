#include <iostream>
#include <string>

class S
{
public:
    void log(const std::string& message)
    {
        std::cout << "log: " << message << std::endl;
    }
};

template <typename S>
void call_log(S* s, const std::string& message)
{
    if constexpr (!std::is_same<S, std::nullptr_t>::value)
    {
        s->log(message);
    }
}

template <typename S = std::nullptr_t>
void A(S* s = nullptr)
{
    call_log(s, "message");
    std::cout << "A" << std::endl;
}

int main()
{
    A(new S());
    A();
}
