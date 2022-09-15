// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElement.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Snake.h"

// Sets default values
ASnakeElement::ASnakeElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
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

void ASnakeElement::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnake>(Interactor);

	if (IsValid(Snake))
	{
		Snake->Destroy();
	}
}

void ASnakeElement::SetFirstElementType_Implementation()
{
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElement::HandleBeginOverlap);
}

void ASnakeElement::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
										AActor* OtherActor, 
										UPrimitiveComponent* OtherComp, 
										int32 OtherBodyIndex, 
										bool bFromSweep, 
										const FHitResult& SweepResult)
{
	if (IsValid(SnakeOwner))
	{
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
	}
}

void ASnakeElement::ToggleCollision()
{
	if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::QueryOnly)
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASnakeElement::ToggleVisibility(bool Show)
{
	MeshComponent->SetVisibility(Show);
}

