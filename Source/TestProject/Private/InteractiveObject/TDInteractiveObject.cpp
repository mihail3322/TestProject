// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject/TDInteractiveObject.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Character/TDCharacter.h"
#include "Store/TDStore.h"

// Sets default values
ATDInteractiveObject::ATDInteractiveObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	TextOnObject = CreateAbstractDefaultSubobject<UTextRenderComponent>(TEXT("TextOnObject"));
	//Attach
	SphereCollision->SetupAttachment(Mesh);
	TextOnObject->SetupAttachment(Mesh);
	TextOnObject->SetRelativeLocationAndRotation(FVector(0, 0, 100), FRotator(0, 0, 0));

	//Bind events
	Mesh->OnClicked.AddDynamic(this, &ATDInteractiveObject::InputOnMesh);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATDInteractiveObject::EnteredInCollision);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ATDInteractiveObject::LeaveFromCollision);



}

// Called when the game starts or when spawned
void ATDInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
	SetNameCurrentObject();
}

// Called every frame
void ATDInteractiveObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void ATDInteractiveObject::UseObject()
{
	switch (TypeIneractionObject)
	{
	case Money:
		AddMoneyToPlayer();
		break;
	case ResizeStore:
		SetSizeStore();
		break;
	case SpeedObject:
		AddSpeedPlayer();
		break;
	case DeletebleObject:
		DestroingSelf();
		break;
	default:
		break;
	}
}

void ATDInteractiveObject::AddMoneyToPlayer()
{
	OwningCharacterPlayer->AddMoneyPlayer(Effectivines);
	this->Destroy();
}


void ATDInteractiveObject::SetSizeStore()
{
	if (OwningStore)
	{

		if (Effectivines == 0)
		{
			OwningStore->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
			Effectivines = 1;
		}

		else
		{
			OwningStore->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
			Effectivines = 0;
		}


	}
}

void ATDInteractiveObject::DestroingSelf()
{
	if (Effectivines >= 2)
	{
		this->Destroy();

	}
	else
	{
		Effectivines += 1;
	}
}

void ATDInteractiveObject::AddSpeedPlayer()
{


	if (OwningCharacterPlayer)
	{

		OwningCharacterPlayer->SetSpeedPlayer(float(Effectivines));
		this->Destroy();
	}
}



void ATDInteractiveObject::InteractWithObject(ATDCharacter * Character)
{
	OwningCharacterPlayer = Character;
	UseObject();

}



void ATDInteractiveObject::InputOnMesh(UPrimitiveComponent* pComponent, FKey inKey)
{

	if (OwningCharacterPlayer)
	{


		OwningCharacterPlayer->PreInteractAndRotateToObcjet(this, NameObjct);
		OwningCharacterPlayer->InteractionACtor = this;

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, " Player Entered To Store Collision");
	}

}

void ATDInteractiveObject::EnteredInCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	OwningCharacterPlayer = Cast<ATDCharacter>(OtherActor);

	if (OwningCharacterPlayer)
	{

		OwningCharacterPlayer->PreInteractAndRotateToObcjet(this, NameObjct);



	}


}

void ATDInteractiveObject::LeaveFromCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	OwningCharacterPlayer = Cast<ATDCharacter>(OtherActor);

	if (OwningCharacterPlayer)
	{

		OwningCharacterPlayer->PreInteractAndRotateToObcjet(nullptr, NameObjct);
		OwningCharacterPlayer = nullptr;


	}
}



void ATDInteractiveObject::SetNameCurrentObject()
{
	const TEnumAsByte<TypeInteraction> SurfaceEnum = TypeIneractionObject;
	FString EnumAsString = UEnum::GetValueAsString(SurfaceEnum.GetValue());
	TextOnObject->SetText(FText::FromString(EnumAsString));
}
