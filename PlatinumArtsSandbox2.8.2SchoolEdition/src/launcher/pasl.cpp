/////////////////////////////////////////////////////////////////////////////
// Name:        pasl.cpp
// Purpose:
// Author:      James Burns
// Modified by:
// Created:     17/12/2008 19:03:58
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "wx/stdpaths.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "pasl.h"

////@begin XPM images
#include "sandboxlogo.xpm"
#include "NoImage.xpm"
////@end XPM images


/*!
 * PASL type definition
 */

IMPLEMENT_CLASS( PASL, wxFrame )


/*!
 * PASL event table definition
 */

BEGIN_EVENT_TABLE( PASL, wxFrame )

////@begin PASL event table entries
    EVT_COMBOBOX( ID_COMBOBOX, PASL::OnResBoxSelected )

    EVT_COMBOBOX( ID_COMBOBOX1, PASL::OnShaderBoxSelected )

    EVT_COMBOBOX( ID_COMBOBOX2, PASL::OnVSyncSelected )

    EVT_COMBOBOX( ID_COMBOBOX6, PASL::OnMapBoxSelected )

    EVT_BUTTON( ID_BUTTON, PASL::OnFPSLaunch )

    EVT_BUTTON( ID_BUTTON1, PASL::OnSSPLaunch )

    EVT_BUTTON( ID_BUTTON2, PASL::OnRPGLaunch )

    EVT_TEXT( ID_TEXTCTRL, PASL::OnServerNameTextUpdated )

    EVT_COMBOBOX( ID_COMBOBOX3, PASL::OnPlayerBoxSelected )

    EVT_COMBOBOX( ID_COMBOBOX4, PASL::OnMasterBoxSelected )

    EVT_TEXT( ID_TEXTCTRL1, PASL::OnServerPasswordTextUpdated )

    EVT_COMBOBOX( ID_COMBOBOX5, PASL::OnDedBoxSelected )

    EVT_COMBOBOX( ID_COMBOBOX7, PASL::OnModeBoxSelected )

    EVT_BUTTON( ID_BUTTON3, PASL::OnServerLaunch )

    EVT_TEXT( ID_TEXTCTRL2, PASL::OnClientIPTextUpdated )

    EVT_TEXT( ID_TEXTCTRL3, PASL::OnClientPasswordTextUpdated )

    EVT_COMBOBOX( ID_COMBOBOX8, PASL::OnCModeBoxSelected )

    EVT_BUTTON( ID_BUTTON4, PASL::OnClientLaunch )

    EVT_BUTTON( ID_BUTTON5, PASL::OnMovieCubeButtonClick )

////@end PASL event table entries

END_EVENT_TABLE()


/*!
 * PASL constructors
 */

PASL::PASL()
{
    Init();
}

PASL::PASL( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*!
 * PASL creator
 */

bool PASL::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin PASL creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    SetIcon(GetIconResource(wxT("sandboxlogo.xpm")));
    Centre();
////@end PASL creation
    return true;
}


/*!
 * PASL destructor
 */

PASL::~PASL()
{
////@begin PASL destruction
////@end PASL destruction
}


/*!
 * Member initialisation
 */

void PASL::Init()
{
////@begin PASL member initialisation
    ResBox = NULL;
    ShaderBox = NULL;
    VSyncBox = NULL;
    MapBox = NULL;
    MapPrev = NULL;
    FPSLaunch = NULL;
    SSPLaunch = NULL;
    RPGLaunch = NULL;
    ServerName = NULL;
    PlayerBox = NULL;
    MasterBox = NULL;
    ServerPassword = NULL;
    DedBox = NULL;
    ModeBox = NULL;
    ServerLaunch = NULL;
    ClientIP = NULL;
    ClientPassword = NULL;
    CModeBox = NULL;
    ClientLaunch = NULL;
    MovieCubeButton = NULL;
////@end PASL member initialisation
}


/*!
 * Control creation for PASL
 */

