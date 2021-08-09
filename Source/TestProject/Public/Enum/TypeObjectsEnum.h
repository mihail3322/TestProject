// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TypeObjectsEnum.generated.h"


UENUM(BlueprintType)
enum TypeInteraction
{
	Money           UMETA(DisplayName = "Money"),
	ResizeStore     UMETA(DisplayName = "Resize Store"),
	SpeedObject     UMETA(DisplayName = "Add Player Speed"),
	DeletebleObject UMETA(DisplayName = "Destroy After 3 using")

};
