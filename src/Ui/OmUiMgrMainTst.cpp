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

#include "OmBaseWin.h"
  #include <UxTheme.h>

#include "OmManager.h"
#include "Ui/OmUiMgr.h"

#include "Util/OmUtilWin.h"

//#include "3rdP/cwb/cwb.h"

///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
#include "Ui/OmUiMgrMainTst.h"

///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
OmUiMgrMainTst::OmUiMgrMainTst(HINSTANCE hins) : OmDialog(hins),
  _pUiMgr(nullptr),
  _hdivHwnd(nullptr),
  _hdivHovr(false),
  _hdivCur{100,0},
  _hdivOld{0,0}
{


}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
OmUiMgrMainTst::~OmUiMgrMainTst()
{

}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
long OmUiMgrMainTst::id() const
{
  return IDD_MGR_MAIN_TST;
}


///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiMgrMainTst::_onInit()
{
  // retrieve main dialog
  this->_pUiMgr = static_cast<OmUiMgr*>(this->root());

  //SetWindowLongPtr(this->_hwnd, GWL_STYLE, WS_CHILD|WS_BORDER); //3d argument=style
  SetWindowLongPtr(this->_hwnd, GWL_EXSTYLE, WS_EX_STATICEDGE); //3d argument=style

  this->enableItem(IDC_SC_SEPAR, false);
  // set white background to fit tab background
  EnableThemeDialogTexture(this->getItem(IDC_SC_SEPAR), ETDT_ENABLETAB);

  // Defines fonts for package description, title, and log output
  HFONT hFt = Om_createFont(21, 400, L"Ms Shell Dlg");
  this->msgItem(IDC_SC_TITLE, WM_SETFONT, reinterpret_cast<WPARAM>(hFt), true);

  //WebBrowserCreate(0, WS_CHILD, this->_hwnd, reinterpret_cast<HMENU>(IDC_SC_HTML), this->_hins);
  //WebBrowserAttach(this->getItem(IDC_SC_HTML), nullptr);

  this->enableItem(IDC_SC_HTML, false);

  wstring html =
    L"<html><head>"
    "<style>"
    "  body {text-align:center; border:0; overflow:auto; font-family:helvetica;}"
    "  h1 {font-size: 1em;}"
    "</style>"
    "</head><body oncontextmenu=\"return false;\">"
    "<h1>This is a test</h1>"
    "</body></html>";

  //WebBrowserDocumentClose(this->getItem(IDC_SC_HTML));
  //WebBrowserDocumentWrite(this->getItem(IDC_SC_HTML), html.c_str());

  // splitter handle
  this->_hdivHwnd = this->getItem(IDC_SC_SEPAR);
  // initial splitter position
  this->_hdivCur[1] = this->cliUnitY() - this->_hdivCur[0];
}

///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiMgrMainTst::_onShow()
{

}

///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiMgrMainTst::_onHide()
{

}

///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiMgrMainTst::_onResize()
{
  // Horizontal separator
  this->_setItemPos(IDC_SC_SEPAR, 5, this->_hdivCur[1], this->cliUnitX()-10, 1);
  // Title
  this->_setItemPos(IDC_SC_TITLE, 5, this->_hdivCur[1] + 2, this->cliUnitX()-161, 12);
  // HTML Frame
  this->_setItemPos(IDC_SC_HTML, 5, this->_hdivCur[1] + 17, this->cliUnitX()-10, 78);
}

///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiMgrMainTst::_onRefresh()
{

}

///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
void OmUiMgrMainTst::_onQuit()
{

}

///
///  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
///
INT_PTR OmUiMgrMainTst::_onMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if(uMsg == WM_LBUTTONDOWN) {

    #ifdef DEBUG
    std::cout << "DEBUG => OmUiMgrMainTst::_onMsg : WM_LBUTTONDOWN\n";
    #endif

    if(this->_hdivHovr) {

      this->_hdivOld[0] = this->_hdivCur[0];
      this->_hdivOld[1] = HIWORD(lParam);

      SetCapture(this->_hwnd);
    }

  }

  if(uMsg == WM_LBUTTONUP) {

    #ifdef DEBUG
    std::cout << "DEBUG => OmUiMgrMainTst::_onMsg : WM_LBUTTONUP\n";
    #endif

    if(GetCapture() == this->_hwnd) {
      ReleaseCapture();
    }
  }

  if(uMsg == WM_MOUSEMOVE) {

    long y = HIWORD(lParam);

    if(GetCapture() == this->_hwnd) {

      this->_hdivCur[0] = this->_hdivOld[0] + MulDiv(this->_hdivOld[1] - y, 8, this->ubaseY());

      if(this->_hdivCur[0] < 100) this->_hdivCur[0] = 100;
      if(this->_hdivCur[0] > this->cliUnitY()-100) this->_hdivCur[0] = this->cliUnitY() - 100;

      // splitter position
      this->_hdivCur[1] = this->cliUnitY() - this->_hdivCur[0];

      this->_onResize();

    } else {

      long pos[4];

      GetWindowRect(this->_hdivHwnd, reinterpret_cast<LPRECT>(&pos));
      MapWindowPoints(HWND_DESKTOP, this->_hwnd, reinterpret_cast<LPPOINT>(&pos), 1);

      this->_hdivHovr = (y > (pos[1] - 5) && y < (pos[1] + 5));
    }

    return true;
  }

  if(uMsg == WM_SETCURSOR) {

    if(this->_hdivHovr) {

      SetCursor(LoadCursor(0,IDC_SIZENS));

      return true;
    }
  }

  if(uMsg == WM_COMMAND) {

  }

  return false;
}