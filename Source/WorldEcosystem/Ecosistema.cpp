// Fill out your copyright notice in the Description page of Project Settings.

#include "Ecosistema.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


// Sets default values
AEcosistema::AEcosistema()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

    Camara = CreateDefaultSubobject<UCameraComponent>("Camara");
    Camara->SetupAttachment(RootComponent);
    Camara->SetRelativeLocation(FVector(-200.0f, 0.0f, 200.0f));

    static ConstructorHelpers::FClassFinder<ACelda> CeldaClass(TEXT("Class'/Script/WorldEcosystem.Celda'"));
    if (CeldaClass.Succeeded()) {
        if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Celda type founded."));
        CeldaType = CeldaClass.Class;
    }

    static ConstructorHelpers::FClassFinder<APasto> PastoClass(TEXT("Class'/Script/WorldEcosystem.Pasto'"));
    if (PastoClass.Succeeded()) {
        if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pasto type founded."));
        PastoType = PastoClass.Class;
    }

    static ConstructorHelpers::FClassFinder<AConejo> ConejoClass(TEXT("Class'/Script/WorldEcosystem.Conejo'"));
    if (ConejoClass.Succeeded()) {
        if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Conejo type founded."));
        ConejoType = ConejoClass.Class;
    }

    static ConstructorHelpers::FClassFinder<AZorro> ZorroClass(TEXT("Class'/Script/WorldEcosystem.Zorro'"));
    if (ZorroClass.Succeeded()) {
        if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Zorro type founded."));
        ZorroType = ZorroClass.Class;
    }

    LadoMundo = 10;
    LadoCelda = 100.0f;
    TiempoIteracion = 1.0f;

    NumeroPastosIniciales = 10;
    NumeroConejosIniciales = 5;
    NumeroZorrosIniciales = 3;
    NumeroConejosReproduccionConejo = 2;
    NumeroIteracionesReproduccionConejo = 12;
    NumeroIteracionesVidaConejo = 6;
    NumeroIteracionesReproduccionPasto = 10;
    NumeroZorrosReproduccionZorro = 2;
    NumeroIteracionesReproduccionZorro = 16;
    NumeroIteracionesVidaZorro = 8;

}

// Called when the game starts or when spawned
void AEcosistema::BeginPlay() {
	Super::BeginPlay();
    APlayerController * PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    //al parecer el controlador del jugador tiene una un campo camara al cual podemos decirle que camara sera, que la aprecer es un objeto AActor
    if (PlayerController) {
        PlayerController->SetViewTarget(this);//cambio instantaneo
    }
	
}

// Called every frame
void AEcosistema::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AEcosistema::MatarPasto(APasto * PastoMuriendo) {
    Pastos.Remove(PastoMuriendo);
    PastoMuriendo->Destroy();//la pregunta es cuando se destruye?, o es que deberia poner los actores que deban morir en una cola de matanza, para que se terminen de ejecutar todas las llamas sinproblemas?
}

void AEcosistema::MatarConejo(AConejo * ConejoMuriendo) {
    Conejos.Remove(ConejoMuriendo);
    ConejoMuriendo->Destroy();
}

void AEcosistema::MatarZorro(AZorro * ZorroMuriendo) {
    Zorros.Remove(ZorroMuriendo);
    ZorroMuriendo->Destroy();
}

