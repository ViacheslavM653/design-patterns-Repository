#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// Prototype Design Pattern
// Intent: Lets you copy existing objects without making your code dependent on
// their classes.
enum Type 
{
    PROTOTYPE_1 = 0, PROTOTYPE_2
};
/**
 * The example class that has cloning ability. We'll see how the values of field
 * with different types will be cloned.
 */
class Prototype
{
protected:
    std::string prototype_name_;
    float prototype_field_;

public:
    Prototype(){}
    Prototype(std::string prototype_name)
        :prototype_name_(prototype_name)
    {}
    virtual ~Prototype(){}
    virtual std::unique_ptr<Prototype> Clone() const = 0;
    virtual void Method(float prototype_field){
        this->prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_
                  << " with field: " << prototype_field << std::endl;
    }    
};
/**
 * ConcretePrototype1 is a Sub-Class of Prototype and implement the Clone Method
 * In this example all data members of Prototype Class are in the Stack. If you
 * have pointers in your properties for ex: String* name_ ,you will need to
 * implement the Copy-Constructor to make sure you have a deep copy from the
 * clone method
 */

class ConcretePrototype1 : public Prototype
{
private:
    float concrete_prototype_field1_;
public:
    ConcretePrototype1(std::string prototype_name, float concrete_prototype_field)
        :Prototype {prototype_name}, concrete_prototype_field1_ {concrete_prototype_field} 
    {}
     /**
   * Notice that Clone method return a Pointer to a new ConcretePrototype1
   * replica. so, the client (who call the clone method) has the responsability
   * to free that memory. I you have smart pointer knowledge you may prefer to
   * use unique_pointer here.
   */
   std::unique_ptr<Prototype> Clone() const override {
       return std::make_unique<ConcretePrototype1>(*this); 
   }
};

class ConcretePrototype2 : public Prototype
{
private:
    float concrete_prototype_field2_;
public:
    ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
        :Prototype{prototype_name}, concrete_prototype_field2_{concrete_prototype_field}
        {}
    std::unique_ptr<Prototype> Clone() const override {
        return std::make_unique<ConcretePrototype2>(*this); 
    }
};

class PrototypeFactory
{
private:
    std::unordered_map<Type, std::unique_ptr<Prototype> , std::hash<int>> prototypes_;
public: 
    PrototypeFactory(){
        prototypes_[Type::PROTOTYPE_1] = std::make_unique<ConcretePrototype1>("PROTOTYPE_1 ", 50.f);
        prototypes_[Type::PROTOTYPE_2] = std::make_unique<ConcretePrototype2>("PROTOTYPE_2 ", 60.f);
    }

      /**
   * Be carefull of free all memory allocated. Again, if you have smart pointers
   * knowelege will be better to use it here.
   */
    ~PrototypeFactory(){}
  /**
   * Notice here that you just need to specify the type of the prototype you
   * want and the method will create from the object with this type.
   */
  std::unique_ptr<Prototype> CreatePrototype(Type type){
      return prototypes_[type]->Clone();
  }
};

void Client(PrototypeFactory &prototypeFactory){
    std::cout << "Let's create a Prototype 1\n";

    std::unique_ptr<Prototype> prototype = prototypeFactory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90.6486f);

    std::cout << "\n";

    std::cout << "Let's create a Prototype 2\n";

    std::unique_ptr<Prototype> prototype2 = prototypeFactory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10.4478f);
}

int main()
{
    std::unique_ptr<PrototypeFactory> prototype_factory {new PrototypeFactory()}; 
    Client(*prototype_factory);
    return 0;
}
