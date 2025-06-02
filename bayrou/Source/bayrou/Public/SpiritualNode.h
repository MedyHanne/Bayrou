#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/PointLightComponent.h>
#include "SpiritualNode.generated.h"

class ASpiritualArtefact;

UCLASS()
class BAYROU_API ASpiritualNode : public AActor
{
	GENERATED_BODY()
protected:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNodeDestroyed);
	UPROPERTY(BlueprintAssignable, BlueprintType) FOnNodeDestroyed onNodeDestroyed;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr< ASpiritualArtefact> artefactRef;

	UPROPERTY(EditAnywhere) TObjectPtr<UPointLightComponent> glowLight;
public:
	FORCEINLINE FOnNodeDestroyed& OnNodeDestroyed() { return onNodeDestroyed; }

public:
	ASpiritualNode();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	void SetSpiritualArtefact(ASpiritualArtefact* _spiritualArtefact);
private:
	void Init();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
