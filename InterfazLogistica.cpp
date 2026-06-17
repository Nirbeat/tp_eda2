//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InterfazLogistica.h"
#include <System.SysUtils.hpp>
#include <Vcl.Dialogs.hpp>
#include <mapa.h>
#include <stdint.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Mapa *mapa = nullptr;
int **matriz;
Ciudad *ciudadesUI = nullptr;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner) : TForm(Owner) {

  mapa = new Mapa();
  matriz = mapa->obtenerMatrizAdyacencia();
  ShowMessage(IntToStr(matriz[0][1]));
  ciudadesUI = new Ciudad[mapa->obtenerCantidadCiudades()];
  mapa->pasarListaCiudades(ciudadesUI);
  actualizarCombosCiudades(ciudadesUI);

  mapaOverlay = new TPaintBox(this);
  mapaOverlay->Parent = Panel2;
  mapaOverlay->Align = alClient;
  mapaOverlay->OnPaint = MapaOverlayPaint;
  mapaOverlay->BringToFront();

  pintarCiudades(mapaOverlay->Canvas);

    txtCiudadId = nullptr;
  txtCiudadNombre = nullptr;
  txtCiudadX = nullptr;
  txtCiudadY = nullptr;
  pnlCiudades->Align = alClient;
  pnlCiudades->Caption = "";
  pnlCiudades->Color = clWhite;
  pnlRutas->Color = clWhite;
  pnlCiudades->Visible = false;
  pnlRutas->Visible = false;
  pnlHistorial->Visible = false;
  pnlCalcularDistancia->Visible = true;
  pnlCalcularDistancia->BringToFront();
}
// void TForm1::inicializarInterfazLogistica() {
//   picMapa->Left = 0;
//   picMapa->Top = 0;
//   picMapa->Width = Panel2->ClientWidth;
//   picMapa->Height = Panel2->ClientHeight;
//
//   mapaOverlay = new TPaintBox(this);
//   mapaOverlay->Parent = Panel2;
//   mapaOverlay->Align = alClient;
//   mapaOverlay->OnPaint = MapaOverlayPaint;
//   mapaOverlay->BringToFront();
//
//   btnCalcularRutaOptima->OnClick = btnCalcularRutaOptimaClick;
//   btnLimpiarCampos->OnClick = btnLimpiarCamposClick;
//   Panel2->OnResize = PanelMapaResize;
//
//   actualizarCombosCiudades(ciudadesUI);
//   redibujarMapa();
// }

void TForm1::actualizarCombosCiudades(Ciudad *ciudadesUI) {
  cbOrigen->Items->Clear();
  cbDestino->Items->Clear();

  for (int i = 0; i < mapa->obtenerCantidadCiudades(); i++) {

    cbOrigen->Items->Add(ciudadesUI[i].obtenerNombre().c_str());
    cbDestino->Items->Add(ciudadesUI[i].obtenerNombre().c_str());

    if (cbOrigen->Items->Count > 0) {
      cbOrigen->ItemIndex = 0;
    }
    if (cbDestino->Items->Count > 1) {
      cbDestino->ItemIndex = 1;
    } else if (cbDestino->Items->Count > 0) {
      cbDestino->ItemIndex = 0;
    }
  }
}

void TForm1::redibujarMapa() {
  // if (mapaOverlay) {
  // 	mapaOverlay->Invalidate();
  // }
}

TPoint TForm1::puntoCiudadEnMapa(int id) const {
  // const CiudadLogistica &ciudad = sistemaLogistico.obtenerCiudad(id);
  // int x = static_cast<int>(ciudad.mapaX * mapaOverlay->ClientWidth);
  // int y = static_cast<int>(ciudad.mapaY * mapaOverlay->ClientHeight);
  // return TPoint(x, y);
}

void TForm1::pintarConexiones(TCanvas *canvas) {
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
  // 	if (sistemaLogistico.ciudadActiva(origen) &&
  // sistemaLogistico.ciudadActiva(destino)) { 		TPoint p1 =
  // puntoCiudadEnMapa(origen); 		TPoint p2 =
  // puntoCiudadEnMapa(destino); 		canvas->MoveTo(p1.X, p1.Y);
  // 		canvas->LineTo(p2.X, p2.Y);
  // 	}
  // }

  // canvas->Pen->Style = psSolid;
}
//
//
void TForm1::pintarRutaCalculada(TCanvas *canvas) {
  //  if (!hayRutaDibujada || !ultimaRuta.encontrada ||
  //      ultimaRuta.cantidadCiudades < 2) {
  //    return;
  //  }
  //
  //  canvas->Pen->Color = (TColor)0x00A65400;
  //  canvas->Pen->Width = 5;
  //  canvas->Pen->Style = psSolid;
  //
  //  for (int i = 0; i < ultimaRuta.cantidadCiudades - 1; i++) {
  //    TPoint p1 = puntoCiudadEnMapa(ultimaRuta.camino[i]);
  //    TPoint p2 = puntoCiudadEnMapa(ultimaRuta.camino[i + 1]);
  //    canvas->MoveTo(p1.X, p1.Y);
  //    canvas->LineTo(p2.X, p2.Y);
}
//