void PASL::CreateControls()
{
////@begin PASL content construction
    // Generated by DialogBlocks, Fri 15 Jan 2010 16:18:25 EST (unregistered)

    PASL* itemFrame1 = this;

    wxPanel* itemPanel2 = new wxPanel( itemFrame1, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(3, 1, 0, 0);
    itemPanel2->SetSizer(itemFlexGridSizer3);

    wxFlexGridSizer* itemFlexGridSizer4 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer3->Add(itemFlexGridSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer5Static = new wxStaticBox(itemPanel2, wxID_ANY, _("Resolution"));
    wxStaticBoxSizer* itemStaticBoxSizer5 = new wxStaticBoxSizer(itemStaticBoxSizer5Static, wxHORIZONTAL);
    itemFlexGridSizer4->Add(itemStaticBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString ResBoxStrings;
    ResBoxStrings.Add(_("640x480"));
    ResBoxStrings.Add(_("800x600"));
    ResBoxStrings.Add(_("1024x768"));
    ResBoxStrings.Add(_("1280x960"));
    ResBoxStrings.Add(_("1600x1200"));
    ResBox = new wxComboBox( itemPanel2, ID_COMBOBOX, _("1024x768"), wxDefaultPosition, wxSize(110, -1), ResBoxStrings, wxCB_READONLY );
    ResBox->SetStringSelection(_("1024x768"));
    itemStaticBoxSizer5->Add(ResBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer7Static = new wxStaticBox(itemPanel2, wxID_ANY, _("Shaders"));
    wxStaticBoxSizer* itemStaticBoxSizer7 = new wxStaticBoxSizer(itemStaticBoxSizer7Static, wxHORIZONTAL);
    itemFlexGridSizer4->Add(itemStaticBoxSizer7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString ShaderBoxStrings;
    ShaderBoxStrings.Add(_("Off"));
    ShaderBoxStrings.Add(_("Low"));
    ShaderBoxStrings.Add(_("High"));
    ShaderBox = new wxComboBox( itemPanel2, ID_COMBOBOX1, _("Low"), wxDefaultPosition, wxSize(70, -1), ShaderBoxStrings, wxCB_READONLY );
    ShaderBox->SetStringSelection(_("Low"));
    itemStaticBoxSizer7->Add(ShaderBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer9Static = new wxStaticBox(itemPanel2, wxID_ANY, _("VSync"));
    wxStaticBoxSizer* itemStaticBoxSizer9 = new wxStaticBoxSizer(itemStaticBoxSizer9Static, wxHORIZONTAL);
    itemFlexGridSizer4->Add(itemStaticBoxSizer9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString VSyncBoxStrings;
    VSyncBoxStrings.Add(_("Off"));
    VSyncBoxStrings.Add(_("On"));
    VSyncBox = new wxComboBox( itemPanel2, ID_COMBOBOX2, _("Off"), wxDefaultPosition, wxSize(60, -1), VSyncBoxStrings, wxCB_READONLY );
    VSyncBox->SetStringSelection(_("Off"));
    itemStaticBoxSizer9->Add(VSyncBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer11 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer3->Add(itemFlexGridSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer12Static = new wxStaticBox(itemPanel2, wxID_ANY, _("Map"));
    wxStaticBoxSizer* itemStaticBoxSizer12 = new wxStaticBoxSizer(itemStaticBoxSizer12Static, wxHORIZONTAL);
    itemFlexGridSizer11->Add(itemStaticBoxSizer12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString MapBoxStrings;
    MapBox = new wxComboBox( itemPanel2, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxSize(180, -1), MapBoxStrings, wxCB_READONLY );
    itemStaticBoxSizer12->Add(MapBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer14Static = new wxStaticBox(itemPanel2, wxID_ANY, _("Map Image"));
    wxStaticBoxSizer* itemStaticBoxSizer14 = new wxStaticBoxSizer(itemStaticBoxSizer14Static, wxHORIZONTAL);
    itemFlexGridSizer11->Add(itemStaticBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    MapPrev = new wxStaticBitmap( itemPanel2, wxID_STATIC, itemFrame1->GetBitmapResource(wxT("NoImage.xpm")), wxDefaultPosition, wxSize(64, 64), wxSIMPLE_BORDER );
    itemStaticBoxSizer14->Add(MapPrev, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer16 = new wxFlexGridSizer(1, 1, 0, 0);
    itemFlexGridSizer3->Add(itemFlexGridSizer16, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxNotebook* itemNotebook17 = new wxNotebook( itemPanel2, ID_NOTEBOOK, wxDefaultPosition, wxSize(320, -1), wxBK_DEFAULT );

    wxPanel* itemPanel18 = new wxPanel( itemNotebook17, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel18->SetBackgroundColour(wxColour(224, 223, 227));
    wxFlexGridSizer* itemFlexGridSizer19 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer19->AddGrowableCol(0);
    itemPanel18->SetSizer(itemFlexGridSizer19);

    FPSLaunch = new wxButton( itemPanel18, ID_BUTTON, _("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer19->Add(FPSLaunch, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemNotebook17->AddPage(itemPanel18, _("FPS"));

    wxPanel* itemPanel21 = new wxPanel( itemNotebook17, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel21->SetBackgroundColour(wxColour(224, 223, 227));
    wxFlexGridSizer* itemFlexGridSizer22 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer22->AddGrowableCol(0);
    itemPanel21->SetSizer(itemFlexGridSizer22);

    SSPLaunch = new wxButton( itemPanel21, ID_BUTTON1, _("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer22->Add(SSPLaunch, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemNotebook17->AddPage(itemPanel21, _("SSP"));

    wxPanel* itemPanel24 = new wxPanel( itemNotebook17, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel24->SetBackgroundColour(wxColour(224, 223, 227));
    wxFlexGridSizer* itemFlexGridSizer25 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer25->AddGrowableCol(0);
    itemPanel24->SetSizer(itemFlexGridSizer25);

    RPGLaunch = new wxButton( itemPanel24, ID_BUTTON2, _("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer25->Add(RPGLaunch, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemNotebook17->AddPage(itemPanel24, _("RPG"));

    wxPanel* itemPanel27 = new wxPanel( itemNotebook17, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel27->SetBackgroundColour(wxColour(224, 223, 227));
    wxFlexGridSizer* itemFlexGridSizer28 = new wxFlexGridSizer(3, 1, 0, 0);
    itemPanel27->SetSizer(itemFlexGridSizer28);

    wxFlexGridSizer* itemFlexGridSizer29 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer28->Add(itemFlexGridSizer29, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxStaticBox* itemStaticBoxSizer30Static = new wxStaticBox(itemPanel27, wxID_ANY, _("Server Name"));
    wxStaticBoxSizer* itemStaticBoxSizer30 = new wxStaticBoxSizer(itemStaticBoxSizer30Static, wxHORIZONTAL);
    itemFlexGridSizer29->Add(itemStaticBoxSizer30, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    ServerName = new wxTextCtrl( itemPanel27, ID_TEXTCTRL, _("Sandbox Server"), wxDefaultPosition, wxSize(100, -1), 0 );
    itemStaticBoxSizer30->Add(ServerName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer32Static = new wxStaticBox(itemPanel27, wxID_ANY, _("Players"));
    wxStaticBoxSizer* itemStaticBoxSizer32 = new wxStaticBoxSizer(itemStaticBoxSizer32Static, wxHORIZONTAL);
    itemFlexGridSizer29->Add(itemStaticBoxSizer32, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxArrayString PlayerBoxStrings;
    PlayerBoxStrings.Add(_("0"));
    PlayerBoxStrings.Add(_("1"));
    PlayerBoxStrings.Add(_("2"));
    PlayerBoxStrings.Add(_("3"));
    PlayerBoxStrings.Add(_("4"));
    PlayerBoxStrings.Add(_("5"));
    PlayerBoxStrings.Add(_("6"));
    PlayerBoxStrings.Add(_("7"));
    PlayerBoxStrings.Add(_("8"));
    PlayerBoxStrings.Add(_("9"));
    PlayerBoxStrings.Add(_("10"));
    PlayerBoxStrings.Add(_("11"));
    PlayerBoxStrings.Add(_("12"));
    PlayerBoxStrings.Add(_("13"));
    PlayerBoxStrings.Add(_("14"));
    PlayerBoxStrings.Add(_("15"));
    PlayerBoxStrings.Add(_("16"));
    PlayerBoxStrings.Add(_("17"));
    PlayerBoxStrings.Add(_("18"));
    PlayerBoxStrings.Add(_("19"));
    PlayerBoxStrings.Add(_("20"));
    PlayerBoxStrings.Add(_("21"));
    PlayerBoxStrings.Add(_("22"));
    PlayerBoxStrings.Add(_("23"));
    PlayerBoxStrings.Add(_("24"));
    PlayerBoxStrings.Add(_("25"));
    PlayerBoxStrings.Add(_("26"));
    PlayerBoxStrings.Add(_("27"));
    PlayerBoxStrings.Add(_("28"));
    PlayerBoxStrings.Add(_("29"));
    PlayerBoxStrings.Add(_("30"));
    PlayerBoxStrings.Add(_("31"));
    PlayerBoxStrings.Add(_("32"));
    PlayerBox = new wxComboBox( itemPanel27, ID_COMBOBOX3, _("12"), wxDefaultPosition, wxSize(60, -1), PlayerBoxStrings, wxCB_READONLY );
    PlayerBox->SetStringSelection(_("12"));
    itemStaticBoxSizer32->Add(PlayerBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer34Static = new wxStaticBox(itemPanel27, wxID_ANY, _("MMode"));
    wxStaticBoxSizer* itemStaticBoxSizer34 = new wxStaticBoxSizer(itemStaticBoxSizer34Static, wxHORIZONTAL);
    itemFlexGridSizer29->Add(itemStaticBoxSizer34, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxArrayString MasterBoxStrings;
    MasterBoxStrings.Add(_("N"));
    MasterBoxStrings.Add(_("Y"));
    MasterBox = new wxComboBox( itemPanel27, ID_COMBOBOX4, _("N"), wxDefaultPosition, wxSize(50, -1), MasterBoxStrings, wxCB_READONLY );
    MasterBox->SetStringSelection(_("N"));
    itemStaticBoxSizer34->Add(MasterBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer36 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer28->Add(itemFlexGridSizer36, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxStaticBox* itemStaticBoxSizer37Static = new wxStaticBox(itemPanel27, wxID_ANY, _("Server Password"));
    wxStaticBoxSizer* itemStaticBoxSizer37 = new wxStaticBoxSizer(itemStaticBoxSizer37Static, wxHORIZONTAL);
    itemFlexGridSizer36->Add(itemStaticBoxSizer37, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    ServerPassword = new wxTextCtrl( itemPanel27, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(100, -1), 0 );
    itemStaticBoxSizer37->Add(ServerPassword, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer39Static = new wxStaticBox(itemPanel27, wxID_ANY, _("Dedicated"));
    wxStaticBoxSizer* itemStaticBoxSizer39 = new wxStaticBoxSizer(itemStaticBoxSizer39Static, wxHORIZONTAL);
    itemFlexGridSizer36->Add(itemStaticBoxSizer39, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxArrayString DedBoxStrings;
    DedBoxStrings.Add(_("N"));
    DedBoxStrings.Add(_("Y"));
    DedBox = new wxComboBox( itemPanel27, ID_COMBOBOX5, _("N"), wxDefaultPosition, wxSize(60, -1), DedBoxStrings, wxCB_READONLY );
    DedBox->SetStringSelection(_("N"));
    itemStaticBoxSizer39->Add(DedBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer41Static = new wxStaticBox(itemPanel27, wxID_ANY, _("Mode"));
    wxStaticBoxSizer* itemStaticBoxSizer41 = new wxStaticBoxSizer(itemStaticBoxSizer41Static, wxHORIZONTAL);
    itemFlexGridSizer36->Add(itemStaticBoxSizer41, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxArrayString ModeBoxStrings;
    ModeBoxStrings.Add(_("FPS"));
    ModeBoxStrings.Add(_("SSP"));
    ModeBoxStrings.Add(_("RPG"));
    ModeBox = new wxComboBox( itemPanel27, ID_COMBOBOX7, _("FPS"), wxDefaultPosition, wxSize(65, -1), ModeBoxStrings, wxCB_READONLY );
    ModeBox->SetStringSelection(_("FPS"));
    itemStaticBoxSizer41->Add(ModeBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer43 = new wxFlexGridSizer(1, 3, 0, 0);
    itemFlexGridSizer28->Add(itemFlexGridSizer43, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    itemFlexGridSizer43->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    ServerLaunch = new wxButton( itemPanel27, ID_BUTTON3, _("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer43->Add(ServerLaunch, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer43->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemNotebook17->AddPage(itemPanel27, _("Server"));

    wxPanel* itemPanel47 = new wxPanel( itemNotebook17, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel47->SetBackgroundColour(wxColour(224, 223, 227));
    wxFlexGridSizer* itemFlexGridSizer48 = new wxFlexGridSizer(2, 1, 0, 0);
    itemFlexGridSizer48->AddGrowableCol(0);
    itemPanel47->SetSizer(itemFlexGridSizer48);

    wxFlexGridSizer* itemFlexGridSizer49 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer48->Add(itemFlexGridSizer49, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxStaticBox* itemStaticBoxSizer50Static = new wxStaticBox(itemPanel47, wxID_ANY, _("IP Address"));
    wxStaticBoxSizer* itemStaticBoxSizer50 = new wxStaticBoxSizer(itemStaticBoxSizer50Static, wxHORIZONTAL);
    itemFlexGridSizer49->Add(itemStaticBoxSizer50, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    ClientIP = new wxTextCtrl( itemPanel47, ID_TEXTCTRL2, _("192.168.1.100"), wxDefaultPosition, wxSize(120, -1), 0 );
    itemStaticBoxSizer50->Add(ClientIP, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer52Static = new wxStaticBox(itemPanel47, wxID_ANY, _("Password"));
    wxStaticBoxSizer* itemStaticBoxSizer52 = new wxStaticBoxSizer(itemStaticBoxSizer52Static, wxHORIZONTAL);
    itemFlexGridSizer49->Add(itemStaticBoxSizer52, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    ClientPassword = new wxTextCtrl( itemPanel47, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(100, -1), 0 );
    itemStaticBoxSizer52->Add(ClientPassword, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer54 = new wxFlexGridSizer(1, 2, 0, 0);
    itemFlexGridSizer48->Add(itemFlexGridSizer54, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxStaticBox* itemStaticBoxSizer55Static = new wxStaticBox(itemPanel47, wxID_ANY, _("Mode"));
    wxStaticBoxSizer* itemStaticBoxSizer55 = new wxStaticBoxSizer(itemStaticBoxSizer55Static, wxHORIZONTAL);
    itemFlexGridSizer54->Add(itemStaticBoxSizer55, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxArrayString CModeBoxStrings;
    CModeBoxStrings.Add(_("FPS"));
    CModeBoxStrings.Add(_("SSP"));
    CModeBoxStrings.Add(_("RPG"));
    CModeBox = new wxComboBox( itemPanel47, ID_COMBOBOX8, _("FPS"), wxDefaultPosition, wxSize(70, -1), CModeBoxStrings, wxCB_DROPDOWN );
    CModeBox->SetStringSelection(_("FPS"));
    itemStaticBoxSizer55->Add(CModeBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    ClientLaunch = new wxButton( itemPanel47, ID_BUTTON4, _("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer54->Add(ClientLaunch, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemNotebook17->AddPage(itemPanel47, _("Client"));

    wxPanel* itemPanel58 = new wxPanel( itemNotebook17, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel58->SetBackgroundColour(wxColour(224, 223, 227));
    wxFlexGridSizer* itemFlexGridSizer59 = new wxFlexGridSizer(1, 1, 0, 0);
    itemFlexGridSizer59->AddGrowableCol(0);
    itemPanel58->SetSizer(itemFlexGridSizer59);

    MovieCubeButton = new wxButton( itemPanel58, ID_BUTTON5, _("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer59->Add(MovieCubeButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemNotebook17->AddPage(itemPanel58, _("MovieCube"));

    itemFlexGridSizer16->Add(itemNotebook17, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end PASL content construction

    //Enable JPEG Loading
    wxInitAllImageHandlers();

    //Get Current Resolution
    ResWidth = wxString::Format(wxT("%i"),wxSystemSettings::GetMetric(wxSYS_SCREEN_X));
    ResHeight = wxString::Format(wxT("%i"),wxSystemSettings::GetMetric(wxSYS_SCREEN_Y));
    ResBox->Append(ResWidth + wxT("x") + ResHeight);
    ResBox->SetValue(ResWidth + wxT("x") + ResHeight);

    //Figure Out Which OS Is Running And Set EXE/Map Directories
    #ifdef __WIN32__
        //WinExe = wxT("bin\\sandbox.exe -r ");
        CurFPSc = wxT("bin\\sandbox_fps.exe -qmy_stuff -r ");
        CurSSPc = wxT("bin\\sandbox_ssp.exe -qmy_stuff -r ");
        CurRPGc = wxT("bin\\sandbox_rpg.exe -qmy_stuff -r ");
        CurFPSs = wxT("bin\\sandbox_fps.exe -r ");
        CurSSPs = wxT("bin\\sandbox_ssp.exe -r ");
        CurRPGs = wxT("bin\\sandbox_rpg.exe -r ");
        CurMovie = wxT("bin\\sandbox_movie.exe");
        //CurExe = WinExe;
        MapDir = (wxGetCwd() + wxT("\\packages\\base\\"));
		StuffDir = (wxGetCwd() + wxT("\\my_stuff\\packages\\base\\"));
    #endif
    #ifdef __UNIX__
        if(wxIsPlatform64Bit())
        {
            //LinExe = wxT("./bin//sandbox_client_x86_64 -r ");
            CurFPSc = wxT("./bin/sandbox_client_64_fps -q") + wxStandardPaths::Get().GetUserConfigDir() + wxT("/.platinumarts -r ");
            CurSSPc = wxT("./bin/sandbox_client_64_ssp -q") + wxStandardPaths::Get().GetUserConfigDir() + wxT("/.platinumarts -r ");
            CurRPGc = wxT("./bin/sandbox_client_64_rpg -q") + wxStandardPaths::Get().GetUserConfigDir() + wxT("/.platinumarts -r ");
            CurFPSs = wxT("./bin/sandbox_server_64_fps ");
            CurSSPs = wxT("./bin/sandbox_server_64_ssp ");
            CurRPGs = wxT("./bin/sandbox_server_64_rpg ");
            CurMovie = wxT("./bin/sandbox_client_32_movie");
        }
        else
        {
            CurFPSc = wxT("./bin/sandbox_client_32_fps -q") + wxStandardPaths::Get().GetUserConfigDir() + wxT("/.platinumarts -r ");
            CurSSPc = wxT("./bin/sandbox_client_32_ssp -q") + wxStandardPaths::Get().GetUserConfigDir() + wxT("/.platinumarts -r ");
            CurRPGc = wxT("./bin/sandbox_client_32_rpg -q") + wxStandardPaths::Get().GetUserConfigDir() + wxT("/.platinumarts -r ");
            CurFPSs = wxT("./bin/sandbox_server_32_fps ");
            CurSSPs = wxT("./bin/sandbox_server_32_ssp ");
            CurRPGs = wxT("./bin/sandbox_server_32_rpg ");
            CurMovie = wxT("./bin/sandbox_client_32_movie");
            //LinExe = wxT(".//bin//sandbox_client_i686 -r ");
        }
        //LinExe = wxT(".//bin//sandbox_client_") + wxGetCommandOutput(wxT("uname -m")) + " -r ");
        //CurExe = LinExe;
        MapDir = (wxGetCwd() + wxT("/packages/base/"));
	StuffDir = (wxStandardPaths::Get().GetUserConfigDir() + wxT("/.platinumarts/packages/base/"));
    #endif

    //Get Map List
	wxString filename;
    wxDir dir(MapDir);
    if (dir.IsOpened())
    {
        bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
        while(cont)
        {
            if(filename.Right(4).IsSameAs(wxT(".ogz")))
            {
                MapBox->Append(filename.Left(filename.Len() - 4));
            }
            cont = dir.GetNext(&filename);
        }
    }
    wxDir dir2(StuffDir);
    if (dir2.IsOpened())
    {
        bool cont = dir2.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
        while(cont)
        {
            if(filename.Right(4).IsSameAs(wxT(".ogz")))
            {
                MapBox->Append(filename.Left(filename.Len() - 4));
            }
            cont = dir2.GetNext(&filename);
        }
    }
    MapBox->SetValue(wxT("village"));

    //Set Default Values
    wxCommandEvent ce;
    OnResBoxSelected(ce);
    OnShaderBoxSelected(ce);
    OnVSyncSelected(ce);
    OnMapBoxSelected(ce);
    OnServerNameTextUpdated(ce);
    OnPlayerBoxSelected(ce);
    OnMasterBoxSelected(ce);
    OnServerPasswordTextUpdated(ce);
    OnDedBoxSelected(ce);
    OnModeBoxSelected(ce);
    OnClientIPTextUpdated(ce);
    OnClientPasswordTextUpdated(ce);
    OnCModeBoxSelected(ce);

}


/*!
 * Should we show tooltips?
 */

bool PASL::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap PASL::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin PASL bitmap retrieval
    wxUnusedVar(name);
    if (name == _T("NoImage.xpm"))
    {
        wxBitmap bitmap(NoImage_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end PASL bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon PASL::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin PASL icon retrieval
    wxUnusedVar(name);
    if (name == _T("sandboxlogo.xpm"))
    {
        wxIcon icon(sandboxlogo_xpm);
        return icon;
    }
    return wxNullIcon;
////@end PASL icon retrieval
}

void PASL::GetError(wxProcess* MyProc)
{
    pid = MyProc->GetPid();
    err = MyProc->GetErrorStream();
    if(err->CanRead())
    {
        char *buf = new char[2048];
        err->Read(buf,2048);
        wxMessageBox(wxString::FromAscii(buf));
    }
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void PASL::OnFPSLaunch( wxCommandEvent& event )
{
    SBProc = SBProc->Open(CurFPSc + CurRes + Shader + VSync + Map,wxEXEC_ASYNC);
    GetError(SBProc);
    event.Skip();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void PASL::OnSSPLaunch( wxCommandEvent& event )
{
    SBProc = SBProc->Open(CurSSPc + CurRes + Shader + VSync + Map,wxEXEC_ASYNC);
    GetError(SBProc);
    event.Skip();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
 */

void PASL::OnRPGLaunch( wxCommandEvent& event )
{
    SBProc = SBProc->Open(CurRPGc + CurRes + Shader + VSync + Map,wxEXEC_ASYNC);
    GetError(SBProc);
    event.Skip();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
 */

void PASL::OnServerLaunch( wxCommandEvent& event )
{
    if(Mode.IsSameAs(wxT("-gfps ")))
        SBSProc = SBSProc->Open(CurFPSs + CurRes + Shader + VSync + Map + ServerN + ServerP + Players + Master + Ded,wxEXEC_ASYNC);
    if(Mode.IsSameAs(wxT("-gssp ")))
        SBSProc = SBSProc->Open(CurSSPs + CurRes + Shader + VSync + Map + ServerN + ServerP + Players + Master + Ded,wxEXEC_ASYNC);
    if(Mode.IsSameAs(wxT("-grpg ")))
        SBSProc = SBSProc->Open(CurRPGs + CurRes + Shader + VSync + Map + ServerN + ServerP + Players + Master + Ded,wxEXEC_ASYNC);

    GetError(SBSProc);
    event.Skip();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON4
 */

void PASL::OnClientLaunch( wxCommandEvent& event )
{
    if(CMode.IsSameAs(wxT("-gfps ")))
        SBProc = SBProc->Open(CurFPSc + CurRes + Shader + VSync + Client,wxEXEC_ASYNC);
    if(CMode.IsSameAs(wxT("-gssp ")))
        SBProc = SBProc->Open(CurSSPc + CurRes + Shader + VSync + Client,wxEXEC_ASYNC);
    if(CMode.IsSameAs(wxT("-grpg ")))
        SBProc = SBProc->Open(CurRPGc + CurRes + Shader + VSync + Client,wxEXEC_ASYNC);

    GetError(SBProc);
    event.Skip();
}

/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX
 */

void PASL::OnResBoxSelected( wxCommandEvent& event )
{
    wxStringTokenizer tkz(ResBox->GetValue(), wxT("x"));
    ResWidth = tkz.GetNextToken();
    ResHeight = tkz.GetNextToken();
    CurRes = wxT("-w") + ResWidth + wxT(" -h") + ResHeight + wxT(" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX1
 */

void PASL::OnShaderBoxSelected( wxCommandEvent& event )
{
    Shader = wxT("-f") + wxString::Format(wxT("%i"),ShaderBox->GetCurrentSelection()) + wxT(" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX2
 */

void PASL::OnVSyncSelected( wxCommandEvent& event )
{
    VSync = wxT("-v") + wxString::Format(wxT("%i"),VSyncBox->GetCurrentSelection()) + wxT(" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX6
 */

void PASL::OnMapBoxSelected( wxCommandEvent& event )
{
    Map = wxT("-l") + MapBox->GetValue() + wxT(" ");
    PrevImg.Destroy();
    if(wxFile::Exists(MapDir + MapBox->GetValue() + wxT(".png")))
        PrevImg.LoadFile(MapDir + MapBox->GetValue() + wxT(".png"));
    else if(wxFile::Exists(MapDir + MapBox->GetValue() + wxT(".jpg")))
        PrevImg.LoadFile(MapDir + MapBox->GetValue() + wxT(".jpg"));
    else if(wxFile::Exists(MapDir + MapBox->GetValue() + wxT(".bmp")))
        PrevImg.LoadFile(MapDir + MapBox->GetValue() + wxT(".bmp"));

	wxSize imgsize = PASL::ConvertDialogToPixels(wxSize(35, 35));
    imgsize.Set(64,64);

    if(PrevImg.IsOk())
        MapPrev->SetBitmap(wxBitmap(PrevImg.Rescale(imgsize.x,imgsize.y)));
    else
        MapPrev->SetBitmap(wxBitmap(GetBitmapResource(wxT("NoImage.xpm"))).ConvertToImage().Rescale(imgsize.x,imgsize.y));
    event.Skip();
}


/*!
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL
 */

void PASL::OnServerNameTextUpdated( wxCommandEvent& event )
{
    if(ServerName)
        ServerN = wxT("-n\"") + ServerName->GetValue() + wxT("\" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX3
 */

void PASL::OnPlayerBoxSelected( wxCommandEvent& event )
{
    Players = wxT("-c") + wxString::Format(wxT("%i"),PlayerBox->GetCurrentSelection()) + wxT(" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX4
 */

void PASL::OnMasterBoxSelected( wxCommandEvent& event )
{
    Master = wxT("-o") + wxString::Format(wxT("%i"),MasterBox->GetCurrentSelection()) + wxT(" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL1
 */

void PASL::OnServerPasswordTextUpdated( wxCommandEvent& event )
{
    if(ServerPassword)
        ServerP = wxT("-p\"") + ServerPassword->GetValue() + wxT("\" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX5
 */

void PASL::OnDedBoxSelected( wxCommandEvent& event )
{
    if(DedBox->GetCurrentSelection() == 1)
        Ded = wxT("-d ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX7
 */

void PASL::OnModeBoxSelected( wxCommandEvent& event )
{
    Mode = wxT("-g") + ModeBox->GetValue().MakeLower() + wxT(" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL2
 */

void PASL::OnClientIPTextUpdated( wxCommandEvent& event )
{
    if(ClientIP)
        CIP = wxT("[ connect ") + ClientIP->GetValue() + wxT(" ]");
    Client = wxT("-x\"sleep 1000 ") + CIP + CPassword + wxT("\" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TEXTCTRL3
 */

void PASL::OnClientPasswordTextUpdated( wxCommandEvent& event )
{
    if(ClientPassword)
        CPassword = wxT("[ setmaster ") + ClientPassword->GetValue() + wxT(" ]");
    Client = wxT("-x\"sleep 1000 ") + CIP + CPassword + wxT("\" ");
    event.Skip();
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_COMBOBOX8
 */

void PASL::OnCModeBoxSelected( wxCommandEvent& event )
{
    CMode = wxT("-g") + CModeBox->GetValue().MakeLower() + wxT(" ");
    event.Skip();

}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON5
 */

void PASL::OnMovieCubeButtonClick( wxCommandEvent& event )
{
    //SBProc = SBProc->Open(CurMovie + CurRes + Shader + VSync + Map,wxEXEC_ASYNC);
    SBProc = SBProc->Open(CurMovie,wxEXEC_ASYNC);
    GetError(SBProc);
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON5 in PASL.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON5 in PASL. 
}

