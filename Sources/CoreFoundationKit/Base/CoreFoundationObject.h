/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreFoundationObject.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/4/25.
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

#ifndef CoreFoundationObject_h
#define CoreFoundationObject_h

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

typedef void CoreFoundationAnyObject;

typedef struct _CoreFoundationObject {
  void* isa;

  CUnsignedInteger64 referenceCount;

#if C_TARGET_OS_ONLINE_JUDGE
  CUnsignedInteger8 typeID;
#endif
} _CoreFoundationObject;

typedef struct _CoreFoundationClass {
  void (*deinitialize)(CoreFoundationAnyObject* object);
} _CoreFoundationClass;

extern _CoreFoundationClass _CoreFoundationClassTable[256];

typedef enum CoreFoundationTypeID {
  kCoreFoundationTypeIDNotAType = 0,
  kCoreFoundationTypeIDNumber = 1,
  kCoreFoundationTypeIDString = 2,
  kCoreFoundationTypeIDArray = 3,
  kCoreFoundationTypeIDValue = 4
} CoreFoundationTypeID;

/**
 * Retains a CoreFoundationKit object.
 *
 * You should retain a CoreFoundationKit object when you receive it from elsewhere (that is, you did not create or copy it) and you want it to persist. If you retain a
 * CoreFoundationKit object you are responsible for releasing it.
 *
 * ### Special Considerations
 *
 * If `object` is `null`, this will cause a runtime error and your application will crash.
 *
 * - Parameter object: The CoreFoundationKit object to retain. This value must not be `null`.
 */
void CoreFoundationObjectRetain(CoreFoundationAnyObject* object);

/**
 * Releases a CoreFoundationKit object.
 *
 * If the retain count of `object` becomes zero the memory allocated to the object is deallocated and the object is destroyed. If you create, copy, or explicitly retain (see the
 * ``CoreFoundationObjectRetain`` function) a CoreFoundationKit object, you are responsible for releasing it when you no longer need it.
 *
 * ### Special Considerations
 *
 * If `object` is `null`, this will cause a runtime error and your application will crash.
 *
 * - Parameter object: A CoreFoundationKit object to release. This value must not be `null`.
 */
void CoreFoundationObjectRelease(CoreFoundationAnyObject* object);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationObject_h */
