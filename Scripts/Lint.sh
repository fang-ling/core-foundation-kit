#!/bin/bash

##===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===##
##
##  Lint.sh
##  core-foundation-kit
##
##  Created by Fang Ling on 2026/8/22.
##
##  This file is part of the CoreFoundationKit open source project
##
##  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
##  Licensed under Apache License v2.0
##
##  See LICENSE for license information
##
##  SPDX-License-Identifier: Apache-2.0
##
##===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===##

clang-format --dry-run -Werror Sources/CoreFoundationKit/Collections/CoreFoundationArray.h Sources/CoreFoundationKit/Collections/CoreFoundationArray.c

swift-format lint . --parallel --recursive --strict
