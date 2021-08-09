// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDCharacter.generated.h"

UCLASS(Blueprintable)
class TESTPROJECT_API ATDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	//Set On Edit widget 
	UPROPERTY(EditAnyWhere, Category = "WidgetPlayer")
		TSubclassOf<class UPlayerWidget> ClassWidgetInterface;
		
	//Status Player
	class AActor* InteractionACtor;
	float MoneyPlayer;
	class UPlayerWidget* WidgetPlayer;


	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;



public:

	void PreInteractAndRotateToObcjet(AActor* ActorToInteract, FText& NameObject);
	void RotateToActor(AActor * ACtorToRotate);



	// Inherited Functions from Interface for interaction



	void AddMoneyPlayer(int32 AmountMoney);
	void SetSpeedPlayer(float NewSpeedPlayer);

	FTimerHandle SpeedTimer;

	//Call From Player Widget
	UFUNCTION()
		void Interaction();


	UFUNCTION()
		void ResetSpeed();

};
