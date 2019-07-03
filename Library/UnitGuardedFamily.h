//---------------------------------------------------------------------------

#ifndef UnitGuardedFamilyH
#define UnitGuardedFamilyH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <cassert>
#include <mutex>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Forward Declaration of CGuardedMember
//---------------------------------------------------------------------------

class CGuardedMemberBase;
//---------------------------------------------------------------------------
// Declaration of CGuard
//---------------------------------------------------------------------------

class CGuard {
friend class CGuardedMemberBase;
public:
private:
  std::mutex guardian_;
};
//---------------------------------------------------------------------------
// Declaration of CGuardedMemberBase
//---------------------------------------------------------------------------

class CGuardedMemberBase {
public:
  inline CGuardedMemberBase();
  inline CGuardedMemberBase(CGuard& Guard);
  inline void initializeBase(CGuard& Guard);
protected:
  std::mutex* pGuardian_;
};
//---------------------------------------------------------------------------
// Declaration of CActionLocker
//---------------------------------------------------------------------------

template<class TType>
class CActionLocker {
public:
  inline CActionLocker(TType* pObject, std::mutex* pGuardian);
  inline ~CActionLocker();
  inline TType* operator->();
private:
  TType* pObject_;
  std::mutex* pGuardian_;
};
//---------------------------------------------------------------------------
// Declaration of CGuardedObjectMember
//---------------------------------------------------------------------------

template<class TType>
class CGuardedObjectMember : protected CGuardedMemberBase {
  using CBase = CGuardedMemberBase;
public:
  inline CGuardedObjectMember();
  inline CGuardedObjectMember(CGuard& Guard, TType& Object);
  inline void initialize(CGuard& Guard, TType& Object);
  inline CActionLocker<TType> operator->();
private:
  TType* pObject_;
};
//---------------------------------------------------------------------------
// Declaration of CGuardedActionMember
//---------------------------------------------------------------------------

template<class TType>
class CGuardedActionMember : protected CGuardedMemberBase {
  using CBase = CGuardedMemberBase;
public:
  inline CGuardedActionMember();
  inline CGuardedActionMember(CGuard& Guard);
  inline void initialize(CGuard& Guard);
  inline CActionLocker<TType> operator->();
private:
  TType object_;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CGuardedMemberBase
//---------------------------------------------------------------------------

CGuardedMemberBase::CGuardedMemberBase()
  : pGuardian_(nullptr) {
}
//---------------------------------------------------------------------------

CGuardedMemberBase::CGuardedMemberBase(CGuard& Guard)
  : pGuardian_(&Guard.guardian_) {
  assert(pGuardian_ != nullptr);
}
//---------------------------------------------------------------------------

void CGuardedMemberBase::initializeBase(CGuard& Guard) {
  pGuardian_ = &Guard.guardian_;
  assert(pGuardian_ != nullptr);
}
//---------------------------------------------------------------------------
// Definition of CActionLocker
//---------------------------------------------------------------------------

template<class TType>
CActionLocker<TType>::CActionLocker(TType* pObject, std::mutex* pGuardian)
  : pObject_(pObject),
    pGuardian_(pGuardian) {
  assert(pObject != nullptr && pGuardian_ != nullptr);
  pGuardian_->lock();
}
//---------------------------------------------------------------------------

template<class TType>
CActionLocker<TType>::~CActionLocker() {
  pGuardian_->unlock();
}
//---------------------------------------------------------------------------

template<class TType>
TType* CActionLocker<TType>::operator->() {
  return pObject_;
}
//---------------------------------------------------------------------------
// Definition of CGuardedObjectMember
//---------------------------------------------------------------------------

template<class TType>
CGuardedObjectMember<TType>::CGuardedObjectMember()
  : CBase(),
    pObject_(nullptr) {
}
//---------------------------------------------------------------------------

template<class TType>
CGuardedObjectMember<TType>::
              CGuardedObjectMember(CGuard& Guard, TType& Object)
  : CBase(Guard),
    pObject_(&Object) {
  assert(pObject_ != nullptr);
}
//---------------------------------------------------------------------------

template<class TType>
void CGuardedObjectMember<TType>::initialize(CGuard& Guard, TType& Object) {
  CBase::initializeBase(Guard);
  assert(pObject_ == nullptr);
  pObject_ = &Object;
  assert(pObject_ != nullptr);
}
//---------------------------------------------------------------------------

template<class TType>
CActionLocker<TType> CGuardedObjectMember<TType>::operator->() {
  assert(pObject_ != nullptr);
  return CActionLocker<TType>(pObject_, CBase::pGuardian_);
}
//---------------------------------------------------------------------------
// Definition of CGuardedActionMember
//---------------------------------------------------------------------------

template<class TType>
CGuardedActionMember<TType>::CGuardedActionMember()
  : CBase(),
    object_(TType()) {
}
//---------------------------------------------------------------------------

template<class TType>
CGuardedActionMember<TType>::CGuardedActionMember(CGuard& Guard)
  : CBase(Guard),
    object_(TType()) {
}
//---------------------------------------------------------------------------

template<class TType>
void CGuardedActionMember<TType>::initialize(CGuard& Guard) {
  CBase::initializeBase(Guard);
}
//---------------------------------------------------------------------------

template<class TType>
CActionLocker<TType> CGuardedActionMember<TType>::operator->() {
  return CActionLocker<TType>(&object_, CBase::pGuardian_);
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