APasto * AEcosistema::CrearPasto(ACelda * Celda) {
	UWorld * const World = GetWorld();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = Instigator;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    FVector SpawnLocation(Celda->GetActorLocation());
    APasto * const InstancedPasto = World->SpawnActor<APasto>(PastoType, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (InstancedPasto) {
        if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pasto instanciado."));
        Pastos.Add(InstancedPasto);
        InstancedPasto->CeldaActual = Celda;
        InstancedPasto->AccionActual = EAccionPasto::EEsperar;
        InstancedPasto->IteracionesReproduccion = NumeroIteracionesReproduccionPasto;
        InstancedPasto->IteracionesReproduccionActual = 0;
        //InstancedPasto->CambiarPosicionMesh();//debo poner el mesh del pastito en algun punto aleatorio dentro de la celda, para que haya poca sobre posicion con otros elementos.
    }
    return InstancedPasto;
}

AConejo * AEcosistema::CrearConejo(ACelda * Celda) {
	UWorld * const World = GetWorld();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = Instigator;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    FVector SpawnLocation(Celda->GetActorLocation());
    AConejo * const InstancedConejo = World->SpawnActor<AConejo>(ConejoType, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (InstancedConejo) {
        Conejos.Add(InstancedConejo);
        InstancedConejo->CeldaActual = Celda;
        InstancedConejo->AccionActual = EAccionConejo::EEsperar;
        InstancedConejo->VidaMaxima = NumeroIteracionesVidaConejo;
        InstancedConejo->VidaActual = NumeroIteracionesVidaConejo;
        InstancedConejo->NumeroReproduccion = NumeroConejosReproduccionConejo;
        InstancedConejo->IteracionesReproduccion = NumeroIteracionesReproduccionConejo;
        InstancedConejo->IteracionesReproduccionActual = 0;
        //InstancedConejo->ChangePositionMesh();//debo poner el mesh del pastito en algun punto aleatorio dentro de la celda, para que haya poca sobre posicion con otros elementos.
    }
    return InstancedConejo;
}

AZorro * AEcosistema::CrearZorro(ACelda * Celda) {
	UWorld * const World = GetWorld();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = Instigator;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    FVector SpawnLocation(Celda->GetActorLocation());
    AZorro * const InstancedZorro = World->SpawnActor<AZorro>(ZorroType, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (InstancedZorro) {
        Zorros.Add(InstancedZorro);
        InstancedZorro->CeldaActual = Celda;
        InstancedZorro->AccionActual = EAccionZorro::EEsperar;
        InstancedZorro->VidaMaxima = NumeroIteracionesVidaZorro;
        InstancedZorro->VidaActual = NumeroIteracionesVidaZorro;
        InstancedZorro->NumeroReproduccion = NumeroZorrosReproduccionZorro;
        InstancedZorro->IteracionesReproduccion = NumeroIteracionesReproduccionZorro;
        InstancedZorro->IteracionesReproduccionActual = 0;
        //InstancedPasto->ChangePositionMesh();//debo poner el mesh del pastito en algun punto aleatorio dentro de la celda, para que haya poca sobre posicion con otros elementos.
    }
    return InstancedZorro;
}

void AEcosistema::IniciarSimulacion() {
    IteracionActual = 0;
    CrearMundo();
    PoblarMundo();
    //GetWorldTimerManager().SetTimer(TimerDeterminarAccion, this, &AEcosistema::DeterminarAcciones, 1.0f, false);//esto hace que llame a advance timer cada segundo que pasa
    DeterminarAcciones();
}

void AEcosistema::PausarSimulacion() {
    GetWorldTimerManager().PauseTimer(TimerDeterminarAccion);//Pausar timer
}

void AEcosistema::ContinuarSimulacion() {
    GetWorldTimerManager().UnPauseTimer(TimerDeterminarAccion);//reanudar timer
}

void AEcosistema::DetenerSimulacion() {
    for (int i = 0; i < Pastos.Num(); i++) {
        Pastos[i]->Destroy();
    }
    Pastos.Empty();
    for (int i = 0; i < Conejos.Num(); i++) {
        Conejos[i]->Destroy();
    }
    Conejos.Empty();
    for (int i = 0; i < Zorros.Num(); i++) {
        Zorros[i]->Destroy();
    }
    Zorros.Empty();
    GetWorldTimerManager().ClearTimer(TimerDeterminarAccion);//le damos el timer que queremos detener
}

void AEcosistema::DeterminarAcciones() {
    UE_LOG(LogClass, Log, TEXT("Iteracion actual %d."), IteracionActual);
    UE_LOG(LogClass, Log, TEXT("Numero Pastos %d."), Pastos.Num());
    UE_LOG(LogClass, Log, TEXT("Numero Conejos %d."), Conejos.Num());
    UE_LOG(LogClass, Log, TEXT("Numero Zorros %d."), Zorros.Num());
    for (int i = 0; i < Pastos.Num(); i++) {
        Pastos[i]->DeterminarAccion();
    }
    for (int i = 0; i < Conejos.Num(); i++) {
        Conejos[i]->DeterminarAccion();
    }
    for (int i = 0; i < Zorros.Num(); i++) {
        Zorros[i]->DeterminarAccion();
    }
    EjecutarAcciones();
}

void AEcosistema::EjecutarAcciones() {
    for (int i = 0; i < Pastos.Num(); i++) {
        Pastos[i]->EjecutarAccion();
    }
    for (int i = 0; i < Conejos.Num(); i++) {
        Conejos[i]->EjecutarAccion();
    }
    for (int i = 0; i < Zorros.Num(); i++) {
        Zorros[i]->EjecutarAccion();
    }
    Intervalos();
}

void AEcosistema::Intervalos() {
    IteracionActual++;
    for (int i = 0; i < Pastos.Num(); i++) {
        Pastos[i]->IntervaloIteracion();
    }
    for (int i = 0; i < Conejos.Num(); i++) {
        Conejos[i]->IntervaloIteracion();
    }
    for (int i = 0; i < Zorros.Num(); i++) {
        Zorros[i]->IntervaloIteracion();
    }
    GetWorldTimerManager().SetTimer(TimerDeterminarAccion, this, &AEcosistema::DeterminarAcciones, TiempoIteracion, false);//esto hace que llame a advance timer cada segundo que pasa
}

void AEcosistema::CrearMundo() {
	UWorld * const World = GetWorld();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = Instigator;
    FVector Offset(LadoMundo/2 * LadoCelda + (!(LadoMundo & 1))*(LadoCelda/2), LadoMundo/2 * LadoCelda + (!(LadoMundo & 1))*(LadoCelda/2), 0.0f);
    //Instanciando celdas
    for (int i = 0; i < LadoMundo; i++) {
        for (int j = 0; j < LadoMundo; j++) {
            FVector SpawnLocation(i*LadoCelda, j*LadoCelda, 0.0f);
            ACelda * CeldaInstanciada = World->SpawnActor<ACelda>(CeldaType, SpawnLocation - Offset, FRotator::ZeroRotator, SpawnParams);
            //CeldaInstanciada->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
            Celdas.Add(CeldaInstanciada);
        }
    }
    //Asociando punteros entre celdas;
    for (int i = 0; i < LadoMundo; i++) {
        for (int j = 0; j < LadoMundo; j++) {
            int IdCelda = i * LadoMundo + j;
            int IdArriba = (i + 1)*LadoMundo + (j);
            if (0 <= IdArriba && IdArriba <= Celdas.Num() - 1) {
                Celdas[IdCelda]->CeldaArriba = Celdas[IdArriba];
            }
            int IdAbajo = (i - 1)*LadoMundo + (j);
            if (0 <= IdAbajo && IdAbajo <= Celdas.Num() - 1) {
                Celdas[IdCelda]->CeldaAbajo = Celdas[IdAbajo];
            }
            int IdDerecha = (i)*LadoMundo + (j + 1);
            if (0 <= IdDerecha && IdDerecha <= Celdas.Num() - 1) {
                Celdas[IdCelda]->CeldaDerecha = Celdas[IdDerecha];
            }
            int IdIzquierda = (i)*LadoMundo + (j - 1);
            if (0 <= IdIzquierda && IdIzquierda <= Celdas.Num() - 1) {
                Celdas[IdCelda]->CeldaIzquierda = Celdas[IdIzquierda];
            }
        }
    }
}

void AEcosistema::PoblarMundo() {
    if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Poblando mundo."));
    for (int i = 0; i < NumeroPastosIniciales; i++) {
        int IdCelda = FMath::RandRange(0, Celdas.Num()-1);
        UE_LOG(LogClass, Log, TEXT("Itentando poblar pasto %d."), IdCelda);
        CrearPasto(Celdas[IdCelda]);
    }
    for (int i = 0; i < NumeroConejosIniciales; i++) {
        int IdCelda = FMath::RandRange(0, Celdas.Num()-1);
        CrearConejo(Celdas[IdCelda]);
    }
    for (int i = 0; i < NumeroZorrosIniciales; i++) {
        int IdCelda = FMath::RandRange(0, Celdas.Num()-1);
        CrearZorro(Celdas[IdCelda]);
    }
}

