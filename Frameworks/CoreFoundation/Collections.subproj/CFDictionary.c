// clang-format off

// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//


/*  CFDictionary.c
    Copyright (c) 1998 - 2015 Apple Inc. and the Swift project authors
    Responsibility: Michael LeHew
    Machine generated from Notes/HashingCode.template
*/





#include <CoreFoundation/CFDictionary.h>
#include "CFInternal.h"
#include "CFBasicHash.h"
#include <CoreFoundation/CFString.h>
#include <Foundation/NSMutableDictionary.h>

#define CF_IS_SWIFT(type,obj) false


#define CFDictionary 0
#define CFSet 0
#define CFBag 0
#undef CFDictionary
#define CFDictionary 1

#if CFDictionary


const CFDictionaryKeyCallBacks kCFTypeDictionaryKeyCallBacks = {0, __CFTypeCollectionRetain, __CFTypeCollectionRelease, CFCopyDescription, CFEqual, CFHash};
const CFDictionaryKeyCallBacks kCFCopyStringDictionaryKeyCallBacks = {0, __CFStringCollectionCopy, __CFTypeCollectionRelease, CFCopyDescription, CFEqual, CFHash};
const CFDictionaryValueCallBacks kCFTypeDictionaryValueCallBacks = {0, __CFTypeCollectionRetain, __CFTypeCollectionRelease, CFCopyDescription, CFEqual};

#define CFHashRef CFDictionaryRef
#define CFMutableHashRef CFMutableDictionaryRef
#define CFHashKeyCallBacks CFDictionaryKeyCallBacks
#define CFHashValueCallBacks CFDictionaryValueCallBacks
#endif

#if CFSet
const CFDictionaryCallBacks kCFTypeDictionaryCallBacks = {0, __CFTypeCollectionRetain, __CFTypeCollectionRelease, CFCopyDescription, CFEqual, CFHash};
const CFDictionaryCallBacks kCFCopyStringDictionaryCallBacks = {0, __CFStringCollectionCopy, __CFTypeCollectionRelease, CFCopyDescription, CFEqual, CFHash};

#define CFDictionaryKeyCallBacks CFDictionaryCallBacks
#define CFDictionaryValueCallBacks CFDictionaryCallBacks
#define kCFTypeDictionaryKeyCallBacks kCFTypeDictionaryCallBacks
#define kCFTypeDictionaryValueCallBacks kCFTypeDictionaryCallBacks

#define CFHashRef CFSetRef
#define CFMutableHashRef CFMutableSetRef
#define CFHashKeyCallBacks CFDictionaryCallBacks
#define CFHashValueCallBacks CFDictionaryCallBacks
#endif

#if CFBag
const CFDictionaryCallBacks kCFTypeDictionaryCallBacks = {0, __CFTypeCollectionRetain, __CFTypeCollectionRelease, CFCopyDescription, CFEqual, CFHash};
const CFDictionaryCallBacks kCFCopyStringDictionaryCallBacks = {0, __CFStringCollectionCopy, __CFTypeCollectionRelease, CFCopyDescription, CFEqual, CFHash};

#define CFDictionaryKeyCallBacks CFDictionaryCallBacks
#define CFDictionaryValueCallBacks CFDictionaryCallBacks
#define kCFTypeDictionaryKeyCallBacks kCFTypeDictionaryCallBacks
#define kCFTypeDictionaryValueCallBacks kCFTypeDictionaryCallBacks

#define CFHashRef CFBagRef
#define CFMutableHashRef CFMutableBagRef
#define CFHashKeyCallBacks CFDictionaryCallBacks
#define CFHashValueCallBacks CFDictionaryCallBacks
#endif


typedef uintptr_t any_t;
typedef const void * const_any_pointer_t;
typedef void * any_pointer_t;

static Boolean __CFDictionaryEqual(CFTypeRef cf1, CFTypeRef cf2) {
    return __CFBasicHashEqual((CFBasicHashRef)cf1, (CFBasicHashRef)cf2);
}

static CFHashCode __CFDictionaryHash(CFTypeRef cf) {
    return __CFBasicHashHash((CFBasicHashRef)cf);
}

static CFStringRef __CFDictionaryCopyDescription(CFTypeRef cf) {
    return __CFBasicHashCopyDescription((CFBasicHashRef)cf);
}

static void __CFDictionaryDeallocate(CFTypeRef cf) {
    __CFBasicHashDeallocate((CFBasicHashRef)cf);
}

static CFTypeID __kCFDictionaryTypeID = _kCFRuntimeNotATypeID;

static const CFRuntimeClass __CFDictionaryClass = {
    _kCFRuntimeScannedObject,
    "CFDictionary",
    NULL,        // init
    NULL,        // copy
    __CFDictionaryDeallocate,
    __CFDictionaryEqual,
    __CFDictionaryHash,
    NULL,        //
    __CFDictionaryCopyDescription
};

CFTypeID CFDictionaryGetTypeID(void) {
    static dispatch_once_t initOnce = 0;
    dispatch_once(&initOnce, ^{
        __kCFDictionaryTypeID = _CFRuntimeRegisterClass(&__CFDictionaryClass);
    });
    return __kCFDictionaryTypeID;
}


