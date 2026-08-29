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
#include "../Values and Collections/Basic Values/Ranges/CoreFoundationRange.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * An ordered, random-access collection.
 *
 * ``CoreFoundationArray`` manages ordered collections of objects called arrays. ``CoreFoundationArray`` creates both static and dynamic arrays.
 *
 * You create an array object using either the ``CoreFoundationArrayInitialize`` or ``CoreFoundationArrayCopy`` function. This functions return an array containing the objects you pass in as
 * arguments. (Note that arrays can't contain `null` pointers; in most cases, though, you can use the ``kCoreFoundationNull`` constant instead.) Objects are not copied but retained when an array was
 * created. Similarly, when an object is removed from an array, it is released.
 *
 * ``CoreFoundationArray``'s two primitive functions ``CoreFoundationArrayGetCount`` and ``CoreFoundationArrayGetObjectAtIndex`` provide the basis for all other non-mutating functions in its
 * interface. The ``CoreFoundationArrayGetCount`` function returns the number of elements in an array; ``CoreFoundationArrayGetObjectAtIndex`` gives you access to an array's elements by index, with
 * index values starting at `0`.
 *
 * ``CoreFoundationArray`` also provides several functions for changing the contents of an array, for example the ``CoreFoundationArrayAppendObject`` and ``CoreFoundationArrayInsertObjectAtIndex``
 * functions add objects to an array; ``CoreFoundationArrayRemoveLastObject`` and ``CoreFoundationArrayRemoveObjectAtIndex`` removes objects from an array. You can also reorder the contents of an
 * array using ``CoreFoundationArrayExchangeObjectsAtIndices`` and ``CoreFoundationArraySortObjects``.
 *
 * ## Topics
 *
 * ### Creating an Array
 *
 * - ``CoreFoundationArrayInitialize``
 * - ``CoreFoundationArrayCopy``
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
 * - ``CoreFoundationArrayReplaceSubrangeWithObjects``
 */
typedef struct _CoreFoundationArray* CoreFoundationArray;

/**
 * Creates a new array with the given objects.
 *
 * - Parameters:
 *   - objects: A C array of the pointer-sized objects to be in the new array. The objects in the new array are ordered in the same order in which they appear in this C array. This value may be `null`
 *     if `count` is 0. This C array is not changed or freed by this function. If `objects` is not a valid pointer to a C array of at least `count` elements, the behavior is undefined.
 *   - count: The number of objects to copy from the objects C array into the new array. This number will be the count of the new array—it must not be negative or greater than the number of elements
 *     in `objects`.
 *
 * - Returns: A new array containing `count` number of objects from `objects`.
 */
CoreFoundationArray CoreFoundationArrayInitialize(CoreFoundationAnyObject const nonnil* nillable objects, CInteger count);

void _CoreFoundationArrayRetain(CoreFoundationArray array);

void _CoreFoundationArrayRelease(CoreFoundationArray array);

/**
 * Creates a new array with the objects from another array.
 *
 * The objects from the `array` are copied into the new array; the objects are also retained by the new array. The count of the new array is the same as the `array`.
 *
 * - Parameter array: The array to copy.
 *
 * - Returns: A new ``CoreFoundationArray`` object that contains the same objects as the `array`.
 */
CoreFoundationArray CoreFoundationArrayCopy(CoreFoundationArray array);

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
 *     of the type expected by the retain function, the behavior is undefined. The indices of other objects are not affected.
 */
void CoreFoundationArraySetObjectAtIndex(CoreFoundationArray array, CoreFoundationAnyObject object, CInteger index);

/**
 * Replaces the objects in the receiving array specified by a given range with all of the objects from a given array.
 *
 * - Parameters:
 *   - array: The array in which some objects are to be replaced.
 *   - range: The range of objects within the `array` to replace. The range `location` or end point (defined by the `location` plus `count` minus 1) must not lie outside the index space of the `array`
 *     (`0` to `N-1` inclusive, where `N` is the count of the `array`). The range `count` must not be negative. The range may be empty (`count` `0`), in which case the new objects are merely inserted
 *     at the range location.
 *   - newObjects: A C array of the pointer-sized objects to be placed into the `array`. The new objects in the `array` are ordered in the same order in which they appear in this C array. This
 *     parameter may be `null` if the `newCount` parameter is `0`. This C array is not changed or freed by this function. If this parameter is not a valid pointer to a C array of at least `newCount`
 *     objects, the behavior is undefined.
 *   - newCount: The number of objects to copy from the `newObjects` C array into the `array`. If this parameter is different from the range length, the excess `newCount` objects are inserted after
 *     the range or the excess range objects are deleted. This parameter may be `0`, in which case no new objects are replaced into the `array` and the objects in the range are simply removed. If this
 *     parameter is negative or greater than the number of objects actually in the `newObjects` C array, the behavior is undefined.
 */
void CoreFoundationArrayReplaceSubrangeWithObjects(CoreFoundationArray array, CoreFoundationRange range, CoreFoundationAnyObject const nonnil* nillable newObjects, CInteger newCount);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationArray_h */
