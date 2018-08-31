// Fill out your copyright notice in the Description page of Project Settings.

#include "Conejo.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"
#include "Pasto.h"
#include "Ecosistema.h"
#include "Engine/Engine.h"
#include "WorldEcosystemGameModeBase.h"


// Sets default values
AConejo::AConejo() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    RootComponent = Trigger;
    //Zona->SetupAttachment(RootComponent);
    Trigger->InitBoxExtent(FVector(45.0f, 45.0f, 45.0f));
    //Trigger->OnComponentBeginOverlap.AddDynamic(this, &APasto::OnBeginOverlapZona);
    //Trigger->OnComponentEndOverlap.AddDynamic(this, &APasto::OnEndOverlapZona);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeScale3D(FVector(0.20f));
    //Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
    Mesh->SetRelativeLocation(FVector(FMath::RandRange(-35.0f, 35.0f), FMath::RandRange(-35.0f, 35.0f), 10.0f));
	//ArticulacionCuello->SetWorldScale3D(FVector(0.05f));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (MeshAsset.Succeeded()) {
        Mesh->SetStaticMesh(MeshAsset.Object);
        static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterialAsset(TEXT("Material'/Game/WorldEcosystem/Materials/ConejoMaterial.ConejoMaterial'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
        if (MeshMaterialAsset.Succeeded()) {
            Mesh->SetMaterial(0, MeshMaterialAsset.Object);
			//ArticulacionMaterialDynamic = UMaterialInstanceDynamic::Create(CuelloMaterialAsset.Object, this);
        }
    }

}

// Called when the game starts or when spawned
void AConejo::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AConejo::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

bool AConejo::HayPastoDisponible() {
    //esta funcion verfica que haya pasto dispoinible para comer, tengo que verificar que ese pasto no este reservado, que baya a ser comido
    TArray<AActor *> ActorsInCelda;
    Trigger->GetOverlappingActors(ActorsInCelda);//le pasamos el array donde se guardaran

    // para cada actor encontrado
    for (int i = 0; i < ActorsInCelda.Num(); ++i) {
        //casteamos el actor a un pickup, esto para quedarno socn tosdos lo pickups que podriian se clases c++ o blueprints,
        APasto * const PastoActor = Cast<APasto>(ActorsInCelda[i]);//por estos usos de pickup es que hemos incluido Pickup.h
        //si el casteo es exitoso y el pickup es valido y esta activo 
        if (PastoActor && !PastoActor->bSiendoComido && !PastoActor->IsPendingKill()) {//se comprueba que no se haya ordenado la destruccion de ese pickup, por que aveces pasa eso
            //entonces llamamos a la funcoin del pickup WasCollected();
            PastoComida = PastoActor;
            return true;
        }
    }
    return false;
}

void AConejo::Comer() {
    AGameModeBase * GameMode = UGameplayStatics::GetGameMode(GetWorld());//el miso error de set material
    AWorldEcosystemGameModeBase * EcoGameMode = Cast<AWorldEcosystemGameModeBase>(GameMode);
    AEcosistema * Ecosistema;
    if (EcoGameMode) {
        Ecosistema = EcoGameMode->EcosistemaReference;
        if (Ecosistema) {
            Ecosistema->MatarPasto(PastoComida);
            VidaActual = VidaMaxima;
        }
    }
}

void AConejo::Morir() {
    AGameModeBase * GameMode = UGameplayStatics::GetGameMode(GetWorld());//el miso error de set material
    AWorldEcosystemGameModeBase * EcoGameMode = Cast<AWorldEcosystemGameModeBase>(GameMode);
    AEcosistema * Ecosistema;

    UE_LOG(LogClass, Log, TEXT("Conejo muriendo."));
    if (EcoGameMode) {
        Ecosistema = EcoGameMode->EcosistemaReference;
        if (Ecosistema) {
            Ecosistema->MatarConejo(this);
        }
    }
}

