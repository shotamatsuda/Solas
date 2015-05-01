//
//  SLSDefines.h
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
//
//  All information contained herein is, and remains the property of takram
//  design engineering and its suppliers, if any. The intellectual and
//  technical concepts contained herein are proprietary to takram design
//  engineering and its suppliers and may be covered by U.S. and Foreign
//  Patents, patents in process, and are protected by trade secret or copyright
//  law. Dissemination of this information or reproduction of this material is
//  strictly forbidden unless prior written permission is obtained from takram
//  design engineering.
//

#ifdef __cplusplus
#define SLS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define SLS_EXTERN extern __attribute__((visibility ("default")))
#endif

#define SLS_DEFINE_REFERENCE_MAKE_CAST(name, T)                                \
    inline name##Ref name##Make(T *ptr) {                                      \
      return reinterpret_cast<name##Ref>(ptr);                                 \
    }                                                                          \
    inline name##ConstRef name##Make(const T *ptr) {                           \
      return reinterpret_cast<name##ConstRef>(ptr);                            \
    }                                                                          \
    inline T * name##Cast(name##Ref ref) {                                     \
      return reinterpret_cast<T *>(ref);                                       \
    }                                                                          \
    inline const T * name##Cast(name##ConstRef ref) {                          \
      return reinterpret_cast<const T *>(ref);                                 \
    }
