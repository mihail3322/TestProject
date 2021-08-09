// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "Enum/TypeObjectsEnum.h"
#include "Interface/TDUseInterface.h"
#include "TDInteractiveObject.generated.h"

UCLASS()
class TESTPROJECT_API ATDInteractiveObject : public AActor, public ITDUseInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDInteractiveObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditAnyWhere, Category = "Components")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnyWhere, Category = "Components")
		class  USphereComponent* SphereCollision;

	UPROPERTY(EditAnyWhere, Category = "Components")
		class  UTextRenderComponent* TextOnObject;



	TypeInteraction TypeIneractionObject = Money;

	int32 Effectivines = 2000;
	FText NameObjct = FText::FromString("Money");

	class ATDStore* OwningStore;
	class ATDCharacter* OwningCharacterPlayer;


	void UseObject();
	void AddMoneyToPlayer();
	void SetSizeStore();
	void DestroingSelf();
	void AddSpeedPlayer();
	void SetNameCurrentObject();

	//Interface Function
	virtual void InteractWithObject(ATDCharacter* Character)override;


	//Collision Events
	UFUNCTION()
		void EnteredInCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void LeaveFromCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void InputOnMesh(UPrimitiveComponent* pComponent, FKey inKey);

};
