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

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * Flags used by ``CoreFoundationNumber`` to indicate the data type of a value.
 */
typedef enum CoreFoundationNumberType {
  /**
   * Sixty-four-bit, signed integer. The ``CInteger64`` data type is defined in
   * ``CKit``.
   */
  kCoreFoundationNumberTypeInteger64,

  /**
   * Sixty-four-bit, unsigned integer. The ``CUnsignedInteger64`` data type is
   * defined in ``CKit``.
   */
  kCoreFoundationNumberTypeUnsignedInteger64,

  /**
   * Sixty-four-bit real. The ``CFloatingPoint64`` data type is defined in
   * ``CKit`` and conforms to the 64-bit IEEE 754 standard.
   */
  kCoreFoundationNumberTypeFloatingPoint64,
} CoreFoundationNumberType;

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

C_ASSUME_NONNULL_END

#endif /* CoreFoundationNumber_h */
