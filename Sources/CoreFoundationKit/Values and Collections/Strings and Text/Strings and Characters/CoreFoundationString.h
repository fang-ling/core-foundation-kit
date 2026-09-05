/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreFoundationString.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/4/26.
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

#ifndef CoreFoundationString_h
#define CoreFoundationString_h

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A Unicode string value that is a collection of characters.
 *
 * ``CoreFoundationString`` provides a suite of efficient string-manipulation and string-conversion functions. It offers seamless Unicode support and facilitates the sharing of data between
 * CoreFoundationKit and C-based programs.
 *
 * ``CoreFoundationString`` objects manage static and dynamic strings.
 *
 * ``CoreFoundationString`` has two primitive functions, ``CoreFoundationStringGetCount`` and ``CoreFoundationStringGetUTF8CodeUnitAtIndex``, that provide the basis for all other non-mutating
 * functions in its interface. The ``CoreFoundationStringGetCount`` function returns the length (in terms of UTF-8 code units) of the string. The ``CoreFoundationStringGetUTF8CodeUnitAtIndex``
 * function gives access to each code unit in the string by index, with index values starting at 0.
 *
 * ``CoreFoundationString`` provides functions for finding and comparing strings. It also provides functions for reading numeric values from strings, for combining strings in various ways, and for
 * converting a string to different forms (such as encoding and case changes). A number of functions, for example ``CoreFoundationStringFindWithOptions``, allow you to specify a range over which to
 * operate within a string. The specified range must not exceed the length of the string. Debugging options may help you to catch any errors that arise if a range does exceed a string's length.
 *
 * ## Topics
 *
 * ### Creating a CoreFoundationString
 *
 * - ``CoreFoundationStringInitializeWithUTF8CString``
 *
 * ### Getting a CoreFoundationString's Length
 *
 * - ``CoreFoundationStringGetCount``
 *
 * ### Accessing Characters
 *
 * - ``CoreFoundationStringGetUTF8CodeUnitAtIndex``
 */
typedef struct _CoreFoundationString* CoreFoundationString;

/**
 * Creates a string from a C string.
 *
 * A C string is a string of 8-bit characters terminated with an 8-bit null character.
 *
 * - Parameter cString: The null-terminated C string to be used to create the ``CoreFoundationString`` object. The string must use an 8-bit encoding.
 *
 * - Returns: A string containing `cString`.
 */
CoreFoundationString CoreFoundationStringInitializeWithUTF8CString(CString cString);

void _CoreFoundationStringRetain(CoreFoundationString string);

void _CoreFoundationStringRelease(CoreFoundationString string);

/**
 * Returns the length (in terms of UTF-8 code units) of a string.
 *
 * - Parameter string: The string to examine.
 *
 * - Returns: The length (in terms of UTF-8 code units) of the `string`.
 */
CInteger CoreFoundationStringGetCount(CoreFoundationString string);

/**
 * Returns the UTF-8 code unit at a specified location in a string.
 *
 * This function is typically called in a loop to fetch the UTF-8 code units of a string in sequence or to fetch a character at a known position (first or last, for example). Using it in a loop can be
 * inefficient, especially with longer strings, so consider the ``CoreFoundationStringGetUTF8CString`` function as alternatives.
 *
 * - Parameters:
 *   - string: The string from which the UTF-8 code unit is obtained.
 *   - index: The position of the UTF-8 code unit in the `string`.
 *
 * - Returns: A UTF-8 code unit.
 */
CInteger8 CoreFoundationStringGetUTF8CodeUnitAtIndex(CoreFoundationString string, CInteger index);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationString_h */
