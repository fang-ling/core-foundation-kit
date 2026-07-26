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

CBoolean CoreFoundationRectangleIsEqual(
  CoreFoundationRectangle lhs,
  CoreFoundationRectangle rhs
) {
  return (
    CoreFoundationPointEqual(lhs.origin, rhs.origin) &&
    CoreFoundationSizeEqual(lhs.size, rhs.size)
  );
}

CBoolean CoreFoundationRectangleIsNull(CoreFoundationRectangle rectangle) {
  return CNumberIsNaN(rectangle.origin.x) || CNumberIsNaN(rectangle.origin.y) || CNumberIsNaN(rectangle.size.width) || CNumberIsNaN(rectangle.size.height);
}

CBoolean CoreFoundationRectangleIsEmpty(CoreFoundationRectangle rectangle) {
  if (CoreFoundationRectangleIsNull(rectangle)) {
    return yes;
  }

  return rectangle.size.width == 0 || rectangle.size.height == 0;
}

CoreFoundationRectangle CoreFoundationRectangleStandardize(CoreFoundationRectangle rectangle) {
  if (rectangle.size.width < 0) {
    rectangle.origin.x += rectangle.size.width;
    rectangle.size.width = -rectangle.size.width;
  }
  if (rectangle.size.height < 0) {
    rectangle.origin.y += rectangle.size.height;
    rectangle.size.height = -rectangle.size.height;
  }

  return rectangle;
}

CoreFoundationRectangle CoreFoundationRectangleUnion(CoreFoundationRectangle r1, CoreFoundationRectangle r2) {
  let rectangle = CoreFoundationRectangleZero;

  /* If both of them are empty we can return r2 as an empty rect, so this covers all cases. */
  if (CoreFoundationRectangleIsEmpty(r1)) {
    return r2;
  } else if (CoreFoundationRectangleIsEmpty(r2)) {
    return r1;
  }

  r1 = CoreFoundationRectangleStandardize(r1);
  r2 = CoreFoundationRectangleStandardize(r2);
  rectangle.origin.x = CNumberFindMinimum(r1.origin.x, r2.origin.x);
  rectangle.origin.y = CNumberFindMinimum(r1.origin.y, r2.origin.y);
  rectangle.size.width = CNumberFindMaximum(r1.origin.x + r1.size.width, r2.origin.x + r2.size.width);
  rectangle.size.height = CNumberFindMaximum(r1.origin.y + r1.size.height, r2.origin.y + r2.size.height);

  return rectangle;
}

CoreFoundationRectangle CoreFoundationRectangleIntersect(CoreFoundationRectangle r1, CoreFoundationRectangle r2) {
  let rectangle = CoreFoundationRectangleZero;

  /* If both of them are empty we can return r2 as an empty rect, so this covers all cases. */
  if (CoreFoundationRectangleIsEmpty(r1)) {
    return r2;
  } else if (CoreFoundationRectangleIsEmpty(r2)) {
    return r1;
  }

  r1 = CoreFoundationRectangleStandardize(r1);
  r2 = CoreFoundationRectangleStandardize(r2);

  if (
    r1.origin.x + r1.size.width <= r2.origin.x ||
    r2.origin.x + r2.size.width <= r1.origin.x ||
    r1.origin.y + r1.size.height <= r2.origin.y ||
    r2.origin.y + r2.size.height <= r1.origin.y
  ) {
    return CoreFoundationRectangleNull;
  }

  rectangle.origin.x = (r1.origin.x > r2.origin.x ? r1.origin.x : r2.origin.x);
  rectangle.origin.y = (r1.origin.y > r2.origin.y ? r1.origin.y : r2.origin.y);

  if (r1.origin.x + r1.size.width < r2.origin.x + r2.size.width) {
    rectangle.size.width = r1.origin.x + r1.size.width - rectangle.origin.x;
  } else {
    rectangle.size.width = r2.origin.x + r2.size.width - rectangle.origin.x;
  }

  if (r1.origin.y + r1.size.height < r2.origin.y + r2.size.height) {
    rectangle.size.height = r1.origin.y + r1.size.height - rectangle.origin.y;
  } else {
    rectangle.size.height = r2.origin.y + r2.size.height - rectangle.origin.y;
  }

  return rectangle;
}

CBoolean CoreFoundationRectangleIsIntersection(CoreFoundationRectangle r1, CoreFoundationRectangle r2) {
  return !CoreFoundationRectangleIsNull(CoreFoundationRectangleIntersect(r1, r2));
}

C_ASSUME_NONNULL_END
