/*
 *  CoreFoundationIO.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/4/26.
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

#ifndef CoreFoundationIO_h
#define CoreFoundationIO_h

#include <CKit/CKit.h>

#include "../Numerics/CoreFoundationNumber.h"
#include "../Strings/CoreFoundationString.h"

C_ASSUME_NONNULL_BEGIN

CoreFoundationNumber* nillable CoreFoundationIOScanInteger();

CoreFoundationNumber* nillable CoreFoundationIOScanUnsignedInteger();

CoreFoundationString* nillable CoreFoundationIOScanString();

void CoreFoundationIOPrintInteger(
  CoreFoundationNumber* number,
  CString terminator
);

void CoreFoundationIOPrintUnsignedInteger(
  CoreFoundationNumber* number,
  CString terminator
);

void CoreFoundationIOPrintString(
  CoreFoundationString* string,
  CString terminator
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationIO_h */
