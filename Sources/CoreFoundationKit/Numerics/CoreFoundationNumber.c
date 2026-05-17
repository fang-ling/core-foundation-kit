/*
 *  CoreFoundationNumber.c
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

#include "CoreFoundationNumber.h"

#include "../Base/CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

#ifndef ONLINE_JUDGE
  extern CoreFoundationAnyObject* FoundationCoreFoundationNumberInitialize(
    CoreFoundationNumberType type,
    void* valueBuffer
  );
#endif /* !ONLINE_JUDGE */

struct CoreFoundationNumber {
  CoreFoundationObject object;

  union {
    CInteger64 integer64;
    CUnsignedInteger64 unsignedInteger64;
    CFloatingPoint64 floatingPoint64;
  } value;

  CoreFoundationNumberType type;
};

CoreFoundationNumber* CoreFoundationNumberInitialize(
  CoreFoundationNumberType type,
  void* valueBuffer
) {
#ifdef ONLINE_JUDGE
  let size = sizeof(CoreFoundationNumber);
  let number = (CoreFoundationNumber*)CMemoryAllocate(size);

  number->object.isa = null;
  number->object.referenceCount = 1;
  number->object.typeID = kCoreFoundationTypeIDNumber;

  number->type = type;
  switch (type) {
    case kCoreFoundationNumberTypeInteger64:
      number->value.integer64 = *(CInteger64*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger64:
      number->value.unsignedInteger64 = *(CUnsignedInteger64*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeFloatingPoint64:
      number->value.floatingPoint64 = *(CFloatingPoint64*)valueBuffer;
      break;
  }

  return number;
#else
  return FoundationCoreFoundationNumberInitialize(type, valueBuffer);
#endif
}

CoreFoundationString*
CoreFoundationNumberCopyDescription(CoreFoundationAnyObject* number) {
  CoreFoundationRetain(number);

  let buffer = (CInteger8 [128]){ 0 };

  switch (((CoreFoundationNumber*)number)->type) {
    case kCoreFoundationNumberTypeInteger64:
      CStringInitializeWithFormat(
        buffer,
        "%lld",
        ((CoreFoundationNumber*)number)->value.integer64
      );
      break;

    case kCoreFoundationNumberTypeUnsignedInteger64:
      CStringInitializeWithFormat(
        buffer,
        "%llu",
        ((CoreFoundationNumber*)number)->value.unsignedInteger64
      );
      break;

    case kCoreFoundationNumberTypeFloatingPoint64:
      CStringInitializeWithFormat(
        buffer,
        "%lf",
        ((CoreFoundationNumber*)number)->value.floatingPoint64
      );
      break;
  }

  let descriptionString = CoreFoundationStringInitializeWithCString(buffer);

  CoreFoundationRelease(number);

  return descriptionString;
}

void CoreFoundationNumberGetValue(
  CoreFoundationNumber* number,
  void* valueBuffer
) {
  CoreFoundationRetain(number);

  switch (number->type) {
    case kCoreFoundationNumberTypeInteger64:
      *(CInteger64*)valueBuffer = number->value.integer64;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger64:
      *(CUnsignedInteger64*)valueBuffer = number->value.unsignedInteger64;
      break;

    case kCoreFoundationNumberTypeFloatingPoint64:
      *(CFloatingPoint64*)valueBuffer = number->value.floatingPoint64;
      break;
  }

  CoreFoundationRelease(number);
}

CoreFoundationNumberType CoreFoundationNumberGetType(
  CoreFoundationNumber* number
) {
  CoreFoundationRetain(number);

  let type = number->type;

  CoreFoundationRelease(number);
  return type;
}

C_INITIALIZER
void CoreFoundationNumberRegisterClass() {
  CoreFoundationClassTable[kCoreFoundationTypeIDNumber].deinitialize = null;
  CoreFoundationClassTable[kCoreFoundationTypeIDNumber].copyDescription =
    CoreFoundationNumberCopyDescription;
}

C_ASSUME_NONNULL_END
