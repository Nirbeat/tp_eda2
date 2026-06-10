//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InterfazLogistica.h"
#include <System.SysUtils.hpp>
#include <Vcl.Dialogs.hpp>
#include <stdint.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	hayRutaDibujada = false;
	ultimaRuta.encontrada = false;
	ultimaRuta.cantidadCiudades = 0;
	inicializarInterfazLogistica();
 }

void TForm1::inicializarInterfazLogistica()
{
	picMapa->Left = 0;
	picMapa->Top = 0;
	picMapa->Width = Panel2->ClientWidth;
	picMapa->Height = Panel2->ClientHeight;

	mapaOverlay = new TPaintBox(this);
	mapaOverlay->Parent = Panel2;
	mapaOverlay->Align = alClient;
	mapaOverlay->OnPaint = MapaOverlayPaint;
	mapaOverlay->BringToFront();

	btnCalcularRutaOptima->OnClick = btnCalcularRutaOptimaClick;
	btnLimpiarCampos->OnClick = btnLimpiarCamposClick;
	Panel2->OnResize = PanelMapaResize;

	actualizarCombosCiudades();
	redibujarMapa();
}

void TForm1::actualizarCombosCiudades()
{
	// ComboBox1->Items->Clear();
	// cbDestino->Items->Clear();

	// for (int i = 0; i < sistemaLogistico.cantidadCiudades(); i++) {
	// 	const CiudadLogistica &ciudad = sistemaLogistico.obtenerCiudad(i);
	// 	if (ciudad.activa) {
	// 		UnicodeString texto = IntToStr(ciudad.id) + " - " + UnicodeString(ciudad.nombre.c_str());
	// 		ComboBox1->Items->AddObject(texto, reinterpret_cast<TObject*>((intptr_t)ciudad.id));
	// 		cbDestino->Items->AddObject(texto, reinterpret_cast<TObject*>((intptr_t)ciudad.id));
	// 	}
	// }

	// if (ComboBox1->Items->Count > 0) {
	// 	ComboBox1->ItemIndex = 0;
	// }
	// if (cbDestino->Items->Count > 1) {
	// 	cbDestino->ItemIndex = 1;
	// } else if (cbDestino->Items->Count > 0) {
	// 	cbDestino->ItemIndex = 0;
	// }
}

void TForm1::redibujarMapa()
{
	// if (mapaOverlay) {
	// 	mapaOverlay->Invalidate();
	// }
}

TPoint TForm1::puntoCiudadEnMapa(int id) const
{
	// const CiudadLogistica &ciudad = sistemaLogistico.obtenerCiudad(id);
	// int x = static_cast<int>(ciudad.mapaX * mapaOverlay->ClientWidth);
	// int y = static_cast<int>(ciudad.mapaY * mapaOverlay->ClientHeight);
	// return TPoint(x, y);
}

void TForm1::pintarConexiones(TCanvas *canvas)
{
	// const int conexiones[][2] = {
	// 	{0, 1}, {0, 7}, {1, 2}, {1, 3}, {1, 4},
	// 	{2, 5}, {2, 7}, {3, 4}, {4, 5}, {4, 6}, {5, 6}
	// };
	// const int cantidadConexiones = sizeof(conexiones) / sizeof(conexiones[0]);

	// canvas->Pen->Color = (TColor)0x00C8C8C8;
	// canvas->Pen->Width = 2;
	// canvas->Pen->Style = psDot;

	// for (int i = 0; i < cantidadConexiones; i++) {
	// 	int origen = conexiones[i][0];
	// 	int destino = conexiones[i][1];
	// 	if (sistemaLogistico.ciudadActiva(origen) && sistemaLogistico.ciudadActiva(destino)) {
	// 		TPoint p1 = puntoCiudadEnMapa(origen);
	// 		TPoint p2 = puntoCiudadEnMapa(destino);
	// 		canvas->MoveTo(p1.X, p1.Y);
	// 		canvas->LineTo(p2.X, p2.Y);
	// 	}
	// }

	// canvas->Pen->Style = psSolid;
}

void TForm1::pintarRutaCalculada(TCanvas *canvas)
{
	if (!hayRutaDibujada || !ultimaRuta.encontrada || ultimaRuta.cantidadCiudades < 2) {
		return;
	}

	canvas->Pen->Color = (TColor)0x00A65400;
	canvas->Pen->Width = 5;
	canvas->Pen->Style = psSolid;

	for (int i = 0; i < ultimaRuta.cantidadCiudades - 1; i++) {
		TPoint p1 = puntoCiudadEnMapa(ultimaRuta.camino[i]);
		TPoint p2 = puntoCiudadEnMapa(ultimaRuta.camino[i + 1]);
		canvas->MoveTo(p1.X, p1.Y);
		canvas->LineTo(p2.X, p2.Y);
	}
}

