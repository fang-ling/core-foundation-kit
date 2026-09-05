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

clang-format --dry-run -Werror \
             "Sources/CoreFoundationKit/Values and Collections/Basic Values/Ranges/CoreFoundationRange.h" \
             "Sources/CoreFoundationKit/Values and Collections/Basic Values/Ranges/CoreFoundationRange.c" \
             "Sources/CoreFoundationKit/Values and Collections/Collections/Arrays and Dictionaries/CoreFoundationArray.h" \
             "Sources/CoreFoundationKit/Values and Collections/Collections/Arrays and Dictionaries/CoreFoundationArray.c" \
             "Sources/CoreFoundationKit/Values and Collections/Strings and Text/Strings and Characters/CoreFoundationString.h" \
             "Sources/CoreFoundationKit/Values and Collections/Strings and Text/Strings and Characters/CoreFoundationString.c"

swift-format lint . --parallel --recursive --strict
