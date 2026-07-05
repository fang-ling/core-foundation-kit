/*
 *  CoreFoundationNumber.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/4/25.
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

#ifndef CoreFoundationNumber_h
#define CoreFoundationNumber_h

#include "../Sorting/CoreFoundationComparisonResult.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * Flags used by ``CoreFoundationNumber`` to indicate the data type of a value.
 */
typedef enum CoreFoundationNumberType {
  /**
   * Eight-bit, signed integer. The ``CInteger8`` data type is defined in
   * ``CKit``.
   */
  kCoreFoundationNumberTypeInteger8,

  /**
   * Sixteen-bit, signed integer. The ``CInteger16`` data type is defined in
   * ``CKit``.
   */
  kCoreFoundationNumberTypeInteger16,

  /**
   * Thirty-two-bit, signed integer. The ``CInteger32`` data type is defined in
   * ``CKit``.
   */
  kCoreFoundationNumberTypeInteger32,

  /**
   * Sixty-four-bit, signed integer. The ``CInteger64`` data type is defined in
   * ``CKit``.
   */
  kCoreFoundationNumberTypeInteger64,

  /**
   * Platform-native signed integer. The ``CInteger`` data type is defined in
   * ``CKit``.
   */
  kCoreFoundationNumberTypeInteger,

  /**
   * Eight-bit, unsigned integer. The ``CUnsignedInteger8`` data type is defined
   * in ``CKit``.
   */
  kCoreFoundationNumberTypeUnsignedInteger8,

  /**
   * Sixteen-bit, unsigned integer. The ``CUnsignedInteger16`` data type is
   * defined in ``CKit``.
   */
  kCoreFoundationNumberTypeUnsignedInteger16,

  /**
   * Thirty-two-bit, unsigned integer. The ``CUnsignedInteger32`` data type is
   * defined in ``CKit``.
   */
  kCoreFoundationNumberTypeUnsignedInteger32,

  /**
   * Sixty-four-bit, unsigned integer. The ``CUnsignedInteger64`` data type is
   * defined in ``CKit``.
   */
  kCoreFoundationNumberTypeUnsignedInteger64,

  /**
   * Platform-native unsigned integer. The ``CUnsignedInteger`` data type is
   * defined in ``CKit``.
   */
  kCoreFoundationNumberTypeUnsignedInteger,

  /**
   * Thirty-two-bit real. The ``CFloatingPoint32`` data type is defined in
   * ``CKit`` and conforms to the 32-bit IEEE 754 standard.
   */
  kCoreFoundationNumberTypeFloatingPoint32,

  /**
   * Sixty-four-bit real. The ``CFloatingPoint64`` data type is defined in
   * ``CKit`` and conforms to the 64-bit IEEE 754 standard.
   */
  kCoreFoundationNumberTypeFloatingPoint64,

  /**
   * Platform-native real. The ``CFloatingPoint`` data type is defined in
   * ``CKit``.
   */
  kCoreFoundationNumberTypeFloatingPoint,
} CoreFoundationNumberType;

/**
 * ## Topics
 *
 * ### Comparing Numbers
 *
 * - ``CoreFoundationNumberCompare``
 */
typedef struct CoreFoundationNumber CoreFoundationNumber;

/**
 * Creates a ``CoreFoundationNumber`` object using a specified value.
 *
 * - Parameters:
 *   - type: A constant that specifies the data type of the value to convert.
 *     See ``CoreFoundationNumberType`` for a list of possible values.
 *   - valueBuffer: A buffer that holds the value for the returned number
 *     object.
 *
 * - Returns: A new number with the value specified by `valueBuffer`.
 */
CoreFoundationNumber* CoreFoundationNumberInitialize(
  CoreFoundationNumberType type,
  void* valueBuffer
);

/**
 * Obtains the value of a ``CoreFoundationNumber`` object cast to a specified
 * type.
 *
 * If the argument type differs from the return type, then the conversion is
 * lossy or the return value is out of range.
 *
 * - Parameters:
 *   - number: The ``CoreFoundationNumber`` object to examine.
 *   - valueBuffer: On return, contains the value of number.
 */
void CoreFoundationNumberGetValue(
  CoreFoundationNumber* number,
  void* valueBuffer
);

/**
 * Returns the type used by a ``CoreFoundationNumber`` object to store its
 * value.
 *
 * - Parameter number: The ``CoreFoundationNumber`` object to examine.
 *
 * - Returns: A constant that indicates the data type of the value contained in
 *   number. See ``CoreFoundationNumberType`` for a list of possible values.
 */
CoreFoundationNumberType CoreFoundationNumberGetType(
  CoreFoundationNumber* number
);

/**
 * Compares two CFNumber objects and returns a comparison result.
 *
 * When comparing two ``CoreFoundationNumber`` objects using this function, one
 * or both objects can represent a special-case number such as signed 0, signed
 * infinity, or NaN.
 *
 * The following rules apply:
 *
 *   - Negative 0 compares less than positive 0.
 *   - Positive infinity compares greater than everything except itself, to
 *     which it compares equal.
 *   - Negative infinity compares less than everything except itself, to which
 *     it compares equal.
 *   - If both numbers are NaN, then they compare equal.
 *   - If only one of the numbers is NaN, then the NaN compares greater than the
 *     other number if it is negative, and smaller than the other number if it
 *     is positive.
 *
 * - Parameters:
 *   - number1: The first ``CoreFoundationNumber`` object to compare.
 *   - number2: The second ``CoreFoundationNumber`` object to compare.
 *
 * - Returns: A ``CoreFoundationComparisonResult`` constant that indicates
 *   whether `number` is equal to, less than, or greater than `otherNumber`.
 */
CoreFoundationComparisonResult CoreFoundationNumberCompare(
  CoreFoundationNumber* number,
  CoreFoundationNumber* otherNumber
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationNumber_h */
