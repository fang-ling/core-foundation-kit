/*
 *  CoreFoundationGeometry.c
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

#include "CoreFoundationGeometry.h"

C_ASSUME_NONNULL_BEGIN

const CoreFoundationPoint CoreFoundationPointZero = (CoreFoundationPoint){ 0 };

const CoreFoundationSize CoreFoundationSizeZero = (CoreFoundationSize){ 0 };

const CoreFoundationRectangle CoreFoundationRectangleZero = (CoreFoundationRectangle){ 0 };

const CoreFoundationRectangle CoreFoundationRectangleNull = (CoreFoundationRectangle){ { CFloatingPointNaN, CFloatingPointNaN }, { CFloatingPointNaN, CFloatingPointNaN } };

CBoolean CoreFoundationPointEqual(
  CoreFoundationPoint lhs,
  CoreFoundationPoint rhs
) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

CBoolean CoreFoundationSizeEqual(
  CoreFoundationSize lhs,
  CoreFoundationSize rhs
) {
  return lhs.width == rhs.width && lhs.height == rhs.height;
}

CBoolean CoreFoundationRectangleEqual(
  CoreFoundationRectangle lhs,
  CoreFoundationRectangle rhs
) {
  return (
    CoreFoundationPointEqual(lhs.origin, rhs.origin) &&
    CoreFoundationSizeEqual(lhs.size, rhs.size)
  );
}

C_ASSUME_NONNULL_END
