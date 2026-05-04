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

CUnsignedInteger64 CoreFoundationStringGetCount(CoreFoundationString* string);

CInteger32 CoreFoundationStringGetCharacterAtIndex(
  CoreFoundationString* string,
  CUnsignedInteger64 index
);

void CoreFoundationStringCopyCharacters(
  CoreFoundationString* string,
  CInteger32* characters
);

CoreFoundationComparisonResult CoreFoundationStringCompare(
  CoreFoundationString* string1,
  CoreFoundationString* string2
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationString_h */
