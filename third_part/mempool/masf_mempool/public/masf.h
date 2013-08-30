// Copyright 2010 Yunrang Inc. All Rights Reserved.
// Author: yanliangcui@yunrang.com (Yanliang Cui)
// 单线程多次分配一次释放的内存(对象)池
// 使用方法:
// 1,注册内存池
// #define REGIST_OBJPOOL(Type, item_per_block, balance_factor, balance_period)
// 四个单数分别为: class类型,每个block中的item数,平衡因子,平衡周期,
// 2,New and Delete
// 3,定期Recycle
//
// sample 见unittest

#ifndef UTIL_YMEMPOOL_MASF_MEMPOOL_MASF_H_
#define UTIL_YMEMPOOL_MASF_MEMPOOL_MASF_H_

#include "third_part/mempool/masf_mempool/public/pool_manager.h"

namespace util {
namespace mempool {

template <class Type>
inline Type *New() {
  return MasfObjPoolHolder<Type>::GetInst().New();
}

template <class Type, class Arg1>
inline Type *New(Arg1 arg1) {
  return MasfObjPoolHolder<Type>::GetInst().New(arg1);
}

template <class Type, class Arg1, class Arg2>
inline Type *New(Arg1 arg1, Arg2 arg2) {
  return MasfObjPoolHolder<Type>::GetInst().New(arg1, arg2);
}

template <class Type, class Arg1, class Arg2, class Arg3>
inline Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3) {
  return MasfObjPoolHolder<Type>::GetInst().New(arg1, arg2, arg3);
}

template <class Type,
          class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) {
  return MasfObjPoolHolder<Type>::GetInst().New(arg1, arg2, arg3, arg4, arg5);
}

template <class Type, class Arg1, class Arg2, class Arg3, class Arg4>
inline Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) {
  return MasfObjPoolHolder<Type>::GetInst().New(arg1, arg2, arg3, arg4);
}

template <class Type>
inline void Delete(Type *obj) {
  MasfObjPoolHolder<Type>::GetInst().Delete(obj);
}

inline void RecycleAll() {
  ObjPoolManager::Recycle();
}

template <class Type>
inline void Recycle() {
  MasfObjPoolHolder<Type>::Recycle();
}

}  // namespace mempool
}  // namespace util

#define DEFINE_OBJPOOL(Type)                                                  \
  namespace util { namespace mempool {                                        \
  template <>                                                                 \
  MasfObjPool<Type> *MasfObjPoolHolder<Type>::pool_ = NULL;                   \
  }  /* namespace masf_mempool */                                             \
  }  /* namespace util */

#define DEFINE_OBJPOOL_CREATOR(                                               \
    Type, item_per_block, balance_factor, balance_period)                     \
  namespace util { namespace mempool {                                        \
  __attribute__((constructor))                                                \
  void Create##Type##ObjPool() {                                              \
    MasfObjPoolHolder<Type>::                                                 \
        CreatePool(item_per_block, balance_factor, balance_period);           \
  }                                                                           \
  }  /* namespace masf_mempool */                                             \
  }  /* namespace util */

#define REGIST_OBJPOOL(Type, item_per_block, balance_factor, balance_period)  \
  DEFINE_OBJPOOL(Type);                                                       \
  DEFINE_OBJPOOL_CREATOR(Type, item_per_block, balance_factor, balance_period);


#endif  // UTIL_YMEMPOOL_MASF_MEMPOOL_MASF_H_