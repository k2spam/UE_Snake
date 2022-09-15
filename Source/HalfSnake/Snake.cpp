// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake.h"
#include "SnakeElement.h"
#include "Interactable.h"

// Sets default values
ASnake::ASnake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 0.5;
	LastMoveDirection = EMovementDirection::UP;
}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(5);
}

// Called every frame
void ASnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnake::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++)
	{
		FVector newLocation(-SnakeElements.Num() * ElementSize, 0, 0);
		FTransform newTransform(newLocation);
		ASnakeElement* newElement = GetWorld()->SpawnActor<ASnakeElement>(SnakeElementClass, newTransform);
		newElement->SnakeOwner = this;
		int32 ElementIndex = SnakeElements.Add(newElement);

		if (ElementIndex == 0)
		{
			newElement->SetFirstElementType();
		}

		newElement->ToggleVisibility(false);
	}
}

void ASnake::Move()
{
	FVector MovementVector(ForceInitToZero);

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}

	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
		CurrentElement->ToggleVisibility(true);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
	SnakeElements[0]->ToggleVisibility(true);
}

void ASnake::SnakeElementOverlap(ASnakeElement* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}

void ASnake::IncrementMovementSpeed()
{
	MovementSpeed -= MovementSpeed * MovementSpeedStep / 100;
	SetActorTickInterval(MovementSpeed);
}

