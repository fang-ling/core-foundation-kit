/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreFoundationString.c
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/4/26.
 *
 *  This source file is part of the CoreFoundationKit open source project
 *
 *  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
 *  Licensed under Apache License v2.0
 *
 *  See LICENSE for license information
 *
 *  SPDX-License-Identifier: Apache-2.0
 *
 *===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#include "CoreFoundationString.h"

C_ASSUME_NONNULL_BEGIN

struct _CoreFoundationString {
  _CoreFoundationObject _object;

  CUnsignedInteger32* _characters;
  CInteger _count;
};

CoreFoundationString CoreFoundationStringInitializeWithCharacters(const CUnsignedInteger32* characters, CInteger count) {
#if C_TARGET_OS_ONLINE_JUDGE
  let string = (struct _CoreFoundationString*)CMemoryAllocate(1, sizeof(struct _CoreFoundationString));

  string->_object.isa = null;
  string->_object.referenceCount = 1;
  string->_object.typeID = kCoreFoundationTypeIDString;

  string->_characters = CMemoryAllocate(count, sizeof(CUnsignedInteger32));
  string->_count = count;
  CMemoryCopy(string->_characters, characters, count * sizeof(CUnsignedInteger32));

  return string;
#else
  return _CoreFoundationStringInitializeWithCharacters(characters, count);
#endif
}

void _CoreFoundationStringRetain(CoreFoundationString string) {
  CoreFoundationObjectRetain((void*)string);
}

void _CoreFoundationStringRelease(CoreFoundationString string) {
  CoreFoundationObjectRelease((void*)string);
}

void _CoreFoundationStringDeinitialize(CoreFoundationAnyObject* string) {
  CMemoryDeallocate(((CoreFoundationString)string)->_characters);
}

CInteger CoreFoundationStringGetCount(CoreFoundationString string) {
  return string->_count;
}

CUnsignedInteger32 CoreFoundationStringGetCharacterAtIndex(CoreFoundationString string, CInteger index) {
  return string->_characters[index];
}

C_INITIALIZER void CoreFoundationStringRegisterClass() {
  _CoreFoundationClassTable[kCoreFoundationTypeIDString].deinitialize = _CoreFoundationStringDeinitialize;
}

C_ASSUME_NONNULL_END
