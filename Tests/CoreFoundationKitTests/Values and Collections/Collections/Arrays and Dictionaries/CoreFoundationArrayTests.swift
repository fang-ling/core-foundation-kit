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
  @Test func testCopying() {
    var cats = [Cat(name: "Alice"), Cat(name: "Tracy"), Cat(name: "Diana")]
    let array = CoreFoundationArray(objects: cats.map { Swift::Unmanaged<Cat>.passUnretained($0).toOpaque() }, count: 3)
    let copiedArray = array.copy()
    #expect(copiedArray.count == array.count)

    for index in cats.indices {
      let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: index)).takeUnretainedValue()
      let copiedCat = Swift::Unmanaged<Cat>.fromOpaque(copiedArray.object(at: index)).takeUnretainedValue()
      #expect(cat.name == cats[index].name)
      #expect(copiedCat.name == cats[index].name)
    }

    cats[2] = Cat(name: "Clara")
    copiedArray.setObject(Swift::Unmanaged<Cat>.passUnretained(cats[2]).toOpaque(), at: 2)
    let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: 2)).takeUnretainedValue()
    let copiedCat = Swift::Unmanaged<Cat>.fromOpaque(copiedArray.object(at: 2)).takeUnretainedValue()
    #expect(cat.name != copiedCat.name)
    #expect(copiedCat.name == "Clara")
  }

  @Test func testGettingCount() {
    var array = CoreFoundationArray(objects: nil, count: 0)
    #expect(array.count == 0)

    let cats = [Cat(), Cat(), Cat()]
    array = CoreFoundationArray(objects: cats.map { Swift::Unmanaged<Cat>.passUnretained($0).toOpaque() }, count: 3)
    #expect(array.count == cats.count)
  }

  @Test func testGettingObjectAtIndex() async {
    let cats = [Cat(name: "Alice"), Cat(name: "Tracy"), Cat(name: "Diana")]
    let array = CoreFoundationArray(objects: cats.map { Swift::Unmanaged<Cat>.passUnretained($0).toOpaque() }, count: 3)

    for index in cats.indices {
      let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: index)).takeUnretainedValue()
      #expect(cat.name == cats[index].name)
    }

    await #expect(processExitsWith: .failure) {
      let emptyArray = CoreFoundationArray(objects: nil, count: 0)
      emptyArray.object(at: 19358)
    }
  }

  @Test func testSettingObjectAtIndex() async {
    var cats = [Cat(name: "Alice"), Cat(name: "Tracy"), Cat(name: "Diana")]
    let array = CoreFoundationArray(objects: cats.map { Swift::Unmanaged<Cat>.passUnretained($0).toOpaque() }, count: 3)

    cats[2] = Cat(name: "Clara")
    array.setObject(Swift::Unmanaged<Cat>.passUnretained(cats[2]).toOpaque(), at: 2)

    for index in cats.indices {
      let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: index)).takeUnretainedValue()
      #expect(cat.name == cats[index].name)
    }

    await #expect(processExitsWith: .failure) {
      let emptyArray = CoreFoundationArray(objects: nil, count: 0)
      emptyArray.setObject(Swift::Unmanaged<Cat>.passUnretained(Cat(name: "Ruby")).toOpaque(), at: 19358)
    }
  }

  @Test func testReplacingSubrangeWithObjects() {
    // Pure append to an empty array.
    var cats = [Cat(name: "Alice"), Cat(name: "Tracy"), Cat(name: "Diana")]
    let array = CoreFoundationArray(objects: nil, count: 0)
    array.replaceSubrange(CoreFoundationRange(location: 0, count: 0), with: cats.map { Swift::Unmanaged<Cat>.passUnretained($0).toOpaque() }, 3)

    for index in cats.indices {
      let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: index)).takeUnretainedValue()
      #expect(cat.name == cats[index].name)
    }
    #expect(cats.count == array.count)

    // Insert in the middle, growing the array.
    cats.insert(contentsOf: [Cat(name: "Laura"), Cat(name: "Clara"), Cat(name: "Ruby"), Cat(name: "Eva"), Cat(name: "Sue")], at: 1)
    array.replaceSubrange(CoreFoundationRange(location: 1, count: 0), with: cats[1 ... 5].map { Swift::Unmanaged<Cat>.passUnretained($0).toOpaque() }, 5)

    for index in cats.indices {
      let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: index)).takeUnretainedValue()
      #expect(cat.name == cats[index].name)
    }
    #expect(cats.count == array.count)

    // Remove from the middle.
    cats.removeSubrange(3 ..< 6)
    array.replaceSubrange(CoreFoundationRange(location: 3, count: 3), with: nil, 0)

    for index in cats.indices {
      let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: index)).takeUnretainedValue()
      #expect(cat.name == cats[index].name)
    }
    #expect(cats.count == array.count)

    // Replace with equal count.
    cats.replaceSubrange(0 ..< 3, with: [Cat(name: "Grace"), Cat(name: "Anna"), Cat(name: "Rachel")])
    array.replaceSubrange(CoreFoundationRange(location: 0, count: 3), with: cats[0 ..< 3].map { Swift::Unmanaged<Cat>.passUnretained($0).toOpaque() }, 3)

    for index in cats.indices {
      let cat = Swift::Unmanaged<Cat>.fromOpaque(array.object(at: index)).takeUnretainedValue()
      #expect(cat.name == cats[index].name)
    }
    #expect(cats.count == array.count)

    // Remove everything.
    cats.removeAll()
    array.replaceSubrange(CoreFoundationRange(location: 0, count: array.count), with: nil, 0)
    #expect(cats.count == array.count)
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
