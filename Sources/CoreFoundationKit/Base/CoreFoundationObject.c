/*
 *  CoreFoundationObject.c
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/4/25.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

#ifndef ONLINE_JUDGE
  extern void* objc_retain(void* object);
  extern void objc_release(void* object);
#endif

CoreFoundationClass CoreFoundationClassTable[256];

void CoreFoundationRetain(CoreFoundationAnyObject* object) {
  if (object == null) {
    CDebuggingHaltWithMessage(
      "*** CoreFoundationRetain() CALLED WITH null. ***"
    );
  }

#ifndef ONLINE_JUDGE
  objc_retain(object);
#else
  CAtomicityIncrease(&((CoreFoundationObject*)object)->referenceCount);
#endif
}

void CoreFoundationRelease(CoreFoundationAnyObject* object) {
  if (object == null) {
    CDebuggingHaltWithMessage(
      "*** CoreFoundationRelease() CALLED WITH null. ***"
    );
  }

#ifndef ONLINE_JUDGE
  objc_release(object);
#else
  CAtomicityReleaseMemoryBarrier();

  if (
    CAtomicityDecrease(&((CoreFoundationObject*)object)->referenceCount) <= 0
  ) {
    CAtomicityAcquireMemoryBarrier();

    let typeID = ((CoreFoundationObject*)object)->typeID;
    let class = CoreFoundationClassTable[typeID];
    if (class.deinitialize) {
      class.deinitialize(object);
    }

    CMemoryDeallocate(object);
  }
#endif
}

C_ASSUME_NONNULL_END
