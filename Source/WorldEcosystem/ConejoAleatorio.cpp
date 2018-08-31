// Fill out your copyright notice in the Description page of Project Settings.

#include "ConejoAleatorio.h"

void AConejoAleatorio::DeterminarAccion() {//esto deberia ser virtual
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



