//
//  CoreFoundationStringTests.swift
//  core-foundation-kit
//
//  Created by Fang Ling on 2026/5/1.
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

@Test("CoreFoundationStringTests")
func testCoreFoundationString() {
  let inputStrings = ["", "Hello, world!", "こんにち", "🌍", "🐮 say ", "ω"]

  for inputString in inputStrings {
    let string = CoreFoundationStringInitializeWithCString(inputString)!
    let count = CoreFoundationStringGetCount(string)
    let characters = UnsafeMutablePointer<CInteger32>.allocate(
      capacity: Int(count)
    )
    CoreFoundationStringCopyCharacters(string, characters)
    let inputCharacters = inputString.unicodeScalars.map {
      CInteger32($0.value)
    }
    let comparisonResult = memcmp(
      characters,
      inputCharacters,
      MemoryLayout<CInteger32>.size * Int(count)
    )

    #expect(comparisonResult == 0)
    #expect(count == inputCharacters.count)

    characters.deallocate()
    CoreFoundationRelease(UnsafeMutableRawPointer(string))
  }
}