static CFBasicHashRef __CFDictionaryCreateGeneric(CFAllocatorRef allocator, const CFHashKeyCallBacks *keyCallBacks, const CFHashValueCallBacks *valueCallBacks, Boolean useValueCB) {
    CFOptionFlags flags = kCFBasicHashLinearHashing; // kCFBasicHashExponentialHashing
    flags |= (CFDictionary ? kCFBasicHashHasKeys : 0) | (CFBag ? kCFBasicHashHasCounts : 0);

    if (CF_IS_COLLECTABLE_ALLOCATOR(allocator)) { // all this crap is just for figuring out two flags for GC in the way done historically; it probably simplifies down to three lines, but we let the compiler worry about that
        Boolean set_cb = false;
        Boolean std_cb = false;
        const_any_pointer_t (*key_retain)(CFAllocatorRef, const_any_pointer_t) = NULL;
        void (*key_release)(CFAllocatorRef, const_any_pointer_t) = NULL;
        const_any_pointer_t (*value_retain)(CFAllocatorRef, const_any_pointer_t) = NULL;
        void (*value_release)(CFAllocatorRef, const_any_pointer_t) = NULL;

    if ((NULL == keyCallBacks || 0 == keyCallBacks->version) && (!useValueCB || NULL == valueCallBacks || 0 == valueCallBacks->version)) {
        Boolean keyRetainNull = NULL == keyCallBacks || NULL == keyCallBacks->retain;
        Boolean keyReleaseNull = NULL == keyCallBacks || NULL == keyCallBacks->release;
        Boolean keyEquateNull = NULL == keyCallBacks || NULL == keyCallBacks->equal;
        Boolean keyHashNull = NULL == keyCallBacks || NULL == keyCallBacks->hash;
        Boolean keyDescribeNull = NULL == keyCallBacks || NULL == keyCallBacks->copyDescription;

        Boolean valueRetainNull = (useValueCB && (NULL == valueCallBacks || NULL == valueCallBacks->retain)) || (!useValueCB && keyRetainNull);
        Boolean valueReleaseNull = (useValueCB && (NULL == valueCallBacks || NULL == valueCallBacks->release)) || (!useValueCB && keyReleaseNull);
        Boolean valueEquateNull = (useValueCB && (NULL == valueCallBacks || NULL == valueCallBacks->equal)) || (!useValueCB && keyEquateNull);
        Boolean valueDescribeNull = (useValueCB && (NULL == valueCallBacks || NULL == valueCallBacks->copyDescription)) || (!useValueCB && keyDescribeNull);

        Boolean keyRetainStd = keyRetainNull || __CFTypeCollectionRetain == keyCallBacks->retain;
        Boolean keyReleaseStd = keyReleaseNull || __CFTypeCollectionRelease == keyCallBacks->release;
        Boolean keyEquateStd = keyEquateNull || CFEqual == keyCallBacks->equal;
        Boolean keyHashStd = keyHashNull || CFHash == keyCallBacks->hash;
        Boolean keyDescribeStd = keyDescribeNull || CFCopyDescription == keyCallBacks->copyDescription;

        Boolean valueRetainStd = (useValueCB && (valueRetainNull || __CFTypeCollectionRetain == valueCallBacks->retain)) || (!useValueCB && keyRetainStd);
        Boolean valueReleaseStd = (useValueCB && (valueReleaseNull || __CFTypeCollectionRelease == valueCallBacks->release)) || (!useValueCB && keyReleaseStd);
        Boolean valueEquateStd = (useValueCB && (valueEquateNull || CFEqual == valueCallBacks->equal)) || (!useValueCB && keyEquateStd);
        Boolean valueDescribeStd = (useValueCB && (valueDescribeNull || CFCopyDescription == valueCallBacks->copyDescription)) || (!useValueCB && keyDescribeStd);

        if (keyRetainStd && keyReleaseStd && keyEquateStd && keyHashStd && keyDescribeStd && valueRetainStd && valueReleaseStd && valueEquateStd && valueDescribeStd) {
        set_cb = true;
        if (!(keyRetainNull || keyReleaseNull || keyEquateNull || keyHashNull || keyDescribeNull || valueRetainNull || valueReleaseNull || valueEquateNull || valueDescribeNull)) {
            std_cb = true;
        } else {
            // just set these to tickle the GC Strong logic below in a way that mimics past practice
            key_retain = keyCallBacks ? keyCallBacks->retain : NULL;
            key_release = keyCallBacks ? keyCallBacks->release : NULL;
            if (useValueCB) {
            value_retain = valueCallBacks ? valueCallBacks->retain : NULL;
            value_release = valueCallBacks ? valueCallBacks->release : NULL;
            } else {
            value_retain = key_retain;
            value_release = key_release;
            }
        }
        }
    }

        if (!set_cb) {
            key_retain = keyCallBacks ? keyCallBacks->retain : NULL;
            key_release = keyCallBacks ? keyCallBacks->release : NULL;
            if (useValueCB) {
                value_retain = valueCallBacks ? valueCallBacks->retain : NULL;
                value_release = valueCallBacks ? valueCallBacks->release : NULL;
            } else {
                value_retain = key_retain;
                value_release = key_release;
            }
        }

        if (std_cb || value_retain != NULL || value_release != NULL) {
            flags |= kCFBasicHashStrongValues;
        }
        if (std_cb || key_retain != NULL || key_release != NULL) {
            flags |= kCFBasicHashStrongKeys;
        }
    }


    CFBasicHashCallbacks callbacks;
    callbacks.retainKey = keyCallBacks ? (uintptr_t (*)(CFAllocatorRef, uintptr_t))keyCallBacks->retain : NULL;
    callbacks.releaseKey = keyCallBacks ? (void (*)(CFAllocatorRef, uintptr_t))keyCallBacks->release : NULL;
    callbacks.equateKeys = keyCallBacks ? (Boolean (*)(uintptr_t, uintptr_t))keyCallBacks->equal : NULL;
    callbacks.hashKey = keyCallBacks ? (CFHashCode (*)(uintptr_t))keyCallBacks->hash : NULL;
    callbacks.getIndirectKey = NULL;
    callbacks.copyKeyDescription = keyCallBacks ? (CFStringRef (*)(uintptr_t))keyCallBacks->copyDescription : NULL;
    callbacks.retainValue = useValueCB ? (valueCallBacks ? (uintptr_t (*)(CFAllocatorRef, uintptr_t))valueCallBacks->retain : NULL) : (callbacks.retainKey);
    callbacks.releaseValue = useValueCB ? (valueCallBacks ? (void (*)(CFAllocatorRef, uintptr_t))valueCallBacks->release : NULL) : (callbacks.releaseKey);
    callbacks.equateValues = useValueCB ? (valueCallBacks ? (Boolean (*)(uintptr_t, uintptr_t))valueCallBacks->equal : NULL) : (callbacks.equateKeys);
    callbacks.copyValueDescription = useValueCB ? (valueCallBacks ? (CFStringRef (*)(uintptr_t))valueCallBacks->copyDescription : NULL) : (callbacks.copyKeyDescription);

    CFBasicHashRef ht = CFBasicHashCreate(allocator, flags, &callbacks);
    return ht;
}

