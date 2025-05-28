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
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
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

	SetMeshCollision(ECollisionResponse::ECR_Overlap);
	//jadeChallengeWidget->SetVisibility(ESlateVisibility::Hidden);
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

	/*if (!jadeChallengeWidget)
	{
		FTimerHandle _timer;
		GetWorld()->GetTimerManager().SetTimer(_timer, [&]()
			{
				jadeChallengeWidget = GetMainWidget()->GetJadeChallengeWidget();
			},
			0.2f, false);
	}

	if (!winPopupWidget)
	{
		FTimerHandle _timer;
		GetWorld()->GetTimerManager().SetTimer(_timer, [&]()
			{
				winPopupWidget = GetMainWidget()->GetWinPopupWidget();
			},
			0.2f, false);
	}*/
}

void AChallengeOfJade::UpdateTime(float _deltaTime)
{
	currentTime += _deltaTime;
	if (currentTime > timeLimit)
	{
		raceStarted = false;
		ChallengeFailed();
	}
	FString _time = FString::FromInt(currentTime) + "s";
	//jadeChallengeWidget->SetCurrentTimetText(FText::FromString(_time));
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
		/*jadeChallengeWidget->SetVisibility(ESlateVisibility::Hidden);
		winPopupWidget->SetVisibility(ESlateVisibility::Visible);
		FTimerHandle _timer;

		GetWorld()->GetTimerManager().SetTimer(_timer, [&]() {winPopupWidget->SetVisibility(ESlateVisibility::Hidden); }, 4.0f, false);*/
		//endZone->SetIsActive(false);

		//Add the life here

	}
}

void AChallengeOfJade::SetMaterial(UMaterial* _mat)
{
	if (!_mat) return;
	mesh->SetMaterial(0, _mat);
}


void AChallengeOfJade::OnPlayerReachEnd(AActor* _overlappedActor)
{
	if (!raceStarted) return;
	raceStarted = false;

	//Check if the player pass the end before the time => Win or after => Loose
	if (HasWin())
		ChallengeSucceeded(_overlappedActor);

	endZone->SetIsActive(false);
}

void AChallengeOfJade::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (raceStarted || raceCompleted || !isPlayerDashing)return;
	if (!OtherActor)return;
	ACharacter* _player = Cast< ACharacter>(OtherActor);

	if (_player)
	{
		raceStarted = true;
		/*if (jadeChallengeWidget)
		{
			FString _limit = FString::FromInt(timeLimit) + "s";
			jadeChallengeWidget->SetTimeLimitText(FText::FromString(_limit));
			jadeChallengeWidget->SetVisibility(ESlateVisibility::Visible);
		}*/
		currentTime = 0.0f;
		SetMaterial(onGoingMat);
		endZone->SetIsActive(true);
		PRINT_MSG("Begin");
		for (AActor* _platform : allPlatforms)
		{
			_platform->SetActorHiddenInGame(false);
		}
		FTimerHandle _timer;
		GetWorld()->GetTimerManager().SetTimer(_timer, [&]() {SetMeshCollision(ECollisionResponse::ECR_Block); }, 1.0f, false);
	}
}

void AChallengeOfJade::SetMeshCollision(ECollisionResponse _rep)
{
	mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, _rep);
}

//UMainWidget* AChallengeOfJade::GetMainWidget()
//{
//	ACharacter* _player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
//	if (!_player) return nullptr;
//	APlayerController* _playerController = Cast<APlayerController>(_player->GetController());
//	if (!_playerController) return nullptr;
//	APlayer_HUD* _HUD = Cast< APlayer_HUD>(_playerController->GetHUD());
//	if (!_HUD)return nullptr;
//	return _HUD->GetMainWidget();
//}

