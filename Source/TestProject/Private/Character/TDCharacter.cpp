// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Widgets/PlayerWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interface/TDUseInterface.h"
// Sets default values
ATDCharacter::ATDCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Geometry/MaterialCursor/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;



}

// Called when the game starts or when spawned
void ATDCharacter::BeginPlay()
{
	Super::BeginPlay();


	// Create and add to vieport Widget
	if (ClassWidgetInterface)
	{

		WidgetPlayer = CreateWidget<UPlayerWidget>(GetWorld()->GetFirstPlayerController(), ClassWidgetInterface);
		WidgetPlayer->AddToViewport();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Add Widget");
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, " You nedd to add Widget in Editor");
	}
	
}

// Called every frame
void ATDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void ATDCharacter::PreInteractAndRotateToObcjet(AActor * ActorToInteract, FText & NameObject)
{
	//If player Intered to collision or Touched to Interacteble actor


	if (WidgetPlayer)
	{
		if (ActorToInteract)
		{

			WidgetPlayer->ShowInteractionButton(true, NameObject);
			InteractionACtor = ActorToInteract;
			RotateToActor(ActorToInteract);

		}

		else
		{
			WidgetPlayer->ShowInteractionButton(false, NameObject);
		}
	}
}

void ATDCharacter::RotateToActor(AActor * ACtorToRotate)
{
	if (ACtorToRotate)
	{
		GetCharacterMovement()->StopMovementImmediately();
		FRotator LookAtObject = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), ACtorToRotate->GetActorLocation());
		this->SetActorRotation(FRotator(0, LookAtObject.Yaw, 0));
	}
}

void ATDCharacter::AddMoneyPlayer(int32 AmountMoney)
{
	MoneyPlayer += AmountMoney;
	WidgetPlayer->UpdateMoneyText(MoneyPlayer);
}

void ATDCharacter::SetSpeedPlayer(float NewSpeedPlayer)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeedPlayer;

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, " Add Speed");


	//Add Timer

	GetWorld()->GetTimerManager().SetTimer(SpeedTimer, this, &ATDCharacter::ResetSpeed, 30.0f, false, 30.0f);
	WidgetPlayer->ChangePlayerSpeedInformation(false);//If false that increased speed 

}

void ATDCharacter::Interaction()
{

	if (WidgetPlayer)
	{

		if (InteractionACtor)
		{

			ITDUseInterface* Interface = Cast<ITDUseInterface>(InteractionACtor);

			if (Interface)
			{
				Interface->InteractWithObject(this);

				RotateToActor(InteractionACtor);
			}
		}
	}
}

void ATDCharacter::ResetSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, " ResetSpeed Speed");


	GetWorld()->GetTimerManager().ClearTimer(SpeedTimer);
	WidgetPlayer->ChangePlayerSpeedInformation(true);//If false that Normal speed 
}


