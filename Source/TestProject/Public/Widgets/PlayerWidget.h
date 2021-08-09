// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual bool Initialize();

	virtual void NativeConstruct() override;



	// Player's Character 
	class ATDCharacter* OwningPlayerCharacter;

	//Widget Elements

		// Button For Interaction
	UPROPERTY(meta = (BindWidget))
		class UButton* InteractButton;


	//Name Interaction object
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* NameInteracionObject;


	//Vertical box for hide text and button
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* ButtonVerticalBox;


	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MoneyPlayerTextBlock;


	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SpeedPlayerTextBlock;

public:

	// Call Whe Character Pre Interact wih Objcts
	void ShowInteractionButton(bool ShowButton, FText& Name);
	void UpdateMoneyText(int32 AmountMoneyPlayer);
	void ChangePlayerSpeedInformation(bool NormalSpeed);
	
};
