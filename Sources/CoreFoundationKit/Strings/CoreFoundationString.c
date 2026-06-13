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

  extern CoreFoundationAnyObject*
  ObjectiveCObjectCopyDescription(CoreFoundationAnyObject* object);
#endif /* !ONLINE_JUDGE */

struct CoreFoundationString {
  CoreFoundationObject object;

  CInteger32* characters;
  CInteger count;
};

CoreFoundationString* nillable
CoreFoundationStringInitializeWithCString(CString cString) {
#ifdef ONLINE_JUDGE
  let size = sizeof(CoreFoundationString);
  let string = (CoreFoundationString*)CMemoryAllocate(size);

  string->object.isa = null;
  string->object.referenceCount = 1;
  string->object.typeID = kCoreFoundationTypeIDString;

  let cStringCount = CStringGetCount(cString);
  let count = CStringConvertUTF8CharactersToUTF32Characters(
    null,
    cString,
    cStringCount,
    0
  );

  string->characters = CMemoryAllocate(count * sizeof(CInteger32));

  CStringConvertUTF8CharactersToUTF32Characters(
    string->characters,
    cString,
    cStringCount,
    count
  );
  if (count == -1ull) {
    CMemoryDeallocate(string->characters);
    CMemoryDeallocate(string);

    return null;
  }

  string->count = count;

  return string;
#else
  return FoundationCoreFoundationStringInitializeWithCString(cString);
#endif
}

#ifdef ONLINE_JUDGE
CoreFoundationString* nillable
CoreFoundationStringInitializeWithFormat(CString format, ...) {
  let arguments = (CVariableArgumentList){ 0 };
  CVariableArgumentListInitialize(arguments, format);

  let cString = (CInteger8*)CMemoryAllocate(1 * sizeof(CInteger8));
  let cStringCapacity = 1ll;
  let cStringCount = 0ll;

  let formatCount = CStringGetCount(format);
  let i = 0ll;
  for (; i < formatCount; i += 1) {
    let buffer = (CInteger8*)null;
    let bufferCount = 0ll;
    let needsDeallocate = no;

    if (format[i] == '%' && format[i + 1] == 'd') {
      let value = CVariableArgumentListGetNextArgument(arguments, CInteger);

      buffer = (CInteger8 [32]){ 0 };
      bufferCount = CStringInitializeWithFormat(buffer, "%ld", value);

      i += 1;
      needsDeallocate = no;
    } else if (format[i] == '%' && format[i + 1] == 'f') {
      let value = CVariableArgumentListGetNextArgument(
        arguments,
        CFloatingPoint64
      );

      buffer = (CInteger8 [32]){ 0 };
      bufferCount = CStringInitializeWithFormat(buffer, "%lf", value);

      i += 1;
      needsDeallocate = no;
    } else if (format[i] == '%' && format[i + 1] == '@') {
      let value = CVariableArgumentListGetNextArgument(
        arguments,
        CoreFoundationAnyObject*
      );
      CoreFoundationRetain(value);

      let typeID = ((CoreFoundationObject*)value)->typeID;
      let class = CoreFoundationClassTable[typeID];
      let descriptionString = class.copyDescription(value);

      bufferCount = CoreFoundationStringGetCStringCount(descriptionString);
      buffer = (CInteger8*)CMemoryAllocate(
        (bufferCount + 1) * sizeof(CInteger8)
      );
      CoreFoundationStringCopyCString(descriptionString, buffer);

      CoreFoundationRelease(value);
      CoreFoundationRelease(descriptionString);

      i += 1;
      needsDeallocate = yes;
    } else {
      let j = i;
      for (; j < formatCount && format[j] != '%'; j += 1);

      bufferCount = j - i;
      buffer = (CInteger8*)CMemoryAllocate(bufferCount * sizeof(CInteger8));

      let k = 0ll;
      for (j = i; k < bufferCount; k += 1, j += 1) {
        buffer[k] = format[j];
      }

      i = j - 1;
      needsDeallocate = yes;
    }

    /* Append the buffer to cString. */
    while (cStringCapacity < cStringCount + bufferCount + 1) {
      cStringCapacity *= 2;
      cString = CMemoryResize(cString, cStringCapacity * sizeof(CInteger8));
    }
    CMemoryCopy(
      cString + cStringCount,
      buffer,
      bufferCount * sizeof(CInteger8)
    );
    cStringCount += bufferCount;

    if (needsDeallocate) {
      CMemoryDeallocate(buffer);
    }
  }

  cString[cStringCount] = '\0';
  let string = CoreFoundationStringInitializeWithCString(cString);

  CMemoryDeallocate(cString);

  CVariableArgumentListDeinitialize(arguments);

  return string;
}
#endif /* ONLINE_JUDGE */

void CoreFoundationStringDeinitialize(CoreFoundationAnyObject* string) {
  CMemoryDeallocate(((CoreFoundationString*)string)->characters);
}

CoreFoundationString*
CoreFoundationStringCopyDescription(CoreFoundationAnyObject* string) {
  CoreFoundationRetain(string);

  /* TODO: Copy self. */
  let copy = CoreFoundationStringInitializeWithCString("");
  CMemoryDeallocate(copy->characters);
  copy->count = ((CoreFoundationString*)string)->count;
  copy->characters = CMemoryAllocate(copy->count * sizeof(CInteger32));
  CMemoryCopy(
    copy->characters,
    ((CoreFoundationString*)string)->characters,
    copy->count * sizeof(CInteger32)
  );

  CoreFoundationRelease(string);

  return copy;
}

CInteger CoreFoundationStringGetCount(CoreFoundationString* string) {
  CoreFoundationRetain(string);
  let count = string->count;

  CoreFoundationRelease(string);

  return count;
}

CInteger
CoreFoundationStringGetCStringCount(CoreFoundationString* string) {
  CoreFoundationRetain(string);

  let count = CStringConvertUTF32CharactersToUTF8Characters(
    null,
    string->characters,
    string->count,
    0
  );

  CoreFoundationRelease(string);

  return count;
}

CInteger32 CoreFoundationStringGetCharacterAtIndex(
  CoreFoundationString* string,
  CInteger index
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

void CoreFoundationStringCopyCString(
  CoreFoundationString* string,
  CInteger8* cString
) {
  CoreFoundationRetain(string);

  let count = CStringConvertUTF32CharactersToUTF8Characters(
    cString,
    string->characters,
    string->count,
    string->count
  );
  cString[count] = '\0';

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
  CoreFoundationClassTable[kCoreFoundationTypeIDString].copyDescription =
    CoreFoundationStringCopyDescription;
}

C_ASSUME_NONNULL_END
