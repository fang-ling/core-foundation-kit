/*
 *  CoreFoundationMutableSet.c
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/7/25.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and limitations under the License.
 */

#include "CoreFoundationMutableSet.h"

#include "CoreFoundationSet+Private.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
extern CoreFoundationAnyObject* FoundationCoreFoundationSetInitialize(const void* nonnil* nillable objects, CInteger count, CBoolean isMutable);
#endif /* !C_TARGET_OS_ONLINE_JUDGE */

CoreFoundationMutableSet* CoreFoundationMutableSetInitialize() {
#if C_TARGET_OS_ONLINE_JUDGE
#else
  return FoundationCoreFoundationSetInitialize(null, 0, yes);
#endif
}

void CoreFoundationMutableSetInsertObject(CoreFoundationMutableSet* set, CoreFoundationAnyObject* object) {
  CoreFoundationRetain(set);
  if (!set->isMutable) {
    CDebuggingHaltWithMessage("*** IMMUTABLE COLLECTION IS BEING MUTATED. ***");
  }

  CoreFoundationRetain(object);

  set->mutationCount += 1;

  if (_CoreFoundationRedBlackTreeContainsKey(set->tree, &object)) {
    CoreFoundationRelease(object);

    return;
  }

  _CoreFoundationRedBlackTreeInsertKey(set->tree, &object);

  CoreFoundationRelease(set);
}

C_ASSUME_NONNULL_END
