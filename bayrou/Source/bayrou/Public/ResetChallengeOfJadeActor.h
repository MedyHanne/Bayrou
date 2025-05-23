#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResetChallengeOfJadeActor.generated.h"

class AChallengeOfJade;

UCLASS()
class BAYROU_API AResetChallengeOfJadeActor : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> resetMesh;
	UPROPERTY(EditAnywhere) TObjectPtr<AChallengeOfJade> challengeToReset;

public:
	AResetChallengeOfJadeActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
