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
#ifndef OMUIMGRMAINTST_H
#define OMUIMGRMAINTST_H

#include "OmDialog.h"

/// \brief Main window - Test Tab child
///
/// OmDialog class derived for Main window Test tab child dialog window
/// This dialog has only development and debug purposes
///
class OmUiMgrMainTst : public OmDialog
{
  public: ///          - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    /// \brief Constructor.
    ///
    /// Default constructor.
    ///
    /// \param[in]  hins    : API Instance handle.
    ///
    OmUiMgrMainTst(HINSTANCE hins);

    /// \brief Destructor.
    ///
    /// Default destructor.
    ///
    ~OmUiMgrMainTst();

    /// \brief Get resource id.
    ///
    /// Returns dialog window resource id.
    ///
    /// \return dialog resource id.
    ///
    long id() const;

  private: ///          - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    OmUiMgr*            _pUiMgr;

    void                _onInit();

    void                _onShow();

    void                _onHide();

    void                _onResize();

    void                _onRefresh();

    void                _onQuit();

    INT_PTR             _onMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // OMUIMGRMAINTST_H
