/*
 *  CoreFoundationMutableDictionary.c
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

#include "CoreFoundationMutableDictionary.h"

#include "CoreFoundationDictionary+Private.h"
#include "CoreFoundationRedBlackTree.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
extern CoreFoundationAnyObject*
FoundationCoreFoundationMutableDictionaryInitialize();
#endif /* !C_TARGET_OS_ONLINE_JUDGE */

CoreFoundationMutableDictionary* CoreFoundationMutableDictionaryInitialize() {
#if C_TARGET_OS_ONLINE_JUDGE
#else
  return FoundationCoreFoundationMutableDictionaryInitialize();
#endif
}

void CoreFoundationMutableDictionarySetValue(
  CoreFoundationMutableDictionary* dictionary,
  CoreFoundationAnyObject* key,
  CoreFoundationAnyObject* value
) {
  CoreFoundationRetain(dictionary);
  CoreFoundationRetain(key);
  CoreFoundationRetain(value);

  let entry = (_CoreFoundationDictionaryEntry){ key, value };

  if (_CoreFoundationRedBlackTreeContainsKey(dictionary->tree, &entry)) {
    let previousEntry = (_CoreFoundationDictionaryEntry){ 0 };
    _CoreFoundationRedBlackTreeGetKey(dictionary->tree, &entry, &previousEntry);

    _CoreFoundationRedBlackTreeRemoveKey(dictionary->tree, &previousEntry);

    CoreFoundationRelease(previousEntry.key);
    CoreFoundationRelease(previousEntry.value);
  }

  _CoreFoundationRedBlackTreeInsertKey(dictionary->tree, &entry);

  CoreFoundationRelease(dictionary);
}

C_ASSUME_NONNULL_END
