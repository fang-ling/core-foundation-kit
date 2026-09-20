/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreFoundationObject.c
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/4/25.
 *
 *  This source file is part of the CoreFoundationKit open source project
 *
 *  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
 *  Licensed under Apache License v2.0
 *
 *  See LICENSE for license information
 *
 *  SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#include "CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
extern void* swift_retain(void* object);
extern void swift_release(void* object);
#endif

_CoreFoundationClass _CoreFoundationClassTable[256];

void CoreFoundationObjectRetain(CoreFoundationAnyObject object) {
  CDebuggingPrecondition(object != null, "*** CoreFoundationObjectRetain() CALLED WITH null. ***");

  if (((_CoreFoundationObject*)object)->_metadata == 0) {
    CAtomicityIncrease(&((_CoreFoundationObject*)object)->_referenceCount);
  } else {
#if !C_TARGET_OS_ONLINE_JUDGE
    swift_retain(object);
#endif
  }
}

void CoreFoundationObjectRelease(CoreFoundationAnyObject object) {
  CDebuggingPrecondition(object != null, "*** CoreFoundationObjectRelease() CALLED WITH null. ***");

  if (((_CoreFoundationObject*)object)->_metadata == 0) {
    CAtomicityReleaseMemoryBarrier();

    if (CAtomicityDecrease(&((_CoreFoundationObject*)object)->_referenceCount) <= 0) {
      CAtomicityAcquireMemoryBarrier();

      if (_CoreFoundationClassTable[((_CoreFoundationObject*)object)->_typeID]._deinitialize) {
        _CoreFoundationClassTable[((_CoreFoundationObject*)object)->_typeID]._deinitialize(object);
      }

      CMemoryDeallocate(object);
    }
  } else {
#if !C_TARGET_OS_ONLINE_JUDGE
    swift_release(object);
#endif
  }
}

C_ASSUME_NONNULL_END
