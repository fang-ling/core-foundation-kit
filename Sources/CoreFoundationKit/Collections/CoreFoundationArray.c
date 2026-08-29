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

  CoreFoundationAnyObject* _objects;
  CInteger _count;
  CInteger _capacity;
};

CoreFoundationArray CoreFoundationArrayInitialize(CoreFoundationAnyObject const* objects, CInteger count) {
  let array = (struct _CoreFoundationArray*)CMemoryAllocate(1, sizeof(struct _CoreFoundationArray));

  array->_object._metadata = 0;
  array->_object._referenceCount = 1;
  array->_object._typeID = kCoreFoundationTypeIDArray;

  array->_objects = CMemoryAllocate(count, sizeof(CoreFoundationAnyObject));
  array->_count = count;
  array->_capacity = count;

  let i = 0;
  for (; i < count; i += 1) {
    CoreFoundationObjectRetain(objects[i]);
    array->_objects[i] = objects[i];
  }

  return array;
}

void _CoreFoundationArrayDeinitialize(CoreFoundationAnyObject array) {
  let i = 0;
  for (; i < ((CoreFoundationArray)array)->_count; i += 1) {
    CoreFoundationObjectRelease(((CoreFoundationArray)array)->_objects[i]);
  }

  CMemoryDeallocate(((CoreFoundationArray)array)->_objects);
}

void _CoreFoundationArrayRetain(CoreFoundationArray array) {
  CoreFoundationObjectRetain((void*)array);
}

void _CoreFoundationArrayRelease(CoreFoundationArray array) {
  CoreFoundationObjectRelease((void*)array);
}

CoreFoundationArray CoreFoundationArrayCopy(CoreFoundationArray array) {
  return CoreFoundationArrayInitialize(array->_objects, array->_count);
}

CInteger CoreFoundationArrayGetCount(CoreFoundationArray array) {
  return array->_count;
}

CoreFoundationAnyObject CoreFoundationArrayGetObjectAtIndex(CoreFoundationArray array, CInteger index) {
  CDebuggingPrecondition(index >= 0 && index < array->_count, "Index out of range.");

  return array->_objects[index];
}

void CoreFoundationArraySetObjectAtIndex(CoreFoundationArray array, CoreFoundationAnyObject object, CInteger index) {
  CDebuggingPrecondition(index >= 0 && index < array->_count, "Index out of range.");

  CoreFoundationObjectRetain(object);
  CoreFoundationObjectRelease(array->_objects[index]);
  array->_objects[index] = object;
}

void CoreFoundationArrayReplaceSubrangeWithObjects(CoreFoundationArray array, CoreFoundationRange range, CoreFoundationAnyObject const nonnil* nillable newObjects, CInteger newCount) {
  CDebuggingPrecondition(range.count >= 0, "Range count must not be negative.");
  CDebuggingPrecondition(range.location >= 0 && range.location + range.count <= array->_count, "Index out of range.");
  CDebuggingPrecondition(newCount >= 0, "newCount must not be negative.");
  CDebuggingPrecondition(newCount == 0 || newObjects != null, "newObjects must not be null when newCount is nonzero.");

  let i = 0;
  for (; i < newCount; i += 1) {
    CoreFoundationObjectRetain(newObjects[i]);
  }

  let rangeEndLocation = range.location + range.count;
  for (i = range.location; i < rangeEndLocation; i += 1) {
    CoreFoundationObjectRelease(array->_objects[i]);
  }

  let newArrayCount = array->_count - range.count + newCount;
  if (array->_capacity < newArrayCount) {
    array->_capacity = array->_capacity > 0 ? array->_capacity : 1;
    while (array->_capacity < newArrayCount) {
      array->_capacity *= 2;
    }

    array->_objects = CMemoryResize(array->_objects, array->_capacity * sizeof(CoreFoundationAnyObject));
  }

  /* Make room for new objects. */
  let tailCount = array->_count - rangeEndLocation;
  if (newCount != range.count && tailCount > 0) {
    CMemoryCopy(array->_objects + range.location + newCount, array->_objects + rangeEndLocation, tailCount * sizeof(CoreFoundationAnyObject));
  }

  CMemoryCopy(array->_objects + range.location, newObjects, newCount * sizeof(CoreFoundationAnyObject));

  if (array->_capacity > 1 && newArrayCount * 4 <= array->_capacity) {
    while (array->_capacity > 1 && newArrayCount * 4 <= array->_capacity) {
      array->_capacity /= 2;
    }

    array->_objects = CMemoryResize(array->_objects, array->_capacity * sizeof(CoreFoundationAnyObject));
  }

  array->_count = newArrayCount;
}

C_INITIALIZER void CoreFoundationArrayRegisterClass() {
  _CoreFoundationClassTable[kCoreFoundationTypeIDArray]._deinitialize = _CoreFoundationArrayDeinitialize;
}

C_ASSUME_NONNULL_END
