/*
 *  CoreFoundationString.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/4/26.
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

#ifndef CoreFoundationString_h
#define CoreFoundationString_h

#include <CKit/CKit.h>

#include "../Sorting/CoreFoundationComparisonResult.h"

C_ASSUME_NONNULL_BEGIN

typedef struct CoreFoundationString CoreFoundationString;

CoreFoundationString* nillable
CoreFoundationStringInitializeWithCString(CString cString);

/**
 * Creates an immutable string from a formatted string and a variable number of
 * arguments.
 *
 * - Parameter format: The formatted string with `printf`-style specifiers
 *   followed by the variable argument list of values.
 *
 * - Returns An immutable string, or `null` if there was a problem creating the
 *   object.
 */
CoreFoundationString* nillable
CoreFoundationStringInitializeWithFormat(CString format, ...);

CUnsignedInteger64 CoreFoundationStringGetCount(CoreFoundationString* string);

/**
 * Returns the number of characters in the C-string representation.
 */
CUnsignedInteger64
CoreFoundationStringGetCStringCount(CoreFoundationString* string);

CInteger32 CoreFoundationStringGetCharacterAtIndex(
  CoreFoundationString* string,
  CUnsignedInteger64 index
);

void CoreFoundationStringCopyCharacters(
  CoreFoundationString* string,
  CInteger32* characters
);

/**
 * Copies the character contents of a string to a C string buffer
 *
 * - Parameters:
 *   - string: The string whose contents you wish to access.
 *   - cString: The C string buffer into which to copy the string. The buffer
 *     must be large enough to contain the converted characters and a `null`
 *     terminator.
 */
void CoreFoundationStringCopyCString(
  CoreFoundationString* string,
  CInteger8* cString
);

CoreFoundationComparisonResult CoreFoundationStringCompare(
  CoreFoundationString* string1,
  CoreFoundationString* string2
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationString_h */