void TForm1::pintarCiudades(TCanvas *canvas) {
  // Configuramos la fuente y pincel base
  canvas->Font->Name = "Segoe UI";
  canvas->Font->Size = 7;
  canvas->Font->Style = TFontStyles() << fsBold;
  canvas->Brush->Style = bsSolid;

  // -------------------------------------------------------------------------
  // FASE 1: DIBUJAR LAS RUTAS (LÍNEAS) EXISTENTES
  // -------------------------------------------------------------------------
  int **matrizUI = mapa->obtenerMatrizAdyacencia();
  int totalCiudades = mapa->obtenerCantidadCiudades();

  // Configuramos el lápiz para las calles/rutas iniciales
  canvas->Pen->Color = clGray; // Un color gris para que no compita con el azul
  canvas->Pen->Width = 2;      // Grosor de la línea de la calle

  for (int i = 0; i < totalCiudades; i++) {
    // Solo procesamos si la ciudad de origen está activa
    if (ciudadesUI[i].obtenerEstado() == true) {

      // El truco 'j = i + 1' evita procesar la diagonal (0) y pintar rutas
      // duplicadas
      for (int j = i + 1; j < totalCiudades; j++) {

        // Verificamos que la ciudad destino también esté activa y que exista
        // ruta real
        if (ciudadesUI[j].obtenerEstado() == true && matrizUI[i][j] != 0 &&
            matrizUI[i][j] != -1) {

          // Extraemos las coordenadas de la ciudad de Origen (i)
          Coordenadas coordsOrigen = ciudadesUI[i].obtenerCoordenadas();
          // Extraemos las coordenadas de la ciudad de Destino (j)
          Coordenadas coordsDestino = ciudadesUI[j].obtenerCoordenadas();

          // TCanvas usa MoveTo para apoyar el lápiz y LineTo para trazar la
          // línea
          canvas->MoveTo((int)coordsOrigen.x, (int)coordsOrigen.y);
          canvas->LineTo((int)coordsDestino.x, (int)coordsDestino.y);
        }
      }
    }
  }

  // -------------------------------------------------------------------------
  // FASE 2: DIBUJAR LOS CÍRCULOS Y TEXTOS (Tu código actual intacto)
  // -------------------------------------------------------------------------
  for (int i = 0; i < totalCiudades; i++) {
    if (ciudadesUI[i].obtenerEstado() == true) {
      Coordenadas coords = ciudadesUI[i].obtenerCoordenadas();
      int posX = (int)coords.x;
      int posY = (int)coords.y;

      // 2. DIBUJAR EL CÍRCULO
      TRect circulo(posX - 11, posY - 11, posX + 11, posY + 11);
      canvas->Brush->Color = clBlue;
      canvas->Pen->Color = clWhite;
      canvas->Pen->Width = 2;
      canvas->Ellipse(circulo);

      // 3. DIBUJAR EL ID ADENTRO
      canvas->Brush->Style = bsClear;
      canvas->Font->Color = clWhite;
      canvas->TextOut(posX - 4, posY - 8, IntToStr(ciudadesUI[i].obtenerId()));

      // 4. DIBUJAR EL NOMBRE AL COSTADO
      canvas->Font->Color = clBlue;
      UnicodeString nombreUI =
          UnicodeString(ciudadesUI[i].obtenerNombre().c_str());
      canvas->TextOut(posX + 15, posY - 9, nombreUI);

      canvas->Brush->Style = bsSolid;
    }
  }
}

int TForm1::obtenerIdCiudadSeleccionada(TComboBox *combo) {
  // if (combo->ItemIndex < 0) {
  // 	return -1;
  // }

  // return
  // static_cast<int>(reinterpret_cast<intptr_t>(combo->Items->Objects[combo->ItemIndex]));
}

