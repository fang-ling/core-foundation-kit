/*
 *  CoreFoundationMutableArray.c
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

#include "CoreFoundationMutableArray.h"

#include "CoreFoundationArray+Private.h"

C_ASSUME_NONNULL_BEGIN

void CoreFoundationMutableArrayAppendObject(
  CoreFoundationMutableArray* array,
  CoreFoundationAnyObject* object
) {
  CoreFoundationRetain(array);
  CoreFoundationRetain(object);

  if (array->capacity == 0) {
    array->objects = CMemoryResize(
      array->objects,
      sizeof(CoreFoundationAnyObject*) * 1
    );
    array->capacity = 1;
  }

  if (array->count == array->capacity) {
    array->capacity *= 2;
    array->objects = CMemoryResize(
      array->objects,
      sizeof(CoreFoundationAnyObject*) * array->capacity
    );
  }

  array->objects[array->count] = object;
  array->count += 1;

  CoreFoundationRelease(array);
}

void CoreFoundationMutableArrayRemoveLastObject(
  CoreFoundationMutableArray* array
) {
  CoreFoundationRetain(array);

  /* Release the last element. */
  CoreFoundationRelease(array->objects[array->count - 1]);
  array->count -= 1;

  if (array->count > 0 && array->count <= array->capacity / 4) {
    array->capacity /= 2;
    array->objects = CMemoryResize(
      array->objects,
      sizeof(CoreFoundationAnyObject*) * array->capacity
    );
  }

  CoreFoundationRelease(array);
}

C_ASSUME_NONNULL_END
