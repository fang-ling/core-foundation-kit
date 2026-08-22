/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreFoundationArray.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/5/2.
 *
 *  This source file is part of the CoreFoundationKit open source project
 *
 *  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
 *  Licensed under Apache License v2.0
 *
 *  See LICENSE for license information
 *
 *  SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#ifndef CoreFoundationArray_h
#define CoreFoundationArray_h

#include "../Base/CoreFoundationObject.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * An ordered, random-access collection.
 *
 * ``CoreFoundationArray`` manages ordered collections of objects called arrays. ``CoreFoundationArray`` creates both static and dynamic arrays.
 *
 * You create an array object using the ``CoreFoundationArrayInitialize`` function. This functions return an array containing the objects you pass in as arguments. (Note that arrays can't contain
 * `null` pointers; in most cases, though, you can use the ``kCoreFoundationNull`` constant instead.) Objects are not copied but retained when an array was created. Similarly, when an object is
 * removed from an array, it is released.
 *
 * ``CoreFoundationArray``'s two primitive functions ``CoreFoundationArrayGetCount`` and ``CoreFoundationArrayGetObjectAtIndex`` provide the basis for all other non-mutating functions in its
 * interface. The ``CoreFoundationArrayGetCount`` function returns the number of elements in an array; ``CoreFoundationArrayGetObjectAtIndex`` gives you access to an array's elements by index, with
 * index values starting at `0`.
 *
 * ``CoreFoundationArray`` also provides several functions for changing the contents of an array, for example the ``CoreFoundationArrayAppendObject`` and ``CoreFoundationArrayInsertObjectAtIndex``
 * functions add values to an array; ``CoreFoundationArrayRemoveLastObject`` and ``CoreFoundationArrayRemoveObjectAtIndex`` removes values from an array. You can also reorder the contents of an array
 * using ``CoreFoundationArrayExchangeObjectsAtIndices`` and ``CoreFoundationArraySortObjects``.
 *
 * ## Topics
 *
 * ### Creating an Array
 *
 * - ``CoreFoundationArrayInitialize``
 *
 * ### Inspecting an Array
 *
 * - ``CoreFoundationArrayGetCount``
 *
 * ### Accessing Objects
 *
 * - ``CoreFoundationArrayGetObjectAtIndex``
 *
 * ### Replacing Objects
 *
 * - ``CoreFoundationArraySetObjectAtIndex``
 */
typedef struct _CoreFoundationArray* CoreFoundationArray;

/**
 * Creates a new array with the given objects.
 *
 * - Parameters:
 *   - objects: A C array of the pointer-sized values to be in the new array. The values in the new array are ordered in the same order in which they appear in this C array. This value may be `null`
 *     if `count` is 0. This C array is not changed or freed by this function. If `objects` is not a valid pointer to a C array of at least `count` elements, the behavior is undefined.
 *   - count: The number of objects to copy from the values C array into the new array. This number will be the count of the new array—it must not be negative or greater than the number of elements in
 *     `objects`.
 */
CoreFoundationArray CoreFoundationArrayInitialize(CoreFoundationAnyObject const nonnil* nillable objects, CInteger count);

void _CoreFoundationArrayRetain(CoreFoundationArray array);

void _CoreFoundationArrayRelease(CoreFoundationArray array);

/**
 * Returns the number of objects currently in an array.
 *
 * - Parameter array: The array to examine.
 *
 * - Returns: The number of objects in the array.
 */
CInteger CoreFoundationArrayGetCount(CoreFoundationArray array);

/**
 * Retrieves an object at a given index.
 *
 * - Parameters:
 *   - array: The array to examine.
 *   - index: The index of the object to retrieve. If the index is outside the index space of the array (`0` to `N-1` inclusive (where `N` is the count of the array)), the behavior is undefined.
 *
 * - Returns: The object at the index in the array.
 */
CoreFoundationAnyObject CoreFoundationArrayGetObjectAtIndex(CoreFoundationArray array, CInteger index);

/**
 * Changes the object at a given index in an array.
 *
 * - Parameters:
 *   - array: The array in which the object is to be changed.
 *   - index: The index at which to set the new object. The object must not lie outside the index space of the array (`0` to `N-1` inclusive, where `N` is the count of the array before the operation).
 *   - object: The object to set in the array. The object is retained by the array using the ``CoreFoundationObjectRetain`` function and the previous object at `index` is released. If the value is not
 *     of the type expected by the retain function, the behavior is undefined. The indices of other values are not affected.
 */
void CoreFoundationArraySetObjectAtIndex(CoreFoundationArray array, CoreFoundationAnyObject object, CInteger index);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationArray_h */