void AConejo::Reproducir() {
    AGameModeBase * GameMode = UGameplayStatics::GetGameMode(GetWorld());//el miso error de set material
    AWorldEcosystemGameModeBase * EcoGameMode = Cast<AWorldEcosystemGameModeBase>(GameMode);
    AEcosistema * Ecosistema;
    if (EcoGameMode) {
        Ecosistema = EcoGameMode->EcosistemaReference;
        if (Ecosistema) {
            TArray<ACelda *> Celdas;
            if (CeldaActual->CeldaArriba) {
                Celdas.Add(CeldaActual->CeldaArriba);
                if (CeldaActual->CeldaArriba->CeldaDerecha) {
                    Celdas.Add(CeldaActual->CeldaArriba->CeldaDerecha);
                }
                if (CeldaActual->CeldaArriba->CeldaIzquierda) {
                    Celdas.Add(CeldaActual->CeldaArriba->CeldaIzquierda);
                }
            }
            if (CeldaActual->CeldaAbajo) {
                Celdas.Add(CeldaActual->CeldaAbajo);
                if (CeldaActual->CeldaAbajo->CeldaDerecha) {
                    Celdas.Add(CeldaActual->CeldaAbajo->CeldaDerecha);
                }
                if (CeldaActual->CeldaAbajo->CeldaIzquierda) {
                    Celdas.Add(CeldaActual->CeldaAbajo->CeldaIzquierda);
                }
            }
            if (CeldaActual->CeldaDerecha) {
                Celdas.Add(CeldaActual->CeldaDerecha);
            }
            if (CeldaActual->CeldaIzquierda) {
                Celdas.Add(CeldaActual->CeldaIzquierda);
            }
            for (int i = 0; i < NumeroReproduccion; i++) {
                if (Celdas.Num()) {
                    int IdCelda = FMath::RandRange(0, Celdas.Num()-1);
                    Ecosistema->CrearConejo(Celdas[IdCelda]);
                }
            }
            IteracionesReproduccionActual = 0;
            bReproduciendo = false;
        }
    }
}

void AConejo::Mover(EAccionConejo Movimiento) {
    if (Movimiento == EAccionConejo::EMoverArriba) {
        CeldaActual = CeldaActual->CeldaArriba;
        SetActorLocation(CeldaActual->GetActorLocation());
    }
    else if (Movimiento == EAccionConejo::EMoverAbajo) {
        CeldaActual = CeldaActual->CeldaAbajo;
        SetActorLocation(CeldaActual->GetActorLocation());
    }
    else if (Movimiento == EAccionConejo::EMoverDerecha) {
        CeldaActual = CeldaActual->CeldaDerecha;
        SetActorLocation(CeldaActual->GetActorLocation());
    }
    else if (Movimiento == EAccionConejo::EMoverIzquierda) {
        CeldaActual = CeldaActual->CeldaIzquierda;
        SetActorLocation(CeldaActual->GetActorLocation());
    }
    else if (Movimiento == EAccionConejo::EEsperar) {
        //no hacer nada
    }
}

void AConejo::DeterminarAccion() {//esto deberia ser virtual
    if (bMuriendo) {
        AccionActual = EAccionConejo::EMorir;
        return;
    }
    if (bReproduciendo) {
        AccionActual = EAccionConejo::EReproducir;
        return;
    }
    //TArray<FAccionConejoStruct> ListaAccionesStructTurno;
    TArray<EAccionConejo> ListaAccionesTurno;
    if (HayPastoDisponible()) {
        ListaAccionesTurno.Add(EAccionConejo::EComer);
    }
    if (CeldaActual) {
        if (CeldaActual->CeldaArriba) {
            ListaAccionesTurno.Add(EAccionConejo::EMoverArriba);
        }
        if (CeldaActual->CeldaAbajo) {
            ListaAccionesTurno.Add(EAccionConejo::EMoverAbajo);
        }
        if (CeldaActual->CeldaDerecha) {
            ListaAccionesTurno.Add(EAccionConejo::EMoverDerecha);
        }
        if (CeldaActual->CeldaIzquierda) {
            ListaAccionesTurno.Add(EAccionConejo::EMoverIzquierda);
        }
    }
    ListaAccionesTurno.Add(EAccionConejo::EEsperar);

    int IdAccion = FMath::RandRange(0, ListaAccionesTurno.Num()-1);
    AccionActual = ListaAccionesTurno[IdAccion];

    if (AccionActual == EAccionConejo::EComer) {
        PastoComida->bSiendoComido = true;
        //esto es para reservar el pasto que comere, para que cuando evalue otros conejos, no tomen en cuestan este pasto que ya escogi
    }
}

void AConejo::EjecutarAccion() {
    //como ejecuto las acciones?
    if (AccionActual == EAccionConejo::EMorir) {
        Morir();
    }
    else if (AccionActual == EAccionConejo::EReproducir) {
        Reproducir();
    }
    else if (AccionActual == EAccionConejo::EComer) {
        Comer();
    }
    else {
        Mover(AccionActual);
    }
}

void AConejo::IntervaloIteracion() {
    VidaActual--;
    if (!VidaActual) {
        bMuriendo = true;
        //tal vez aqui deba matar al individuo
    }
    IteracionesReproduccionActual++;
    if (IteracionesReproduccionActual >= IteracionesReproduccion) {
        bReproduciendo = true;
        //resestablecer la repdorucion actual al ejecutar la accion
    }
}

