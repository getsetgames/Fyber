//
//  Created by Robert Segal on 2016-04-04.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "CoreUObject.h"
#include "Engine.h"

#if PLATFORM_IOS
#import <CommonCrypto/CommonDigest.h>
#import <AdSupport/AdSupport.h>
#endif

#include "IFyber.h"

#include "FyberClasses.h"

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.

DECLARE_LOG_CATEGORY_EXTERN(LogFyber, Log, All);
