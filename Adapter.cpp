#include <iostream>
#include <string>
#include <algorithm>
/**
 * The Target defines the domain-specific interface used by the client code.
 */
class Target 
{
public:
    virtual ~Target() = default;
    virtual std::string Request() const {
        return "Target: The default target's behavior.";
    }
};
/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee
{
public:
    std::string SpecificRequest() const {
        return ".eetpadA eth of roivaheb laicepS";
    }
};
/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface using multiple inheritance.
 */
class Adapter : public Target, public Adaptee
{
public:
    Adapter(){}
    std::string Request() const override {
        std::string to_reverse = SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse; 
    }
};
/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(const Target *target) {
    std::cout << target->Request();
}

int main()
{
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    Adaptee *adaptee = new Adaptee;
    std::cout << '\n';
    std::cout << "Client: The Adaptee class has a weird interface."
                 "See, I don't understand it:\n";
    std::cout << "\n\n";
    std::cout << "Client: But I can work it via the Adapter:\n";
    Adapter *adapter = new Adapter;
    ClientCode(adapter);
    std::cout << '\n';

    delete target;
    delete adaptee;
    delete adapter;
    
    return 0;
};