//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
//
//  CoreFoundationArrayTests.swift
//  core-foundation-kit
//
//  Created by Fang Ling on 2026/8/9.
//
//  This source file is part of the CoreFoundationKit open source project
//
//  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
//  Licensed under Apache License v2.0
//
//  See LICENSE for license information
//
//  SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//

import CoreFoundationKit

import Testing

@Suite("CoreFoundationArrayTests")
struct CoreFoundationArrayTests {
  @Test func testGettingCount() {
    var array = CoreFoundationArray(objects: nil, count: 0, isMutable: true)
    #expect(array.count == 0)

    let cats = [Cat(), Cat(), Cat()]
    array = CoreFoundationArray(objects: cats.map { Swift::UnsafeRawPointer(Swift::Unmanaged<Cat>.passUnretained($0).toOpaque()) }, count: 3, isMutable: false)
    #expect(array.count == 3)
  }

  @Test func testGettingObjectAtIndex() {
    let cats = [Cat(name: "Alice"), Cat(name: "Tracy"), Cat(name: "Diana")]
    let array = CoreFoundationArray(objects: cats.map { Swift::UnsafeRawPointer(Swift::Unmanaged<Cat>.passUnretained($0).toOpaque()) }, count: 3, isMutable: false)

    for index in cats.indices {
      let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: index)).takeUnretainedValue()
      #expect(cat.name == cats[index].name)
    }
  }
}

extension CoreFoundationArrayTests {
  class Cat {
    var name: Swift::String?

    init(name: Swift::String? = nil) {
      self.name = name
    }
  }
}
