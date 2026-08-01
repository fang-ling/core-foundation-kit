// swift-tools-version: 6.3

//===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
//
//  Package.swift
//  core-foundation-kit
//
//  Created by Fang Ling on 2026/4/25.
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

import PackageDescription

let isDevelopment = false

let dependencies = [
  ("c-kit", "main")
]

let package = Package(
  name: "core-foundation-kit",
  products: [
    .library(name: "CoreFoundationKit", targets: ["CoreFoundationKit"])
  ],
  dependencies: dependencies.map { isDevelopment ? .package(path: "../\($0.0)") : .package(url: "https://github.com/fang-ling/\($0.0)", branch: $0.1) },
  targets: [
    .target(
      name: "CoreFoundationKit",
      dependencies: [
        .product(name: "CKit", package: "c-kit")
      ],
      publicHeadersPath: "Includes",
      cSettings: Context.environment["ONLINE_JUDGE"] != nil ? [.define("ONLINE_JUDGE")] : []
    ),
    .testTarget(
      name: "CoreFoundationKitTests",
      dependencies: [
        "CoreFoundationKit"
      ]
    )
  ],
  cLanguageStandard: .c89
)
