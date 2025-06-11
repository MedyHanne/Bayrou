#include "EndZone.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "OurMacros.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TargetArrow.h"
#include "Teleporter.h"
#include "ChallengeOfJade.h"

AEndZone::AEndZone()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;

	beaconLight = CreateDefaultSubobject<USpotLightComponent>("BeaconLight");
	beaconLight->SetupAttachment(mesh);

	beaconLight->SetRelativeLocation(FVector(0, 0, 500));
	beaconLight->SetIntensity(1000.0f);
	beaconLight->SetLightColor(FLinearColor::Green);
	beaconLight->SetInnerConeAngle(10.0f);
	beaconLight->SetOuterConeAngle(30.0f);
	beaconLight->SetAttenuationRadius(10000.0f);
	beaconLight->bUseInverseSquaredFalloff = false;
	beaconLight->SetCastShadows(false);
	beaconLight->SetMobility(EComponentMobility::Movable);
	beaconLight->SetVisibility(false);

}

void AEndZone::BeginPlay()
{
	Super::BeginPlay();
	//Init();
	
}

void AEndZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//isActive ? mesh->SetVisibility(true) : mesh->SetVisibility(false);

	//if (arrow)
	//	isActive ? arrow->SetArrowVisibility(true) : arrow->SetArrowVisibility(false);

	//if (beaconLight)
	//{
	//	beaconLight->SetVisibility(isActive);
	//	if (isActive)
	//	{
	//		if (challenge && challenge->GetRaceStarted())
	//		{
	//			float timeLeft = challenge->GetTimeLimit() - challenge->GetCurrentTime();
	//			if (timeLeft <= blinkingStartTime)
	//			{
	//				blinkTimer += DeltaTime;
	//				if (blinkTimer >= 0.5f)
	//				{
	//					blinkTimer = 0.0f;
	//					blinkState = !blinkState;
	//					beaconLight->SetVisibility(blinkState);
	//					mesh->SetVisibility(blinkState);
	//				}
	//			}
	//			else
	//			{
	//				beaconLight->SetVisibility(true);
	//			}
	//		}
	//	}
	//}

}

void AEndZone::Init()
{
	
}

void AEndZone::InitSpotLight()
{
	
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

void AEndZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor || !isActive)return;

	ACharacter* _player = Cast< ACharacter>(OtherActor);
	if (_player && challenge->IsPlayerDashing())
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