TPanel *TForm1::crearPanelSeccion(TWinControl *parent, int left, int top,
                                  int width, int height,
                                  const UnicodeString &titulo) {
  TPanel *panel = new TPanel(this);
  panel->Parent = parent;
  panel->SetBounds(left, top, width, height);
  panel->BevelOuter = bvLowered;
  panel->Color = clWhite;
  panel->ParentBackground = false;
  panel->Caption = "";

  TLabel *lblTitulo = new TLabel(this);
  lblTitulo->Parent = panel;
  lblTitulo->SetBounds(26, 22, width - 52, 28);
  lblTitulo->Caption = titulo;
  lblTitulo->Font->Name = "Segoe UI";
  lblTitulo->Font->Size = 14;
  lblTitulo->Font->Style = TFontStyles() << fsBold;
  lblTitulo->Font->Color = (TColor)0x00522D0B;

  return panel;
}

TPanel *TForm1::crearBotonAccion(TWinControl *parent, int left, int top,
                                 int width, int height,
                                 const UnicodeString &caption, TColor color) {
  TPanel *boton = new TPanel(this);
  boton->Parent = parent;
  boton->SetBounds(left, top, width, height);
  boton->BevelOuter = bvNone;
  boton->Color = color;
  boton->ParentBackground = false;
  boton->Caption = caption;
  boton->Font->Name = "Segoe UI";
  boton->Font->Size = 12;
  boton->Font->Style = TFontStyles() << fsBold;
  boton->Font->Color = clWhite;
  return boton;
}

void TForm1::actualizarCamposCiudad(int indiceCiudad) {
  int cantidad = mapa->obtenerCantidadCiudades();
  if (indiceCiudad < 0 || indiceCiudad >= cantidad || txtCiudadId == nullptr) {
    return;
  }

  Coordenadas coords = ciudadesUI[indiceCiudad].obtenerCoordenadas();
  txtCiudadId->Text = IntToStr(ciudadesUI[indiceCiudad].obtenerId());
  txtCiudadNombre->Text =
      UnicodeString(ciudadesUI[indiceCiudad].obtenerNombre().c_str());
  txtCiudadX->Text = IntToStr(coords.x);
  txtCiudadY->Text = IntToStr(coords.y);
}

void __fastcall TForm1::grillaCiudadesDrawCell(TObject *Sender, int ACol,
                                               int ARow, const TRect &Rect,
                                               TGridDrawState State) {
  TStringGrid *grilla = static_cast<TStringGrid *>(Sender);
  TCanvas *canvas = grilla->Canvas;
  bool encabezado = ARow == 0;
  bool seleccionado = State.Contains(gdSelected) && !encabezado;

  canvas->Brush->Color = seleccionado ? (TColor)0x00D77D14 : clWhite;
  canvas->Font->Name = "Segoe UI";
  canvas->Font->Size = encabezado ? 13 : 12;
  canvas->Font->Style = encabezado ? (TFontStyles() << fsBold) : TFontStyles();
  canvas->Font->Color = seleccionado ? clWhite : clBlack;
  canvas->FillRect(Rect);

  UnicodeString texto = grilla->Cells[ACol][ARow];
  TRect textoRect = Rect;
  UINT formato = DT_VCENTER | DT_SINGLELINE;
  if (ACol == 0 || ACol == 2 || ACol == 3 || encabezado) {
    formato |= DT_CENTER;
  } else {
    formato |= DT_LEFT;
    textoRect.Left += 14;
  }
  DrawText(canvas->Handle, texto.c_str(), -1, &textoRect, formato);
}

void __fastcall TForm1::grillaCiudadesSelectCell(TObject *Sender, int ACol,
                                                 int ARow, bool &CanSelect) {
  CanSelect = true;
  if (ARow > 0) {
    actualizarCamposCiudad(ARow - 1);
  }
}

