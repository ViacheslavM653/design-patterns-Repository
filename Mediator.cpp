#include <iostream>
#include <string>
#include <memory>
/**
 * The Mediator interface declares a method used by components to notify the
 * mediator about various events. The Mediator may react to these events and
 * pass the execution to other components.
 */
class BaseComponent;
class Mediator
{
public:
    virtual void Notify(BaseComponent *sender, std::string event) const = 0;
    virtual ~Mediator(){}
};

/**
 * The Base Component provides the basic functionality of storing a mediator's
 * instance inside component objects.
 */
class BaseComponent
{
protected:
    Mediator *mediator_;

public:
    BaseComponent(Mediator *mediator = nullptr)
        : mediator_(mediator)
        {}
    void set_mediator(Mediator *mediator) {
        this->mediator_ = mediator;
    }
    virtual ~BaseComponent(){
        std::cout << "~BaseComponent\n";
        delete mediator_;
    }
};
/**
 * Concrete Components implement various functionality. They don't depend on
 * other components. They also don't depend on any concrete mediator classes.
 */
class Component1 : public BaseComponent
{
public:
    Component1(){
        std::cout << "~Component1\n";
    }
    ~Component1(){
        std::cout << "~Component1\n";
        delete mediator_;
    }
    void DoA() {
        std::cout << "Component 1 does A.\n";
        this->mediator_->Notify(this, "A");
    }
    void DoB() {
        std::cout << "Component 1 does B.\n";
        this->mediator_->Notify(this, "B");
    }
};
class Component2 : public BaseComponent
{
public:
    Component2(){
        std::cout << "~Component2\n";
    }
     ~Component2(){
        std::cout << "~Component2\n";
        delete mediator_;
    }
    void DoC() {
        std::cout << "Component 2 does C.\n";
        this->mediator_->Notify(this, "C");
    }
    void DoD() {
        std::cout << "Component 2 does D.\n";
        this->mediator_->Notify(this, "D");
    }
};
/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
class ConcreteMediator : public Mediator
{
private: 
    Component1 *component1_;
    Component2 *component2_;

public:
    ConcreteMediator(Component1 *c1, Component2 *c2)
        : component1_ {c1}, component2_{c2}
        {
            this->component1_->set_mediator(this);
            this->component2_->set_mediator(this);
            std::cout << "ConcreteMediator\n";
        }
    void Notify(BaseComponent *sender, std::string event) const override {
        if (event == "A") {
            std::cout << "Mediator react on A and triggers following operations:\n";
            this->component2_->DoC();
        }
        if (event == "D"){
            std::cout << "Mediator react on D and triggers following operations:\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
    ~ConcreteMediator() {
        std::cout << "~ConcreteMediator()\n";

    }
    
};
/**
 * The client code.
 */

void ClientCode(){
    auto c1 = std::make_unique<Component1>();
    auto c2 = std::make_unique<Component2>();
    auto mediator = std::make_unique<ConcreteMediator>(c1.get(), c2.get());
    std::cout << "Client triggers operation A.\n";
    c1->DoA();
    std::cout << "\n";
    std::cout << "Client triggers operation D.\n";
    c2->DoD();


}

int main()
{
    {
        ClientCode();
    }
    return 0;
}