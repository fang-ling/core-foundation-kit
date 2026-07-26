/*
 *  CoreFoundationSet.c
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

#include "CoreFoundationSet.h"

#include "../Base/CoreFoundationObject.h"
#include "CoreFoundationSet+Private.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
extern CoreFoundationAnyObject* FoundationCoreFoundationSetInitialize(const void* nonnil* nillable objects, CInteger count, CBoolean isMutable);
#endif /* !C_TARGET_OS_ONLINE_JUDGE */

CoreFoundationSet* CoreFoundationSetInitialize(const void* nonnil* nillable objects, CInteger count) {
#if C_TARGET_OS_ONLINE_JUDGE
#else
  return FoundationCoreFoundationSetInitialize(objects, count, no);
#endif
}

CBoolean CoreFoundationSetContainsObject(CoreFoundationSet* set, CoreFoundationAnyObject* object) {
  CoreFoundationRetain(set);
  CoreFoundationRetain(object);

  let result = _CoreFoundationRedBlackTreeContainsKey(set->tree, &object);

  CoreFoundationRelease(set);
  CoreFoundationRelease(object);

  return result;
}

C_ASSUME_NONNULL_END
