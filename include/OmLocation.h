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

#ifndef OMLOCATION_H
#define OMLOCATION_H

#include "OmGlobal.h"
#include "OmConfig.h"
#include "OmPackage.h"

class OmContext;

#define PKG_SORTING_STAT 0x1
#define PKG_SORTING_NAME 0x2
#define PKG_SORTING_VERS 0x4
#define PKG_SORTING_REVERSE 0x100

/// \brief Location object for Context.
///
/// The Location object defines environment for package installation
/// destination, library and backup.
///
class OmLocation
{
  friend class OmPackage;

  public:

    /// \brief Constructor.
    ///
    /// Default constructor.
    ///
    OmLocation(OmContext* context);

    /// \brief Destructor.
    ///
    /// Default destructor.
    ///
    ~OmLocation();

    /// \brief Get last error string.
    ///
    /// Returns last error message string.
    ///
    /// \return Last error message string.
    ///
    const wstring& lastError() const {
      return _error;
    }

    /// \brief Check whether is valid.
    ///
    /// Checks whether this instance is correctly loaded a ready to use.
    ///
    /// \return True if this instance is valid, false otherwise.
    ///
    bool isValid() const {
      return _valid;
    }

    /// \brief Get Location UUID.
    ///
    /// Returns Location UUID.
    ///
    /// \return Location UUID.
    ///
    const wstring& uuid() const {
      return _uuid;
    }

    /// \brief Get Location title.
    ///
    /// Returns Location title.
    ///
    /// \return Location title.
    ///
    const wstring& title() const {
      return _title;
    }

    /// \brief Get Location index.
    ///
    /// Returns Location ordering index.
    ///
    /// \return Ordering index number.
    ///
    unsigned index() const {
      return _index;
    }

    /// \brief Get Location home directory.
    ///
    /// Returns home directory.
    ///
    /// \return Location home directory.
    ///
    const wstring& home() const {
      return _home;
    }

    /// \brief Get Location definition path.
    ///
    /// Returns Location definition file path.
    ///
    /// \return Location definition file path.
    ///
    const wstring& path() const {
      return _path;
    }

    /// \brief Get Location destination path.
    ///
    /// Returns Location packages installation destination directory.
    ///
    /// \return Location destination directory.
    ///
    const wstring& installDir() const {
      return _installDir;
    }

    /// \brief Get Location library path.
    ///
    /// Returns Location packages library directory.
    ///
    /// \return Packages library directory.
    ///
    const wstring& libraryDir() const {
      return _libraryDir;
    }

    /// \brief Get Location backup path.
    ///
    /// Returns Location packages installation backup directory.
    ///
    /// \return Backup directory.
    ///
    const wstring& backupDir() const {
      return _backupDir;
    }

    /// \brief Get backup compression level.
    ///
    /// Returns defined backup compression level.
    ///
    /// \return Zip compression level.
    ///
    int backupZipLevel() const {
      return _backupZipLevel;
    }

    /// \brief Verify Library folder access.
    ///
    /// Checks whether the Library folder is accessible. If Library folder is
    /// not valid, the function prompt a message dialog box to warn user and
    /// select a valid folder.
    ///
    /// \param[in]  hwnd    : Parent window handle (HWND) for dialog boxes.
    ///
    /// \return True if Library folder is accessible, false otherwise.
    ///
    bool libraryAccess(HWND hWnd = nullptr);

    /// \brief Verify Backup folder access.
    ///
    /// Checks whether the Backup folder is accessible. If Backup folder is
    /// not valid, the function prompt a message dialog box to warn user and
    /// select a valid folder.
    ///
    /// \param[in]  hwnd    : Parent window handle (HWND) for dialog boxes.
    ///
    /// \return True if Backup folder is accessible, false otherwise.
    ///
    bool backupAccess(HWND hWnd = nullptr);

    /// \brief Verify Location folder access.
    ///
    /// Checks whether the Location folder is accessible. If Location folder is
    /// not valid, the function prompt a message dialog box to warn user and
    /// select a valid folder.
    ///
    /// \param[in]  hwnd    : Parent window handle (HWND) for dialog boxes.
    ///
    /// \return True if Location folder is accessible, false otherwise.
    ///
    bool installAccess(HWND hWnd = nullptr);

    /// \brief Clear Location package list.
    ///
    /// Resets Location package list.
    ///
    void packageListClear();

