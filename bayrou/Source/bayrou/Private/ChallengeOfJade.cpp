#include "ChallengeOfJade.h"
#include "OurMacros.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "EndZone.h"
#include "GameFramework/Character.h"

AChallengeOfJade::AChallengeOfJade()
{
	PrimaryActorTick.bCanEverTick = true;

	startTrigger = CreateDefaultSubobject<UBoxComponent>("StartTrigger");
	RootComponent = startTrigger;
	startTrigger->OnComponentBeginOverlap.AddDynamic(this, &AChallengeOfJade::OnPlayerEnterStart);
}

void AChallengeOfJade::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AChallengeOfJade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (raceStarted)
		UpdateTime(DeltaTime);

}

void AChallengeOfJade::ChallengeFailed()
{
	PRINT_MSG("You Loose ! ");
	raceCompleted = false;
	SetMaterial(looseMat);
	endZone->SetIsActive(false);
	for (AActor* _platform : allPlatforms)
	{
		_platform->SetActorHiddenInGame(true);
	}
}

void AChallengeOfJade::Init()
{
	if (endZone)
	{
		endZone->OnEndZoneReached().AddDynamic(this, &AChallengeOfJade::OnPlayerReachEnd);
	}

	for (AActor* _platform : allPlatforms)
	{
		_platform->SetActorHiddenInGame(true);
	}
}

void AChallengeOfJade::UpdateTime(float _deltaTime)
{
	currentTime += _deltaTime;
}

void AChallengeOfJade::ChallengeSucceeded(AActor* _player)
{
	ACharacter* _playerCast = Cast< ACharacter>(_player);
	if (_playerCast)
	{
		PRINT_MSG_COLOR("You Won ! ", FLinearColor::Green);
		raceCompleted = true;
		SetMaterial(mat);
		for (AActor* _platform : allPlatforms)
		{
			_platform->SetActorHiddenInGame(true);
		}
		//endZone->SetIsActive(false);

		//Add the life here

	}
}

void AChallengeOfJade::SetMaterial(UMaterial* _mat)
{
	if (!_mat) return;

	if (right)
	{
		UStaticMeshComponent* _mesh = right->FindComponentByClass<UStaticMeshComponent>();
		if (_mesh)
		{
			_mesh->SetMaterial(0, _mat);
		}
	}

	if (left)
	{
		UStaticMeshComponent* _mesh = left->FindComponentByClass<UStaticMeshComponent>();
		if (_mesh)
		{
			_mesh->SetMaterial(0, _mat);
		}
	}
}

void AChallengeOfJade::OnPlayerEnterStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (raceStarted || raceCompleted)return;
	if (!OtherActor)return;
	ACharacter* _player = Cast< ACharacter>(OtherActor);

	if (_player)
	{
		raceStarted = true;
		currentTime = 0.0f;
		SetMaterial(onGoingMat);
		endZone->SetIsActive(true);
		PRINT_MSG("Begin");
		for (AActor* _platform : allPlatforms)
		{
			_platform->SetActorHiddenInGame(false);
		}
	}
}

void AChallengeOfJade::OnPlayerReachEnd(AActor* _overlappedActor)
{
	if (!raceStarted) return;
	raceStarted = false;
	//raceCompleted = true;

	//Check if the player pass the end before the time => Win or after => Loose
	if (HasWin())
		ChallengeSucceeded(_overlappedActor);
	else
		ChallengeFailed();

	endZone->SetIsActive(false);
}