void TForm1::pintarCiudades(TCanvas *canvas)
{
//	const TColor colores[CANTIDAD_CIUDADES] = {
	// 	(TColor)0x00C06000,
	// 	(TColor)0x0020A020,
	// 	(TColor)0x000080FF,
	// 	(TColor)0x00802080,
	// 	(TColor)0x00305090,
	// 	(TColor)0x008020E8,
	// 	(TColor)0x00C0A000,
	// 	(TColor)0x0000C0D0
	// };

	// canvas->Font->Name = "Segoe UI";
	// canvas->Font->Size = 9;
	// canvas->Font->Style = TFontStyles() << fsBold;
	// canvas->Brush->Style = bsSolid;

	// for (int i = 0; i < sistemaLogistico.cantidadCiudades(); i++) {
	// 	const CiudadLogistica &ciudad = sistemaLogistico.obtenerCiudad(i);
	// 	if (!ciudad.activa) {
	// 		continue;
	// 	}

	// 	TPoint p = puntoCiudadEnMapa(ciudad.id);
	// 	TRect circulo(p.X - 11, p.Y - 11, p.X + 11, p.Y + 11);

	// 	canvas->Brush->Color = colores[ciudad.id];
	// 	canvas->Pen->Color = clWhite;
	// 	canvas->Pen->Width = 2;
	// 	canvas->Ellipse(circulo);

	// 	canvas->Brush->Style = bsClear;
	// 	canvas->Font->Color = clWhite;
	// 	canvas->TextOut(p.X - 4, p.Y - 8, IntToStr(ciudad.id));

	// 	canvas->Font->Color = clBlack;
	// 	canvas->TextOut(p.X + 15, p.Y - 9, UnicodeString(ciudad.nombre.c_str()));
	// 	canvas->Brush->Style = bsSolid;
	// }
}

int TForm1::obtenerIdCiudadSeleccionada(TComboBox *combo)
{
	// if (combo->ItemIndex < 0) {
	// 	return -1;
	// }

	// return static_cast<int>(reinterpret_cast<intptr_t>(combo->Items->Objects[combo->ItemIndex]));
}

  void __fastcall TForm1::PanelMouseEnter(TObject *Sender)
{
	TPanel *P = nullptr;

	if (dynamic_cast<TPanel*>(Sender))
		P = dynamic_cast<TPanel*>(Sender);
	else if (dynamic_cast<TControl*>(Sender))
		P = dynamic_cast<TPanel*>(dynamic_cast<TControl*>(Sender)->Parent);

	if (P)
		P->Color = (TColor)0x007A4A1F;
}

void __fastcall TForm1::PanelMouseLeave(TObject *Sender)
{
	TPanel *P = nullptr;

	if (dynamic_cast<TPanel*>(Sender))
		P = dynamic_cast<TPanel*>(Sender);
	else if (dynamic_cast<TControl*>(Sender))
		P = dynamic_cast<TPanel*>(dynamic_cast<TControl*>(Sender)->Parent);

	if (P)
		P->Color = (TColor)0x00522D0B;
}


void __fastcall TForm1::btnCalcularRutasClick(TObject *Sender)
{
		// pnlCiudades->Visible = false;
		// pnlHistorial->Visible = false;
		// pnlRutas->Visible = false;
		// pnlCalcularDistancia->Visible = true;
		// pnlCalcularDistancia->BringToFront();
 }
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnCiudadesClick(TObject *Sender)
{

		pnlCalcularDistancia->Visible = false;
		pnlHistorial->Visible = false;
		pnlRutas-> Visible = false;
		pnlCiudades->Visible = true;
		pnlCiudades->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnRutasClick(TObject *Sender)
{

		pnlCalcularDistancia->Visible = false;
		pnlHistorial->Visible = false;
		pnlCiudades-> Visible = false;
		pnlRutas->Visible = true;
		pnlRutas->BringToFront();
}

void __fastcall TForm1::BtnHistorialClick(TObject *Sender)
{
		pnlCalcularDistancia->Visible = false;
		pnlCiudades->Visible = false;
		pnlRutas->Visible = false;
		pnlHistorial->Visible = true;
		pnlHistorial->BringToFront();

}

void __fastcall TForm1::btnCalcularRutaOptimaClick(TObject *Sender)
{
	// int origen = obtenerIdCiudadSeleccionada(ComboBox1);
	// int destino = obtenerIdCiudadSeleccionada(cbDestino);

	// ResultadoRuta resultado = sistemaLogistico.calcularRutaOptima(origen, destino);

	// if (!resultado.encontrada) {
	// 	ShowMessage(UnicodeString(resultado.mensaje.c_str()));
	// 	return;
	// }

	// ultimaRuta = resultado;
	// hayRutaDibujada = true;
	// redibujarMapa();

	// sistemaLogistico.guardarEnHistorial(origen, destino, resultado);
	// ShowMessage(UnicodeString(sistemaLogistico.describirRuta(resultado).c_str()));
}

void __fastcall TForm1::btnLimpiarCamposClick(TObject *Sender)
{
	// if (ComboBox1->Items->Count > 0) {
	// 	ComboBox1->ItemIndex = 0;
	// }

	// if (cbDestino->Items->Count > 1) {
	// 	cbDestino->ItemIndex = 1;
	// } else if (cbDestino->Items->Count > 0) {
	// 	cbDestino->ItemIndex = 0;
	// }

	// hayRutaDibujada = false;
	// ultimaRuta.encontrada = false;
	// ultimaRuta.cantidadCiudades = 0;
	// redibujarMapa();
}

void __fastcall TForm1::PanelMapaResize(TObject *Sender)
{
	redibujarMapa();
}

void __fastcall TForm1::MapaOverlayPaint(TObject *Sender)
{
	pintarConexiones(mapaOverlay->Canvas);
	pintarRutaCalculada(mapaOverlay->Canvas);
	pintarCiudades(mapaOverlay->Canvas);
}
