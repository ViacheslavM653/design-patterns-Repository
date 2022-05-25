#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * The Handler interface declares a method for building the chain of handlers.
 * It also declares a method for executing a request.
 */
class Handler 
{
public:
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual std::string Handle(std::string request) = 0;
    virtual ~Handler() {}
};
/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class AbstractHandler : public Handler
{
/**
   * @var Handler
   */
private:
    Handler *next_handler_;

public:
    AbstractHandler()
        : next_handler_{nullptr}
        {}
    ~AbstractHandler() {std::cout << "~AbstractHandler\n";}
    Handler *SetNext(Handler *handler) override {
        this->next_handler_ = handler;
         // Returning a handler from here will let us link handlers in a convenient
        // way like this:
        // $monkey->setNext($squirrel)->setNext($dog);
        return handler;
    }
    std::string Handle(std::string request) override {
        if (this->next_handler_){
            return this->next_handler_->Handle(request);
        }
        return {};
    }
};

/**
 * All Concrete Handlers either handle a request or pass it to the next handler
 * in the chain.
 */
class MonkeyHandler : public AbstractHandler
{
public:
    ~MonkeyHandler() {std::cout << "~MonkeyHandler\n";}
    std::string Handle(std::string request) override {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

class SquirrelHandler : public AbstractHandler
{
public:
    ~SquirrelHandler() {std::cout << "~SquirrelHandler\n";}
    std::string Handle(std::string request) override {
        if (request == "Nut") {
            return "Squirrel: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

class DogHandler : public AbstractHandler
{
public:
    ~DogHandler() {std::cout << "~DogHandler\n";}
    std::string Handle(std::string request) override {
        if (request == "MeatBall"){
            return "Dog: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

/**
 * The client code is usually suited to work with a single handler. In most
 * cases, it is not even aware that the handler is part of a chain.
 */

void ClientCode(Handler &handler){
    std::vector<std::string> food {"Nut", "Banana", "Cup of coffe"};
    for (const std::string &f : food) {
        std::cout << "Client: Who wants a  " << f << "?\n";
        const std::string result = handler.Handle(f);
        if (!result.empty()){
            std::cout << "     +" << result;
        } else {
            std::cout << "          -" << f << " was left untouched.\n";
        }
    }
}

/**
 * The other part of the client code constructs the actual chain.
 */
int main()
{
    auto monkey = std::make_unique<MonkeyHandler>();
    auto squirrel = std::make_unique<SquirrelHandler>();
    auto dog = std::make_unique<DogHandler>();
    monkey->SetNext(squirrel.get())->SetNext(dog.get());
    
  /**
   * The client should be able to send a request to any handler, not just the
   * first one in the chain.
   */
    std::cout << "Chain: Monkey > Squirrel > Dog \n\n";
    ClientCode(*monkey);
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog \n\n" ;
    ClientCode(*squirrel);
    
    return 0;

}