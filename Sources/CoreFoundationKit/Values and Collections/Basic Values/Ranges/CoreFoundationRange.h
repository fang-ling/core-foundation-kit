/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreFoundationRange.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/8/29.
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

#ifndef CoreFoundationRange_h
#define CoreFoundationRange_h

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A structure representing a range of sequential items in a container, such as characters in a buffer or elements in a collection.
 *
 * ## Topics
 *
 * ### Creating a Range
 *
 * - ``CoreFoundationRangeMake``
 */
typedef struct {
  /**
   * An integer representing the starting location of the range. For type compatibility with the rest of the system, ``CIntegerMaximum`` is the maximum value you should use for `location`.
   */
  CInteger location;

  /**
   * An integer representing the number of items in the range. For type compatibility with the rest of the system, ``CIntegerMaximum`` is the maximum value you should use for `count`.
   */
  CInteger count;
} CoreFoundationRange;

/**
 * Declares and initializes a ``CoreFoundationRange`` structure.
 *
 * This is an in-line convenience function for creating initialized ``CoreFoundationRange`` structures.
 *
 * - Parameters:
 *   - location: The starting location of the range.
 *   - count: The length of the range.
 *
 * - Returns: An initialized structure of type ``CoreFoundationRange``.
 */
static CoreFoundationRange CoreFoundationRangeMake(CInteger location, CInteger count) {
  return (CoreFoundationRange){location, count};
}

C_ASSUME_NONNULL_END

#endif
