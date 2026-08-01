/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
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
 *===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#ifndef CoreFoundationString_h
#define CoreFoundationString_h

#include "../Base/CoreFoundationObject.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A Unicode string value that is a collection of characters.
 *
 * ``CoreFoundationString`` provides a suite of efficient string-manipulation and string-conversion functions. It offers seamless Unicode support and facilitates the sharing of
 * data between CoreFoundationKit and C-based programs.
 *
 * ``CoreFoundationString`` objects manages static and dynamic strings.
 *
 * ``CoreFoundationString`` provides functions for finding and comparing strings. It also provides functions for reading numeric values from strings, for combining strings in
 * various ways, and for converting a string to different forms (such as encoding and case changes). A number of functions, for example ``CoreFoundationStringFindWithOptions``,
 * allow you to specify a range over which to operate within a string. The specified range must not exceed the length of the string. Debugging options may help you to catch any
 * errors that arise if a range does exceed a string's length.
 *
 * ``CoreFoundationString`` is "toll-free bridged" with its FoundationKit counterpart, ``FoundationString``. This means that the CoreFoundationKit type is interchangeable in
 * function or method calls with the bridged FoundationKit object. Therefore, in a method where you see an ``FoundationString`` parameter, you can pass in a
 * ``CoreFoundationString``, and in a function where you see a ``CoreFoundationString`` parameter, you can pass in an ``FoundationString`` instance.
 *
 * ## Topics
 *
 * ### Creating a CoreFoundationString
 *
 * - ``CoreFoundationStringInitializeWithCharacters``
 *
 * ### Getting a CoreFoundationString's Length
 *
 * - ``CoreFoundationStringGetCount``
 *
 * ### Accessing Characters
 *
 * - ``CoreFoundationStringGetCharacterAtIndex``
 */
typedef struct C_SWIFT_SHARED_REFERENCE(_CoreFoundationStringRetain, _CoreFoundationStringRelease) _CoreFoundationString* CoreFoundationString;

/**
 * Creates a string from a buffer of Unicode characters.
 *
 * This function creates an immutable string from a client-supplied Unicode buffer. You must supply a count of the characters in the buffer. This function always copies the
 * characters in the provided buffer into internal storage.
 *
 * - Parameters:
 *   - characters: The buffer of Unicode characters to copy into the new string.
 *   - count: The number of characters in the buffer pointed to by `characters`. Only this number of characters will be copied to internal storage.
 *
 * - Returns: An immutable string containing `characters`.
 */
CoreFoundationString CoreFoundationStringInitializeWithCharacters(const CUnsignedInteger32* characters, CInteger count)
C_SWIFT_RETURNS_RETAINED
C_SWIFT_NAME(_CoreFoundationString.init(characters:count:));

CoreFoundationAnyObject* _CoreFoundationStringInitializeWithCharacters(const CUnsignedInteger32* characters, CInteger count);

void _CoreFoundationStringRetain(CoreFoundationString string);

void _CoreFoundationStringRelease(CoreFoundationString string);

/**
 * Returns the number (in terms of UTF-32 code pairs) of Unicode characters in a string.
 *
 * - Parameter string: The string to examine.
 *
 * - Returns: The number (in terms of UTF-32 code pairs) of characters stored in the `string`.
 */
CInteger CoreFoundationStringGetCount(CoreFoundationString string)
C_SWIFT_NAME(getter:_CoreFoundationString.count(self:));

/**
 * Returns the Unicode character at a specified location in a string.
 *
 * This function is typically called in a loop to fetch the Unicode characters of a string in sequence or to fetch a character at a known position (first or last, for example).
 * Using it in a loop can be inefficient, especially with longer strings, so consider the ``CoreFoundationStringGetCharacters`` function as alternatives.
 *
 * - Parameters:
 *   - string: The string from which the Unicode character is obtained.
 *   - index: The position of the Unicode character in the String.
 *
 * - Returns: A Unicode character.
 */
CUnsignedInteger32 CoreFoundationStringGetCharacterAtIndex(CoreFoundationString string, CInteger index)
C_SWIFT_NAME(_CoreFoundationString.character(self:at:));

C_ASSUME_NONNULL_END

#endif /* CoreFoundationString_h */
