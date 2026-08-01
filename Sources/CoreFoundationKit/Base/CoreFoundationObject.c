/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
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
 *===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#include "CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
extern void* swift_retain(void* object);
extern void swift_release(void* object);
#endif

_CoreFoundationClass _CoreFoundationClassTable[256];

void CoreFoundationObjectRetain(CoreFoundationAnyObject* object) {
  if (object == null) {
    CDebuggingHaltWithMessage("*** CoreFoundationObjectRetain() CALLED WITH null. ***");
  }

#if !C_TARGET_OS_ONLINE_JUDGE
  swift_retain(object);
#else
  CAtomicityIncrease(&((_CoreFoundationObject*)object)->referenceCount);
#endif
}

void CoreFoundationObjectRelease(CoreFoundationAnyObject* object) {
  if (object == null) {
    CDebuggingHaltWithMessage("*** CoreFoundationObjectRelease() CALLED WITH null. ***");
  }

#if !C_TARGET_OS_ONLINE_JUDGE
  objc_release(object);
#else
  CAtomicityReleaseMemoryBarrier();

  if (CAtomicityDecrease(&((_CoreFoundationObject*)object)->referenceCount) <= 0) {
    CAtomicityAcquireMemoryBarrier();

    if (_CoreFoundationClassTable[((_CoreFoundationObject*)object)->typeID].deinitialize) {
      _CoreFoundationClassTable[((_CoreFoundationObject*)object)->typeID].deinitialize(object);
    }

    CMemoryDeallocate(object);
  }
#endif
}

C_ASSUME_NONNULL_END
