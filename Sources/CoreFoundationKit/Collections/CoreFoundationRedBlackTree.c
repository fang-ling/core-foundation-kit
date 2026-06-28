/*
 *  CoreFoundationRedBlackTree.c
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

#include "CoreFoundationRedBlackTree.h"

C_ASSUME_NONNULL_BEGIN

_CoreFoundationRedBlackTreeNode* _CoreFoundationRedBlackTreeNodeInitialize(
  const void* nillable key,
  CInteger keySize,
  CInteger size,
  CInteger count,
  _CoreFoundationRedBlackTreeNode* nillable left,
  _CoreFoundationRedBlackTreeNode* nillable right,
  _CoreFoundationRedBlackTreeNode* nillable parent,
  _CoreFoundationRedBlackTreeNodeColor color
) {
  let node = (_CoreFoundationRedBlackTreeNode*)CMemoryAllocate(
    sizeof(_CoreFoundationRedBlackTreeNode)
  );

  node->children[0] = left;
  node->children[1] = right;
  node->parent = parent;
  node->color = color;
  node->count = count;
  node->size = size;

  node->key = CMemoryAllocate(keySize);
  if (key) {
    CMemoryCopy(node->key, key, keySize);
  }

  return node;
}

void _CoreFoundationRedBlackTreeNodeDeinitialize(
  _CoreFoundationRedBlackTreeNode* node
) {
  CMemoryDeallocate(node->key);
  CMemoryDeallocate(node);
}

/*
 * Rotation: Modify tree structure without breaking binary search tree property,
 * i.e. x.left.key < x.key < x.right.key.
 *
 *        |                               |
 *       [y]       left_rotate(x)        [x]
 *      /   \      <--------------      /   \
 *    [x]    c                         a    [y]
 *   /   \         -------------->         /   \
 *  a     b        right_rotate(y)        b     c
 */
void _CoreFoundationRedBlackTreeRotate(
  _CoreFoundationRedBlackTree* tree,
  _CoreFoundationRedBlackTreeNode* x,
  CInteger isRightChild
) {
  let y = x->children[isRightChild ^ 1];
  x->children[isRightChild ^ 1] = y->children[isRightChild];

  if (y->children[isRightChild] != tree->sentinel) {
    y->children[isRightChild]->parent = x;
  }

  y->parent = x->parent;
  if (x->parent == tree->sentinel) {
    tree->root = y;
  } else {
    x->parent->children[x == x->parent->children[1] ? 1 : 0] = y;
  }

  y->children[isRightChild] = x;
  x->parent = y;

  /* Maintain augmented data. */
  y->size = x->size;
  x->size = x->children[0]->size + x->children[1]->size + x->count;
}

/*
 * Maintain the red black tree property violated by insertion.
 *
 * Case 1: z's uncle y is red, {[A]: red node, (A): black node}
 *
 *           |                                   |
 *          (C)                                 [z] <--~ {new z}
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           / _old z\
 *      /         \                         / /       \
 *    [A]         [y]    ------------>    (A) |       (y)
 *   /   \       /   \                   /   \|      /   \
 *  a    [z]    d     e                 a    [z]    d     e
 *      /   \                               /   \
 *     b     c                             b     c
 *
 * Because z.p.p (in here: C) is black, we can color both z.p (A) and y black,
 * thereby fixing the problem of z and z.p (A) both being red, and we can color
 * z.p.p (C) red, thereby maintaining property 5. We then repeat the while loop
 * with z.p.p (C) as the new node z. The pointer z moves up two levels in the
 * tree.
 *
 * Case 2: z's uncle y is black, and z is a right child.
 * Case 3: z's uncle y is black, and z is a left child.
 *
 *           |                                  |
 *          (C)                                (C)
 *         /   \                              /   \
 *        /     \       left-rotate(A)       /     \
 *       /       \      ------------->      /       \
 *      /         \                        /         \
 *    [A]          d y                   [B]          d y
 *   /   \                              /   \
 *  a    [B]z                         [A]z   c
 *      /   \                        /   \
 *     b     c                      a     b
 *              Case 2                        Case 3
 *
 *                                              |
 *                              right-rotate(C) |
 *                                              |
 *                                              V
 *
 *                                              |
 *                                             (C)
 *                                            /   \
 *                                           /     \
 *                                          /       \
 *                                         /         \
 *                                       [A]         [B]
 *                                      /   \       /   \
 *                                     a     b     c     d
 *
 * In case 2 and 3, the color of z's uncle y is black. We distinguish the two
 * cases according to whether z is a right or left child of z.p. In case 2,
 * node z is a right child of its parent. We immediately use a left rotation
 * to transform the situation into case 3, in which node z is a left child.
 * Because both z and z.p are red, the rotation affects neither the black-
 * height of nodes nor property 5. Whether we enter case 3 directly or through
 * case 2, z's uncle y is black, since otherwise we would have executed case 1.
 * Additionally, the node z.p.p exists. In case 3, we execute some color
 * changes and a right rotation, which preserve property 5, and then, since we
 * no longer have two red nodes in a row, we are done. The while loop does not
 * iterate another time, since z.p is now black.
 */
