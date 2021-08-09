// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDUseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTDUseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TESTPROJECT_API ITDUseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


	//Call When Player Press button on Widget interface
	UFUNCTION()
		virtual void InteractWithObject(ATDCharacter* Character) = 0;

};
