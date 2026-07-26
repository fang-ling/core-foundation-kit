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
  CFloatingPoint x;
  CFloatingPoint y;
} CoreFoundationPoint;

typedef struct CoreFoundationSize {
  CFloatingPoint width;
  CFloatingPoint height;
} CoreFoundationSize;

typedef struct CoreFoundationRectangle {
  CoreFoundationPoint origin;
  CoreFoundationSize size;
} CoreFoundationRectangle;

/**
 * A point constant with location `(0, 0)`.
 *
 * The zero point is equivalent to `CoreFoundationPointMake(0, 0)`.
 */
extern const CoreFoundationPoint CoreFoundationPointZero;

/**
 * A size constant with width and height of `0`.
 *
 * The zero size is equivalent to `CoreFoundationSizeMake(0, 0)`.
 */
extern const CoreFoundationSize CoreFoundationSizeZero;

/**
 * A rectangle constant with location `(0, 0)`, and width and height of `0`.
 */
extern const CoreFoundationRectangle CoreFoundationRectangleZero;

/**
 * The null rectangle, representing an invalid value.
 *
 * This is the rectangle returned when, for example, you intersect two disjoint rectangles.
 * Note that the null rectangle is not the same as the ``CoreFoundationRectangleZero`` rectangle.
 * For example, the union of a rectangle with the null rectangle is the original rectangle (that is, the null rectangle contributes nothing).
 */
extern const CoreFoundationRectangle CoreFoundationRectangleNull;

/**
 * Returns a point with the specified coordinates.
 *
 * - Parameters:
 *   - x: The x-coordinate of the point to construct.
 *   - y: The y-coordinate of the point to construct.
 *
 * - Returns: A point.
 */
#define CoreFoundationPointMake(x, y) \
  ((CoreFoundationPoint){ (x), (y) })

/**
 * Returns a size with the specified dimension values.
 *
 * - Parameters:
 *   - width: A width value.
 *   - height: A height value.
 *
 * - Returns: Returns a size structure with the specified width and height.
 */
#define CoreFoundationSizeMake(width, height) \
  ((CoreFoundationSize){ (width), (height) })

/**
 * Returns a rectangle with the specified coordinate and size values.
 *
 * - Parameters:
 *   - x: The x-coordinate of the rectangle's origin point.
 *   - y: The y-coordinate of the rectangle's origin point.
 *   - width: The width of the rectangle.
 *   - height: The height of the rectangle.
 *
 * - Returns: A rectangle with the specified location and dimensions.
 */
#define CoreFoundationRectangleMake(x, y, width, height) \
  ((CoreFoundationRectangle){ \
    .origin = (CoreFoundationPoint){ (x), (y) }, \
    .size = (CoreFoundationSize){ (width), (height) } })

CBoolean CoreFoundationPointEqual(
  CoreFoundationPoint lhs,
  CoreFoundationPoint rhs
);

CBoolean CoreFoundationSizeEqual(
  CoreFoundationSize lhs,
  CoreFoundationSize rhs
);

/**
 * Returns whether two rectangles are equal in size and position.
 *
 * - Parameters:
 *   - r1: The first rectangle to examine.
 *   - r2: The second rectangle to examine.
 *
 * - Returns: `yes` if the two specified rectangles have equal size and origin values, or if both rectangles are null rectangles.
 *   Otherwise, `no`.
 */
CBoolean CoreFoundationRectangleIsEqual(CoreFoundationRectangle r1, CoreFoundationRectangle r2);

/**
 * Returns whether a rectangle has zero width or height, or is a null rectangle.
 *
 * An empty rectangle is either a null rectangle or a valid rectangle with zero height or width.
 *
 * - Parameter rectangle: The rectangle to examine.
 *
 * - Returns: `yes` if the specified rectangle is empty; otherwise, `no`.
 */
CBoolean CoreFoundationRectangleIsEmpty(CoreFoundationRectangle rectangle);

/**
 * Returns the smallest rectangle that contains the two source rectangles.
 *
 * Both rectangles are standardized prior to calculating the union.
 * If either of the rectangles is a null rectangle, a copy of the other rectangle is returned (resulting in a null rectangle if both rectangles are null).
 * Otherwise a rectangle that completely contains the source rectangles is returned.
 *
 * - Parameters:
 *   - r1: The first source rectangle.
 *   - r2: The second source rectangle.
 *
 * - Returns: The smallest rectangle that completely contains both of the source rectangles.
 */
CoreFoundationRectangle CoreFoundationRectangleUnion(CoreFoundationRectangle r1, CoreFoundationRectangle r2);

/**
 * Returns whether two rectangles intersect.
 *
 * - Parameters:
 *   - r1: The first rectangle to examine.
 *   - r2: The second rectangle to examine.
 *
 * - Returns: `yes` if the two specified rectangles intersect; otherwise, `no`.
 *   The first rectangle intersects the second if the intersection of the rectangles is not equal to the null rectangle.
 */
CBoolean CoreFoundationRectangleIsIntersection(CoreFoundationRectangle r1, CoreFoundationRectangle r2);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationGeometry_h */
