#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
/**
 * The Strategy interface declares operations common to all supported versions
 * of some algorithm.
 *
 * The Context uses this interface to call the algorithm defined by Concrete
 * Strategies.
 */
class Strategy
{
public:
    virtual ~Strategy() {std::cout << "~Strategy\n";}
    virtual std::string DoAlforithm(const std::vector<std::string> &data) const = 0;
};
/**
 * The Context defines the interface of interest to clients.
 */
class Context
{
 /**
     * @var Strategy The Context maintains a reference to one of the Strategy
     * objects. The Context does not know the concrete class of a strategy. It
     * should work with all strategies via the Strategy interface.
     */
private:
    Strategy *strategy_;
        /**
     * Usually, the Context accepts a strategy through the constructor, but also
     * provides a setter to change it at runtime.
     */
public:
    Context(Strategy *strategy = nullptr)
    : strategy_ {strategy}
    {}
    ~Context(){
        delete this->strategy_;
        std::cout << "~Context\n";
    }
        /**
     * Usually, the Context allows replacing a Strategy object at runtime.
     */
    void set_strategy(Strategy *strategy) {
        delete this->strategy_;
        this->strategy_ = strategy;
    }
       /**
     * The Context delegates some work to the Strategy object instead of
     * implementing +multiple versions of the algorithm on its own.
     */
    void DoSomeBusinessLogic() const {
        std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
        std::string result = this->strategy_->DoAlforithm(std::vector<std::string>{"a", "e", "c", "b", "d"});
        std::cout << result << "\n";
    }
};
/**
 * Concrete Strategies implement the algorithm while following the base Strategy
 * interface. The interface makes them interchangeable in the Context.
 */
class ConcreteStrategyA : public Strategy
{
public:
    ~ConcreteStrategyA(){std::cout << "~Strategy A\n";}
    std::string DoAlforithm(const std::vector<std::string> &data) const override {
        std::string result;
        std::for_each(std::begin(data), std::end(data), 
                     [&result](const std::string &letter) { result += letter;}  );
        std::sort(std::begin(result), std::end(result));
        return result;
    }
};
/**
 * The client code picks a concrete strategy and passes it to the context. The
 * client should be aware of the differences between strategies in order to make
 * the right choice.
 */
class ConcreteStrategyB : public Strategy
{
public:
    ~ConcreteStrategyB(){std::cout << "~Strategy B\n";}
    std::string DoAlforithm(const std::vector<std::string> &data) const override {
        std::string result;
        std::for_each(std::begin(data), std::end(data), 
                     [&result](const std::string &letter) { result += letter;}  );
        std::sort(std::begin(result), std::end(result));
        for (int i = 0; i < result.size() / 2; i++) {
            std::swap(result[i], result[result.size() - i - 1]);
        }
        return result;
    }
};

void ClientCode() {
    auto strategyA = std::make_unique<ConcreteStrategyA>();
    auto context = std::make_unique<Context>(strategyA.get());
    context->DoSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    auto strategyB = std::make_unique<ConcreteStrategyB>();
    context->set_strategy(strategyB.get());
    context->DoSomeBusinessLogic();
}

int main()
{
    ClientCode();
    return 0;

}