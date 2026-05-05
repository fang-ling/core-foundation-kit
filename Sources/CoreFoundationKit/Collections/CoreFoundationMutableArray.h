/*
 *  CoreFoundationMutableArray.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/5/2.
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

#ifndef CoreFoundationMutableArray_h
#define CoreFoundationMutableArray_h

#include <CKit/CKit.h>

#include "CoreFoundationArray.h"

C_ASSUME_NONNULL_BEGIN

typedef CoreFoundationArray CoreFoundationMutableArray;

#ifdef ONLINE_JUDGE
#  define CoreFoundationMutableArrayInitialize CoreFoundationArrayInitialize
#else
  CoreFoundationMutableArray* CoreFoundationMutableArrayInitialize();
#endif

#define CoreFoundationMutableArrayGetCount CoreFoundationArrayGetCount

#define CoreFoundationMutableArrayGetObjectAtIndex \
  CoreFoundationArrayGetObjectAtIndex

void CoreFoundationMutableArrayAppendObject(
  CoreFoundationArray* array,
  CoreFoundationAnyObject* object
);

void CoreFoundationMutableArrayRemoveLastObject(CoreFoundationArray* array);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationMutableArray_h */
