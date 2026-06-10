//---------------------------------------------------------------------------

#ifndef InterfazLogisticaH
#define InterfazLogisticaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "Logistica.h"
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
	TComboBox *ComboBox2;

void __fastcall PanelMouseEnter(TObject *Sender);
void __fastcall PanelMouseLeave(TObject *Sender);

void __fastcall btnCalcularRutasClick(TObject *Sender);
void __fastcall BtnCiudadesClick(TObject *Sender);
void __fastcall BtnRutasClick(TObject *Sender);
void __fastcall BtnHistorialClick(TObject *Sender);
void __fastcall btnCalcularRutaOptimaClick(TObject *Sender);
void __fastcall btnLimpiarCamposClick(TObject *Sender);
void __fastcall PanelMapaResize(TObject *Sender);
void __fastcall MapaOverlayPaint(TObject *Sender);

private:
	SistemaLogistico sistemaLogistico;
	TPaintBox *mapaOverlay;
	ResultadoRuta ultimaRuta;
	bool hayRutaDibujada;
	void inicializarInterfazLogistica();
	void actualizarCombosCiudades();
	void redibujarMapa();
	TPoint puntoCiudadEnMapa(int id) const;
	void pintarConexiones(TCanvas *canvas);
	void pintarRutaCalculada(TCanvas *canvas);
	void pintarCiudades(TCanvas *canvas);
	int obtenerIdCiudadSeleccionada(TComboBox *combo);
public:
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
