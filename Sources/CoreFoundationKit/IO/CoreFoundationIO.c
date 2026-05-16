/*
 *  CoreFoundationIO.c
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

#include "CoreFoundationIO.h"

#include "../Base/CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

CInteger8 CoreFoundationIOByteBuffer[1048576]; /* FIXME: Not thread-safe. */

CoreFoundationNumber* nillable CoreFoundationIOScanNumber(
  CoreFoundationNumberType type
) {
  switch (type) {
    case kCoreFoundationNumberTypeInteger64: {
      let buffer = 0ll;
      if (CIOScanWithFormat("%lld", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger64: {
      let buffer = 0ull;
      if (CIOScanWithFormat("%llu", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeFloatingPoint64: {
      let buffer = 0.0;
      if (CIOScanWithFormat("%lf", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }
  }

  return null;
}

CoreFoundationString* nillable CoreFoundationIOScanString() {
  if (CIOScanWithFormat("%s", CoreFoundationIOByteBuffer) == 1) {
    let string = CoreFoundationStringInitializeWithCString(
      CoreFoundationIOByteBuffer
    );

    return string;
  }

  return null;
}

void CoreFoundationIOPrintNumber(
  CoreFoundationNumber* number,
  CString terminator
) {
  CoreFoundationRetain(number);

  let type = CoreFoundationNumberGetType(number);
  switch (type) {
    case kCoreFoundationNumberTypeInteger64: {
      let buffer = 0ll;
      CoreFoundationNumberGetValue(number, type, &buffer);
      CIOPrintWithFormat("%lld", buffer);
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger64: {
      let buffer = 0ull;
      CoreFoundationNumberGetValue(number, type, &buffer);
      CIOPrintWithFormat("%llu", buffer);
      break;
    }

    case kCoreFoundationNumberTypeFloatingPoint64: {
      let buffer = 0.0;
      CoreFoundationNumberGetValue(number, type, &buffer);
      CIOPrintWithFormat("%lf", buffer);
      break;
    }
  }

  CIOPrintWithFormat("%s", terminator);

  CoreFoundationRelease(number);
}

void CoreFoundationIOPrintString(
  CoreFoundationString* string,
  CString terminator
) {
  CoreFoundationRetain(string);

  /* FIXME: These buffers may overflow. */
  CInteger32 characters[1024];
  let _characters = (const CInteger32*)characters;
  CInteger8 buffer[1024] = { 0 };

  CoreFoundationStringCopyCharacters(string, characters);
  CStringConvertUTF32CharactersToUTF8Characters(
    buffer,
    &_characters,
    CoreFoundationStringGetCount(string),
    1024
  );

  CIOPrintWithFormat("%s%s", buffer, terminator);

  CoreFoundationRelease(string);
}

C_ASSUME_NONNULL_END
