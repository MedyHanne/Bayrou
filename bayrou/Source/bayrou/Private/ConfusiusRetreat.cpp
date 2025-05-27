#include "ConfusiusRetreat.h"
#include "GameFramework/Character.h"
#include "OurMacros.h"
#include <Kismet/GameplayStatics.h>
#include "Components/SpotLightComponent.h"

AConfusiusRetreat::AConfusiusRetreat()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
}

void AConfusiusRetreat::BeginPlay()
{
	Super::BeginPlay();
	
}

void AConfusiusRetreat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Check();
}

void AConfusiusRetreat::Reward(ACharacter* _player)
{
	//Add to the place where i can read the information (ui)
	// add an event in reward BLUE PRINT 
	Destroy();
}

void AConfusiusRetreat::Check()
{
	ACharacter* _player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!_player) return;

	float _dist = FVector::Dist(_player->GetActorLocation(), GetActorLocation());
	isPlayerInRange = (_dist <= interactionDistance);



	APlayerController* _pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (isPlayerInRange && _pc->IsInputKeyDown(EKeys::E))
	{
		Reward(_player);
	}
}

