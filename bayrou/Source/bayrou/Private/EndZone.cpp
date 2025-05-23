#include "EndZone.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "OurMacros.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TargetArrow.h"
#include "Teleporter.h"

AEndZone::AEndZone()
{
	PrimaryActorTick.bCanEverTick = true;

	endTrigger = CreateDefaultSubobject<UBoxComponent>("EndTrigger");
	RootComponent = endTrigger;
	endTrigger->SetGenerateOverlapEvents(true);

}

void AEndZone::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void AEndZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (spotLight)
		isActive ? spotLight->SetVisibility(true) : spotLight->SetVisibility(false);

	if (arrow)
		isActive ? arrow->SetArrowVisibility(true) : arrow->SetArrowVisibility(false);

}

void AEndZone::Init()
{
	endTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEndZone::HandleOverlap);
	InitSpotLight();
}

void AEndZone::InitSpotLight()
{
	spotLight = NewObject<USpotLightComponent>(this, "ObjectiveSpotlight");
	if (spotLight)
	{
		spotLight->SetupAttachment(endTrigger);
		spotLight->RegisterComponent();

		spotLight->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));

		FRotator _rotationDown = FRotator(-90.f, 0.f, 0.f);
		spotLight->SetRelativeRotation(_rotationDown);

		spotLight->SetIntensity(5000000.0f);
		spotLight->SetLightColor(FLinearColor::Green);
		spotLight->SetInnerConeAngle(2.0f);
		spotLight->SetOuterConeAngle(5.0f);
		spotLight->SetAttenuationRadius(15000.0f);
		spotLight->bUseInverseSquaredFalloff = false;
		spotLight->SetCastShadows(false);
		spotLight->SetMobility(EComponentMobility::Movable);
		spotLight->SetVisibility(false);
	}
}

void AEndZone::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !isActive)return;

	ACharacter* _player = Cast< ACharacter>(OtherActor);
	if (_player)
	{
		PRINT_MSG("End");
		isActive = false;
		onEndZoneReached.Broadcast(OtherActor);
		if (teleporter)
		{
			teleporter->SetIsActivated(true);
		}
	}
}

