/*
 *  CoreFoundationDictionary.h
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

#ifndef CoreFoundationDictionary_h
#define CoreFoundationDictionary_h

#include "../Base/CoreFoundationObject.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

typedef struct _CoreFoundationDictionaryEntry {
  void* key;
  void* value;
} _CoreFoundationDictionaryEntry;

/**
 * ``CoreFoundationDictionary`` and its derived mutable type,
 * ``CoreFoundationMutableDictionary``, manage associations of key-value pairs.
 * ``CoreFoundationDictionary`` creates static dictionaries where you set the
 * key-value pairs when first creating a dictionary and cannot modify them
 * afterward; ``CoreFoundationMutableDictionary`` creates dynamic dictionaries
 * where you can add or delete key-value pairs at any time, and the dictionary
 * automatically allocates memory as needed.
 *
 * A key-value pair within a dictionary is called an entry. Each entry consists
 * of one object that represents the key and a second object that is that key's
 * value. Within a dictionary, the keys are unique. That is, no two keys in a
 * single dictionary are equal. Internally, a dictionary uses a red black tree
 * to organize its storage and to provide rapid access to a value given the
 * corresponding key.
 *
 * You create static dictionaries using the
 * ``CoreFoundationDictionaryInitialize`` function. Key-value pairs are passed
 * as parameters to ``CoreFoundationDictionaryInitialize``. When adding
 * key-value pairs to a dictionary, the keys and values are not copied—they are
 * retained so they are not invalidated before the dictionary is deallocated.
 *
 * ``CoreFoundationDictionary`` provides functions for querying the values of a
 * dictionary. The function ``CoreFoundationDictionaryGetCount`` returns the
 * number of key-value pairs in a dictionary; the
 * ``CoreFoundationDictionaryContainsValue`` function checks if a value is in a
 * dictionary; and ``CoreFoundationDictionaryGetValue`` returns the value
 * associated with a given key in a dictionary.
 *
 * ## Topics
 *
 * ### Creating a dictionary
 *
 * - ``CoreFoundationDictionaryInitialize``
 *
 * ### Examining a dictionary
 *
 * - ``CoreFoundationDictionaryContainsKey``
 * - ``CoreFoundationDictionaryGetCount``
 * - ``CoreFoundationDictionaryGetValue``
 */
typedef struct CoreFoundationDictionary CoreFoundationDictionary;

/**
 * Creates an immutable dictionary containing the specified key-value pairs.
 *
 * - Parameters:
 *   - keys: A C array of the pointer-sized keys to be in the new dictionary.
 *     This value may be `null` if the `count` parameter is `0`. This C array is
 *     not changed or freed by this function. The value must be a valid pointer
 *     to a C array of at least `count` pointers.
 *   - values: A C array of the pointer-sized values to be in the new
 *     dictionary. This value may be `null` if the `count` parameter is `0`.
 *     This C array is not changed or freed by this function. The value must be
 *     a valid pointer to a C array of at least `count` elements.
 *   - count: The number of key-value pairs to copy from the keys and values C
 *     arrays into the new dictionary. This number will be the count of the
 *     dictionary; it must be non-negative and less than or equal to the actual
 *     number of keys or values.
 */
CoreFoundationDictionary* CoreFoundationDictionaryInitialize(
  const void * nillable * nonnil keys,
  const void * nillable * nonnil values,
  CInteger count
);

/**
 * Returns a Boolean value that indicates whether a given key is in a
 * dictionary.
 *
 * - Parameters:
 *   - dictionary: The dictionary to examine.
 *   - key: The key for which to find matches in the dictionary.
 *
 * - Returns: `yes` if key is in the dictionary, otherwise `no`.
 */
CBoolean CoreFoundationDictionaryContainsKey(
  CoreFoundationDictionary* dictionary,
  CoreFoundationAnyObject* key
);

/**
 * Returns the number of key-value pairs in a dictionary.
 *
 * - Parameter dictionary: The dictionary to examine.
 *
 * - Returns: The number of number of key-value pairs in the dictionary.
 */
CInteger CoreFoundationDictionaryGetCount(CoreFoundationDictionary* dictionary);

/**
 * Returns the value associated with a given key.
 *
 * - Parameters:
 *   - dictionary: The dictionary to examine.
 *   - key: The key for which to find a match in the dictionary.
 *
 * - Returns: The value associated with key in the dictionary, or `null` if no
 *   key-value pair matching key exists.
 */
CoreFoundationAnyObject* CoreFoundationDictionaryGetValue(
  CoreFoundationDictionary* dictionary,
  CoreFoundationAnyObject* key
);

void _CoreFoundationDictionaryGetEntryAtIndex(
  CoreFoundationDictionary* dictionary,
  CInteger index,
  _CoreFoundationDictionaryEntry* result
);

C_ASSUME_NONNULL_END

#endif /* CoreFoundationDictionary_h */
