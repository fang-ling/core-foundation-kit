//
//  CoreFoundationArrayTests.swift
//  core-foundation-kit
//
//  Created by Fang Ling on 2026/5/2.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

import Testing

import CoreFoundationKit

@Test("CoreFoundationArrayTests")
func testCoreFoundationArray() {
  var array = CoreFoundationArrayInitialize()
  #expect(CoreFoundationArrayGetCount(array) == 0)
  CoreFoundationRelease(UnsafeMutableRawPointer(array))

  array = CoreFoundationArrayInitialize()
  var cat = CoreFoundationStringInitializeWithCString("Alice")!
  CoreFoundationMutableArrayAppendObject(array, UnsafeMutableRawPointer(cat))
  CoreFoundationRelease(UnsafeMutableRawPointer(cat))
  #expect(CoreFoundationArrayGetCount(array) == 1)
  cat = OpaquePointer(CoreFoundationArrayGetObjectAtIndex(array, 0))
  var newCat = CoreFoundationStringInitializeWithCString("Alice")!
  #expect(
    CoreFoundationStringCompare(
      newCat,
      cat
    ) == kCoreFoundationComparisonResultSameOrder
  )
  CoreFoundationRelease(UnsafeMutableRawPointer(newCat))

  cat = CoreFoundationStringInitializeWithCString("Tracy")!
  CoreFoundationMutableArrayAppendObject(array, UnsafeMutableRawPointer(cat))
  CoreFoundationRelease(UnsafeMutableRawPointer(cat))
  #expect(CoreFoundationArrayGetCount(array) == 2)
  cat = OpaquePointer(CoreFoundationArrayGetObjectAtIndex(array, 1))
  newCat = CoreFoundationStringInitializeWithCString("Tracy")!
  #expect(
    CoreFoundationStringCompare(
      newCat,
      cat
    ) == kCoreFoundationComparisonResultSameOrder
  )
  CoreFoundationRelease(UnsafeMutableRawPointer(newCat))

  CoreFoundationMutableArrayRemoveLastObject(array)
  #expect(CoreFoundationArrayGetCount(array) == 1)
  cat = OpaquePointer(CoreFoundationArrayGetObjectAtIndex(array, 0))
  newCat = CoreFoundationStringInitializeWithCString("Alice")!
  #expect(
    CoreFoundationStringCompare(
      newCat,
      cat
    ) == kCoreFoundationComparisonResultSameOrder
  )
  CoreFoundationRelease(UnsafeMutableRawPointer(newCat))

  CoreFoundationMutableArrayRemoveLastObject(array)
  #expect(CoreFoundationArrayGetCount(array) == 0)

  CoreFoundationRelease(UnsafeMutableRawPointer(array))
}
