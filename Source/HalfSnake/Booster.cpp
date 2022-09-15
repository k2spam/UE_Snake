// Fill out your copyright notice in the Description page of Project Settings.


#include "Booster.h"
#include "Snake.h"

// Sets default values
ABooster::ABooster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABooster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABooster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABooster::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnake>(Interactor);
	if (IsValid(Snake))
	{
		Snake->IncrementMovementSpeed();
		this->Destroy();
	}
}

