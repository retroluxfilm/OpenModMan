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
#ifndef OMUIMGRMAINLIB_H
#define OMUIMGRMAINLIB_H

#include "OmDialog.h"

class OmUiMgr;
//class OmContext;

/// \brief Main window - Library tab child
///
/// OmDialog class derived for Main window Library tab child dialog window
///
class OmUiMgrMainLib : public OmDialog
{
  public:

    /// \brief Constructor.
    ///
    /// Default constructor.
    ///
    /// \param[in]  hins    : API Instance handle.
    ///
    OmUiMgrMainLib(HINSTANCE hins);

    /// \brief Destructor.
    ///
    /// Default destructor.
    ///
    ~OmUiMgrMainLib();

    /// \brief Get resource id.
    ///
    /// Returns dialog window resource id.
    ///
    /// \return dialog resource id.
    ///
    long id() const;

    /// \brief Set dialog freeze mode
    ///
    /// Enable or disable the dialog freeze mode.
    ///
    /// The freeze mode is a modal-kind emulation for threaded operations,
    /// it disables (almost) all controls of the dialog and its children
    /// to prevent user to interact with elements while a threaded process
    /// is running.
    ///
    /// \param[in]  enable  : Enable or disable freeze mode.
    ///
    void freeze(bool enable);

    /// \brief Set dialog safe mode
    ///
    /// Enables or disable the dialog safe mode.
    ///
    /// The safe mode is used to operate modifications on sensitive
    /// or monitored elements such as deleting or moving Location in
    /// order to prevent conflicts or crash during process.
    ///
    /// \param[in]  enable  : Enable or disable safe mode.
    ///
    void safemode(bool enable);

    /// \brief Select Location
    ///
    /// Select or unselect Location then refresh dialog.
    ///
    /// \param[in]  i  Index of Location to select or -1 to select none.
    ///
    void locSel(int i);

    /// \brief Install selected packages.
    ///
    /// Public function to launch install process for selected packages if
    /// any.
    ///
    void pkgInst();

    /// \brief Uninstall selected packages.
    ///
    /// Public function to launch unsintall process for selected packages if
    /// any.
    ///
    void pkgUnin();

    /// \brief Cleanse selected packages.
    ///
    /// Public function to launch cleanse unsintall process for selected packages if
    /// any.
    ///
    void pkgClns();

    /// \brief Toggle selected packages installation.
    ///
    /// Public function to toggle installation (either install or uninstall) of
    /// the selected packages if any.
    ///
    void pkgTogg();

    /// \brief View package details.
    ///
    /// Public function to open selected package property dialog.
    ///
    void pkgProp();

    /// \brief Move package to trash.
    ///
    /// Public function to move selected package to trash.
    ///
    void pkgTrsh();

    /// \brief Open package in explorer.
    ///
    /// Public function to open package in file explorer.
    ///
    void pkgOpen();

    /// \brief Open package in package editor.
    ///
    /// Public function to open package in package editor.
    ///
    void pkgEdit();

  private: ///          - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    OmUiMgr*            _pUiMgr;

    void                _pkgInstLs(const vector<OmPackage*>& pkg_ls, bool silent = false);

    void                _pkgUninLs(const vector<OmPackage*>& pkg_ls, bool silent = false);

    void                _pkgClnsLs(const vector<OmPackage*>& pkg_ls, bool silent = false);

    static bool         _pkgProgressCb(void* ptr, size_t tot, size_t cur, uint64_t data);

    void                _dirMon_init(const wstring& path);

    void                _dirMon_stop();

    void*               _dirMon_hth;

    void*               _dirMon_hev[3];

    static DWORD WINAPI _dirMon_fth(void*);

    void                _pkgInst_init();

    void                _pkgInst_stop();

    void*               _pkgInst_hth;

    static DWORD WINAPI _pkgInst_fth(void*);

    void                _pkgUnin_init();

    void                _pkgUnin_stop();

    void*               _pkgUnin_hth;

    static DWORD WINAPI _pkgUnin_fth(void*);

    void                _pkgClns_init();

    void                _pkgClns_stop();

    void*               _pkgClns_hth;

    static DWORD WINAPI _pkgClns_fth(void*);

    void                _batExe_init();

    void                _batExe_stop();

    void*               _batExe_hth;

    static DWORD WINAPI _batExe_fth(void*);

    bool                _thread_abort;

    void                _buildCbLoc();

    void                _buildLvBat();

    void                _rsizeLvBat();

    unsigned            _buildLvBat_icSize;

    void                _buildEcLib();

    void                _buildLvPkg();

    void                _rsizeLvPkg();

    unsigned            _buildLvPkg_icSize;

    bool                _buildLvPkg_legacy;

    void                _onCbLocSel();

    void                _onLvPkgRclk();

    void                _onLvPkgSel();

    void                _onLvBatSel();

    void                _onBcRunBat();

    void                _onBcNewBat();

    void                _onBcEdiBat();

    void                _onInit();

    void                _onShow();

    void                _onHide();

    void                _onResize();

    void                _onRefresh();

    void                _onQuit();

    INT_PTR             _onMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // OMUIMGRMAINLIB_H
