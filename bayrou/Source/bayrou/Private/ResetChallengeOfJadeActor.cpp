#include "ResetChallengeOfJadeActor.h"
#include "GameFramework/Character.h"
#include "ChallengeOfJade.h"

AResetChallengeOfJadeActor::AResetChallengeOfJadeActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	resetMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = resetMesh;
}

void AResetChallengeOfJadeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AResetChallengeOfJadeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResetChallengeOfJadeActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor || !challengeToReset)return;

	ACharacter* _player = Cast<ACharacter>(OtherActor);
	if (!_player)return;

	bool _raceStarted = challengeToReset->GetRaceStarted();
	if (!_raceStarted)return;
	challengeToReset->ChallengeFailed();
	challengeToReset->SetRaceStarted(false);
}

