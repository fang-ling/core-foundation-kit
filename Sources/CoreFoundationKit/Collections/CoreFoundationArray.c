/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreFoundationArray.c
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/5/2.
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

#include "CoreFoundationArray.h"

C_ASSUME_NONNULL_BEGIN

struct _CoreFoundationArray {
  _CoreFoundationObject _object;

  CoreFoundationAnyObject** _objects;
  CInteger _count;
  CInteger _capacity;
  CBoolean _isMutable;
};

CoreFoundationArray CoreFoundationArrayInitialize(const void* const * objects, CInteger count, CBoolean isMutable) {
#if C_TARGET_OS_ONLINE_JUDGE
  let array = (struct _CoreFoundationArray*)CMemoryAllocate(1, sizeof(struct _CoreFoundationArray));

  array->_object.isa = null;
  array->_object.referenceCount = 1;
  array->_object.typeID = kCoreFoundationTypeIDArray;

  array->_objects = CMemoryAllocate(count, sizeof(const void*));
  array->_count = count;
  array->_capacity = count;
  array->_isMutable = isMutable;

  let i = 0;
  for (; i < count; i += 1) {
    CoreFoundationObjectRetain((void*)objects[i]);
    array->_objects[i] = (void*)objects[i];
  }

  return array;
#else
  return _CoreFoundationArrayInitialize(objects, count, isMutable);
#endif
}

void _CoreFoundationArrayRetain(CoreFoundationArray array) {
  CoreFoundationObjectRetain((void*)array);
}

void _CoreFoundationArrayRelease(CoreFoundationArray array) {
  CoreFoundationObjectRelease((void*)array);
}

void _CoreFoundationArrayDeinitialize(CoreFoundationAnyObject* array) {
  let i = 0;
  for (; i < ((CoreFoundationArray)array)->_count; i += 1) {
    CoreFoundationObjectRelease(((CoreFoundationArray)array)->_objects[i]);
  }

  CMemoryDeallocate(((CoreFoundationArray)array)->_objects);
}

CInteger CoreFoundationArrayGetCount(CoreFoundationArray array) {
  return array->_count;
}

CoreFoundationAnyObject* CoreFoundationArrayGetObjectAtIndex(CoreFoundationArray array, CInteger index) {
  return array->_objects[index];
}

C_INITIALIZER void CoreFoundationArrayRegisterClass() {
  _CoreFoundationClassTable[kCoreFoundationTypeIDArray].deinitialize = _CoreFoundationArrayDeinitialize;
}

C_ASSUME_NONNULL_END
