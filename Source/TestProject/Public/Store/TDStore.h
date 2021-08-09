// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "Enum/TypeObjectsEnum.h"
#include "Interface/TDUseInterface.h"
#include "TDStore.generated.h"

UCLASS()
class TESTPROJECT_API ATDStore : public AActor, public ITDUseInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDStore();

	UPROPERTY(EditAnyWhere, Category = "Components")
		class UArrowComponent* FirstPoint;

	UPROPERTY(EditAnyWhere, Category = "Components")
		class UArrowComponent* SecondPoint;

	UPROPERTY(EditAnyWhere, Category = "Components")
		class UArrowComponent* ThirdPoint;

	UPROPERTY(EditAnyWhere, Category = "Components")
		class UStaticMeshComponent* StoreMesh;

	UPROPERTY(EditAnyWhere, Category = "Components")
		class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnyWhere, Category = "Components")
		class UWidgetComponent* StoreWidgetComponent;

	
	UPROPERTY(EditAnyWhere, Category = "Components")
		TSubclassOf<class ATDInteractiveObject> ActorToSpawn;
		

	// Widget for Player's interaction 
	class USroreWidget* WidgetForInteraction;
	class ATDCharacter* PlayerCharacter;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void InteractWithObject(ATDCharacter* Character)override;

	UFUNCTION()
		void BuyObject(TypeInteraction TypeObjet, int32 cost);

	UFUNCTION()
		void InputOnMesh(UPrimitiveComponent* pComponent, FKey inKey);

	//Collision Events
	UFUNCTION()
		void EnteredInCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void LeaveFromCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);
};
