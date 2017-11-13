// #include "TObject.h"
// #include "Python.h"
// #include <stdexcept>
// void call_python_method(PyObject* self, const char* method)
// {
//    // check arguments
//    if ( 0 == self || 0 == method ) { throw std::runtime_error("Invalid Python object and method"); }
//    // call Python
//    PyObject* r = PyObject_CallMethod(self, const_cast<char*>(method), const_cast<char*>(""));
//    if ( 0 == r ) { PyErr_Print(); return;}
//    // release used objects
//    Py_XDECREF( r ) ;
//    //
//    return;
// }

// class Base {
//  public:
//    Base() {}
//    virtual ~Base() {}
//    virtual void Foo() { cout << "base::Foo" << endl; }
//    void CallFoo() { this->Foo(); }
// };

// class PyBase : public Base {
//  public:
//    PyBase(PyObject* self) : fSelf(self) {}
//    virtual ~PyBase() {}
//    virtual void Foo() { call_python_method(fSelf,"Foo"); }
//  private:
//    PyObject* fSelf;
// };