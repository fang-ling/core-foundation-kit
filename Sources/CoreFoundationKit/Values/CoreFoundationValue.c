/*
 *  CoreFoundationValue.c
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/6/13.
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

#include "CoreFoundationValue.h"

#include "../Base/CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
  extern CoreFoundationAnyObject*
  FoundationCoreFoundationValueInitializeWithBytesAndSize(
    const void* bytes,
    CInteger size
  );
#endif /* !C_TARGET_OS_ONLINE_JUDGE */

struct CoreFoundationValue {
  CoreFoundationObject object;

  void* value;
  CInteger size;
};

CoreFoundationValue* CoreFoundationValueInitializeWithBytesAndSize(
  const void* bytes,
  CInteger size
) {
#if C_TARGET_OS_ONLINE_JUDGE
  let value = (CoreFoundationValue*)CMemoryAllocate(sizeof(CoreFoundationValue));

  value->object.isa = null;
  value->object.referenceCount = 1;
  value->object.typeID = kCoreFoundationTypeIDValue;

  value->value = CMemoryAllocate(size);
  CMemoryCopy(value->value, bytes, size);
  value->size = size;

  return value;
#else
  return (CoreFoundationValue*)
    FoundationCoreFoundationValueInitializeWithBytesAndSize(bytes, size);
#endif
}

CInteger CoreFoundationValueGetSize(CoreFoundationValue* value) {
  CoreFoundationRetain(value);

  let size = value->size;

  CoreFoundationRelease(value);
  return size;
}

void CoreFoundationValueCopyValue(CoreFoundationValue* value, void* buffer) {
  CoreFoundationRetain(value);

  CMemoryCopy(buffer, value->value, value->size);

  CoreFoundationRelease(value);
}

void CoreFoundationValueDeinitialize(CoreFoundationAnyObject* object) {
  CMemoryDeallocate(((CoreFoundationValue*)object)->value);
}

C_INITIALIZER
void CoreFoundationValueRegisterClass() {
  CoreFoundationClassTable[kCoreFoundationTypeIDValue].deinitialize =
    CoreFoundationValueDeinitialize;
  CoreFoundationClassTable[kCoreFoundationTypeIDValue].copyDescription = null;
}

C_ASSUME_NONNULL_END
