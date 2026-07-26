/*
 *  CoreFoundationMutableArray.c
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/5/2.
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

#include "CoreFoundationMutableArray.h"

#include "CoreFoundationArray+Private.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
extern CoreFoundationAnyObject* FoundationCoreFoundationArrayInitialize(const void** objects, CInteger count, CBoolean isMutable);
#endif

CoreFoundationMutableArray* CoreFoundationMutableArrayInitialize() {
#if C_TARGET_OS_ONLINE_JUDGE
  let array = CoreFoundationArrayInitialize(null, 0);

  array->isMutable = yes;

  return array;
#else
  return FoundationCoreFoundationArrayInitialize(null, 0, yes);
#endif
}

void CoreFoundationMutableArraySetObjectAtIndex(CoreFoundationMutableArray* array, CInteger index, CoreFoundationAnyObject* object) {
  CoreFoundationRetain(array);

  if (!array->isMutable) {
    CDebuggingHaltWithMessage("*** IMMUTABLE COLLECTION IS BEING MUTATED. ***");
  }
  array->mutationCount += 1;

  CoreFoundationRetain(object);

  CoreFoundationRelease(array->objects[index]);
  array->objects[index] = object;

  CoreFoundationRelease(array);
}

void CoreFoundationMutableArrayAppendObject(CoreFoundationMutableArray* array, CoreFoundationAnyObject* object) {
  CoreFoundationRetain(array);

  if (!array->isMutable) {
    CDebuggingHaltWithMessage("*** IMMUTABLE COLLECTION IS BEING MUTATED. ***");
  }
  array->mutationCount += 1;

  CoreFoundationRetain(object);

  if (array->capacity == 0) {
    array->objects = CMemoryResize(array->objects, sizeof(CoreFoundationAnyObject*) * 1);
    array->capacity = 1;
  }

  if (array->count == array->capacity) {
    array->capacity *= 2;
    array->objects = CMemoryResize(array->objects, sizeof(CoreFoundationAnyObject*) * array->capacity);
  }

  array->objects[array->count] = object;
  array->count += 1;

  CoreFoundationRelease(array);
}

void CoreFoundationMutableArrayInsertObjectAtIndex(CoreFoundationArray* array, CoreFoundationAnyObject* object, CInteger index) {
  CoreFoundationRetain(array);

  CoreFoundationMutableArrayAppendObject(array, object);

  CMemoryCopy(array->objects + index + 1, array->objects + index, sizeof(CoreFoundationAnyObject*) * (array->count - index - 1));
  array->objects[index] = object;

  CoreFoundationRelease(array);
}

void CoreFoundationMutableArrayRemoveLastObject(CoreFoundationMutableArray* array) {
  CoreFoundationRetain(array);

  if (!array->isMutable) {
    CDebuggingHaltWithMessage("*** IMMUTABLE COLLECTION IS BEING MUTATED. ***");
  }
  array->mutationCount += 1;

  /* Release the last element. */
  CoreFoundationRelease(array->objects[array->count - 1]);
  array->count -= 1;

  if (array->count > 0 && array->count <= array->capacity / 4) {
    array->capacity /= 2;
    array->objects = CMemoryResize(array->objects, sizeof(CoreFoundationAnyObject*) * array->capacity);
  }

  CoreFoundationRelease(array);
}

void CoreFoundationMutableArrayRemoveObjectAtIndex(CoreFoundationMutableArray* array, CInteger index) {
  CoreFoundationRetain(array);

  let object = array->objects[index];
  CMemoryCopy(array->objects + index, array->objects + index + 1, sizeof(CoreFoundationAnyObject*) * (array->count - index - 1));
  array->objects[array->count - 1] = object;

  CoreFoundationMutableArrayRemoveLastObject(array);

  CoreFoundationRelease(array);
}

C_ASSUME_NONNULL_END