    /// \brief Refresh Location package list.
    ///
    /// Refreshes the Location package list.
    ///
    void packageListRefresh();

    /// \brief Set package list sorting.
    ///
    /// Sets the package list sorting, available values are the following:
    /// - \c PKG_SORTING_STAT : Sort by installation state
    /// - \c PKG_SORTING_NAME : Sort by name
    /// - \c PKG_SORTING_VERS : Sort by version
    ///
    /// \param[in]  sorting : Package list sorting type.
    ///
    void setPackageSorting(unsigned sorting);

    /// \brief Get package list sorting.
    ///
    /// Sets the package list sorting.
    ///
    /// \return current package sorting mask.
    ///
    unsigned packageSorting() const {
      return _packageSorting;
    }

    /// \brief Get package count.
    ///
    /// Returns current package count in library.
    ///
    /// \return Package count.
    ///
    size_t packageCount() const {
      return _package.size();
    }

    /// \brief Get package.
    ///
    /// Returns package at index.
    ///
    /// \param[in]  i       : Package index to get.
    ///
    /// \return Package.
    ///
    OmPackage* package(unsigned i) const {
      return _package[i];
    }

    /// \brief Find package by hash.
    ///
    /// Find package by its computed hash.
    ///
    /// \param[in] hash  : Package hash to search.
    ///
    /// \return Package or nullptr if not found.
    ///
    OmPackage* findPackage(uint64_t hash) const {
      for(size_t i = 0; i < _package.size(); ++i) {
        if(_package[i]->hash() == hash) return _package[i];
      }
      return nullptr;
    }

    /// \brief Get package index.
    ///
    /// Returns package index in list.
    ///
    /// \param[in]  pkg     : Package to get index of.
    ///
    /// \return Package index or -1 if not found.
    ///
    int packageIndex(const OmPackage* pkg) const {
      for(size_t i = 0; i < _package.size(); ++i) {
        if(pkg == _package[i]) return i;
      }
      return -1;
    }

    /// \brief Find package index by hash.
    ///
    /// Find package index in list by its computed hash.
    ///
    /// \param[in] hash      : Package hash to search.
    ///
    /// \return Package index or -1 if not found.
    ///
    int findPackageIndex(uint64_t hash) const{
      for(size_t i = 0; i < _package.size(); ++i) {
        if(_package[i]->hash() == hash) return i;
      }
      return -1;
    }

    /// \brief Open Location.
    ///
    /// Load Location from specified file.
    ///
    /// \param[in]  path    : File path of Location to be loaded.
    ///
    /// \return True if operation succeed, false otherwise.
    ///
    bool open(const wstring& path);

    /// \brief Close Location.
    ///
    /// Close and empty the current instance.
    ///
    void close();

    /// \brief Set Location title.
    ///
    /// Defines and save Location title.
    ///
    /// \param[in]  title   : Title to defines and save
    ///
    void setTitle(const wstring& title);

    /// \brief Set Location index.
    ///
    /// Defines and save Location index for ordering.
    ///
    /// \param[in]  index   : Index number to defines and save
    ///
    void setIndex(unsigned index);

    /// \brief Set Location destination path.
    ///
    /// Defines and save Location installation destination path.
    ///
    /// \param[in]  path    : destination path to save.
    ///
    void setInstallDir(const wstring& path);

    /// \brief Set custom Library folder.
    ///
    /// Defines and save a custom package Library folder. If custom
    /// Library folder is not defined, the default location is used:
    /// <Location path>\library
    ///
    /// \param[in]  path    : Custom Library folder path to save.
    ///
    void setCustLibraryDir(const wstring& path);

    /// \brief Check for custom Library.
    ///
    /// Checks whether this instance currently has and use a custom
    /// Library folder path.
    ///
    /// \return True if a custom Library path is used, false otherwise.
    ///
    bool hasCustLibraryDir() const {
      return _custLibraryDir;
    }

    /// \brief Remove custom Backup.
    ///
    /// Removes the current custom Backup configuration and reset to
    /// default settings.
    ///
    void remCustLibraryDir();

    /// \brief Set custom Backup folder.
    ///
    /// Defines and save a custom package Backup folder. If custom
    /// Backup folder is not defined, the default location is used:
    /// <Location path>\backup
    ///
    /// \param[in]  path    : Custom Backup folder path to save.
    ///
    void setCustBackupDir(const wstring& path);

