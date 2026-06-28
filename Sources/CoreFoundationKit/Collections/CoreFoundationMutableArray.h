/*
 *  CoreFoundationMutableArray.h
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

#ifndef CoreFoundationMutableArray_h
#define CoreFoundationMutableArray_h

#include "CoreFoundationArray.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

typedef CoreFoundationArray CoreFoundationMutableArray;

#ifdef ONLINE_JUDGE
#  define CoreFoundationMutableArrayInitialize CoreFoundationArrayInitialize
#else
  CoreFoundationMutableArray* CoreFoundationMutableArrayInitialize();
#endif

#define CoreFoundationMutableArrayGetCount CoreFoundationArrayGetCount

#define CoreFoundationMutableArrayGetObjectAtIndex \
  CoreFoundationArrayGetObjectAtIndex

/**
 * Changes the object at a given index in an array.
 *
 * - Parameters:
 *   - array: The array in which the object is to be changed.
 *   - index: The index at which to set the new value. The value must not lie
 *     outside the index space of array (`0` to `N-1` inclusive, where `N` is
 *     the count of the array before the operation).
 *   - object: The object to set in the array. The value is retained by the
 *     array and the previous value at `index` is released. The indices of
 *     other values are not affected.
 */
void CoreFoundationMutableArraySetObjectAtIndex(
  CoreFoundationMutableArray* array,
  CInteger index,
  CoreFoundationAnyObject* object
);

void CoreFoundationMutableArrayAppendObject(
  CoreFoundationArray* array,
  CoreFoundationAnyObject* object
);

/**
 * Inserts an object into an array at a given index.
 *
 * The object parameter is assigned to the index, and all values in the array
 * with equal and larger indices have their indices increased by one.
 *
 * - Parameters:
 *   - array: The array into which value is inserted. If the array is a
 *     fixed-capacity array and it is full before this operation, the behavior
 *     is undefined.
 *   - object: The value to insert into the array. The value is retained by the
 *     array.
 *   - index: The index at which to insert value. The index must be in the range
 *     `0` to `N` inclusive, where `N` is the count of the array before the
 *     operation. If the index is the same as the count of the array, this
 *     function has the same effect as
 *     ``CoreFoundationMutableArrayAppendObject``.
 */
void CoreFoundationMutableArrayInsertObjectAtIndex(
  CoreFoundationArray* array,
  CoreFoundationAnyObject* object,
  CInteger index
);

void CoreFoundationMutableArrayRemoveLastObject(CoreFoundationArray* array);

/**
 * Removes the object at a given index from an array.
 *
 * - Parameters:
 *   - array: The array from which the value is removed.
 *   - index: The index of the value to remove. The index must be in the range
 *     `0` to `N-1` inclusive, where `N` is the count of the array before the
 *     operation.
 */
void CoreFoundationMutableArrayRemoveObjectAtIndex(
  CoreFoundationMutableArray* array,
  CInteger index
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationMutableArray_h */
