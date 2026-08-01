//===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
//
//  CoreFoundationStringTests.swift
//  core-foundation-kit
//
//  Created by Fang Ling on 2026/8/1.
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
//===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//

import CoreFoundationKit

import Testing

@Suite("CoreFoundationStringTests")
struct CoreFoundationStringTests {
  let strings = ["", "Hello, world!", "こんにちは!", "Heil!", "Γεια σου, κόσμε!", "你好，世界！", "👋, 🌍!"]

  @Test func testGettingCount() {
    for input in strings {
      #expect(CoreFoundationString(characters: input.unicodeScalars.map { CUnsignedInteger32($0) }, count: input.count).count == input.count)
    }
  }

  @Test func testGettingCharacterAtIndex() {
    for input in strings {
      let string = CoreFoundationString(characters: input.unicodeScalars.map { CUnsignedInteger32($0) }, count: input.count)

      var index = 0
      for scalar in input.unicodeScalars {
        #expect(string.character(at: index) == scalar.value)

        index += 1
      }
    }
  }
}
