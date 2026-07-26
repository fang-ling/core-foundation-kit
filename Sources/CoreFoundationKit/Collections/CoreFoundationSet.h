/*
 *  CoreFoundationSet.h
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

#ifndef CoreFoundationSet_h
#define CoreFoundationSet_h

#include "../Base/CoreFoundationObject.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A static, unordered collection of unique objects.
 *
 * ``CoreFoundationSet`` and its derived mutable type, ``CoreFoundationMutableSet``, provide support for the mathematical concept of a set.
 * A set, both in its mathematical sense and in the implementation of ``CoreFoundationSet``, is an unordered collection of distinct elements.
 * ``CoreFoundationSet`` creates static sets and ``CoreFoundationMutableSet`` creates dynamic sets.
 *
 * Use bags or sets as an alternative to arrays when the performance in testing whether an object is contained in the collection is a consideration—
 * while arrays are ordered, testing for membership is slower than with bags or sets.
 * Use bags over sets if you want to allow duplicate objects in your collections.
 *
 * You create a static set object using the ``CoreFoundationSetInitialize`` function.
 * (Note that sets can't contain `null` pointers; in most cases, though, you can use the ``kCoreFoundationNaught`` constant instead.)
 * Objects are not copied but retained. Similarly, when an object is removed from a set, it is released.
 *
 * ``CoreFoundationSet`` provides functions for querying the objects of a set.
 * The ``CoreFoundationSetGetCount`` returns the number of objects in a set, the ``CoreFoundationSetContainsObject`` function checks if an object is in a set,
 * and ``CoreFoundationSetGetObjects`` returns a C array containing all the objects in a set.
 *
 * ## Topics
 *
 * ### Creating Sets
 *
 * - ``CoreFoundationSetInitialize``
 *
 * ### Examining a Set
 *
 * - ``CoreFoundationSetContainsObject``
 */
typedef struct CoreFoundationSet CoreFoundationSet;

/**
 * Creates an immutable ``CoreFoundationSet`` object containing supplied objects.
 *
 * - Parameters:
 *   - objects: A C array of the pointer-sized objects to be in the new set.
 *     This parameter may be `null` if the `count` parameter is `0`.
 *     The C array is not changed or freed by this function. `objects` must be a pointer to a C array of at least `count` elements.
 *   - count: The number of objects to copy from the values C array in the new set.
 *
 * - Returns: A new immutable set, or `null` if there was a problem creating the object.
 */
CoreFoundationSet* CoreFoundationSetInitialize(const void* nonnil* nillable objects, CInteger count);

/**
 * Returns a Boolean that indicates whether a set contains a given object.
 *
 * - Parameters:
 *   - set: The set to search.
 *   - object: The value to match in the set.
 *
 * - Returns: `yes` if value is contained in the `set`, otherwise `no`.
 */
CBoolean CoreFoundationSetContainsObject(CoreFoundationSet* set, CoreFoundationAnyObject* object);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationSet_h */
