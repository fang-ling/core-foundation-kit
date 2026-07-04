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
    CInteger8 integer8;
    CInteger16 integer16;
    CInteger32 integer32;
    CInteger64 integer64;
    CInteger integer;
    CUnsignedInteger8 unsignedInteger8;
    CUnsignedInteger16 unsignedInteger16;
    CUnsignedInteger32 unsignedInteger32;
    CUnsignedInteger64 unsignedInteger64;
    CUnsignedInteger unsignedInteger;
    CFloatingPoint32 floatingPoint32;
    CFloatingPoint64 floatingPoint64;
    CFloatingPoint floatingPoint;
  } value;

  CoreFoundationNumberType type;
};

CoreFoundationNumber* CoreFoundationNumberInitialize(
  CoreFoundationNumberType type,
  void* valueBuffer
) {
#if C_TARGET_OS_ONLINE_JUDGE
  let size = sizeof(CoreFoundationNumber);
  let number = (CoreFoundationNumber*)CMemoryAllocate(size);

  number->object.isa = null;
  number->object.referenceCount = 1;
  number->object.typeID = kCoreFoundationTypeIDNumber;

  number->type = type;
  switch (type) {
    case kCoreFoundationNumberTypeInteger8:
      number->value.integer8 = *(CInteger8*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeInteger16:
      number->value.integer16 = *(CInteger16*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeInteger32:
      number->value.integer32 = *(CInteger32*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeInteger64:
      number->value.integer64 = *(CInteger64*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeInteger:
      number->value.integer = *(CInteger*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger8:
      number->value.unsignedInteger8 = *(CUnsignedInteger8*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger16:
      number->value.unsignedInteger16 = *(CUnsignedInteger16*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger32:
      number->value.unsignedInteger32 = *(CUnsignedInteger32*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger64:
      number->value.unsignedInteger64 = *(CUnsignedInteger64*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger:
      number->value.unsignedInteger = *(CUnsignedInteger*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeFloatingPoint32:
      number->value.floatingPoint32 = *(CFloatingPoint32*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeFloatingPoint64:
      number->value.floatingPoint64 = *(CFloatingPoint64*)valueBuffer;
      break;

    case kCoreFoundationNumberTypeFloatingPoint:
      number->value.floatingPoint = *(CFloatingPoint*)valueBuffer;
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
    case kCoreFoundationNumberTypeInteger8:
      CStringInitializeWithFormat(
        buffer,
        "%hhd",
        ((CoreFoundationNumber*)number)->value.integer8
      );
      break;

    case kCoreFoundationNumberTypeInteger16:
      CStringInitializeWithFormat(
        buffer,
        "%hd",
        ((CoreFoundationNumber*)number)->value.integer16
      );
      break;

    case kCoreFoundationNumberTypeInteger32:
      CStringInitializeWithFormat(
        buffer,
        "%d",
        ((CoreFoundationNumber*)number)->value.integer32
      );
      break;

    case kCoreFoundationNumberTypeInteger64:
      CStringInitializeWithFormat(
        buffer,
        "%lld",
        ((CoreFoundationNumber*)number)->value.integer64
      );
      break;

    case kCoreFoundationNumberTypeInteger:
      CStringInitializeWithFormat(
        buffer,
        "%ld",
        ((CoreFoundationNumber*)number)->value.integer
      );
      break;

    case kCoreFoundationNumberTypeUnsignedInteger8:
      CStringInitializeWithFormat(
        buffer,
        "%hhu",
        ((CoreFoundationNumber*)number)->value.unsignedInteger8
      );
      break;

    case kCoreFoundationNumberTypeUnsignedInteger16:
      CStringInitializeWithFormat(
        buffer,
        "%hu",
        ((CoreFoundationNumber*)number)->value.unsignedInteger16
      );
      break;

    case kCoreFoundationNumberTypeUnsignedInteger32:
      CStringInitializeWithFormat(
        buffer,
        "%u",
        ((CoreFoundationNumber*)number)->value.unsignedInteger32
      );
      break;

    case kCoreFoundationNumberTypeUnsignedInteger64:
      CStringInitializeWithFormat(
        buffer,
        "%llu",
        ((CoreFoundationNumber*)number)->value.unsignedInteger64
      );
      break;

    case kCoreFoundationNumberTypeUnsignedInteger:
      CStringInitializeWithFormat(
        buffer,
        "%lu",
        ((CoreFoundationNumber*)number)->value.unsignedInteger
      );
      break;

    case kCoreFoundationNumberTypeFloatingPoint32:
      CStringInitializeWithFormat(
        buffer,
        "%f",
        ((CoreFoundationNumber*)number)->value.floatingPoint32
      );
      break;

    case kCoreFoundationNumberTypeFloatingPoint64:
      CStringInitializeWithFormat(
        buffer,
        "%lf",
        ((CoreFoundationNumber*)number)->value.floatingPoint64
      );
      break;

    case kCoreFoundationNumberTypeFloatingPoint:
      CStringInitializeWithFormat(
        buffer,
        "%lf",
        ((CoreFoundationNumber*)number)->value.floatingPoint
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
    case kCoreFoundationNumberTypeInteger8:
      *(CInteger8*)valueBuffer = number->value.integer8;
      break;

    case kCoreFoundationNumberTypeInteger16:
      *(CInteger16*)valueBuffer = number->value.integer16;
      break;

    case kCoreFoundationNumberTypeInteger32:
      *(CInteger32*)valueBuffer = number->value.integer32;
      break;

    case kCoreFoundationNumberTypeInteger64:
      *(CInteger64*)valueBuffer = number->value.integer64;
      break;

    case kCoreFoundationNumberTypeInteger:
      *(CInteger*)valueBuffer = number->value.integer;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger8:
      *(CUnsignedInteger8*)valueBuffer = number->value.unsignedInteger8;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger16:
      *(CUnsignedInteger16*)valueBuffer = number->value.unsignedInteger16;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger32:
      *(CUnsignedInteger32*)valueBuffer = number->value.unsignedInteger32;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger64:
      *(CUnsignedInteger64*)valueBuffer = number->value.unsignedInteger64;
      break;

    case kCoreFoundationNumberTypeUnsignedInteger:
      *(CUnsignedInteger*)valueBuffer = number->value.unsignedInteger;
      break;

    case kCoreFoundationNumberTypeFloatingPoint32:
      *(CFloatingPoint32*)valueBuffer = number->value.floatingPoint32;
      break;

    case kCoreFoundationNumberTypeFloatingPoint64:
      *(CFloatingPoint64*)valueBuffer = number->value.floatingPoint64;
      break;

    case kCoreFoundationNumberTypeFloatingPoint:
      *(CFloatingPoint*)valueBuffer = number->value.floatingPoint;
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

CoreFoundationComparisonResult CoreFoundationNumberCompare(
  CoreFoundationNumber* number,
  CoreFoundationNumber* otherNumber
) {
  CoreFoundationRetain(number);
  CoreFoundationRetain(otherNumber);

  if (
    number->type == kCoreFoundationNumberTypeFloatingPoint ||
    number->type == kCoreFoundationNumberTypeFloatingPoint32 ||
    number->type == kCoreFoundationNumberTypeFloatingPoint64 ||
    otherNumber->type == kCoreFoundationNumberTypeFloatingPoint ||
    otherNumber->type == kCoreFoundationNumberTypeFloatingPoint32 ||
    otherNumber->type == kCoreFoundationNumberTypeFloatingPoint64
  ) {
    CDebuggingHaltWithMessage("TODO");
  }

  let comparisonResult = kCoreFoundationComparisonResultSameOrder;
  if (number->value.integer64 < otherNumber->value.integer64) {
    comparisonResult = kCoreFoundationComparisonResultAscendingOrder;
  } else if (number->value.integer64 > otherNumber->value.integer64) {
    comparisonResult = kCoreFoundationComparisonResultDescendingOrder;
  }

  CoreFoundationRelease(number);
  CoreFoundationRelease(otherNumber);

  return comparisonResult;
}

C_INITIALIZER
void CoreFoundationNumberRegisterClass() {
  CoreFoundationClassTable[kCoreFoundationTypeIDNumber].deinitialize = null;
  CoreFoundationClassTable[kCoreFoundationTypeIDNumber].copyDescription =
    CoreFoundationNumberCopyDescription;
}

C_ASSUME_NONNULL_END