#if CFDictionary
CF_PRIVATE CFHashRef __CFDictionaryCreateTransfer(CFAllocatorRef allocator, const_any_pointer_t *klist, const_any_pointer_t *vlist, CFIndex numValues) {
#endif
#if CFSet || CFBag
CF_PRIVATE CFHashRef __CFDictionaryCreateTransfer(CFAllocatorRef allocator, const_any_pointer_t *klist, CFIndex numValues) {
    const_any_pointer_t *vlist = klist;
#endif
    CFTypeID typeID = CFDictionaryGetTypeID();
    CFAssert2(0 <= numValues, __kCFLogAssertion, "%s(): numValues (%ld) cannot be less than zero", __PRETTY_FUNCTION__, numValues);
    CFOptionFlags flags = kCFBasicHashLinearHashing; // kCFBasicHashExponentialHashing
    flags |= (CFDictionary ? kCFBasicHashHasKeys : 0) | (CFBag ? kCFBasicHashHasCounts : 0);

    CFBasicHashCallbacks callbacks;
    callbacks.retainKey = (uintptr_t (*)(CFAllocatorRef, uintptr_t))kCFTypeDictionaryKeyCallBacks.retain;
    callbacks.releaseKey = (void (*)(CFAllocatorRef, uintptr_t))kCFTypeDictionaryKeyCallBacks.release;
    callbacks.equateKeys = (Boolean (*)(uintptr_t, uintptr_t))kCFTypeDictionaryKeyCallBacks.equal;
    callbacks.hashKey = (CFHashCode (*)(uintptr_t))kCFTypeDictionaryKeyCallBacks.hash;
    callbacks.getIndirectKey = NULL;
    callbacks.copyKeyDescription = (CFStringRef (*)(uintptr_t))kCFTypeDictionaryKeyCallBacks.copyDescription;
    callbacks.retainValue = CFDictionary ? (uintptr_t (*)(CFAllocatorRef, uintptr_t))kCFTypeDictionaryValueCallBacks.retain : callbacks.retainKey;
    callbacks.releaseValue = CFDictionary ? (void (*)(CFAllocatorRef, uintptr_t))kCFTypeDictionaryValueCallBacks.release : callbacks.releaseKey;
    callbacks.equateValues = CFDictionary ? (Boolean (*)(uintptr_t, uintptr_t))kCFTypeDictionaryValueCallBacks.equal : callbacks.equateKeys;
    callbacks.copyValueDescription = CFDictionary ? (CFStringRef (*)(uintptr_t))kCFTypeDictionaryValueCallBacks.copyDescription : callbacks.copyKeyDescription;

    CFBasicHashRef ht = CFBasicHashCreate(allocator, flags, &callbacks);
    CFBasicHashSuppressRC(ht);
    if (0 < numValues) CFBasicHashSetCapacity(ht, numValues);
    for (CFIndex idx = 0; idx < numValues; idx++) {
        CFBasicHashAddValue(ht, (uintptr_t)klist[idx], (uintptr_t)vlist[idx]);
    }
    CFBasicHashUnsuppressRC(ht);
    CFBasicHashMakeImmutable(ht);
    _CFRuntimeSetInstanceTypeIDAndIsa(ht, typeID);
    if (__CFOASafe) __CFSetLastAllocationEventName(ht, "CFDictionary (immutable)");
    return (CFHashRef)ht;
}

#if CFDictionary
CFHashRef CFDictionaryCreate(CFAllocatorRef allocator, const_any_pointer_t *klist, const_any_pointer_t *vlist, CFIndex numValues, const CFDictionaryKeyCallBacks *keyCallBacks, const CFDictionaryValueCallBacks *valueCallBacks) {
#endif
#if CFSet || CFBag
CFHashRef CFDictionaryCreate(CFAllocatorRef allocator, const_any_pointer_t *klist, CFIndex numValues, const CFDictionaryKeyCallBacks *keyCallBacks) {
    const_any_pointer_t *vlist = klist;
    const CFDictionaryValueCallBacks *valueCallBacks = 0;
#endif
    
    CFTypeID typeID = CFDictionaryGetTypeID();
    CFAssert2(0 <= numValues, __kCFLogAssertion, "%s(): numValues (%ld) cannot be less than zero", __PRETTY_FUNCTION__, numValues);
    CFBasicHashRef ht = __CFDictionaryCreateGeneric(allocator, keyCallBacks, valueCallBacks, CFDictionary);
    if (!ht) return NULL;
    if (0 < numValues) CFBasicHashSetCapacity(ht, numValues);
    for (CFIndex idx = 0; idx < numValues; idx++) {
        CFBasicHashAddValue(ht, (uintptr_t)klist[idx], (uintptr_t)vlist[idx]);
    }
    CFBasicHashMakeImmutable(ht);
    _CFRuntimeSetInstanceTypeIDAndIsa(ht, typeID);
    if (__CFOASafe) __CFSetLastAllocationEventName(ht, "CFDictionary (immutable)");
    return (CFHashRef)ht;
}

#if CFDictionary
CFMutableHashRef CFDictionaryCreateMutable(CFAllocatorRef allocator, CFIndex capacity, const CFDictionaryKeyCallBacks *keyCallBacks, const CFDictionaryValueCallBacks *valueCallBacks) {
#endif
#if CFSet || CFBag
CFMutableHashRef CFDictionaryCreateMutable(CFAllocatorRef allocator, CFIndex capacity, const CFDictionaryKeyCallBacks *keyCallBacks) {
    const CFDictionaryValueCallBacks *valueCallBacks = 0;
#endif
    CFTypeID typeID = CFDictionaryGetTypeID();
    CFAssert2(0 <= capacity, __kCFLogAssertion, "%s(): capacity (%ld) cannot be less than zero", __PRETTY_FUNCTION__, capacity);
    CFBasicHashRef ht = __CFDictionaryCreateGeneric(allocator, keyCallBacks, valueCallBacks, CFDictionary);
    if (!ht) return NULL;
    _CFRuntimeSetInstanceTypeIDAndIsa(ht, typeID);
    if (__CFOASafe) __CFSetLastAllocationEventName(ht, "CFDictionary (mutable)");
    return (CFMutableHashRef)ht;
}

CFHashRef CFDictionaryCreateCopy(CFAllocatorRef allocator, CFHashRef other) {
    CFTypeID typeID = CFDictionaryGetTypeID();
    CFAssert1(other, __kCFLogAssertion, "%s(): other CFDictionary cannot be NULL", __PRETTY_FUNCTION__);
    __CFGenericValidateType(other, typeID);
    Boolean markImmutable = false;
    CFBasicHashRef ht = NULL;
    if (CF_IS_OBJC(typeID, other)) {
        if (objc_collectingEnabled()) {
            CFIndex numValues = CFDictionaryGetCount(other);
            const_any_pointer_t vbuffer[256], kbuffer[256];
            const_any_pointer_t *vlist = (numValues <= 256) ? vbuffer : (const_any_pointer_t *)CFAllocatorAllocate(kCFAllocatorSystemDefault, numValues * sizeof(const_any_pointer_t), 0);
#if CFSet || CFBag
            const_any_pointer_t *klist = vlist;
            CFDictionaryGetValues(other, vlist);
#endif
#if CFDictionary
            const_any_pointer_t *klist = (numValues <= 256) ? kbuffer : (const_any_pointer_t *)CFAllocatorAllocate(kCFAllocatorSystemDefault, numValues * sizeof(const_any_pointer_t), 0);
            CFDictionaryGetKeysAndValues(other, klist, vlist);
#endif
            ht = __CFDictionaryCreateGeneric(allocator, & kCFTypeDictionaryKeyCallBacks, CFDictionary ? & kCFTypeDictionaryValueCallBacks : NULL, CFDictionary);
            if (ht && 0 < numValues) CFBasicHashSetCapacity(ht, numValues);
            for (CFIndex idx = 0; ht && idx < numValues; idx++) {
                CFBasicHashAddValue(ht, (uintptr_t)klist[idx], (uintptr_t)vlist[idx]);
            }
            if (klist != kbuffer && klist != vlist) CFAllocatorDeallocate(kCFAllocatorSystemDefault, klist);
            if (vlist != vbuffer) CFAllocatorDeallocate(kCFAllocatorSystemDefault, vlist);
            markImmutable = true;
        }
        else { // non-GC
#if CFDictionary || CFSet
            ht = (CFBasicHashRef)CF_OBJC_CALLV((id)other, copyWithZone:NULL);
#elif CFBag
            CFIndex numValues = CFDictionaryGetCount(other);
            const_any_pointer_t vbuffer[256];
            const_any_pointer_t *vlist = (numValues <= 256) ? vbuffer : (const_any_pointer_t *)CFAllocatorAllocate(kCFAllocatorSystemDefault, numValues * sizeof(const_any_pointer_t), 0);
            const_any_pointer_t *klist = vlist;
            CFDictionaryGetValues(other, vlist);
            ht = __CFDictionaryCreateGeneric(allocator, & kCFTypeDictionaryKeyCallBacks, CFDictionary ? & kCFTypeDictionaryValueCallBacks : NULL, CFDictionary);
            if (ht && 0 < numValues) CFBasicHashSetCapacity(ht, numValues);
            for (CFIndex idx = 0; ht && idx < numValues; idx++) {
                CFBasicHashAddValue(ht, (uintptr_t)klist[idx], (uintptr_t)vlist[idx]);
            }
            if (vlist != vbuffer) CFAllocatorDeallocate(kCFAllocatorSystemDefault, vlist);
            markImmutable = true;
#endif // CFBag
        }
    }
    else { // non-objc types
        ht = CFBasicHashCreateCopy(allocator, (CFBasicHashRef)other);
        markImmutable = true;
    }
    if (ht && markImmutable) {
        CFBasicHashMakeImmutable(ht);
        _CFRuntimeSetInstanceTypeIDAndIsa(ht, typeID);
        if (__CFOASafe) __CFSetLastAllocationEventName(ht, "CFDictionary (immutable)");
        return (CFHashRef)ht;
    }
    return (CFHashRef)ht;
}

CFMutableHashRef CFDictionaryCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFHashRef other) {
    CFTypeID typeID = CFDictionaryGetTypeID();
    CFAssert1(other, __kCFLogAssertion, "%s(): other CFDictionary cannot be NULL", __PRETTY_FUNCTION__);
    __CFGenericValidateType(other, typeID);
    CFAssert2(0 <= capacity, __kCFLogAssertion, "%s(): capacity (%ld) cannot be less than zero", __PRETTY_FUNCTION__, capacity);
    CFBasicHashRef ht = NULL;
    if (CF_IS_OBJC(typeID, other)) {
        CFIndex numValues = CFDictionaryGetCount(other);
        const_any_pointer_t vbuffer[256], kbuffer[256];
        const_any_pointer_t *vlist = (numValues <= 256) ? vbuffer : (const_any_pointer_t *)CFAllocatorAllocate(kCFAllocatorSystemDefault, numValues * sizeof(const_any_pointer_t), 0);
#if CFSet || CFBag
        const_any_pointer_t *klist = vlist;
        CFDictionaryGetValues(other, vlist);
#endif
#if CFDictionary
        const_any_pointer_t *klist = (numValues <= 256) ? kbuffer : (const_any_pointer_t *)CFAllocatorAllocate(kCFAllocatorSystemDefault, numValues * sizeof(const_any_pointer_t), 0);
        CFDictionaryGetKeysAndValues(other, klist, vlist);
#endif
        ht = __CFDictionaryCreateGeneric(allocator, & kCFTypeDictionaryKeyCallBacks, CFDictionary ? & kCFTypeDictionaryValueCallBacks : NULL, CFDictionary);
        if (ht && 0 < numValues) CFBasicHashSetCapacity(ht, numValues);
        for (CFIndex idx = 0; ht && idx < numValues; idx++) {
            CFBasicHashAddValue(ht, (uintptr_t)klist[idx], (uintptr_t)vlist[idx]);
        }
        if (klist != kbuffer && klist != vlist) CFAllocatorDeallocate(kCFAllocatorSystemDefault, klist);
        if (vlist != vbuffer) CFAllocatorDeallocate(kCFAllocatorSystemDefault, vlist);
    } else {
        ht = CFBasicHashCreateCopy(allocator, (CFBasicHashRef)other);
    }
    if (!ht) return NULL;
    _CFRuntimeSetInstanceTypeIDAndIsa(ht, typeID);
    if (__CFOASafe) __CFSetLastAllocationEventName(ht, "CFDictionary (mutable)");
    return (CFMutableHashRef)ht;
}

CFIndex CFDictionaryGetCount(CFHashRef hc) {
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), CFIndex, (CFSwiftRef)hc, NSDictionary.count);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), CFIndex, (NSDictionary *)hc, count);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), CFIndex, (NSSet *)hc, count);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    return CFBasicHashGetCount((CFBasicHashRef)hc);
}
    
