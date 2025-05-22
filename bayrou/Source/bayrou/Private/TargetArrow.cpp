#include "TargetArrow.h"

ATargetArrow::ATargetArrow()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void ATargetArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!mesh)return;
	Levitate(DeltaTime);
}

void ATargetArrow::Levitate(float _delta)
{
	FVector _loc = GetActorLocation();
	_loc.Z += FMath::Sin(runningTime * levitateSpeed) * levitateAmplitude * _delta;

	SetActorLocation(_loc);
	runningTime += _delta;
}

void ATargetArrow::Rotate(float _delta)
{
	FQuat _rotationDelta = FQuat(FRotator(0.f, rotationSpeed * _delta, 0.f));
	mesh->AddLocalRotation(_rotationDelta, false, nullptr, ETeleportType::None);
}

void ATargetArrow::SetArrowVisibility(bool _isVisible)
{
	mesh->SetVisibility(_isVisible);
}

