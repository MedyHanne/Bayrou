#include "Teleporter.h"
#include "GameFramework/Character.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetSystemLibrary.h"

ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* _teleportArea = CreateDefaultSubobject<UBoxComponent>("TeleportArea");
	_teleportArea->SetupAttachment(RootComponent);
	_teleportArea->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);

}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	ACharacter* _playerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	characterRef = _playerCharacter;
	
}

void ATeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!isActivated)return;
    if (OtherActor && OtherActor == characterRef)
    {
        if (target)
        {
            FVector _targetLocation = target->GetActorLocation();
            FRotator _targetRotation = target->GetActorRotation();
            characterRef->SetActorLocationAndRotation(_targetLocation, _targetRotation);
            isActivated = false;
        }
    }
}

void ATeleporter::TeleportPlayer()
{
    if (!characterRef || !target) return;

    FTimerHandle _timerHandle;
    GetWorld()->GetTimerManager().SetTimer(_timerHandle, [this]()
        {
            characterRef->SetActorLocation(target->GetActorLocation());
            characterRef->SetActorRotation(target->GetActorRotation());

            APlayerController* _playerController = UGameplayStatics::GetPlayerController(this, 0);
            if (_playerController)
            {
                _playerController->SetControlRotation(target->GetActorRotation());
            }


        }, 0.5f, false);
}


