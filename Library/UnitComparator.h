//---------------------------------------------------------------------------

#ifndef UnitComparatorH
#define UnitComparatorH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CLexSum
//---------------------------------------------------------------------------

template< class CFirstComparator,
          class CSecondComparator>
class CLexSum {
  public:
  using ArgumentType = typename CFirstComparator::ArgumentType;

  bool operator()(const ArgumentType& first,
                  const ArgumentType& second) const;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CLexSum
//---------------------------------------------------------------------------

template< class CFirstComparator,
          class CSecondComparator>
bool CLexSum<CFirstComparator, CSecondComparator>::
                  operator()( const ArgumentType& first,
                              const ArgumentType& second) const {
  CFirstComparator FirstComparator;
  if (FirstComparator(first, second))
    return true;
  if (FirstComparator(second, first))
    return false;
  CSecondComparator SecondComparator;
  return SecondComparator(first, second);
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
