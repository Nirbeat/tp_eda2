//---------------------------------------------------------------------------

#ifndef InterfazLogisticaH
#define InterfazLogisticaH
//---------------------------------------------------------------------------
#include "Logistica.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <ciudad.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm {
  __published : TPanel *pnlMenu;
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
  TPanel *pnlRutas;
  TPanel *pnlHistorial;
  TComboBox *cbOrigen;
  TComboBox *cbDestino;
  TPanel *btnCalcularRutaOptima;
  TPanel *btnLimpiarCampos;
  TPanel *btnGuardarHistorial;
  TLabel *lblCiudadOrigen;
	TPanel *pnlCiudades;

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
  TEdit *txtCiudadId;
  TEdit *txtCiudadNombre;
  TEdit *txtCiudadX;
  TEdit *txtCiudadY;
  ResultadoRuta ultimaRuta;
  bool hayRutaDibujada;
  void inicializarInterfazLogistica();
  void actualizarCombosCiudades(Ciudad* ciudadesUI);
  void redibujarMapa();
  TPoint puntoCiudadEnMapa(int id) const;
  void pintarConexiones(TCanvas *canvas);
  void pintarRutaCalculada(TCanvas *canvas);
  void pintarCiudades(TCanvas *canvas);
  int obtenerIdCiudadSeleccionada(TComboBox *combo);
  void construirVistaCiudades();
  void construirVistaRutas();
  TPanel *crearPanelSeccion(TWinControl *parent, int left, int top, int width,
                            int height, const UnicodeString &titulo);
  TPanel *crearBotonAccion(TWinControl *parent, int left, int top, int width,
                           int height, const UnicodeString &caption,
                           TColor color);
  void actualizarCamposCiudad(int indiceCiudad);
  void __fastcall grillaCiudadesDrawCell(TObject *Sender, int ACol, int ARow,
                                         const TRect &Rect,
                                         TGridDrawState State);
  void __fastcall grillaCiudadesSelectCell(TObject *Sender, int ACol,
                                           int ARow, bool &CanSelect);

public:
  __fastcall TForm1(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
