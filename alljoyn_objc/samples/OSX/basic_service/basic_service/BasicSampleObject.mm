////////////////////////////////////////////////////////////////////////////////
//    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
//
//    SPDX-License-Identifier: Apache-2.0
//
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//
//     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//     PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import "BasicSampleObject.h"
#import "BasicSampleObjectImpl.h"
#import "AJNInterfaceDescription.h"

@implementation MyBasicSampleObject

@synthesize delegate = _delegate;

- (BasicSampleObjectImpl*)busObject
{
    return (BasicSampleObjectImpl*)self.handle;
}

- (id)initWithBusAttachment:(AJNBusAttachment *)busAttachment onPath:(NSString *)path
{
    self = [super initWithBusAttachment:busAttachment onPath:path];
    if (self) {
        BOOL result;
        
        AJNInterfaceDescription *interfaceDescription;
        
        // create an interface description and add the concatenate method to it
        //
        interfaceDescription = [busAttachment createInterfaceWithName:kBasicObjectInterfaceName withInterfaceSecPolicy:AJN_IFC_SECURITY_OFF];

        result = [interfaceDescription addMethodWithName:kBasicObjectMethodName inputSignature:@"ss" outputSignature:@"s" argumentNames:[NSArray arrayWithObjects:@"str1", @"str2", @"outStr", nil]];
        
        if (result != ER_OK) {
            [self.delegate didReceiveStatusUpdateMessage:@"Failed to create interface 'org.alljoyn.Bus.method_sample'\n"];
            
            @throw [NSException exceptionWithName:@"BusObjectInitFailed" reason:@"Unable to add method to interface" userInfo:nil];
        }
        [self.delegate didReceiveStatusUpdateMessage:@"Interface Created.\n"];
        
        [interfaceDescription activate];
        
        // create the internal C++ bus object
        //
        BasicSampleObjectImpl *busObject = new BasicSampleObjectImpl(*((ajn::BusAttachment*)busAttachment.handle), [path UTF8String], (id<MyMethodSample>)self);
        
        self.handle = busObject;
    }
    return self;
}

- (void)dealloc
{
    BasicSampleObjectImpl *busObject = [self busObject];
    delete busObject;
    self.handle = nil;
}

- (void)objectWasRegistered
{
    [self.delegate didReceiveStatusUpdateMessage:@"MyBasicSampleObject was registered.\n"];
}

@end