void _CoreFoundationRedBlackTreeFixInsertion(
  _CoreFoundationRedBlackTree* tree,
  _CoreFoundationRedBlackTreeNode* node
) {
  let z = node;
  let isLeftChild = 0l;
  while (z->parent->color == _kCoreFoundationRedBlackTreeNodeColorRed) {
    let parent = z->parent;
    let grandparent = parent->parent;
    isLeftChild = parent == grandparent->children[0] ? 1 : 0;
    let y = grandparent->children[isLeftChild];
    if (y->color == _kCoreFoundationRedBlackTreeNodeColorRed) { /* Case 1 */
      y->color = _kCoreFoundationRedBlackTreeNodeColorBlack;
      parent->color = _kCoreFoundationRedBlackTreeNodeColorBlack;
      grandparent->color = _kCoreFoundationRedBlackTreeNodeColorRed;
      z = grandparent;
    } else {
      if (z == parent->children[isLeftChild]) { /* Case 2 */
        z = parent;
        _CoreFoundationRedBlackTreeRotate(tree, z, isLeftChild ^ 1);
      }
      /* Case 3 */
      z->parent->color = _kCoreFoundationRedBlackTreeNodeColorBlack;
      z->parent->parent->color = _kCoreFoundationRedBlackTreeNodeColorRed;
      _CoreFoundationRedBlackTreeRotate(tree, grandparent, isLeftChild);
    }
  }

  tree->root->color = _kCoreFoundationRedBlackTreeNodeColorBlack;
}

/*
 * Replaces one subtree as a child of its parent with another subtree.
 * When transplant(tree, u, v) replaces the subtree rooted at node u with the
 * subtree rooted at node v, node u's parent becomes node v's parent, and u's
 * parent ends up having v as its appropriate child.
 */
void _CoreFoundationRedBlackTreeTransplant(
  _CoreFoundationRedBlackTree* tree,
  _CoreFoundationRedBlackTreeNode* u,
  _CoreFoundationRedBlackTreeNode* v
) {
  if (u->parent == tree->sentinel){
    tree->root = v;
  } else {
    u->parent->children[(u == u->parent->children[0]) ? 0 : 1] = v;
  }

  v->parent = u->parent;
}

_CoreFoundationRedBlackTreeNode* _CoreFoundationRedBlackTreeFindMinimum(
  _CoreFoundationRedBlackTree* tree,
  _CoreFoundationRedBlackTreeNode* x
) {
  while (x->children[0] != tree->sentinel) {
    x = x->children[0];
  }

  return x;
}

_CoreFoundationRedBlackTreeNode* _CoreFoundationRedBlackTreeFindMaximum(
  _CoreFoundationRedBlackTree* tree,
  _CoreFoundationRedBlackTreeNode* x
) {
  while (x->children[1] != tree->sentinel) {
    x = x->children[1];
  }

  return x;
}

