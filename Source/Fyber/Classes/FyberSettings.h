//
//  Created by Robert Segal on 2016-04-04.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "FyberSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UFyberSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UFyberSettings(const FObjectInitializer& ObjectInitializer);
};
