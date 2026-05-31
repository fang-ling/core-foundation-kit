/*
 *  CoreFoundationArray+Private.h
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

#ifndef CoreFoundationArray_Private_h
#define CoreFoundationArray_Private_h

#include "../Base/CoreFoundationObject.h"
#include "../Numerics/CoreFoundationNumber.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

struct CoreFoundationArray {
  CoreFoundationObject object;

  CoreFoundationAnyObject* nonnil * nonnil objects;
  CInteger count;
  CInteger capacity;
};

C_ASSUME_NONNULL_END

#endif /* CoreFoundationArray_Private_h */