/*
 * Maintain the red black tree property violated by removal.
 *
 * Case 1: x's sibling w is red, {[A]: red node, (A): black node}
 *
 *           |                                   |
 *          (B)                                 (D)
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           /       \
 *      /         \ w                       /         \
 *  x (A)         [D]    ------------>    [B]         (E)
 *   /   \       /   \                   /   \new w  /   \
 *  a     b    (C)   (E)             x (A)   (C)    e     f
 *             / \   / \               / \   / \
 *            c   d e   f             a   b c   d
 *
 * Since w must have black children, we can switch the colors of w and x.p and
 * then perform a left-rotation on x.p without violating any of the red-black
 * properties. The new sibling of x, which is one of w's children prior to the
 * rotation, is now black, and thus we have converted case 1 into case 2, 3, or
 * 4.
 *
 * Case 2: x's sibling w is black, and both of w's children are black
 *
 *           |                                   | new x
 *         [(B)]                              c[(B)]
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           /       \
 *      /         \ w                       /         \
 *  x (A)         (D)    ------------>    (A)         [D]
 *   /   \       /   \                   /   \       /   \
 *  a     b    (C)   (E)                a     b    (C)   (E)
 *             / \   / \                           / \   / \
 *            c   d e   f                         c   d e   f
 *
 * Since w is also black, we take one black off both x and w, leaving x with
 * only one black and leaving w red. To compensate for removing one black from
 * x and w, we would like to add an extra black to x.p, which originally either
 * red or black. We do so by repeating the while loop with x.p as the new node
 * x.
 *
 * Case 3: x's sibling w is black, w's left child is red, and w's right child
 * is black
 *
 *           |                                   |
 *       c [(B)]                              c[(B)]
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           /       \
 *      /         \ w                       /         \ new w
 *  x (A)         (D)    ------------>  x (A)         (C)
 *   /   \       /   \                   /   \       /   \
 *  a     b    [C]   (E)                a     b     c    [D]
 *             / \   / \                                 / \
 *            c   d e   f                               d  (E)
 *                                                         / \
 *                                                        e   f
 *
 * We can switch the colors of w and its left child w.left and then perform a
 * right rotation on w without violating any of the red-black properties. The
 * new sibling w of x is now a black node with a red right child, and thus we
 * have transformed case 3 into case 4.
 *
 * Case 4: x's sibling w is black, and w's right child is red
 *
 *           |                                   |
 *       c [(B)]                              c[(D)]
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           /       \
 *      /         \ w                       /         \
 *  x (A)         (D)    ------------>    (B)         (E)
 *   /   \    c' /   \                   /   \  c'   /   \
 *  a     b   [(C)]  [E]               (A)  [(C)]    e     f
 *             / \   / \               / \   / \
 *            c   d e   f             a   b c   d    new x = T.root
 *
 * By making some color changes and performing a left rotation on x.p, we can
 * remove the extra black on x, making it singly black, without violating any
 * of the red-black properties. Setting x to be the root causes the while loop
 * to terminate when it tests the loop condition.
 */