#if CFDictionary
CFIndex CFDictionaryGetCountOfKey(CFHashRef hc, const_any_pointer_t key) {
#endif
#if CFSet || CFBag
CFIndex CFDictionaryGetCountOfValue(CFHashRef hc, const_any_pointer_t key) {
#endif
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), CFIndex, (CFSwiftRef)hc, NSDictionary.countForKey, key);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), CFIndex, (NSDictionary *)hc, countForKey:(id)key);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), CFIndex, (NSSet *)hc, countForObject:(id)key);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    return CFBasicHashGetCountOfKey((CFBasicHashRef)hc, (uintptr_t)key);
}
    
#if CFDictionary
Boolean CFDictionaryContainsKey(CFHashRef hc, const_any_pointer_t key) {
#endif
#if CFSet || CFBag
Boolean CFDictionaryContainsValue(CFHashRef hc, const_any_pointer_t key) {
#endif
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), char, (CFSwiftRef)hc, NSDictionary.containsKey, key);
// WINOBJC: This doesn't exist on NSDictionary //    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), char, (NSDictionary *)hc, containsKey:(id)key);
    if (CFDictionary && CF_IS_OBJC(CFDictionaryGetTypeID(), hc)) {
        return nil != CF_OBJC_CALLV((NSDictionary *)hc, objectForKey:(id)key);
    }
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), char, (NSSet *)hc, containsObject:(id)key);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    return (0 < CFBasicHashGetCountOfKey((CFBasicHashRef)hc, (uintptr_t)key));
}

