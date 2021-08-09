// Fill out your copyright notice in the Description page of Project Settings.


#include "Store/TDStore.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

//Created Classes
#include "Character/TDCharacter.h"
#include "Widgets/SroreWidget.h"
#include "InteractiveObject/TDInteractiveObject.h"


// Sets default values
ATDStore::ATDStore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initail Components
	//Arrows
	FirstPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirstPoint"));
	SecondPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SecondPoint"));
	ThirdPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ThirdPoint"));
	//Mesh
	StoreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//Box Collision
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = StoreMesh; // Root is Mesh

	StoreWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StoreWidgetComponent"));

	//Bind Events
	StoreMesh->OnClicked.AddDynamic(this, &ATDStore::InputOnMesh);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATDStore::EnteredInCollision);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATDStore::LeaveFromCollision);


}

// Called when the game starts or when spawned
void ATDStore::BeginPlay()
{
	Super::BeginPlay();

	//Get Widget In DigetComponent
	WidgetForInteraction = Cast<USroreWidget>(StoreWidgetComponent->GetUserWidgetObject());

	if (WidgetForInteraction)
	{
		WidgetForInteraction->OwnerStore = this;
	}

}

// Called every frame
void ATDStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATDStore::BuyObject(TypeInteraction TypeObjet, int32 cost)
{



	// Setting parameters from the store widget 
	FVector SpawLocation;
	FRotator SpawnRotation;

	//Set Varible for interaction object 
	TypeInteraction TypeInteractObject = TypeInteraction::DeletebleObject;
	int32 EffectivinesObjct = 0;
	FText NameSpawndeObject;

	switch (TypeObjet)
	{
	case DeletebleObject:
		SpawLocation = FirstPoint->GetComponentLocation();
		SpawnRotation = FirstPoint->GetComponentRotation();
		TypeInteractObject = DeletebleObject;
		EffectivinesObjct = 0;
		NameSpawndeObject = FText::FromString("Deleteble Object");
		break;

	case ResizeStore:
		SpawLocation = SecondPoint->GetComponentLocation();
		SpawnRotation = SecondPoint->GetComponentRotation();
		TypeInteractObject = ResizeStore;
		EffectivinesObjct = 0;
		NameSpawndeObject = FText::FromString("Resizible Obcjet");
		break;

	case SpeedObject:
		SpawLocation = ThirdPoint->GetComponentLocation();
		SpawnRotation = SecondPoint->GetComponentRotation();
		TypeInteractObject = SpeedObject;
		EffectivinesObjct = 4000;
		NameSpawndeObject = FText::FromString("Speed Object");
		break;

	default:
		SpawLocation = FirstPoint->GetComponentLocation();
		SpawnRotation = SecondPoint->GetComponentRotation();
		break;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, " Spawn Obcjet");
	
	//Spawn Actor
	const FActorSpawnParameters Parametrs;
	
	ATDInteractiveObject* SpawnedObject = GetWorld()->SpawnActor<ATDInteractiveObject>(ActorToSpawn, SpawLocation, SpawnRotation, Parametrs);
	
	if (SpawnedObject)
	{
		
		SpawnedObject->TypeIneractionObject = TypeObjet;
		SpawnedObject->Effectivines = EffectivinesObjct;
		SpawnedObject->TypeIneractionObject = TypeInteractObject;
		SpawnedObject->NameObjct = NameSpawndeObject;
		SpawnedObject->OwningStore = this;
		SpawnedObject->OwningCharacterPlayer = PlayerCharacter;
		SpawnedObject->SetNameCurrentObject();
	
	}



}

void ATDStore::InputOnMesh(UPrimitiveComponent * pComponent, FKey inKey)
{
	FText Name = FText::FromString("Store");


	if (PlayerCharacter)
	{


		PlayerCharacter->PreInteractAndRotateToObcjet(this, Name);
		PlayerCharacter->InteractionACtor = this;

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, " Player Entered To Store Collision");
	}


}

void ATDStore::EnteredInCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FText Name = FText::FromString("Store");

	PlayerCharacter = Cast<ATDCharacter>(OtherActor);
	if (PlayerCharacter)
	{


		PlayerCharacter->PreInteractAndRotateToObcjet(this, Name);
		PlayerCharacter->InteractionACtor = this;

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, " Player Entered To Store Collision");
	}
}

void ATDStore::LeaveFromCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (PlayerCharacter)
	{

		FText Name = FText::FromString("");
		PlayerCharacter->PreInteractAndRotateToObcjet(nullptr, Name);
		
		WidgetForInteraction->SetVisibilityWidget(false);
		WidgetForInteraction->CurrentCharacter = nullptr;
		PlayerCharacter = nullptr;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, " Player LeaveFrom Store Collision");
		
	}
}



void ATDStore::InteractWithObject(ATDCharacter* Character)
{
	if (WidgetForInteraction)
	{
		WidgetForInteraction->MoneyCurrentPlayer = Character->MoneyPlayer;
		WidgetForInteraction->SetVisibilityWidget(true);
		WidgetForInteraction->CurrentCharacter = Character;

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, " Player  Interact With Store ");


	}

}
