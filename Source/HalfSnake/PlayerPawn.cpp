// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Snake.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	RootComponent = PawnCamera;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawn::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawn::HandlePlayerHorizontalInput);
}

void APlayerPawn::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnake>(SnakeActorClass, FTransform());
}

void APlayerPawn::HandlePlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if(value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN)
			SnakeActor->LastMoveDirection = EMovementDirection::UP;
		else if(value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP)
			SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
	}
}

void APlayerPawn::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::LEFT)
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT)
			SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
	}
}