const_any_pointer_t CFDictionaryGetValue(CFHashRef hc, const_any_pointer_t key) {
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), const_any_pointer_t, (CFSwiftRef)hc, NSDictionary.objectForKey, key);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), const_any_pointer_t, (NSDictionary *)hc, objectForKey:(id)key);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), const_any_pointer_t, (NSSet *)hc, member:(id)key);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFBasicHashBucket bkt = CFBasicHashFindBucket((CFBasicHashRef)hc, (uintptr_t)key);
    return (0 < bkt.count ? (const_any_pointer_t)bkt.weak_value : 0);
}
    
Boolean CFDictionaryGetValueIfPresent(CFHashRef hc, const_any_pointer_t key, const_any_pointer_t *value) {
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), Boolean, (CFSwiftRef)hc, NSDictionary.__getValue, value, key);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), Boolean, (NSDictionary *)hc, __getValue:(id *)value forKey:(id)key);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), Boolean, (NSSet *)hc, __getValue:(id *)value forObj:(id)key);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFBasicHashBucket bkt = CFBasicHashFindBucket((CFBasicHashRef)hc, (uintptr_t)key);
    if (0 < bkt.count) {
        if (value) {
            if (kCFUseCollectableAllocator && (CFBasicHashGetFlags((CFBasicHashRef)hc) & kCFBasicHashStrongValues)) {
                __CFAssignWithWriteBarrier((void **)value, (void *)bkt.weak_value);
            } else {
                *value = (const_any_pointer_t)bkt.weak_value;
            }
        }
        return true;
    }
    return false;
}
    
