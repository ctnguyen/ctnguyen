/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_boost_factory
#include <boost/test/unit_test.hpp>

#include <boost/function.hpp>
#include <boost/functional/factory.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <map>
#include <thread>

struct base {
    base(const std::string& arg1):m1(arg1) {}
    virtual ~base() = default;
    virtual void print() const = 0;

protected:
    const std::string m1;
};

struct derived1 : public base {
    derived1(const std::string& arg1) : base(arg1) {}
    void print() const override { std::cout << "derived1 m1["<< m1 <<"]" << std::endl; }
    virtual ~derived1(){ std::cout<<"called destructor derived1"<<std::endl;}
};

struct derived2 : public base {
    derived2(const std::string& arg1, int arg2) : base(arg1), m2(arg2) {}
    void print() const override { std::cout << "derived2 m1["<< m1 <<"]  m2["<< m2 <<"]" << std::endl; }
    virtual ~derived2(){ std::cout<<"called destructor derived2"<<std::endl;}
    const int m2;
};


class ClassicFactory
{
public:
    // To change boost::  to std::
    typedef boost::function<base* (const std::string&)> ObjectCreator;
    /// Singleton implementation
    ClassicFactory(ClassicFactory const&) = delete;             
    ClassicFactory(ClassicFactory&&) = delete;                  
    ClassicFactory& operator=(ClassicFactory const&) = delete;  
    ClassicFactory& operator=(ClassicFactory &&) = delete;     

    /// Get the singleton instance
    static ClassicFactory& get()
    {
        static ClassicFactory instance;
        return instance;
    }

    std::unique_ptr<base> create(const std::string& crObjTypeName, const std::string& arg1)
    {
        ObjectCreator func = mapCreator[crObjTypeName];
        return std::unique_ptr<base>(func(arg1));
    }

    void registerCreator(const std::string& key, ObjectCreator func)
    {
        mapCreator.insert(std::make_pair(key, func));
    }
private:
    ClassicFactory(){}
    std::map<std::string, ObjectCreator> mapCreator;
};

template<typename GObject>
struct ClassicFactoryRegistor
{
    ClassicFactoryRegistor(const std::string& crObjTypeName)
    {
        ClassicFactory::ObjectCreator fn = [](const std::string& crArg) -> base * { return new GObject(crArg);};
        ClassicFactory::get().registerCreator(crObjTypeName, boost::bind(fn, _1));
    }
};

//static ClassicFactoryRegistor<derived1> registor("derived1");// To put in derived1.cpp
#define CLASSIC_REGISTER_OBJECT(CLASS) \
static ClassicFactoryRegistor<CLASS> registor(#CLASS);

CLASSIC_REGISTER_OBJECT(derived1)

BOOST_AUTO_TEST_SUITE(test_boost_factory)

BOOST_AUTO_TEST_CASE(test_same_argument_list)
{
    const std::string constructor_argument = "toto";
    std::map<std::string, boost::function<base* (const std::string&)>> factories_same_arg;
    factories_same_arg["derived1"] = boost::factory<derived1*>();
    std::unique_ptr<base> b{factories_same_arg.at("derived1")(constructor_argument)};
    b->print();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_diff_argument_list1) /// need to bind
{
    const std::string constructor_argument1 = "foo";
    const int constructor_argument2 = 9;
    std::map<std::string, boost::function<base* (const std::string& arg1)>> factories_diff_arg;
    factories_diff_arg["derived2"] = boost::bind(boost::factory<derived2*>(), _1, constructor_argument2);
    std::unique_ptr<base> b{factories_diff_arg.at("derived2")(constructor_argument1)};
    b->print();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_diff_argument_list2) /// need to bind
{
    const std::string constructor_argument1 = "toto";
    int constructor_argument2 = 7;
    std::map<std::string, boost::function<base* (const std::string& arg1, int& arg2)>> factories_diff_arg; //TODO : understand why the second argument here has to be reference, otherwise it won't compile
    factories_diff_arg["derived2"] = boost::bind(boost::factory<derived2*>(), _1,_2);
    std::unique_ptr<base> b{factories_diff_arg.at("derived2")(constructor_argument1, constructor_argument2)};
    b->print();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_classic_factory)
{
    const std::string constructor_argument1 = "simple";
    
    std::unique_ptr<base> b = ClassicFactory::get().create("derived1", constructor_argument1);
    b->print();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()