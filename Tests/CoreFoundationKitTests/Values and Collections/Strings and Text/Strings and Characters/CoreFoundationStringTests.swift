//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
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
//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//

import CoreFoundationKit

import Testing

@Suite("CoreFoundationStringTests")
struct CoreFoundationStringTests {
  let strings = [
    "", "Hello, world!", "こんにちは!", "Heil!", "Γεια σου, κόσμε!", "你好，世界！", "👋, 🌍!",
    "Japan", "Ιαπωνία", "日本国", "🇯🇵"
  ]

  @Test func testGettingCount() {
    for input in strings {
      #expect(CoreFoundationString(cString: input).count == input.utf8.count)
    }
  }

  @Test func testGettingUTF8CodeUnitAtIndex() {
    for input in strings {
      let string = CoreFoundationString(cString: input)

      var index = 0
      for codeUnit in input.utf8 {
        #expect(string.utf8CodeUnit(at: index) == CInteger8(bitPattern: codeUnit))

        index += 1
      }
    }
  }
}