#if CFDictionary
CFIndex CFDictionaryGetCountOfValue(CFHashRef hc, const_any_pointer_t value) {
    // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), CFIndex, (CFSwiftRef)hc, NSDictionary.countForObject, value);
    CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), CFIndex, (NSDictionary *)hc, countForObject:(id)value);
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    return CFBasicHashGetCountOfValue((CFBasicHashRef)hc, (uintptr_t)value);
}
    
Boolean CFDictionaryContainsValue(CFHashRef hc, const_any_pointer_t value) {
    // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), char, (CFSwiftRef)hc, NSDictionary.containsObject, value);
    CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), char, (NSDictionary *)hc, containsObject:(id)value);
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    return (0 < CFBasicHashGetCountOfValue((CFBasicHashRef)hc, (uintptr_t)value));
}

CF_EXPORT Boolean CFDictionaryGetKeyIfPresent(CFHashRef hc, const_any_pointer_t key, const_any_pointer_t *actualkey) {
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFBasicHashBucket bkt = CFBasicHashFindBucket((CFBasicHashRef)hc, (uintptr_t)key);
    if (0 < bkt.count) {
        if (actualkey) {
            if (kCFUseCollectableAllocator && (CFBasicHashGetFlags((CFBasicHashRef)hc) & kCFBasicHashStrongKeys)) {
                __CFAssignWithWriteBarrier((void **)actualkey, (void *)bkt.weak_key);
            } else {
                *actualkey = (const_any_pointer_t)bkt.weak_key;
            }
        }
        return true;
    }
    return false;
}
#endif
    
#if CFDictionary
void CFDictionaryGetKeysAndValues(CFHashRef hc, const_any_pointer_t *keybuf, const_any_pointer_t *valuebuf) {
#endif
#if CFSet || CFBag
void CFDictionaryGetValues(CFHashRef hc, const_any_pointer_t *keybuf) {
    const_any_pointer_t *valuebuf = 0;
#endif
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (CFSwiftRef)hc, NSDictionary.getObjects, valuebuf, keybuf);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSDictionary *)hc, getObjects:(id *)valuebuf andKeys:(id *)keybuf);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSSet *)hc, getObjects:(id *)keybuf);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    if (kCFUseCollectableAllocator) {
        CFOptionFlags flags = CFBasicHashGetFlags((CFBasicHashRef)hc);
        __block const_any_pointer_t *keys = keybuf;
        __block const_any_pointer_t *values = valuebuf;
        CFBasicHashApply((CFBasicHashRef)hc, ^(CFBasicHashBucket bkt) {
                for (CFIndex cnt = bkt.count; cnt--;) {
                    if (keybuf && (flags & kCFBasicHashStrongKeys)) { __CFAssignWithWriteBarrier((void **)keys, (void *)bkt.weak_key); keys++; }
                    if (keybuf && !(flags & kCFBasicHashStrongKeys)) { *keys++ = (const_any_pointer_t)bkt.weak_key; }
                    if (valuebuf && (flags & kCFBasicHashStrongValues)) { __CFAssignWithWriteBarrier((void **)values, (void *)bkt.weak_value); values++; }
                    if (valuebuf && !(flags & kCFBasicHashStrongValues)) { *values++ = (const_any_pointer_t)bkt.weak_value; }
                }
                return (Boolean)true;
            });
    } else {
        CFBasicHashGetElements((CFBasicHashRef)hc, CFDictionaryGetCount(hc), (uintptr_t *)valuebuf, (uintptr_t *)keybuf);
    }
}
    