void _CoreFoundationRedBlackTreeFixDeletion(
  _CoreFoundationRedBlackTree* tree,
  _CoreFoundationRedBlackTreeNode* node
) {
  let x = node;

  while (
    x != tree->root &&
    x->color == _kCoreFoundationRedBlackTreeNodeColorBlack
  ) {
    let parent = x->parent;
    let isLeftChild = x == x->parent->children[0] ? 1 : 0;
    let w = parent->children[isLeftChild];

    if (w->color == _kCoreFoundationRedBlackTreeNodeColorRed) { /* Case 1 */
      parent->color = _kCoreFoundationRedBlackTreeNodeColorRed;
      w->color = _kCoreFoundationRedBlackTreeNodeColorBlack;
      _CoreFoundationRedBlackTreeRotate(tree, parent, isLeftChild ^ 1);
      w = parent->children[isLeftChild];
    }

    if (
      w->children[0]->color == _kCoreFoundationRedBlackTreeNodeColorBlack &&
      w->children[1]->color == _kCoreFoundationRedBlackTreeNodeColorBlack
    ) { /* Case 2 */
      w->color = _kCoreFoundationRedBlackTreeNodeColorRed;
      x = x->parent;
    } else {
      let color = w->children[isLeftChild]->color;
      if (color == _kCoreFoundationRedBlackTreeNodeColorBlack) { /* Case 3 */
        w->color = _kCoreFoundationRedBlackTreeNodeColorRed;
        w->children[isLeftChild ^ 1]->color =
          _kCoreFoundationRedBlackTreeNodeColorBlack;
        _CoreFoundationRedBlackTreeRotate(tree, w, isLeftChild);
        w = parent->children[isLeftChild];
      }

      /* Case 4 */
      w->color = parent->color;
      parent->color = _kCoreFoundationRedBlackTreeNodeColorBlack;
      w->children[isLeftChild]->color =
        _kCoreFoundationRedBlackTreeNodeColorBlack;
      _CoreFoundationRedBlackTreeRotate(tree, w->parent, isLeftChild ^ 1);
      x = tree->root;
    }
  }

  x->color = _kCoreFoundationRedBlackTreeNodeColorBlack;
}

void __CoreFoundationRedBlackTreeDeinitialize(
  _CoreFoundationRedBlackTree* tree,
  _CoreFoundationRedBlackTreeNode* node
) {
  if (node != tree->sentinel) {
    __CoreFoundationRedBlackTreeDeinitialize(tree, node->children[0]);
    __CoreFoundationRedBlackTreeDeinitialize(tree, node->children[1]);
    _CoreFoundationRedBlackTreeNodeDeinitialize(node);
  }
}

_CoreFoundationRedBlackTree* _CoreFoundationRedBlackTreeInitialize(
  CInteger keySize,
  CoreFoundationComparisonResult (*compare)(const void* lhs, const void* rhs)
) {
  let tree = (_CoreFoundationRedBlackTree*)CMemoryAllocate(
    sizeof(_CoreFoundationRedBlackTree)
  );

  tree->keySize = keySize;
  tree->count = 0;
  tree->compare = compare;

  tree->sentinel = _CoreFoundationRedBlackTreeNodeInitialize(
    null,
    keySize,
    0,
    0,
    null,
    null,
    null,
    _kCoreFoundationRedBlackTreeNodeColorBlack
  );

  tree->root = tree->sentinel;
  tree->root->parent = tree->sentinel;

  return tree;
}

void _CoreFoundationRedBlackTreeDeinitialize(
  _CoreFoundationRedBlackTree* tree
) {
  __CoreFoundationRedBlackTreeDeinitialize(tree, tree->root);
  _CoreFoundationRedBlackTreeNodeDeinitialize(tree->sentinel);

  CMemoryDeallocate(tree);
}

void _CoreFoundationRedBlackTreeInsertKey(
  _CoreFoundationRedBlackTree* tree,
  const void* key
) {
  /*
   * This works by creating a new red node with the key to where it belongs
   * in the tree, using binary search and then fix red black tree property.
   */
  let x = tree->root;
  let y = tree->sentinel;
  let z = _CoreFoundationRedBlackTreeNodeInitialize(
    key,
    tree->keySize,
    1,
    1,
    tree->sentinel,
    tree->sentinel,
    tree->sentinel,
    _kCoreFoundationRedBlackTreeNodeColorRed
  );

  while (x != tree->sentinel) { /* Find the position to insert */
    y = x;
    y->size += 1;

    /* If exists, add `count` by 1. */
    if (
      tree->compare(x->key, key) == kCoreFoundationComparisonResultSameOrder
    ) {
      x->count += 1;
      tree->count += 1;

      return;
    }

    let comparisonResult = tree->compare(y->key, key);
    let childIndex =
      comparisonResult == kCoreFoundationComparisonResultAscendingOrder ? 1 : 0;
    x = x->children[childIndex];
  }

  z->parent = y;
  if (y == tree->sentinel) {
    tree->root = z;
  } else {
    let comparisonResult = tree->compare(y->key, key);
    let childIndex =
      comparisonResult == kCoreFoundationComparisonResultAscendingOrder ? 1 : 0;
    y->children[childIndex] = z;
  }

  _CoreFoundationRedBlackTreeFixInsertion(tree, z);

  tree->count += 1;
}

