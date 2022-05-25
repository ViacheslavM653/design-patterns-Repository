#include <iostream>
#include <memory>
/**
 * The Subject interface declares common operations for both RealSubject and the
 * Proxy. As long as the client works with RealSubject using this interface,
 * you'll be able to pass it a proxy instead of a real subject.
 */
class Subject
{
public:
    virtual void Request() const = 0;
    virtual ~Subject() {}
};

class RealSubject : public Subject
{
public:
    void Request() const override {
        std::cout<< "RealSubject: Handing request.\n";

    }
    ~RealSubject(){}
};
/**
 * The Proxy has an interface identical to the RealSubject.
 */
class Proxy : public Subject
{
  /**
   * @var RealSubject
   */
private:
    RealSubject *real_subject_;

    bool CheckAccess() const {
        // Some real checks sould go here.
        std::cout << "Proxy: Checking access prior to firing a real request. \n";
        return true;
    }
    void LogAccess() const {
        std::cout << "Proxy: Logging the time of request.\n";
    }
    /**
   * The Proxy maintains a reference to an object of the RealSubject class. It
   * can be either lazy-loaded or passed to the Proxy by the client.
   */
public:
    Proxy(RealSubject *real_subject) 
        : real_subject_{new RealSubject(*real_subject)}
        {}
    ~Proxy() {
        delete real_subject_;
    }
    /**
   * The most common applications of the Proxy pattern are lazy loading,
   * caching, controlling the access, logging, etc. A Proxy can perform one of
   * these things and then, depending on the result, pass the execution to the
   * same method in a linked RealSubject object.
   */
    void Request() const override {
        if (this->CheckAccess()){
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
    /**
 * The client code is supposed to work with all objects (both subjects and
 * proxies) via the Subject interface in order to support both real subjects and
 * proxies. In real life, however, clients mostly work with their real subjects
 * directly. In this case, to implement the pattern more easily, you can extend
 * your proxy from the real subject's class.
 */
    
};

void ClientCode(const Subject &Subject){
        //..
        Subject.Request();
        //...
}

int main()
{
    std::cout << "Client: Executing the client code with a real subject: \n";
    auto real_subject = std::make_unique<RealSubject>();
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy: \n";
    auto proxy = std::make_unique<Proxy>(real_subject.get());
    ClientCode(*proxy);

}