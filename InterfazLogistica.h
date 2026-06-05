//---------------------------------------------------------------------------

#ifndef InterfazLogisticaH
#define InterfazLogisticaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:
    TPanel *pnlMenu;
    TPanel *pnlIcono;

    TImage *IconoEmpresa;
    TLabel *lblTitulo1;
    TLabel *lblTitulo2;

    TPanel *btnCalcularRutas;
    TLabel *lblCalcularRuta;
    TImage *IconoCalcular;

    TPanel *BtnCiudades;
    TLabel *lblCiudades;
    TImage *IconoCiudadades;

    TPanel *BtnRutas;
    TLabel *lblRutas;
    TImage *IconoRuta;

    TPanel *BtnHistorial;
    TLabel *lblHistorial;
	TImage *IconoHistorial;
	TPanel *PanelMenuCalcular;

    TPanel *Panel2;
	TImage *picMapa;

	TPanel *pnlContenido;
	TPanel *pnlCalcularDistancia;
	TPanel *pnlCiudades;
	TPanel *pnlRutas;
	TPanel *pnlHistorial;
	TComboBox *ComboBox1;
	TComboBox *cbDestino;
	TPanel *btnCalcularRutaOptima;
	TPanel *btnLimpiarCampos;
	TPanel *btnGuardarHistorial;
	TLabel *lblCiudadOrigen;
	TLabel *lblCiudadDestino;

void __fastcall PanelMouseEnter(TObject *Sender);
void __fastcall PanelMouseLeave(TObject *Sender);

void __fastcall btnCalcularRutasClick(TObject *Sender);
void __fastcall BtnCiudadesClick(TObject *Sender);
void __fastcall BtnRutasClick(TObject *Sender);
void __fastcall BtnHistorialClick(TObject *Sender);

private:
public:
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
