/*
 *  CoreFoundationMutableSet.h
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

#ifndef CoreFoundationMutableSet_h
#define CoreFoundationMutableSet_h

#include "../Base/CoreFoundationObject.h"
#include "CoreFoundationSet.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A dynamic unordered collection of unique objects.
 *
 * ``CoreFoundationMutableSet`` manages dynamic sets.
 * The basic interface for managing sets is provided by ``CoreFoundationSet``.
 * ``CoreFoundationMutableSet`` adds functions to modify the contents of a set.
 *
 * You create a mutable set object using the ``CoreFoundationMutableSetInitialize`` function.
 *
 * ``CoreFoundationMutableSet`` provides several functions for adding and removing values from a set.
 * The ``CoreFoundationMutableSetInsertObject`` function adds a value to a set and ``CoreFoundationMutableSetRemoveObject`` removes a value from a set.
 *
 * ## Topics
 *
 * ### Creating a mutable set
 *
 * - ``CoreFoundationMutableSetInitialize``
 *
 * ### Adding and removing entries
 *
 * - ``CoreFoundationMutableSetInsertObject``
 */
typedef CoreFoundationSet CoreFoundationMutableSet;

/**
 * Creates an empty ``CoreFoundationMutableSet`` object.
 *
 * - Returns: A new mutable set, or `null` if there was a problem creating the object.
 */
CoreFoundationMutableSet* CoreFoundationMutableSetInitialize();

#define CoreFoundationMutableSetContainsObject CoreFoundationSetContainsObject

/**
 * Adds a value to a ``CoreFoundationMutableSet`` object.
 *
 * - Parameters:
 *   - set: The set to modify.
 *   - object: An object or a pointer value to add to the `set` (or the value itself, if it fits into the size of a pointer).
 *     `object` is retained by the `set`.
 *     If `object` is not of the type expected by the retain operation, the behavior is undefined.
 *     If `object` already exists in the collection, this function returns without doing anything.
 */
void CoreFoundationMutableSetInsertObject(CoreFoundationMutableSet* set, CoreFoundationAnyObject* object);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationMutableSet_h */
