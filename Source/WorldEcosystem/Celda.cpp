// Fill out your copyright notice in the Description page of Project Settings.

#include "Celda.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"
#include "Pasto.h"


// Sets default values
ACelda::ACelda()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    RootComponent = Trigger;
    //Zona->SetupAttachment(RootComponent);
    Trigger->InitBoxExtent(FVector(49.0f, 49.0f, 49.0f));
    //Trigger->OnComponentBeginOverlap.AddDynamic(this, &APasto::OnBeginOverlapZona);
    //Trigger->OnComponentEndOverlap.AddDynamic(this, &APasto::OnEndOverlapZona);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.1f));
    Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));
	//ArticulacionCuello->SetWorldScale3D(FVector(0.05f));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (MeshAsset.Succeeded()) {
        Mesh->SetStaticMesh(MeshAsset.Object);
        static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterialAsset(TEXT("Material'/Game/WorldEcosystem/Materials/CeldaMaterial.CeldaMaterial'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
        if (MeshMaterialAsset.Succeeded()) {
            Mesh->SetMaterial(0, MeshMaterialAsset.Object);
			//ArticulacionMaterialDynamic = UMaterialInstanceDynamic::Create(CuelloMaterialAsset.Object, this);
        }
    }

}

// Called when the game starts or when spawned
void ACelda::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACelda::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACelda::HayPasto() {
    if (bPastoCreandose) {
        return true;
    }
    TArray<AActor *> ActorsInCelda;
    Trigger->GetOverlappingActors(ActorsInCelda);//le pasamos el array donde se guardaran

    // para cada actor encontrado
    for (int i = 0; i < ActorsInCelda.Num(); ++i) {
        //casteamos el actor a un pickup, esto para quedarno socn tosdos lo pickups que podriian se clases c++ o blueprints,
        APasto * const PastoActor = Cast<APasto>(ActorsInCelda[i]);//por estos usos de pickup es que hemos incluido Pickup.h
        //si el casteo es exitoso y el pickup es valido y esta activo 
        if (PastoActor && !PastoActor->bSiendoComido && !PastoActor->IsPendingKill()) {//se comprueba que no se haya ordenado la destruccion de ese pickup, por que aveces pasa eso
            //entonces llamamos a la funcoin del pickup WasCollected();
            return true;
        }
    }
    return false;
}

