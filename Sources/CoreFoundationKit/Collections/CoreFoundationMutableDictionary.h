/*
 *  CoreFoundationMutableDictionary.h
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

#ifndef CoreFoundationMutableDictionary_h
#define CoreFoundationMutableDictionary_h

#include "CoreFoundationDictionary.h"
#include "../Base/CoreFoundationObject.h"

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * ``CoreFoundationMutableDictionary`` manages dynamic dictionaries. The basic
 * interface for managing dictionaries is provided by
 * ``CoreFoundationDictionary``. ``CoreFoundationMutableDictionary`` adds
 * functions to modify the contents of a dictionary.
 *
 * You create a mutable dictionary object using the
 * ``CoreFoundationMutableDictionaryInitialize`` function. You can add key-value
 * pairs using the ``CoreFoundationMutableDictionaryAddValue`` and
 * ``CoreFoundationMutableDictionarySetValue`` functions. When adding key-value
 * pairs to a dictionary, the keys and values are not copied—they are retained
 * so they are not invalidated before the dictionary is deallocated. You can
 * remove key-value pairs using the
 * ``CoreFoundationMutableDictionaryRemoveValue`` function. When removing
 * key-value pairs from a dictionary, the keys and values are released.
 *
 * ## Topics
 *
 * ### Creating a Mutable Dictionary
 *
 * - ``CoreFoundationMutableDictionaryInitialize``
 *
 * ### Modifying a Dictionary
 *
 * - ``CoreFoundationMutableDictionarySetValue``
 * - ``CoreFoundationMutableDictionaryRemoveValue``
 */
typedef CoreFoundationDictionary CoreFoundationMutableDictionary;

/**
 * Creates a new mutable dictionary.
 *
 * - Returns: A new dictionary, or `null` if there was a problem creating the
 *   object.
 */
CoreFoundationMutableDictionary* CoreFoundationMutableDictionaryInitialize();

/**
 * Sets the value corresponding to a given key.
 *
 * - Parameters:
 *   - dictionary: The dictionary to modify.
 *   - key: The key of the value to set in the dictionary. If a key which
 *     matches key is already present in the dictionary, only the value for the
 *     key is changed ("add if absent, replace if present"). If no key matches
 *     key, the key-value pair is added to the dictionary.
 *     If a key-value pair is added, both key and value are retained by the
 *     dictionary.
 *   - value: The value to add to or replace in the dictionary. value is
 *     retained, and the previous value if any is released.
 */
void CoreFoundationMutableDictionarySetValue(
  CoreFoundationMutableDictionary* dictionary,
  CoreFoundationAnyObject* key,
  CoreFoundationAnyObject* value
);

/**
 * Removes a key-value pair.
 *
 * - Parameters:
 *   - dictionary: The dictionary to modify.
 *   - key: The key of the value to remove from theDict. If a key which matches
 *     key is present in the dictionary, the key-value pair is removed from the
 *     dictionary, otherwise this function does nothing ("remove if present").
 */
void CoreFoundationMutableDictionaryRemoveValue(
  CoreFoundationMutableDictionary* dictionary,
  CoreFoundationAnyObject* key
);

#define \
  CoreFoundationMutableDictionaryContainsKey CoreFoundationDictionaryContainsKey

#define CoreFoundationMutableDictionaryGetCount CoreFoundationDictionaryGetCount

#define CoreFoundationMutableDictionaryGetValue CoreFoundationDictionaryGetValue

C_ASSUME_NONNULL_END

#endif /* CoreFoundationMutableDictionary_h */
