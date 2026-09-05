/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
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
 *===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#include "CoreFoundationString.h"

#include "../Base/CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

struct _CoreFoundationString {
  _CoreFoundationObject _object;

  CInteger8* _utf8CodeUnits;
  CInteger _count;
};

CoreFoundationString CoreFoundationStringInitializeWithUTF8CString(CString cString) {
  let string = (struct _CoreFoundationString*)CMemoryAllocate(1, sizeof(struct _CoreFoundationString));

  string->_object._metadata = 0;
  string->_object._referenceCount = 1;
  string->_object._typeID = kCoreFoundationTypeIDString;

  string->_count = CStringGetCount(cString);
  string->_utf8CodeUnits = CMemoryAllocate(string->_count + 1, sizeof(CInteger8));
  CMemoryCopy(string->_utf8CodeUnits, cString, (string->_count + 1) * sizeof(CInteger8));

  return string;
}

void _CoreFoundationStringRetain(CoreFoundationString string) {
  CoreFoundationObjectRetain((void*)string);
}

void _CoreFoundationStringRelease(CoreFoundationString string) {
  CoreFoundationObjectRelease((void*)string);
}

void _CoreFoundationStringDeinitialize(CoreFoundationAnyObject string) {
  CMemoryDeallocate(((CoreFoundationString)string)->_utf8CodeUnits);
}

CInteger CoreFoundationStringGetCount(CoreFoundationString string) {
  return string->_count;
}

CInteger8 CoreFoundationStringGetUTF8CodeUnitAtIndex(CoreFoundationString string, CInteger index) {
  return string->_utf8CodeUnits[index];
}

C_INITIALIZER void CoreFoundationStringRegisterClass() {
  _CoreFoundationClassTable[kCoreFoundationTypeIDString]._deinitialize = _CoreFoundationStringDeinitialize;
}

C_ASSUME_NONNULL_END
