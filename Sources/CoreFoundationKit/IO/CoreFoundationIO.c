/*
 *  CoreFoundationIO.c
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

#include "CoreFoundationIO.h"

#include "../Base/CoreFoundationObject.h"

C_ASSUME_NONNULL_BEGIN

CInteger8 CoreFoundationIOByteBuffer[2097152]; /* FIXME: Not thread-safe. */

CoreFoundationNumber* nillable CoreFoundationIOScanNumber(
  CoreFoundationNumberType type
) {
  switch (type) {
    case kCoreFoundationNumberTypeInteger8: {
      let buffer = (CInteger8)0;
      if (CIOScanWithFormat("%hhd", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeInteger16: {
      let buffer = (CInteger16)0;
      if (CIOScanWithFormat("%hd", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeInteger32: {
      let buffer = (CInteger32)0;
      if (CIOScanWithFormat("%d", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeInteger64: {
      let buffer = 0ll;
      if (CIOScanWithFormat("%lld", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeInteger: {
      let buffer = (CInteger)0;
      if (CIOScanWithFormat("%ld", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger8: {
      let buffer = (CUnsignedInteger8)0;
      if (CIOScanWithFormat("%hhu", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger16: {
      let buffer = (CUnsignedInteger16)0;
      if (CIOScanWithFormat("%hu", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger32: {
      let buffer = (CUnsignedInteger32)0;
      if (CIOScanWithFormat("%u", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger64: {
      let buffer = 0ull;
      if (CIOScanWithFormat("%llu", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger: {
      let buffer = (CUnsignedInteger)0;
      if (CIOScanWithFormat("%lu", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeFloatingPoint32: {
      let buffer = (CFloatingPoint32)0;
      if (CIOScanWithFormat("%f", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeFloatingPoint64: {
      let buffer = 0.0;
      if (CIOScanWithFormat("%lf", &buffer) == 1) {
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }

    case kCoreFoundationNumberTypeFloatingPoint: {
      let buffer = (CFloatingPoint)0;
#if C_TARGET_ARCHITECTURE_WASM32
      if (CIOScanWithFormat("%f", &buffer) == 1) {
#else
      if (CIOScanWithFormat("%lf", &buffer) == 1) {
#endif
        let number = CoreFoundationNumberInitialize(type, &buffer);

        return number;
      }
      break;
    }
  }

  return null;
}

CoreFoundationString* nillable CoreFoundationIOScanString() {
  if (CIOScanWithFormat("%s", CoreFoundationIOByteBuffer) == 1) {
    let string = CoreFoundationStringInitializeWithCString(
      CoreFoundationIOByteBuffer
    );

    return string;
  }

  return null;
}

void CoreFoundationIOPrintNumber(
  CoreFoundationNumber* number,
  CString terminator
) {
  CoreFoundationRetain(number);

  let type = CoreFoundationNumberGetType(number);
  switch (type) {
    case kCoreFoundationNumberTypeInteger8: {
      let buffer = (CInteger8)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%hhd", buffer);
      break;
    }

    case kCoreFoundationNumberTypeInteger16: {
      let buffer = (CInteger16)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%hd", buffer);
      break;
    }

    case kCoreFoundationNumberTypeInteger32: {
      let buffer = (CInteger32)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%d", buffer);
      break;
    }

    case kCoreFoundationNumberTypeInteger64: {
      let buffer = 0ll;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%lld", buffer);
      break;
    }

    case kCoreFoundationNumberTypeInteger: {
      let buffer = (CInteger)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%ld", buffer);
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger8: {
      let buffer = (CUnsignedInteger8)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%hhu", buffer);
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger16: {
      let buffer = (CUnsignedInteger16)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%hu", buffer);
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger32: {
      let buffer = (CUnsignedInteger32)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%u", buffer);
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger64: {
      let buffer = 0ull;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%llu", buffer);
      break;
    }

    case kCoreFoundationNumberTypeUnsignedInteger: {
      let buffer = (CUnsignedInteger)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%lu", buffer);
      break;
    }

    case kCoreFoundationNumberTypeFloatingPoint32: {
      let buffer = (CFloatingPoint32)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%f", buffer);
      break;
    }

    case kCoreFoundationNumberTypeFloatingPoint64: {
      let buffer = 0.0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%lf", buffer);
      break;
    }

    case kCoreFoundationNumberTypeFloatingPoint: {
      let buffer = (CFloatingPoint)0;
      CoreFoundationNumberGetValue(number, &buffer);
      CIOPrintWithFormat("%lf", buffer);
      break;
    }
  }

  CIOPrintWithFormat("%s", terminator);

  CoreFoundationRelease(number);
}

void CoreFoundationIOPrintString(
  CoreFoundationString* string,
  CString terminator
) {
  CoreFoundationRetain(string);

  let count = CoreFoundationStringGetCount(string);

  let bufferCount = CoreFoundationStringGetCStringCount(string);
  let buffer = (CInteger8*)CMemoryAllocate(bufferCount + 1, sizeof(CInteger8));
  CoreFoundationStringCopyCString(string, buffer);

  CIOPrintWithFormat("%s%s", buffer, terminator);

  CMemoryDeallocate(buffer);

  CoreFoundationRelease(string);
}

C_ASSUME_NONNULL_END