    /// \brief Check for custom Backup.
    ///
    /// Checks whether this instance currently has and use a custom
    /// Backup folder path.
    ///
    /// \return True if a custom Backup path is used, false otherwise.
    ///
    bool hasCustBackupDir() const {
      return _custBackupDir;
    }

    /// \brief Remove custom Backup.
    ///
    /// Removes the current custom Backup configuration and reset to
    /// default settings.
    ///
    void remCustBackupDir();

    /// \brief Set Backup compression level.
    ///
    /// Defines and save backup compression level. A negative value
    /// means create directory backup instead of zipped backup.
    ///
    /// \param[in]  level   : Zip compression level to save.
    ///
    void setBackupZipLevel(int level);

    /// \brief Rename Location
    ///
    /// Truly rename Location definition name and home folder according
    /// the new title.
    ///
    /// \param[in]  title   : Destination folder to move backup data to.
    /// \param[in]  hWnd    : Parent window handle (HWND) for warning messages.
    ///
    /// \return True if operation succeed, false otherwise.
    ///
    bool rename(const wstring& title, HWND hWnd = nullptr);

    /// \brief Move backup
    ///
    /// If destination folder is different from the current Backup folder,
    /// moves all current Backup folder content to the specified location.
    ///
    /// Notice this function only moves data and does not changes the
    /// current Backup folder path. This function should be used in conjunction
    /// with Location.setCustBackup or Location.remCustBackup.
    ///
    /// \param[in]  dest    : Destination folder to move backup data to.
    /// \param[in]  hWnd    : Parent window handle (HWND) for warning messages.
    /// \param[in]  hSc    : Progress Bar control handle (HWND) to be updated during process.
    ///
    void moveBackups(const wstring& dest, HWND hWnd = nullptr, HWND hPb = nullptr, HWND hSc = nullptr, const bool *pAbort = nullptr);

    /// \brief Cleanup backup data.
    ///
    /// Uninstall all installed package package(s) to cleanup all backup data.
    ///
    /// \param[in]  hWnd       : Parent window handle (HWND) for warning messages.
    /// \param[in]  hSc        : Progress Bar control handle (HWND) to be updated during process.
    /// \param[in]  hSc        : Static Label control handle (HWND) to be updated during process.
    /// \param[in]  pAbort     : Pointer to boolean to cancel operation.
    ///
    void purgeBackups(HWND hWnd, HWND hPb = nullptr, HWND hSc = nullptr, const bool *pAbort = nullptr);

    /// \brief Install package(s).
    ///
    /// Installs one or several package(s) according Location environment.
    ///
    /// \param[in]  selec_list  : List of package index to install.
    /// \param[in]  quiet       : Do not throw warning messages.
    /// \param[in]  hWnd        : Parent window handle (HWND) for warning messages.
    /// \param[in]  hLv         : List View control handle (HWND) to be updated during process.
    /// \param[in]  hSc         : Progress Bar control handle (HWND) to be updated during process.
    /// \param[in]  pAbort      : Pointer to boolean to cancel operation.
    ///
    void installSelection(const vector<unsigned>& selec_list, bool quiet, HWND hWnd = nullptr, HWND hLv = nullptr, HWND hPb = nullptr, const bool *pAbort = nullptr);

    /// \brief Uninstall package(s).
    ///
    /// Uninstall one or several package(s) according Location environment.
    ///
    /// \param[in]  selec_list  : List of package index to uninstall.
    /// \param[in]  quiet       : Do not throw warning messages.
    /// \param[in]  hWnd        : Parent window handle (HWND) for warning messages.
    /// \param[in]  hLv         : List View control handle (HWND) to be updated during process.
    /// \param[in]  hSc         : Progress Bar control handle (HWND) to be updated during process.
    /// \param[in]  pAbort      : Pointer to boolean to cancel operation.
    ///
    void uninstSelection(const vector<unsigned>& selec_list, bool quiet, HWND hWnd = nullptr, HWND hLv = nullptr, HWND hPb = nullptr, const bool *pAbort = nullptr);

    /// \brief Get installation overlap list.
    ///
    /// Retrieve the list of Packages the specified Package could overlap at
    /// installation.
    ///
    /// \param[in]  pkg_list  : Array vector of Package object pointer to receive found packages.
    /// \param[in]  package   : Package to get backup overlap.
    ///
    /// \return Count of Package found.
    ///
    size_t getInstallOverlapList(vector<OmPackage*>& pkg_list, const OmPackage* package) const;

