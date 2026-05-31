/*
 *  CoreFoundationArray.h
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

#ifndef CoreFoundationArray_h
#define CoreFoundationArray_h

#include "../Base/CoreFoundationObject.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

typedef struct CoreFoundationArray CoreFoundationArray;

CoreFoundationArray* CoreFoundationArrayInitialize();

/**
 * Returns the number of values currently in an array.
 *
 * - Parameter array: The array to examine.
 *
 * - Returns: The number of values in the array.
 */
CInteger CoreFoundationArrayGetCount(CoreFoundationArray* array);

/**
 * Retrieves an object at a given index.
 *
 * - Parameters:
 *   - array: The array to examine.
 *   - index: The index of the object to retrieve. If the index is outside the
 *     index space of the array (`0` to `N-1` inclusive (where `N` is the count
 *     of the array), the behavior is undefined.
 *
 * - Returns: The value at the index in the array.
 */
CoreFoundationAnyObject* CoreFoundationArrayGetObjectAtIndex(
  CoreFoundationArray* array,
  CInteger index
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationArray_h */