void CFDictionaryApplyFunction(CFHashRef hc, CFDictionaryApplierFunction applier, any_pointer_t context) {
    FAULT_CALLBACK((void **)&(applier));
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (CFSwiftRef)hc, NSDictionary.__apply, applier, context);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSDictionary *)hc, __apply:(void (*)(const void *, const void *, void *))applier context:(void *)context);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSSet *)hc, __applyValues:(void (*)(const void *, void *))applier context:(void *)context);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFBasicHashApply((CFBasicHashRef)hc, ^(CFBasicHashBucket bkt) {
#if CFDictionary
            INVOKE_CALLBACK3(applier, (const_any_pointer_t)bkt.weak_key, (const_any_pointer_t)bkt.weak_value, context);
#endif
#if CFSet
            INVOKE_CALLBACK2(applier, (const_any_pointer_t)bkt.weak_value, context);
#endif
#if CFBag
            for (CFIndex cnt = bkt.count; cnt--;) {
                INVOKE_CALLBACK2(applier, (const_any_pointer_t)bkt.weak_value, context);
            }
#endif
            return (Boolean)true;
        });
}

// This function is for Foundation's benefit; no one else should use it.
CF_EXPORT unsigned long _CFDictionaryFastEnumeration(CFHashRef hc, struct __objcFastEnumerationStateEquivalent *state, void *stackbuffer, unsigned long count) {
    if (CF_IS_SWIFT(CFDictionaryGetTypeID(), hc)) return 0;
    if (CF_IS_OBJC(CFDictionaryGetTypeID(), hc)) return 0;
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    return __CFBasicHashFastEnumeration((CFBasicHashRef)hc, (struct __objcFastEnumerationStateEquivalent2 *)state, stackbuffer, count);
}

// This function is for Foundation's benefit; no one else should use it.
CF_EXPORT Boolean _CFDictionaryIsMutable(CFHashRef hc) {
    if (CF_IS_SWIFT(CFDictionaryGetTypeID(), hc)) return true;
    if (CF_IS_OBJC(CFDictionaryGetTypeID(), hc)) return false;
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    return CFBasicHashIsMutable((CFBasicHashRef)hc);
}

// This function is for Foundation's benefit; no one else should use it.
CF_EXPORT void _CFDictionarySetCapacity(CFMutableHashRef hc, CFIndex cap) {
    if (CF_IS_SWIFT(CFDictionaryGetTypeID(), hc)) return;
    if (CF_IS_OBJC(CFDictionaryGetTypeID(), hc)) return;
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFAssert2(CFBasicHashIsMutable((CFBasicHashRef)hc), __kCFLogAssertion, "%s(): immutable collection %p passed to mutating operation", __PRETTY_FUNCTION__, hc);
    CFAssert3(CFDictionaryGetCount(hc) <= cap, __kCFLogAssertion, "%s(): desired capacity (%ld) is less than count (%ld)", __PRETTY_FUNCTION__, cap, CFDictionaryGetCount(hc));
    CFBasicHashSetCapacity((CFBasicHashRef)hc, cap);
}

CF_INLINE CFIndex __CFDictionaryGetKVOBit(CFHashRef hc) {
    return __CFBitfieldGetValue(((CFRuntimeBase *)hc)->_cfinfo[CF_INFO_BITS], 0, 0);
}

CF_INLINE void __CFDictionarySetKVOBit(CFHashRef hc, CFIndex bit) {
    __CFBitfieldSetValue(((CFRuntimeBase *)hc)->_cfinfo[CF_INFO_BITS], 0, 0, ((uintptr_t)bit & 0x1));
}

// This function is for Foundation's benefit; no one else should use it.
CF_EXPORT CFIndex _CFDictionaryGetKVOBit(CFHashRef hc) {
    return __CFDictionaryGetKVOBit(hc);
}

// This function is for Foundation's benefit; no one else should use it.
CF_EXPORT void _CFDictionarySetKVOBit(CFHashRef hc, CFIndex bit) {
    __CFDictionarySetKVOBit(hc, bit);
}


#if !defined(CF_OBJC_KVO_WILLCHANGE)
#define CF_OBJC_KVO_WILLCHANGE(obj, key)
#define CF_OBJC_KVO_DIDCHANGE(obj, key)
#define CF_OBJC_KVO_WILLCHANGEALL(obj)
#define CF_OBJC_KVO_DIDCHANGEALL(obj)
#endif
    
#if CFDictionary
void CFDictionaryAddValue(CFMutableHashRef hc, const_any_pointer_t key, const_any_pointer_t value) {
#endif
#if CFSet || CFBag
void CFDictionaryAddValue(CFMutableHashRef hc, const_any_pointer_t key) {
    const_any_pointer_t value = key;
#endif
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (CFSwiftRef)hc, NSMutableDictionary.__addObject, key, value);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableDictionary *)hc, __addObject:(id)value forKey:(id)key);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableSet *)hc, addObject:(id)key);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFAssert2(CFBasicHashIsMutable((CFBasicHashRef)hc), __kCFLogAssertion, "%s(): immutable collection %p passed to mutating operation", __PRETTY_FUNCTION__, hc);
    if (!CFBasicHashIsMutable((CFBasicHashRef)hc)) {
        CFLog(kCFLogLevelError, CFSTR("%s(): immutable collection %p given to mutating function"), __PRETTY_FUNCTION__, hc);
    }
    CF_OBJC_KVO_WILLCHANGE(hc, key);
    CFBasicHashAddValue((CFBasicHashRef)hc, (uintptr_t)key, (uintptr_t)value);
    CF_OBJC_KVO_DIDCHANGE(hc, key);
}

