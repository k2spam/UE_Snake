// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SnakeElement.generated.h"

class UStaticMeshComponent;
class ASnake;

UCLASS()
class HALFSNAKE_API ASnakeElement : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElement();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY()
		ASnake* SnakeOwner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	UFUNCTION(BlueprintNativeEvent)
		void SetFirstElementType();
		void SetFirstElementType_Implementation();

	UFUNCTION()
		void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
								AActor* OtherActor, 
								UPrimitiveComponent* OtherComp, 
								int32 OtherBodyIndex, 
								bool bFromSweep, 
								const FHitResult &SweepResult);

	UFUNCTION()
		void ToggleCollision();

	UFUNCTION()
		void ToggleVisibility(bool Show);
};
