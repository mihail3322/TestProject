// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Character/TDCharacter.h"

bool UPlayerWidget::Initialize()
{
	bool InitializeResult = Super::Initialize();







	return InitializeResult;
}


void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get Pawn and 

	OwningPlayerCharacter = Cast<ATDCharacter>(this->GetOwningPlayerPawn());

	if (OwningPlayerCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Found Player");
		InteractButton->OnClicked.AddDynamic(OwningPlayerCharacter, &ATDCharacter::Interaction);



	}



}







void UPlayerWidget::ShowInteractionButton(bool ShowButton, FText & Name)
{

	if (ShowButton)
	{
		ButtonVerticalBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		NameInteracionObject->SetText(Name);
	}

	else
	{
		ButtonVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
	}

}

void UPlayerWidget::UpdateMoneyText(int32 AmountMoneyPlayer)
{

	MoneyPlayerTextBlock->SetText(FText::AsNumber(AmountMoneyPlayer));
}

void UPlayerWidget::ChangePlayerSpeedInformation(bool NormalSpeed)
{
	if (NormalSpeed)
	{
		SpeedPlayerTextBlock->SetText(FText::FromString("Normal Speed"));
	}
	else
	{
		SpeedPlayerTextBlock->SetText(FText::FromString(" Increased Speed "));
	}
}
