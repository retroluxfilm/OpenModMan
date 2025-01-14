/*
  This file is part of Open Mod Manager.

  Open Mod Manager is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Open Mod Manager is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Open Mod Manager. If not, see <http://www.gnu.org/licenses/>.
*/
#include "OmBase.h"

#include "OmBaseUi.h"

#include "OmManager.h"
#include "OmDialogProp.h"

#include "OmUtilDlg.h"

///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
#include "OmUiPropMgrGle.h"


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
OmUiPropMgrGle::OmUiPropMgrGle(HINSTANCE hins) : OmDialog(hins)
{
  // modified parameters flags
  for(unsigned i = 0; i < 8; ++i)
    this->_chParam[i] = false;
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
OmUiPropMgrGle::~OmUiPropMgrGle()
{

}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
long OmUiPropMgrGle::id() const
{
  return IDD_PROP_MGR_GLE;
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::setChParam(unsigned i, bool en)
{
  _chParam[i] = en;
  static_cast<OmDialogProp*>(this->_parent)->checkChanges();
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::_onCkBoxRaw()
{
  int bm_chk = this->msgItem(IDC_BC_CKBX1, BM_GETCHECK);

  // user modified parameter, notify it
  this->setChParam(MGR_PROP_GLE_NO_MDPARSE, true);
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::_onCkBoxStr()
{
  int bm_chk = this->msgItem(IDC_BC_CKBX2, BM_GETCHECK);

  this->enableItem(IDC_LB_PATH, bm_chk);
  this->enableItem(IDC_BC_BRW01, bm_chk);

  // user modified parameter, notify it
  this->setChParam(MGR_PROP_GLE_START_LIST, true);
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::_onLbStrlsSel()
{
  int lb_sel = this->msgItem(IDC_LB_PATH, LB_GETCURSEL);

  this->enableItem(IDC_BC_REM, (lb_sel >= 0));
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::_onBcBrwStr()
{
  wstring start, result;

  this->getItemText(IDC_EC_INP01, start);

  if(!Om_dlgOpenFile(result, this->_hwnd, L"Select Context file", OMM_CTX_DEF_FILE_FILER, start))
    return;

  // add file path to startup context list
  this->msgItem(IDC_LB_PATH, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(result.c_str()));

  // user modified parameter, notify it
  this->setChParam(MGR_PROP_GLE_START_LIST, true);
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::_onBcRemStr()
{
  int lb_sel = this->msgItem(IDC_LB_PATH, LB_GETCURSEL);

  if(lb_sel >= 0) {
    this->msgItem(IDC_LB_PATH, LB_DELETESTRING, lb_sel);
    // user modified parameter, notify it
    this->setChParam(MGR_PROP_GLE_START_LIST, true);
  }
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::_onInit()
{
  // define controls tool-tips
  this->_createTooltip(IDC_CB_ICS,    L"Size of icons in packages lists");

  this->_createTooltip(IDC_BC_CKBX2,  L"Disables Markdown parsing and display descriptions as raw text");
  this->_createTooltip(IDC_BC_CKBX2,  L"Automatically opens Context files at application startup");
  this->_createTooltip(IDC_LB_PATH,   L"Context files to be opened at application startup");
  this->_createTooltip(IDC_BC_BRW01,  L"Browse to select a Context file to add");
  this->_createTooltip(IDC_BC_REM,    L"Remove the selected entry");

  // add items to Icon Size ComboBox
  this->msgItem(IDC_CB_ICS, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Small"));
  this->msgItem(IDC_CB_ICS, CB_ADDSTRING, 1, reinterpret_cast<LPARAM>(L"Medium"));
  this->msgItem(IDC_CB_ICS, CB_ADDSTRING, 2, reinterpret_cast<LPARAM>(L"Large"));

  // Update values
  this->_onRefresh();

}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::_onResize()
{
  // Icon size Label & ComboBox
  this->_setItemPos(IDC_SC_LBL01, 50, 20, 100, 9);
  this->_setItemPos(IDC_CB_ICS, 50, 30, this->cliUnitX()-100, 14);
  // force ComboBox to repaint by invalidate rect, else it randomly disappears on resize
  InvalidateRect(this->getItem(IDC_CB_ICS), nullptr, true);

  // No Markdown checkbox
  this->_setItemPos(IDC_BC_CKBX1, 50, 55, 200, 9);

  // Startup Contexts list CheckBox & ListBox
  this->_setItemPos(IDC_BC_CKBX2, 50, 79, 100, 9);
  this->_setItemPos(IDC_LB_PATH, 50, 90, this->cliUnitX()-100, this->cliUnitY()-130);

  // Startup Contexts list Add and Remove... buttons
  this->_setItemPos(IDC_BC_BRW01, 50, this->cliUnitY()-38, 50, 14);
  this->_setItemPos(IDC_BC_REM, 102, this->cliUnitY()-38, 50, 14);
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiPropMgrGle::_onRefresh()
{
  OmManager* pMgr = static_cast<OmManager*>(this->_data);

  switch(pMgr->iconsSize()) {
  case 16:
    this->msgItem(IDC_CB_ICS, CB_SETCURSEL, 0, 0);
    break;
  case 32:
    this->msgItem(IDC_CB_ICS, CB_SETCURSEL, 2, 0);
    break;
  default:
    this->msgItem(IDC_CB_ICS, CB_SETCURSEL, 1, 0);
    break;
  }

  // set No Markdown CheckBox
  this->msgItem(IDC_BC_CKBX1, BM_SETCHECK, pMgr->noMarkdown());

  bool auto_open;
  vector<wstring> path_ls;

  // set Load at Startup CheckBox
  pMgr->getStartContexts(&auto_open, path_ls);
  this->msgItem(IDC_BC_CKBX2, BM_SETCHECK, auto_open);

  // Enable or disable Browse button and ListBox
  this->enableItem(IDC_BC_BRW01, auto_open);
  this->enableItem(IDC_LB_PATH, auto_open);

  // Add paths to ListBox
  this->msgItem(IDC_LB_PATH, LB_RESETCONTENT);


  for(size_t i = 0; i < path_ls.size(); ++i) {
    this->msgItem(IDC_LB_PATH, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(path_ls[i].c_str()));
  }

  // Disable the Remove button
  this->enableItem(IDC_BC_REM, false);

  // reset modified parameters flags
  for(unsigned i = 0; i < 8; ++i) _chParam[i] = false;
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
INT_PTR OmUiPropMgrGle::_onMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if(uMsg == WM_COMMAND) {

    switch(LOWORD(wParam))
    {
    case IDC_CB_ICS: //< Combo-Box for icons size
      if(HIWORD(wParam) == CBN_SELCHANGE)
        // parameter modified, must be saved we parent dialog valid changes
        this->setChParam(MGR_PROP_GLE_ICON_SIZE, true);
      break;

    case IDC_BC_CKBX1: //< Check-Box for Display as raw text
      this->_onCkBoxRaw();
      break;

    case IDC_BC_CKBX2: //< Check-Box for Open Context(s) at startup
      this->_onCkBoxStr();
      break;

    case IDC_LB_PATH: //< List-Box for startup Context(s) list
      if(HIWORD(wParam) == LBN_SELCHANGE)
        this->_onLbStrlsSel();
      break;

    case IDC_BC_BRW01: //< Startup Context list "Add.." Button
      this->_onBcBrwStr();
      break;

    case IDC_BC_REM: //< Startup Context list "Remove" Button
      this->_onBcRemStr();
      break;
    }
  }

  return false;
}