    /// \brief Get installation overlap list.
    ///
    /// Retrieve the list of Packages the specified Package could overlap at
    /// installation.
    ///
    /// \param[in]  hash_list : Array vector of uint64_t to receive found packages Hash.
    /// \param[in]  package   : Package to get backup overlap.
    ///
    /// \return Count of Package found.
    ///
    size_t getInstallOverlapList(vector<uint64_t>& hash_list, const OmPackage* package) const;

    /// \brief Get installation dependency list.
    ///
    /// Retrieve the package installation dependencies.
    ///
    /// \param[in]  pkg_list  : Array vector of Package pointer to receive found packages.
    /// \param[in]  miss_list : Array vector of Package pointer to receive missing packages name.
    /// \param[in]  i         : Package index in Library to get installation dependencies.
    ///
    /// \return Count of Package found.
    ///
    size_t getInstallExtraList(vector<OmPackage*>& pkg_list, vector<wstring>& miss_list, unsigned i) const {
      return getInstallExtraList(pkg_list, miss_list, _package[i]);
    }

    /// \brief Get installation dependency list.
    ///
    /// Retrieve the package installation dependencies.
    ///
    /// \param[in]  pkg_list  : Array vector of Package pointer to receive found packages.
    /// \param[in]  miss_list : Array vector of Package pointer to receive missing packages name.
    /// \param[in]  package   : Package to get installation dependencies.
    ///
    /// \return Count of Package found.
    ///
    size_t getInstallExtraList(vector<OmPackage*>& pkg_list, vector<wstring>& miss_list, const OmPackage* package) const;

    /// \brief Get restoration dependency list.
    ///
    /// Retrieve the package restoration dependencies, meaning, the list
    /// of overlapping backup of this package.
    ///
    /// \param[in]  pkg_list  : Array vector of Package pointer to receive list.
    /// \param[in]  i         : Package index in Library to get restoration dependencies.
    ///
    /// \return Count of Package found.
    ///
    size_t getUninstExtraList(vector<OmPackage*>& pkg_list, unsigned i) const {
      return getUninstExtraList(pkg_list, _package[i]);
    }

    /// \brief Get restoration dependency list.
    ///
    /// Retrieve the package restoration dependencies, meaning, the list
    /// of overlapping backup of this package.
    ///
    /// \param[in]  pkg_list  : Array vector of Package pointer to receive list.
    /// \param[in]  package   : Package to get restoration dependencies.
    ///
    /// \return Count of Package found.
    ///
    size_t getUninstExtraList(vector<OmPackage*>& pkg_list, const OmPackage* package) const;

    /// \brief check backup overlap.
    ///
    /// Checks whether the given package backup is overlapped by one or more
    /// other package(s).
    ///
    /// \param[in]  i           : Package index in Library to checks backup overlap.
    ///
    /// \return True if package is overlapped, false otherwise.
    ///
    bool isBakcupOverlapped(unsigned i) const {
      return isBakcupOverlapped(_package[i]);
    }

    /// \brief check backup overlap.
    ///
    /// Checks whether the given package backup is overlapped by one or more
    /// other package(s).
    ///
    /// \param[in]  package     : Package to checks backup overlap.
    ///
    /// \return True if package is overlapped, false otherwise.
    ///
    bool isBakcupOverlapped(const OmPackage* package) const {
      for(size_t i = 0; i < _package.size(); ++i) {
        if(_package[i]->hasOverlap(package->_hash))
          return true;
      }
      return false;
    }

    /// \brief Add log.
    ///
    /// Add entry to log file.
    ///
    void log(unsigned level, const wstring& head, const wstring& detail);

  private: ///          - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void                _packageSort();

    OmContext*          _context;

    OmConfig            _config;

    wstring             _uuid;

    wstring             _title;

    unsigned            _index;

    wstring             _home;

    wstring             _path;

    wstring             _installDir;

    wstring             _libraryDir;

    bool                _custLibraryDir;

    wstring             _backupDir;

    bool                _custBackupDir;

    vector<OmPackage*>  _package;

    int                 _backupZipLevel;

    unsigned            _packageSorting;

    bool                _valid;

    wstring             _error;

};

#endif // OMLOCATION_H