void TForm1::construirVistaCiudades() {
  while (pnlCiudades->ControlCount > 0) {
    delete pnlCiudades->Controls[0];
  }

  pnlCiudades->Color = clWhite;
  pnlCiudades->ParentBackground = false;

  TLabel *titulo = new TLabel(this);
  titulo->Parent = pnlCiudades;
  titulo->SetBounds(38, 30, 520, 48);
  titulo->Caption = "2. GESTION DE CIUDADES";
  titulo->Font->Name = "Segoe UI";
  titulo->Font->Size = 22;
  titulo->Font->Style = TFontStyles() << fsBold;
  titulo->Font->Color = (TColor)0x00B75B20;

  TPanel *panelListado =
      crearPanelSeccion(pnlCiudades, 24, 104, 520, 520, "Listado de Ciudades");
  TPanel *panelDatos =
      crearPanelSeccion(pnlCiudades, 558, 104, 345, 520, "Datos de la Ciudad");
  TPanel *panelAcciones =
      crearPanelSeccion(pnlCiudades, 916, 104, 234, 520, "Acciones");

  TStringGrid *grilla = new TStringGrid(this);
  grilla->Parent = panelListado;
  grilla->SetBounds(20, 76, 480, 440);
  grilla->ColCount = 4;
  grilla->RowCount = mapa->obtenerCantidadCiudades()+1;
  grilla->FixedRows = 1;
  grilla->DefaultRowHeight = 44;
  grilla->FixedColor = clWhite;
  grilla->Color = clWhite;
  grilla->DrawingStyle = gdsClassic;
  grilla->DefaultDrawing = false;
  grilla->ColWidths[0] = 70;
  grilla->ColWidths[1] = 185;
  grilla->ColWidths[2] = 110;
  grilla->ColWidths[3] = 110;
  grilla->Options = grilla->Options << goRowSelect << goFixedVertLine
                                    << goFixedHorzLine << goVertLine
                                    << goHorzLine;
  grilla->Font->Name = "Segoe UI";
  grilla->Font->Size = 12;
  grilla->OnDrawCell = grillaCiudadesDrawCell;
  grilla->OnSelectCell = grillaCiudadesSelectCell;
  grilla->Cells[0][0] = "ID";
  grilla->Cells[1][0] = "Nombre";
  grilla->Cells[2][0] = "X";
  grilla->Cells[3][0] = "Y";

  int cantidad = mapa->obtenerCantidadCiudades();
  for (int i = 0; i < cantidad; i++) {
    Coordenadas coords = ciudadesUI[i].obtenerCoordenadas();
    grilla->Cells[0][i + 1] = IntToStr(ciudadesUI[i].obtenerId());
    grilla->Cells[1][i + 1] =
        UnicodeString(ciudadesUI[i].obtenerNombre().c_str());
    grilla->Cells[2][i + 1] = IntToStr(coords.x);
    grilla->Cells[3][i + 1] = IntToStr(coords.y);
  }
  if (cantidad > 0) {
    grilla->Row = cantidad;
  }

  int indiceDatos = cantidad > 0 ? cantidad - 1 : 0;
  UnicodeString etiquetas[4] = {
      "ID:", "Nombre:", "Coordenada X:", "Coordenada Y:"};
  TEdit **edits[4] = {&txtCiudadId, &txtCiudadNombre, &txtCiudadX, &txtCiudadY};

  for (int i = 0; i < 4; i++) {
    TLabel *lbl = new TLabel(this);
    lbl->Parent = panelDatos;
    lbl->SetBounds(28, 88 + i * 70, 140, 26);
    lbl->Caption = etiquetas[i];
    lbl->Font->Name = "Segoe UI";
    lbl->Font->Size = 12;
    lbl->Font->Color = clBlack;

    TEdit *edit = new TEdit(this);
    edit->Parent = panelDatos;
    edit->SetBounds(166, 80 + i * 70, 150, 36);
    edit->Font->Name = "Segoe UI";
    edit->Font->Size = 12;
    edit->Color = clWhite;
    *edits[i] = edit;
  }
  actualizarCamposCiudad(indiceDatos);

  crearBotonAccion(panelAcciones, 26, 86, 182, 48, "+   Agregar ciudad",
                   (TColor)0x0020A020);
  crearBotonAccion(panelAcciones, 26, 156, 182, 48, "X   Eliminar Ciudad",
                   (TColor)0x002020E8);
}

