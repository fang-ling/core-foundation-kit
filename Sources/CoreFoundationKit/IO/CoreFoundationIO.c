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

C_ASSUME_NONNULL_BEGIN

CoreFoundationNumber* nillable CoreFoundationIOScanInteger() {
  let buffer = 0ll;
  if (CIOScanWithFormat("%lld", &buffer) == 1) {
    let number = CoreFoundationNumberInitializeWithInteger(buffer);

    return number;
  }

  return NULL;
}

CoreFoundationNumber* nillable CoreFoundationIOScanUnsignedInteger() {
  let buffer = 0ull;
  if (CIOScanWithFormat("%llu", &buffer) == 1) {
    let number = CoreFoundationNumberInitializeWithUnsignedInteger(buffer);

    return number;
  }

  return NULL;
}

CoreFoundationString* nillable CoreFoundationIOScanString() {
  CInteger8 buffer[1024]; /* FIXME: This buffer may overflow. */
  if (CIOScanWithFormat("%s", buffer) == 1) {
    let string = CoreFoundationStringInitializeWithCString(buffer);

    return string;
  }

  return NULL;
}

void CoreFoundationIOPrintInteger(
  CoreFoundationNumber* number,
  CString terminator
) {
  let buffer = CoreFoundationNumberGetIntegerValue(number);

  CIOPrintWithFormat("%lld%s", buffer, terminator);
}

void CoreFoundationIOPrintUnsignedInteger(
  CoreFoundationNumber* number,
  CString terminator
) {
  let buffer = CoreFoundationNumberGetUnsignedIntegerValue(number);

  CIOPrintWithFormat("%llu%s", buffer, terminator);
}

void CoreFoundationIOPrintString(
  CoreFoundationString* string,
  CString terminator
) {
  /* FIXME: These buffers may overflow. */
  CInteger32 characters[1024];
  let _characters = (const CInteger32*)characters;
  CInteger8 buffer[1024] = { 0 };

  CoreFoundationStringCopyCharacters(string, characters);
  CStringConvertUTF32CharactersToUTF8Characters(
    buffer,
    &_characters,
    1024,
    1024
  );

  CIOPrintWithFormat("%s%s", buffer, terminator);
}

C_ASSUME_NONNULL_END
