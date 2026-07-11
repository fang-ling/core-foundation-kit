/*
 *  CoreFoundationArray.c
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/5/2.
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

#include "CoreFoundationArray.h"

#include "CoreFoundationArray+Private.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
extern CoreFoundationAnyObject* FoundationCoreFoundationArrayInitialize(
  const void** objects,
  CInteger count,
  CBoolean isMutable
);
#endif

CoreFoundationArray* CoreFoundationArrayInitialize(
  const void** objects,
  CInteger count
) {
#ifdef ONLINE_JUDGE
  let size = sizeof(CoreFoundationArray);
  let array = (CoreFoundationArray*)CMemoryAllocate(size);

  array->object.isa = null;
  array->object.referenceCount = 1;
  array->object.typeID = kCoreFoundationTypeIDArray;

  array->objects = CMemoryAllocate(count * sizeof(const void*));
  array->count = count;
  array->capacity = count;
  array->mutationCount = 0;
  array->isMutable = no;

  let i = 0;
  for (; i < count; i += 1) {
    CoreFoundationRetain(objects[i]);
    array->objects[i] = objects[i];
  }

  return array;
#else
  return FoundationCoreFoundationArrayInitialize(objects, count, no);
#endif
}

void CoreFoundationArrayDeinitialize(CoreFoundationAnyObject* array) {
  let i = 0;
  for (; i < ((CoreFoundationArray*)array)->count; i += 1) {
    CoreFoundationRelease(((CoreFoundationArray*)array)->objects[i]);
  }

  CMemoryDeallocate(((CoreFoundationArray*)array)->objects);
}

CInteger CoreFoundationArrayGetCount(CoreFoundationArray* array) {
  CoreFoundationRetain(array);

  let count = array->count;

  CoreFoundationRelease(array);

  return count;
}

CoreFoundationAnyObject* CoreFoundationArrayGetObjectAtIndex(
  CoreFoundationArray* array,
  CInteger index
) {
  CoreFoundationRetain(array);

  let object = array->objects[index];

  CoreFoundationRelease(array);

  return object;
}

C_INITIALIZER
void CoreFoundationArrayRegisterClass() {
  CoreFoundationClassTable[kCoreFoundationTypeIDArray].deinitialize =
    CoreFoundationArrayDeinitialize;
}

C_ASSUME_NONNULL_END
