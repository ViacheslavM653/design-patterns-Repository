#include <iostream>
#include <string>
#include <array>
#include <memory>

/**
 * The Visitor Interface declares a set of visiting methods that correspond to
 * component classes. The signature of a visiting method allows the visitor to
 * identify the exact class of the component that it's dealing with.
 */
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
public:
    virtual ~Visitor() {}
    virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};
/**
 * The Component interface declares an `accept` method that should take the base
 * visitor interface as an argument.
 */
class Component 
{
public:
    virtual ~Component() {}
    virtual void Accept(Visitor *visitor) const = 0;
};
/**
 * Each Concrete Component must implement the `Accept` method in such a way that
 * it calls the visitor's method corresponding to the component's class.
 */
class ConcreteComponentA : public Component 
{
 /**
   * Note that we're calling `visitConcreteComponentA`, which matches the
   * current class name. This way we let the visitor know the class of the
   * component it works with.
   */
public:
    ~ConcreteComponentA() {}
    void Accept(Visitor *visitor) const override {
        visitor->VisitConcreteComponentA(this);
    }
      /**
   * Concrete Components may have special methods that don't exist in their base
   * class or interface. The Visitor is still able to use these methods since
   * it's aware of the component's concrete class.
   */   
    std::string ExclusiveMethodOfConcreteComponentA() const {
        return "A";
    }
};

class ConcreteComponentB : public Component 
{
 /**
   * Note that we're calling `visitConcreteComponentA`, which matches the
   * current class name. This way we let the visitor know the class of the
   * component it works with.
   */
public:
    ~ConcreteComponentB() {}
    void Accept(Visitor *visitor) const override {
        visitor->VisitConcreteComponentB(this);
    }
      /**
   * Concrete Components may have special methods that don't exist in their base
   * class or interface. The Visitor is still able to use these methods since
   * it's aware of the component's concrete class.
   */   
    std::string ExclusiveMethodOfConcreteComponentB() const {
        return "B";
    }
};
/**
 * Concrete Visitors implement several versions of the same algorithm, which can
 * work with all concrete component classes.
 *
 * You can experience the biggest benefit of the Visitor pattern when using it
 * with a complex object structure, such as a Composite tree. In this case, it
 * might be helpful to store some intermediate state of the algorithm while
 * executing visitor's methods over various objects of the structure.
 */
class ConcreteVisitor1 : public Visitor 
{
public:
    ~ConcreteVisitor1() {}
    void VisitConcreteComponentA(const ConcreteComponentA *element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA()
                  << " + ConcreteVisitor 1\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB *element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentB()
                  << " + ConcreteVisitor 1\n";
    }
};

class ConcreteVisitor2 : public Visitor 
{
public:
    ~ConcreteVisitor2() {}
    void VisitConcreteComponentA(const ConcreteComponentA *element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA()
                  << " + ConcreteVisitor 2\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB *element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentB()
                  << " + ConcreteVisitor 2\n";
    }
};
/**
 * The client code can run visitor operations over any set of elements without
 * figuring out their concrete classes. The accept operation directs a call to
 * the appropriate operation in the visitor object.
 */
void ClientCode(std::array<const Component*, 2>components, Visitor *visitor) {
    for (const Component *comp : components) {
        comp->Accept(visitor);
    }
}

int main()
{
    auto compA = std::make_unique<ConcreteComponentA>();
    auto compB = std::make_unique<ConcreteComponentB>();
    std::array<const Component *, 2> components {compA.get(), compB.get()};
    std::cout << "The client code works with all viditors via the base Visitor interface:\n";
    auto visitor1 = std::make_unique<ConcreteVisitor1>();
    ClientCode(components, visitor1.get());
    std::cout << "\n";
    std::cout << "It allows the same client code to eork wtith different types of visitors:\n";
    auto visitor2 = std::make_unique<ConcreteVisitor2>();
    ClientCode(components, visitor2.get());
    return 0;

}