/*
 *  CoreFoundationDictionary.c
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

#include "CoreFoundationDictionary.h"

#include "CoreFoundationDictionary+Private.h"
#include "CoreFoundationRedBlackTree.h"

C_ASSUME_NONNULL_BEGIN

#if !C_TARGET_OS_ONLINE_JUDGE
extern CoreFoundationAnyObject* FoundationCoreFoundationDictionaryInitialize(
  const void * nillable * nonnil keys,
  const void * nillable * nonnil values,
  CInteger count,
  CBoolean isMutable
);
#endif /* !C_TARGET_OS_ONLINE_JUDGE */

CoreFoundationDictionary* CoreFoundationDictionaryInitialize(
  const void * nillable * nonnil keys,
  const void * nillable * nonnil values,
  CInteger count
) {
#if C_TARGET_OS_ONLINE_JUDGE
#else
  return FoundationCoreFoundationDictionaryInitialize(keys, values, count, no);
#endif
}

CBoolean CoreFoundationDictionaryContainsKey(
  CoreFoundationDictionary* dictionary,
  CoreFoundationAnyObject* key
) {
  CoreFoundationRetain(dictionary);
  CoreFoundationRetain(key);

  let result = no;

  let entry = (_CoreFoundationDictionaryEntry){ key };
  if (_CoreFoundationRedBlackTreeContainsKey(dictionary->tree, &entry)) {
    result = yes;
  }

  CoreFoundationRelease(dictionary);
  CoreFoundationRelease(key);

  return result;
}

CInteger CoreFoundationDictionaryGetCount(
  CoreFoundationDictionary* dictionary
) {
  CoreFoundationRetain(dictionary);

  let count = dictionary->tree->count;

  CoreFoundationRelease(dictionary);

  return count;
}

CoreFoundationAnyObject* CoreFoundationDictionaryGetValue(
  CoreFoundationDictionary* dictionary,
  CoreFoundationAnyObject* key
) {
  CoreFoundationRetain(dictionary);
  CoreFoundationRetain(key);

  let entry = (_CoreFoundationDictionaryEntry){ key };
  let storedEntry = (_CoreFoundationDictionaryEntry){ null, null };
  _CoreFoundationRedBlackTreeGetKey(dictionary->tree, &entry, &storedEntry);

  CoreFoundationRelease(dictionary);
  CoreFoundationRelease(key);

  return storedEntry.value;
}

void _CoreFoundationDictionaryGetEntryAtIndex(
  CoreFoundationDictionary* dictionary,
  CInteger index,
  _CoreFoundationDictionaryEntry* result
) {
  CoreFoundationRetain(dictionary);

  _CoreFoundationRedBlackTreeGetKeyAtIndex(dictionary->tree, index, result);

  CoreFoundationRelease(dictionary);
}

C_ASSUME_NONNULL_END
