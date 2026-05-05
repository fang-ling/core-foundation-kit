/*
 *  CoreFoundationGeometry.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/5/3.
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

#ifndef CoreFoundationGeometry_h
#define CoreFoundationGeometry_h

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

typedef struct CoreFoundationPoint {
  CFloatingPoint64 x;
  CFloatingPoint64 y;
} CoreFoundationPoint;

typedef struct CoreFoundationSize {
  CFloatingPoint64 width;
  CFloatingPoint64 height;
} CoreFoundationSize;

typedef struct CoreFoundationRectangle {
  CoreFoundationPoint origin;
  CoreFoundationSize size;
} CoreFoundationRectangle;

CBoolean CoreFoundationPointEqual(
  CoreFoundationPoint lhs,
  CoreFoundationPoint rhs
);

CBoolean CoreFoundationSizeEqual(
  CoreFoundationSize lhs,
  CoreFoundationSize rhs
);

CBoolean CoreFoundationRectangleEqual(
  CoreFoundationRectangle lhs,
  CoreFoundationRectangle rhs
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationGeometry_h */
