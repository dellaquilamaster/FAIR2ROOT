// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME M2RMidasRootEventDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "M2RMidasRootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_M2RMidasRootEvent(void *p = 0);
   static void *newArray_M2RMidasRootEvent(Long_t size, void *p);
   static void delete_M2RMidasRootEvent(void *p);
   static void deleteArray_M2RMidasRootEvent(void *p);
   static void destruct_M2RMidasRootEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::M2RMidasRootEvent*)
   {
      ::M2RMidasRootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::M2RMidasRootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("M2RMidasRootEvent", ::M2RMidasRootEvent::Class_Version(), "M2RMidasRootEvent.h", 8,
                  typeid(::M2RMidasRootEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::M2RMidasRootEvent::Dictionary, isa_proxy, 4,
                  sizeof(::M2RMidasRootEvent) );
      instance.SetNew(&new_M2RMidasRootEvent);
      instance.SetNewArray(&newArray_M2RMidasRootEvent);
      instance.SetDelete(&delete_M2RMidasRootEvent);
      instance.SetDeleteArray(&deleteArray_M2RMidasRootEvent);
      instance.SetDestructor(&destruct_M2RMidasRootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::M2RMidasRootEvent*)
   {
      return GenerateInitInstanceLocal((::M2RMidasRootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::M2RMidasRootEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr M2RMidasRootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *M2RMidasRootEvent::Class_Name()
{
   return "M2RMidasRootEvent";
}

//______________________________________________________________________________
const char *M2RMidasRootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::M2RMidasRootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int M2RMidasRootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::M2RMidasRootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *M2RMidasRootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::M2RMidasRootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *M2RMidasRootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::M2RMidasRootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void M2RMidasRootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class M2RMidasRootEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(M2RMidasRootEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(M2RMidasRootEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_M2RMidasRootEvent(void *p) {
      return  p ? new(p) ::M2RMidasRootEvent : new ::M2RMidasRootEvent;
   }
   static void *newArray_M2RMidasRootEvent(Long_t nElements, void *p) {
      return p ? new(p) ::M2RMidasRootEvent[nElements] : new ::M2RMidasRootEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_M2RMidasRootEvent(void *p) {
      delete ((::M2RMidasRootEvent*)p);
   }
   static void deleteArray_M2RMidasRootEvent(void *p) {
      delete [] ((::M2RMidasRootEvent*)p);
   }
   static void destruct_M2RMidasRootEvent(void *p) {
      typedef ::M2RMidasRootEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::M2RMidasRootEvent

namespace {
  void TriggerDictionaryInitialization_M2RMidasRootEventDict_Impl() {
    static const char* headers[] = {
"M2RMidasRootEvent.h",
0
    };
    static const char* includePaths[] = {
"./",
"/cern/root-6.18.04/include",
"/mnt/md0/users/dellaquila/software/FAIR2ROOT/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "M2RMidasRootEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$M2RMidasRootEvent.h")))  M2RMidasRootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "M2RMidasRootEventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "M2RMidasRootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"M2RMidasRootEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("M2RMidasRootEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_M2RMidasRootEventDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_M2RMidasRootEventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_M2RMidasRootEventDict() {
  TriggerDictionaryInitialization_M2RMidasRootEventDict_Impl();
}
