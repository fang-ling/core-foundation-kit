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
 * ``CoreFoundationArray``'s two primitive functions ``CoreFoundationArrayGetCount`` and ``CoreFoundationArrayGetObjectAtIndex`` provide the basis for all other functions in its interface. The
 * ``CoreFoundationArrayGetCount`` function returns the number of elements in an array; ``CoreFoundationArrayGetObjectAtIndex`` gives you access to an array's elements by index, with index values
 * starting at `0`.
 *
 * ``CoreFoundationArray`` provides several functions for changing the contents of an array, for example the ``CoreFoundationArrayAppendObject`` and ``CoreFoundationArrayInsertObjectAtIndex``
 * functions add objects to an array and ``CoreFoundationArrayRemoveObjectAtIndex`` removes objects from an array. You can also reorder the contents of an array using
 * ``CoreFoundationArrayExchangeObjectsAtIndices`` and ``CoreFoundationArraySortObjects``.
 *
 * ``CoreFoundationArray`` is "toll-free bridged" with its FoundationKit counterparts, ``FoundationArray`` and ``FoundationMutableArray``. This means that the CoreFoundationKit type is interchangeable
 * in function or method calls with the bridged FoundationKit object. Therefore, in a method where you see a ``FoundationArray`` or ``FoundationMutableArray`` parameter, you can pass in a
 * ``CoreFoundationArray``, and in a function where you see a ``CoreFoundationArray`` parameter, you can pass in a ``FoundationArray`` or ``FoundationMutableArray`` instance.
 *
 * ## Topics
 *
 * ### Creating an Array
 *
 * - ``CoreFoundationArrayInitialize``
 *
 * ### Examining an Array
 *
 * - ``CoreFoundationArrayGetCount``
 * - ``CoreFoundationArrayGetObjectAtIndex``
 */
typedef struct C_SWIFT_SHARED_REFERENCE(_CoreFoundationArrayRetain, _CoreFoundationArrayRelease) _CoreFoundationArray* CoreFoundationArray;

/**
 * Creates a new array with the given objects.
 *
 * - Parameters:
 *   - objects: A C array of the pointer-sized values to be in the new array. The values in the new array are ordered in the same order in which they appear in this C array. This value may be `null`
 *     if `count` is 0. This C array is not changed or freed by this function. If `objects` is not a valid pointer to a C array of at least `count` elements, the behavior is undefined.
 *   - count: The number of objects to copy from the values C array into the new array. This number will be the count of the new array—it must not be negative or greater than the number of elements in
 *     `objects`.
 */
CoreFoundationArray CoreFoundationArrayInitialize(CoreFoundationAnyObject const nonnil * nillable objects, CInteger count)
C_SWIFT_RETURNS_RETAINED
C_SWIFT_NAME(_CoreFoundationArray.init(objects:count:));

void _CoreFoundationArrayRetain(CoreFoundationArray array);

void _CoreFoundationArrayRelease(CoreFoundationArray array);

/**
 * Returns the number of objects currently in an array.
 *
 * - Parameter array: The array to examine.
 *
 * - Returns: The number of objects in the array.
 */
CInteger CoreFoundationArrayGetCount(CoreFoundationArray array)
C_SWIFT_NAME(getter:_CoreFoundationArray.count(self:));

/**
 * Retrieves an object at a given index.
 *
 * - Parameters:
 *   - array: The array to examine.
 *   - index: The index of the object to retrieve. If the index is outside the index space of the array (`0` to `N-1` inclusive (where `N` is the count of the array)), the behavior is undefined.
 *
 * - Returns: The object at the index in the array.
 */
CoreFoundationAnyObject CoreFoundationArrayGetObjectAtIndex(CoreFoundationArray array, CInteger index)
C_SWIFT_NAME(_CoreFoundationArray.object(self:at:));

C_ASSUME_NONNULL_END

#endif /* CoreFoundationArray_h */
