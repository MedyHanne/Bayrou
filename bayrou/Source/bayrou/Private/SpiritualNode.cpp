#include "SpiritualNode.h"
#include "SpiritualArtefact.h"
#include "GameFramework/Character.h"

ASpiritualNode::ASpiritualNode()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
}

void ASpiritualNode::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ASpiritualNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpiritualNode::SetSpiritualArtefact(ASpiritualArtefact* _spiritualArtefact)
{
	artefactRef = _spiritualArtefact;
}

void ASpiritualNode::Init()
{
	if (!artefactRef)return;
	artefactRef->AddNode(this);
}

void ASpiritualNode::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor || !artefactRef)return;

	ACharacter* _player = Cast<ACharacter>(OtherActor);
	if (!_player)return;

	artefactRef->RemoveDestroyedNode(this);
	onNodeDestroyed.Broadcast();
}

