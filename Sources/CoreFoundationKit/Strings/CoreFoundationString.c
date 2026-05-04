/*
 *  CoreFoundationString.c
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

#include "CoreFoundationString.h"

#include "../Base/CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

#ifndef ONLINE_JUDGE
  extern CoreFoundationAnyObject*
  FoundationCoreFoundationStringInitializeWithCString(CString cString);
#endif /* !ONLINE_JUDGE */

struct CoreFoundationString {
  CoreFoundationObject object;

  CInteger32* characters;
  CUnsignedInteger64 count;
};

CoreFoundationString* nillable
CoreFoundationStringInitializeWithCString(CString cString) {
#ifdef ONLINE_JUDGE
  let size = sizeof(CoreFoundationString);
  let string = (CoreFoundationString*)CMemoryAllocate(size);

  string->object.isa = NULL;
  string->object.referenceCount = 1;
  string->object.typeID = kCoreFoundationTypeIDString;

  let cStringCount = CStringGetCount(cString);
  string->characters = CMemoryAllocate(cStringCount * sizeof(CInteger32));

  let count = CStringConvertUTF8CharactersToUTF32Characters(
    string->characters,
    &cString,
    cStringCount,
    cStringCount
  );
  if (count == -1) {
    CMemoryDeallocate(string->characters);
    CMemoryDeallocate(string);

    return NULL;
  }

  string->count = count;

  return string;
#else
  return FoundationCoreFoundationStringInitializeWithCString(cString);
#endif
}

void CoreFoundationStringDeinitialize(CoreFoundationAnyObject* string) {
  CMemoryDeallocate(((CoreFoundationString*)string)->characters);
}

CUnsignedInteger64 CoreFoundationStringGetCount(CoreFoundationString* string) {
  CoreFoundationRetain(string);

  let count = string->count;

  CoreFoundationRelease(string);

  return count;
}

CInteger32 CoreFoundationStringGetCharacterAtIndex(
  CoreFoundationString* string,
  CUnsignedInteger64 index
) {
  CoreFoundationRetain(string);

  let character = string->characters[index];

  CoreFoundationRelease(string);

  return character;
}

void CoreFoundationStringCopyCharacters(
  CoreFoundationString* string,
  CInteger32* characters
) {
  CoreFoundationRetain(string);

  CMemoryCopy(
    characters,
    string->characters,
    string->count * sizeof(CInteger32)
  );

  CoreFoundationRelease(string);
}

CoreFoundationComparisonResult CoreFoundationStringCompare(
  CoreFoundationString* string1,
  CoreFoundationString* string2
) {
  CoreFoundationRetain(string1);
  CoreFoundationRetain(string2);

  let characters1 = string1->characters;
  let characters2 = string2->characters;
  let count1 = string1->count;
  let count2 = string2->count;

  let minimumCount = CNumberFindMinimum(count1, count2);
  let result = kCoreFoundationComparisonResultSameOrder;

  let i = 0;
  for (; i < minimumCount; i += 1) {
    if (characters1[i] != characters2[i]) {
      result = (characters1[i] < characters2[i])
        ? kCoreFoundationComparisonResultAscendingOrder
        : kCoreFoundationComparisonResultDescendingOrder;

      goto cleanup;
    }
  }

  if (count1 < count2) {
    result = kCoreFoundationComparisonResultAscendingOrder;
  } else if (count1 > count2) {
    result = kCoreFoundationComparisonResultDescendingOrder;
  } else {
    result = kCoreFoundationComparisonResultSameOrder;
  }

  cleanup: {
    CoreFoundationRelease(string1);
    CoreFoundationRelease(string2);

    return result;
  }
}

C_INITIALIZER
void CoreFoundationStringRegisterClass() {
  CoreFoundationClassTable[kCoreFoundationTypeIDString].deinitialize =
    CoreFoundationStringDeinitialize;
}

C_ASSUME_NONNULL_END
