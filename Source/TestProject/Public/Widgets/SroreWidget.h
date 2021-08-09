// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/TypeObjectsEnum.h"
#include "SroreWidget.generated.h"


/**
 * 
 */
UCLASS()
class TESTPROJECT_API USroreWidget : public UUserWidget
{
	GENERATED_BODY()


		virtual bool Initialize();

	virtual void NativeConstruct() override;


	// Creting buttons
	UPROPERTY(meta = (BindWidget))
		class UButton* CloseStore;

	UPROPERTY(meta = (BindWidget))
		class UButton* SpeedObjectButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* DeletableObjectButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* SizeStoreObjectButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* BuyObjectObjectButton;

	UPROPERTY(meta = (BindWidget))
		class USizeBox* ParentSizeBox;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MoneyPlayerTextBlock;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CostsTextBlock;

public:

	void SetVisibilityWidget(bool VisibleWidget);

	class ATDStore* OwnerStore;
	class ATDCharacter* CurrentCharacter;
	int32 MoneyCurrentPlayer;
	int32 CurrentCostObjct;
	TypeInteraction TypeObjectSelectedObject;
	int32 EffectivitesSelectedObject;

	TArray<TypeInteraction> TPurchasedObjects;

	


	//Buttons Fucntions
	UFUNCTION()
		void SpeedButtonFunction();

	UFUNCTION()
		void SizeButtonFunction();

	UFUNCTION()
		void DeletebleButtonFunction();

	UFUNCTION()
		void BuyButtonFunction();

	UFUNCTION()
		void CloseButtonFunction();


	
};