void TForm1::construirVistaRutas() {
  while (pnlRutas->ControlCount > 0) {
    delete pnlRutas->Controls[0];
  }

  pnlRutas->Color = clWhite;
  pnlRutas->ParentBackground = false;

  TLabel *titulo = new TLabel(this);
  titulo->Parent = pnlRutas;
  titulo->SetBounds(38, 30, 520, 48);
  titulo->Caption = "3. GESTION DE RUTAS";
  titulo->Font->Name = "Segoe UI";
  titulo->Font->Size = 22;
  titulo->Font->Style = TFontStyles() << fsBold;
  titulo->Font->Color = (TColor)0x00B75B20;

  TPanel *panelListado =
      crearPanelSeccion(pnlRutas, 24, 104, 830, 520, "Listado de Rutas");
  TPanel *panelAcciones =
      crearPanelSeccion(pnlRutas, 870, 104, 280, 520, "Acciones");

  TStringGrid *grilla = new TStringGrid(this);
  grilla->Parent = panelListado;
  grilla->SetBounds(20, 76, 790, 440);
  grilla->ColCount = 3;
  grilla->RowCount = 18;
  grilla->FixedRows = 1;
  grilla->DefaultRowHeight = 38;
  grilla->ColWidths[0] = 250;
  grilla->ColWidths[1] = 270;
  grilla->ColWidths[2] = 250;
  grilla->Options = grilla->Options << goRowSelect;
  grilla->Font->Name = "Segoe UI";
  grilla->Font->Size = 11;
  grilla->Cells[0][0] = "Origen";
  grilla->Cells[1][0] = "Destino";
  grilla->Cells[2][0] = "Distancia (km)";

  int fila = 1;
  int cantidad = mapa->obtenerCantidadCiudades();
  for (int i = 0; i < cantidad; i++) {
    for (int j = i + 1; j < cantidad; j++) {
      if (matriz[i][j] > 0) {
        if (fila >= grilla->RowCount) {
          grilla->RowCount = grilla->RowCount + 1;
        }
        grilla->Cells[0][fila] =
            UnicodeString(ciudadesUI[i].obtenerNombre().c_str());
        grilla->Cells[1][fila] =
            UnicodeString(ciudadesUI[j].obtenerNombre().c_str());
        grilla->Cells[2][fila] = IntToStr(matriz[i][j]);
        fila++;
      }
    }
  }
  if (fila > 2) {
    grilla->Row = 2;
  }

  crearBotonAccion(panelAcciones, 32, 86, 210, 48, "+   Nueva Ruta",
                   (TColor)0x0020A020);
  crearBotonAccion(panelAcciones, 32, 156, 210, 48, "X   Eliminar Ruta",
                   (TColor)0x002020E8);
}

void __fastcall TForm1::PanelMouseEnter(TObject *Sender) {
  TPanel *P = nullptr;

  if (dynamic_cast<TPanel *>(Sender))
    P = dynamic_cast<TPanel *>(Sender);
  else if (dynamic_cast<TControl *>(Sender))
    P = dynamic_cast<TPanel *>(dynamic_cast<TControl *>(Sender)->Parent);

  if (P)
    P->Color = (TColor)0x007A4A1F;
}

void __fastcall TForm1::PanelMouseLeave(TObject *Sender) {
  TPanel *P = nullptr;

  if (dynamic_cast<TPanel *>(Sender))
    P = dynamic_cast<TPanel *>(Sender);
  else if (dynamic_cast<TControl *>(Sender))
    P = dynamic_cast<TPanel *>(dynamic_cast<TControl *>(Sender)->Parent);

  if (P)
    P->Color = (TColor)0x00522D0B;
}

void __fastcall TForm1::btnCalcularRutasClick(TObject *Sender) {
  pnlCiudades->Visible = false;
  pnlHistorial->Visible = false;
  pnlRutas->Visible = false;
  pnlCalcularDistancia->Visible = true;
  pnlCalcularDistancia->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnCiudadesClick(TObject *Sender) {

  pnlCalcularDistancia->Visible = false;
  pnlHistorial->Visible = false;
  pnlRutas->Visible = false;
  pnlCiudades->Align = alClient;
  construirVistaCiudades();
  pnlCiudades->Visible = true;
  pnlCiudades->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnRutasClick(TObject *Sender) {

  pnlCalcularDistancia->Visible = false;
  pnlHistorial->Visible = false;
  pnlCiudades->Visible = false;
  pnlRutas->Align = alClient;
  construirVistaRutas();
  pnlRutas->Visible = true;
  pnlRutas->BringToFront();
}

void __fastcall TForm1::BtnHistorialClick(TObject *Sender) {
  pnlCalcularDistancia->Visible = false;
  pnlCiudades->Visible = false;
  pnlRutas->Visible = false;
  pnlHistorial->Visible = true;
  pnlHistorial->BringToFront();
}

void __fastcall TForm1::btnCalcularRutaOptimaClick(TObject *Sender) {
  // int origen = obtenerIdCiudadSeleccionada(ComboBox1);
  // int destino = obtenerIdCiudadSeleccionada(cbDestino);

  // ResultadoRuta resultado = sistemaLogistico.calcularRutaOptima(origen,
  // destino);

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

void __fastcall TForm1::btnLimpiarCamposClick(TObject *Sender) {
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

void __fastcall TForm1::PanelMapaResize(TObject *Sender) { redibujarMapa(); }
//
void __fastcall TForm1::MapaOverlayPaint(TObject *Sender) {
  pintarConexiones(mapaOverlay->Canvas);
  pintarRutaCalculada(mapaOverlay->Canvas);
  pintarCiudades(mapaOverlay->Canvas);
}
