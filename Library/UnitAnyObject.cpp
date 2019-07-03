//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitAnyObject.h"
#if !defined(NDEBUG)
//#define __ANY_OBJECT_TESTER__
#if defined(__ANY_OBJECT_TESTER__)
#include <vector>
#include <vcl.h>
#endif
#endif
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

#if !defined(NDEBUG)
#if defined(__ANY_OBJECT_TESTER__)

template<class TBase>
class CAnyInterface : public TBase {
  using CBase = TBase;
public:
  using CBase::CBase;
};

template<class TBase>
class IInterface : public TBase {
public:
  virtual void method(UnicodeString* pString) const = 0;
protected:
  virtual ~IInterface() = default;
};

// must expose the constructors of the base
template<class TBase, class TObject>
class CImplementation : public TBase {
  using CBase = TBase;
public:
  using CBase::CBase;
  void method(UnicodeString* pString) const override {
    *pString += L"\nmethod ";
    *pString += CBase::Object();
    //typename CBase::CObjectType x;
  }
};

// must expose the constructors of the base
template<class TBase>
class CImplementation<TBase, int> : public TBase {
  using CBase = TBase;
public:
  using CBase::CBase;
  void method(UnicodeString* pString) const override {
    *pString += L"\nmethod int ";
    *pString += CBase::Object();
    //typename CBase::CObjectType x;
  }
};
// must expose the constructors of the base
template<class TBase>
class CImplementation<TBase, double> : public TBase {
  using CBase = TBase;
public:
  using CBase::CBase;
  void method(UnicodeString* pString) const override {
    *pString += L"\nmethod double ";
    *pString += CBase::Object();
    //typename CBase::CObjectType x;
  }
};


class CAnyObjectTester {
public:
  CAnyObjectTester() {
    runTest();
  }
  void runTest() {
    UnicodeString Result(L"AnyObject:");
    testAnyObject(&Result);
    ShowMessage(Result.c_str());
  }
  void testAnyObject(UnicodeString* pString) {
    using CAnyObject = CAnyObject<CAnyInterface, IInterface, CImplementation>;
    std::vector<CAnyObject> Objects;
    CAnyObject Object1;
    CAnyObject Object2;
    CAnyObject Object3(std::move(Object1));
    CAnyObject Object4(1);
    CAnyObject Object5(1.2);
    CAnyObject Object6(Object5);
    CAnyObject Object7 = std::move(Object6);
    CAnyObject Object8 = "Test String!";
    Objects.push_back(Object1);
    Objects.push_back(Object2);
    Objects.push_back(Object3);
    Objects.push_back(Object4);
    Objects.push_back(Object5);
    Objects.push_back(Object6);
    Objects.push_back(Object7);
    Objects.push_back(std::move(Object8));
    Objects.emplace_back("Last");

    *pString += L"\nObject8.isDefined() = ";
    *pString += Object8.isDefined();

    size_t index = 0;
    for (const auto& Object : Objects) {
      *pString += L"\nObject[";
      *pString += index;
      *pString += "].isDefined() = ";
      *pString += Object.isDefined();
      ++index;
    }
    for (const auto& Object : Objects) {
      if (Object.isDefined())
        Object->method(pString);
    }
  }
protected:
private:
} AnyObjectTester;
#endif
#endif
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
