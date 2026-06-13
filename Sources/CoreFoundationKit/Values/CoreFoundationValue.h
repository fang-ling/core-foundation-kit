/*
 *  CoreFoundationValue.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/6/13.
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

#ifndef CoreFoundationValue_h
#define CoreFoundationValue_h

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A simple container for a single C data item.
 *
 * A ``CoreFoundationValue`` object can hold any of the scalar types such as
 * ``CInteger``, ``CUnsignedInteger``, and ``CFloatingPoint``, as well as
 * pointers, structures, and CoreFoundation object references. Use this class to
 * work with such data types in collections (such as ``CoreFoundationArray`` and
 * ``CoreFoundationDictionary``), and other APIs that require CoreFoundation
 * objects. ``CoreFoundationValue`` objects are always immutable.
 */
typedef struct CoreFoundationValue CoreFoundationValue;

/**
 * Creates a value object containing the specified value with the specified
 * size.
 *
 * - Parameters:
 *   - bytes: A pointer to data to be stored in the new value object.
 *   - size: The size in bytes of the data, as provided by the `sizeof` compiler
 *     directive. Do not hard-code this parameter as a `CInteger`.
 *
 * - Returns: A new value object that contains value.
 */
CoreFoundationValue* CoreFoundationValueInitializeWithBytesAndSize(
  const void* bytes,
  CInteger size
);

/**
 * Returns the size of the data contained in the value object.
 *
 * This property provides the same value produced by the `sizeof` compiler
 * directive.
 *
 * - Parameter value: The value object upon which to operate.
 *
 * - Returns: The size of the data contained in the value object.
 */
CInteger CoreFoundationValueGetSize(CoreFoundationValue* value);

/**
 * Copies the value into the specified buffer.
 *
 * - Parameters:
 *   - value: The value object upon which to operate.
 *   - buffer: A buffer into which to copy the value. The buffer must be
 *     large enough to hold the value.
 */
void CoreFoundationValueCopyValue(CoreFoundationValue* value, void* buffer);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationValue_h */
