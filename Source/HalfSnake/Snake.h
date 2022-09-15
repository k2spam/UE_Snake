// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Snake.generated.h"

class ASnakeElement;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class HALFSNAKE_API ASnake : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnake();
	
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeElement> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
		float ElementSize;

	UPROPERTY()
		float MovementSpeed;

	UPROPERTY(EditDefaultsOnly)
		float MovementSpeedStep;

	UPROPERTY()
		TArray<ASnakeElement*> SnakeElements;

	UPROPERTY()
		EMovementDirection LastMoveDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void AddSnakeElement(int ElementsNum = 1);
	UFUNCTION(BlueprintCallable)
		void Move();
	UFUNCTION()
		void SnakeElementOverlap(ASnakeElement* OverlappedElement, AActor* Other);
	UFUNCTION()
		void IncrementMovementSpeed();
};
