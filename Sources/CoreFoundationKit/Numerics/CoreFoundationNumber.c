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
  extern CoreFoundationAnyObject*
  FoundationCoreFoundationNumberInitializeWithUnsignedInteger(
    CUnsignedInteger64 value
  );
#endif /* !ONLINE_JUDGE */

struct CoreFoundationNumber {
  CoreFoundationObject object;

  union {
    CUnsignedInteger64 unsignedInteger64;
  } value;
};

CoreFoundationNumber*
CoreFoundationNumberInitializeWithUnsignedInteger(CUnsignedInteger64 value) {
#ifdef ONLINE_JUDGE
  let size = sizeof(CoreFoundationNumber);
  let number = (CoreFoundationNumber*)CMemoryAllocate(size);

  number->object.isa = NULL;
  number->object.referenceCount = 1;
  number->object.typeID = kCoreFoundationTypeIDNumber;

  number->value.unsignedInteger64 = value;

  return number;
#else
  return FoundationCoreFoundationNumberInitializeWithUnsignedInteger(value);
#endif
}

CUnsignedInteger64
CoreFoundationNumberGetUnsignedIntegerValue(CoreFoundationNumber* number) {
  CoreFoundationRetain(number);

  let value = number->value.unsignedInteger64;

  CoreFoundationRelease(number);
  return value;
}

C_INITIALIZER
void CoreFoundationNumberRegisterClass() {
  CoreFoundationClassTable[kCoreFoundationTypeIDNumber].deinitialize = NULL;
}

C_ASSUME_NONNULL_END