void _CoreFoundationRedBlackTreeRemoveKey(
  _CoreFoundationRedBlackTree* tree,
  const void* key
) {
  let z = tree->root;
  let w = tree->sentinel;

  while (z != tree->sentinel) { /* Find a node z with the specific key. */
    w = z;
    w->size -= 1;

    let comparisonResult = tree->compare(z->key, key);
    if (comparisonResult == kCoreFoundationComparisonResultSameOrder) {
      break;
    }

    let childIndex =
      comparisonResult == kCoreFoundationComparisonResultAscendingOrder ? 1 : 0;
    z = z->children[childIndex];
  }

  if (z != tree->sentinel) {
    if (z->count > 1) {
      tree->count -= 1;
      z->count -= 1;

      return;
    }

    let x = (_CoreFoundationRedBlackTreeNode*)null;
    let y = z;
    let oldColor = y->color;
    if (z->children[0] == tree->sentinel) {
      x = z->children[1];
      _CoreFoundationRedBlackTreeTransplant(tree, z, z->children[1]);
    } else if (z->children[1] == tree->sentinel) {
      x = z->children[0];
      _CoreFoundationRedBlackTreeTransplant(tree, z, z->children[0]);
    } else {
      y = _CoreFoundationRedBlackTreeFindMinimum(tree, z->children[1]);
      oldColor = y->color;
      x = y->children[1];

      if (y->parent == z) {
        x->parent = y;
      } else {
        let delta = y;
        while (delta != z) {
          delta->size -= y->count;
          delta = delta->parent;
        }

        _CoreFoundationRedBlackTreeTransplant(tree, y, y->children[1]);
        y->children[1] = z->children[1];
        y->children[1]->parent = y;
      }
      _CoreFoundationRedBlackTreeTransplant(tree, z, y);
      y->children[0] = z->children[0];
      y->children[0]->parent = y;
      y->color = z->color;
      y->size = y->children[0]->size + y->children[1]->size + y->count;
    }

    if (oldColor == _kCoreFoundationRedBlackTreeNodeColorBlack) {
      _CoreFoundationRedBlackTreeFixDeletion(tree, x);
    }

    _CoreFoundationRedBlackTreeNodeDeinitialize(z);
    tree->count -= 1;
  } else { /* No such keys, restore subtree sizes */
    while (w != tree->sentinel) {
      w->size += 1;
      w = w->parent;
    }
  }
}

CBoolean _CoreFoundationRedBlackTreeContainsKey(
  _CoreFoundationRedBlackTree* tree,
  void* key
) {
  let x = tree->root;

  while (x != tree->sentinel) {
    let comparisonResult = tree->compare(x->key, key);
    if (comparisonResult == kCoreFoundationComparisonResultSameOrder) {
      return yes;
    }

    let childIndex =
      comparisonResult == kCoreFoundationComparisonResultAscendingOrder ? 1 : 0;
    x = x->children[childIndex];
  }

  return no;
}

void _CoreFoundationRedBlackTreeGetKey(
  _CoreFoundationRedBlackTree* tree,
  void* key,
  void* result
) {
  let x = tree->root;

  while (x != tree->sentinel) {
    let comparisonResult = tree->compare(x->key, key);

    if (comparisonResult == kCoreFoundationComparisonResultSameOrder) {
      CMemoryCopy(result, x->key, tree->keySize);

      break;
    }

    let childIndex =
      comparisonResult == kCoreFoundationComparisonResultAscendingOrder ? 1 : 0;
    x = x->children[childIndex];
  }
}

C_ASSUME_NONNULL_END
