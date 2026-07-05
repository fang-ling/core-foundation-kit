/*
 *  CoreFoundationRedBlackTree.h
 *  core-foundation-kit
 *
 *  Created by Fang Ling on 2026/6/27.
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

#ifndef CoreFoundationRedBlackTree_h
#define CoreFoundationRedBlackTree_h

#include "../Sorting/CoreFoundationComparisonResult.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

typedef enum _CoreFoundationRedBlackTreeNodeColor {
  _kCoreFoundationRedBlackTreeNodeColorRed,
  _kCoreFoundationRedBlackTreeNodeColorBlack
} _CoreFoundationRedBlackTreeNodeColor;

typedef struct _CoreFoundationRedBlackTreeNode {
  void* key;

  struct _CoreFoundationRedBlackTreeNode* nonnil children[2];

  struct _CoreFoundationRedBlackTreeNode* parent;

  /* Duplicate element count for the key. */
  CInteger count;

  /* Subtree size */
  CInteger size;

  _CoreFoundationRedBlackTreeNodeColor color;
} _CoreFoundationRedBlackTreeNode;

typedef struct _CoreFoundationRedBlackTree {
  _CoreFoundationRedBlackTreeNode* root;
  _CoreFoundationRedBlackTreeNode* sentinel;

  CInteger keySize;

  CInteger count;

  CoreFoundationComparisonResult (*compare)(const void* lhs, const void* rhs);
} _CoreFoundationRedBlackTree;

_CoreFoundationRedBlackTree* _CoreFoundationRedBlackTreeInitialize(
  CInteger keySize,
  CoreFoundationComparisonResult (*compare)(const void* lhs, const void* rhs)
);

void _CoreFoundationRedBlackTreeDeinitialize(_CoreFoundationRedBlackTree* tree);

void _CoreFoundationRedBlackTreeInsertKey(
  _CoreFoundationRedBlackTree* tree,
  const void* key
);

void _CoreFoundationRedBlackTreeRemoveKey(
  _CoreFoundationRedBlackTree* tree,
  const void* key
);

CBoolean _CoreFoundationRedBlackTreeContainsKey(
  _CoreFoundationRedBlackTree* tree,
  void* key
);

void _CoreFoundationRedBlackTreeGetKey(
  _CoreFoundationRedBlackTree* tree,
  void* key,
  void* result
);

void _CoreFoundationRedBlackTreeGetKeyAtIndex(
  _CoreFoundationRedBlackTree* tree,
  CInteger index,
  void* result
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationRedBlackTree_h */
