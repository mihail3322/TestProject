// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SroreWidget.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Character/TDCharacter.h"
#include "Store/TDStore.h"


bool USroreWidget::Initialize()
{
	bool CheckOnInitail = Super::Initialize();




	return CheckOnInitail;
}

void USroreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind to click Fuction
	SpeedObjectButton->OnClicked.AddDynamic(this, &USroreWidget::SpeedButtonFunction);
	DeletableObjectButton->OnClicked.AddDynamic(this, &USroreWidget::DeletebleButtonFunction);
	SizeStoreObjectButton->OnClicked.AddDynamic(this, &USroreWidget::SizeButtonFunction);
	CloseStore->OnClicked.AddDynamic(this, &USroreWidget::CloseButtonFunction);
	BuyObjectObjectButton->OnClicked.AddDynamic(this, &USroreWidget::BuyButtonFunction);

}


void USroreWidget::SetVisibilityWidget(bool VisibleWidget)
{
	if (VisibleWidget)
	{
		ParentSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		MoneyPlayerTextBlock->SetText(FText::AsNumber(MoneyCurrentPlayer));

		CostsTextBlock->SetText(FText::AsNumber(0));

	}
	else
	{
		ParentSizeBox->SetVisibility(ESlateVisibility::Collapsed);
	}

}

void USroreWidget::SpeedButtonFunction()
{

	TypeObjectSelectedObject = SpeedObject;
	EffectivitesSelectedObject = 2000;
	CurrentCostObjct = 300;

	CostsTextBlock->SetText(FText::AsNumber(CurrentCostObjct));

}

void USroreWidget::SizeButtonFunction()
{

	TypeObjectSelectedObject = ResizeStore;
	EffectivitesSelectedObject = 0;
	CurrentCostObjct = 400;
	CostsTextBlock->SetText(FText::AsNumber(CurrentCostObjct));
}

void USroreWidget::DeletebleButtonFunction()
{
	TypeObjectSelectedObject = DeletebleObject;
	EffectivitesSelectedObject = 0;
	CurrentCostObjct = 500;
	CostsTextBlock->SetText(FText::AsNumber(CurrentCostObjct));

}

void USroreWidget::BuyButtonFunction()
{
	if (CurrentCostObjct > 0)
	{
		MoneyCurrentPlayer = CurrentCharacter->MoneyPlayer;

		if ((MoneyCurrentPlayer - CurrentCostObjct) >= 0)
		{
			if (OwnerStore && CurrentCharacter)
			{
				if (!(TPurchasedObjects.Contains(TypeObjectSelectedObject)))
				{


					TPurchasedObjects.Add(TypeObjectSelectedObject);

					OwnerStore->BuyObject(TypeObjectSelectedObject, EffectivitesSelectedObject);

					CurrentCharacter->AddMoneyPlayer(CurrentCostObjct*(-1));
					MoneyCurrentPlayer = CurrentCharacter->MoneyPlayer;
					MoneyPlayerTextBlock->SetText(FText::AsNumber(MoneyCurrentPlayer));
				}
				else
				{
					CostsTextBlock->SetText(FText::FromString("Not available"));
				}
			}
		}
	}
	else
	{
		CostsTextBlock->SetText(FText::FromString("Select obcjet"));
	}

}

void USroreWidget::CloseButtonFunction()
{
	SetVisibilityWidget(false);
}