#if CFDictionary
void CFDictionaryReplaceValue(CFMutableHashRef hc, const_any_pointer_t key, const_any_pointer_t value) {
#endif
#if CFSet || CFBag
void CFDictionaryReplaceValue(CFMutableHashRef hc, const_any_pointer_t key) {
    const_any_pointer_t value = key;
#endif
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (CFSwiftRef)hc, NSMutableDictionary.replaceObject, key, value);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableDictionary *)hc, replaceObject:(id)value forKey:(id)key);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableSet *)hc, replaceObject:(id)key);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFAssert2(CFBasicHashIsMutable((CFBasicHashRef)hc), __kCFLogAssertion, "%s(): immutable collection %p passed to mutating operation", __PRETTY_FUNCTION__, hc);
    if (!CFBasicHashIsMutable((CFBasicHashRef)hc)) {
        CFLog(kCFLogLevelError, CFSTR("%s(): immutable collection %p given to mutating function"), __PRETTY_FUNCTION__, hc);
    }
    CF_OBJC_KVO_WILLCHANGE(hc, key);
    CFBasicHashReplaceValue((CFBasicHashRef)hc, (uintptr_t)key, (uintptr_t)value);
    CF_OBJC_KVO_DIDCHANGE(hc, key);
}

#if CFDictionary
void CFDictionarySetValue(CFMutableHashRef hc, const_any_pointer_t key, const_any_pointer_t value) {
#endif
#if CFSet || CFBag
void CFDictionarySetValue(CFMutableHashRef hc, const_any_pointer_t key) {
    const_any_pointer_t value = key;
#endif
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (CFSwiftRef)hc, NSMutableDictionary.__setObject, key, value);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableDictionary *)hc, __setObject:(id)value forKey:(id)key);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableSet *)hc, setObject:(id)key);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFAssert2(CFBasicHashIsMutable((CFBasicHashRef)hc), __kCFLogAssertion, "%s(): immutable collection %p passed to mutating operation", __PRETTY_FUNCTION__, hc);
    if (!CFBasicHashIsMutable((CFBasicHashRef)hc)) {
        CFLog(kCFLogLevelError, CFSTR("%s(): immutable collection %p given to mutating function"), __PRETTY_FUNCTION__, hc);
    }
    CF_OBJC_KVO_WILLCHANGE(hc, key);
//#warning this for a dictionary used to not replace the key
    CFBasicHashSetValue((CFBasicHashRef)hc, (uintptr_t)key, (uintptr_t)value);
    CF_OBJC_KVO_DIDCHANGE(hc, key);
}
    
void CFDictionaryRemoveValue(CFMutableHashRef hc, const_any_pointer_t key) {
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (CFSwiftRef)hc, NSMutableDictionary.removeObjectForKey, key);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableDictionary *)hc, removeObjectForKey:(id)key);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableSet *)hc, removeObject:(id)key);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFAssert2(CFBasicHashIsMutable((CFBasicHashRef)hc), __kCFLogAssertion, "%s(): immutable collection %p passed to mutating operation", __PRETTY_FUNCTION__, hc);
    if (!CFBasicHashIsMutable((CFBasicHashRef)hc)) {
        CFLog(kCFLogLevelError, CFSTR("%s(): immutable collection %p given to mutating function"), __PRETTY_FUNCTION__, hc);
    }
    CF_OBJC_KVO_WILLCHANGE(hc, key);
    CFBasicHashRemoveValue((CFBasicHashRef)hc, (uintptr_t)key);
    CF_OBJC_KVO_DIDCHANGE(hc, key);
}

void CFDictionaryRemoveAllValues(CFMutableHashRef hc) {
#if CFDictionary
    if (CFDictionary) // CF_SWIFT_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (CFSwiftRef)hc, NSMutableDictionary.removeAllObjects);
    if (CFDictionary) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableDictionary *)hc, removeAllObjects);
#endif
#if CFSet
    if (CFSet) CF_OBJC_FUNCDISPATCHV(CFDictionaryGetTypeID(), void, (NSMutableSet *)hc, removeAllObjects);
#endif
    __CFGenericValidateType(hc, CFDictionaryGetTypeID());
    CFAssert2(CFBasicHashIsMutable((CFBasicHashRef)hc), __kCFLogAssertion, "%s(): immutable collection %p passed to mutating operation", __PRETTY_FUNCTION__, hc);
    if (!CFBasicHashIsMutable((CFBasicHashRef)hc)) {
        CFLog(kCFLogLevelError, CFSTR("%s(): immutable collection %p given to mutating function"), __PRETTY_FUNCTION__, hc);
    }
    CF_OBJC_KVO_WILLCHANGEALL(hc);
    CFBasicHashRemoveAllValues((CFBasicHashRef)hc);
    CF_OBJC_KVO_DIDCHANGEALL(hc);
}

#undef CF_OBJC_KVO_WILLCHANGE
#undef CF_OBJC_KVO_DIDCHANGE
#undef CF_OBJC_KVO_WILLCHANGEALL
#undef CF_OBJC_KVO_DIDCHANGEALL

// clang-format on
