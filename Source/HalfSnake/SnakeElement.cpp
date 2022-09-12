// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElement.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ASnakeElement::ASnakeElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
}

// Called when the game starts or when spawned
void ASnakeElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeElement::SetFirstElementType_Implementation()
{
}

