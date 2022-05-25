#include <iostream>
#include <string>
#include <memory>
/**
 * The Command interface declares a method for executing a command.
 */

class Command
{
public:
    virtual ~Command() {}
    virtual void Execute() const = 0;
};
/**
 * Some commands can implement simple operations on their own.
 */

class SimpleComand : public Command 
{
private:
    std::string pay_load_;
public: 
    ~SimpleComand() {
        std::cout << "~~SimpleComand\n";
    }
    explicit SimpleComand(std::string pay_load) 
        : pay_load_ {pay_load}
        {}
    void Execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing ("
                  << this->pay_load_ << ")\n";
    }
};

/**
 * The Receiver classes contain some important business logic. They know how to
 * perform all kinds of operations, associated with carrying out a request. In
 * fact, any class may serve as a Receiver.
 */
class Receiver
{
public:
    ~Receiver(){std::cout << "~Receiver\n";}
    void DoSomething(const std::string &a){
        std::cout << "Receiver: Working on (" << a << ").\n";
    }
    void DoSomethingElese(const std::string &b) {
        std::cout << "Receiver: Also working in (" << b << ").\n";
    }
};

/**
 * However, some commands can delegate more complex operations to other objects,
 * called "receivers."
 */

class ComplexCommand : public Command
{
  /**
   * @var Receiver
   */
private:
    Receiver *reciver_;
/**
   * Context data, required for launching the receiver's methods.
   */
    std::string a_;
    std::string b_;
     /**
   * Complex commands can accept one or several receiver objects along with any
   * context data via the constructor.
   */
public:
    ComplexCommand(Receiver *receiver, std::string a, std::string b)
        : reciver_ {receiver}, a_{a}, b_{b}
        {}
    ~ComplexCommand(){
        std::cout << "~ComplexCommand\n";
        delete reciver_;
    }
    void Execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->reciver_->DoSomething(this->a_);
        this->reciver_->DoSomethingElese(this->b_);
    }

};
/**
 * The Invoker is associated with one or several commands. It sends a request to
 * the command.
 */
class Invoker
{
  /**
   * @var Command
   */
private:
    Command *on_start_;
     /**
   * @var Command
   */
    Command *on_finish_;
     /**
   * Initialize commands.
   */
public:
    ~Invoker(){
        delete on_start_;
        delete on_finish_;
    }
    void SetOnStart(Command *command){
        this->on_start_ = command;
    }
    void SetOnFinish(Command *command){
        this->on_finish_ =command;
    }
    /**
   * The Invoker does not depend on concrete command or receiver classes. The
   * Invoker passes a request to a receiver indirectly, by executing a command.
   */
  void DoSomethingImportant(){
      std::cout << "Invoker: Does anybody want something done before I begin?\n";
      if (this->on_start_){
          this->on_start_->Execute();
      }
      std::cout << "Invoker: ...doing something really important...\n";
      std::cout << "Invoker: Does anybody want something done after I finish?\n";
      if (this->on_finish_){
          this->on_finish_->Execute();
      }
  }
};
/**
 * The client code can parameterize an invoker with any commands.
 */

int main()
{
    auto invoker = std::make_unique<Invoker>();
    auto simpleCommand = std::make_unique<SimpleComand>("Say Hi!");
    invoker->SetOnStart(simpleCommand.get());
    auto receiver = std::make_unique<Receiver>();
    auto complecCommand = std::make_unique<ComplexCommand>(receiver.get(), "Send email", "Save report");
    invoker->SetOnFinish(complecCommand.get());
    invoker->DoSomethingImportant();

    return 0;
}
