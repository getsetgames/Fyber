//
//  Created by Robert Segal on 2016-04-04.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "FyberFunctions.h"
#include "FyberComponent.generated.h"

UCLASS(ClassGroup=Advertising, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class UFyberComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:

	void OnRegister() override;
	void OnUnregister() override;
	
private:	

};
