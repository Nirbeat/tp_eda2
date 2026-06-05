//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InterfazLogistica.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

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
		pnlCiudades->Visible = false;
		pnlHistorial->Visible = false;
		pnlRutas->Visible = false;
		pnlCalcularDistancia->Visible = true;
		pnlCalcularDistancia->BringToFront();
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
		pnlRutas->Visible = true;
		pnlHistorial->BringToFront();

}


