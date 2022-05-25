#include <iostream>
#include <string>

/**
 * The Subsystem can accept requests either from the facade or client directly.
 * In any case, to the Subsystem, the Facade is yet another client, and it's not
 * a part of the Subsystem.
 */
class Subsystem1
{
public:
    ~Subsystem1(){std::cout << "~Subsystem1\n";}
    std::string Operation1() const {
        return "Subsystem1: Ready!\n";
    }
    //..
    std::string OperationN() const {
        return "Subsystem1: Go!\n";
    }
};
/**
 * Some facades can work with multiple subsystems at the same time.
 */
class Subsystem2
{
public:
    ~Subsystem2() {std::cout << "~Subsystem2\n";}
    std::string Operation1() const {
        return "Subsystem2: Get ready!\n";
    }
    //..
    std::string OperationZ() const {
        return "Subsystem2: Fire!\n";
    }

};

/**
 * The Facade class provides a simple interface to the complex logic of one or
 * several subsystems. The Facade delegates the client requests to the
 * appropriate objects within the subsystem. The Facade is also responsible for
 * managing their lifecycle. All of this shields the client from the undesired
 * complexity of the subsystem.
 */
class Facade
{
protected:
    Subsystem1 *subsystem1_;
    Subsystem2 *subsustem2_;
     /**
   * Depending on your application's needs, you can provide the Facade with
   * existing subsystem objects or force the Facade to create them on its own.
   */
public:
    /**
   * In this case we will delegate the memory ownership to Facade Class
   */
    
    Facade() {
        this->subsystem1_ = new Subsystem1;
        this->subsustem2_ = new Subsystem2;

    }
    ~Facade(){
        delete subsystem1_;
        delete subsustem2_;
    }
     /**
   * The Facade's methods are convenient shortcuts to the sophisticated
   * functionality of the subsystems. However, clients get only to a fraction of
   * a subsystem's capabilities.
   */
    std::string Operation(){
        std::string result {"Facade initializes subsystems:\n"};
        result += this->subsystem1_->Operation1();
        result += this->subsustem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsustem2_->OperationZ();
        return result;
    }
};
    /**
 * The client code works with complex subsystems through a simple interface
 * provided by the Facade. When a facade manages the lifecycle of the subsystem,
 * the client might not even know about the existence of the subsystem. This
 * approach lets you keep the complexity under control.
 */
void ClientCode(Facade *facade){
    std::cout << facade->Operation();
}

int main()
{
    //Subsystem1 *subsystem1 = new Subsystem1;
    //Subsystem2 *subsystem2 = new Subsystem2;
    Facade *facade = new Facade();
    ClientCode(facade);

    delete facade;

    return 0;
}