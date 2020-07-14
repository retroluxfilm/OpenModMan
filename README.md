----------------------------------------------------------------------------------------
Open Mod Mananager
----------------------------------------------------------------------------------------

Open source and generic Mod ("Modifications") manager.


Version: 0.9.1 (beta)
----------------------------------------------------------------------------------------


Presentation
----------------------------------------------------------------------------------------
The purpose of Open Mod Manager is to provide an easy and safety way to organize,
install, uninstall and create generic packages of third-party tweaks or add-ons (also
called "mod") to be applied to any software (usually games).

It provide an advanced "mod" management using "packages" paradigm with support for
dependencies and advanced automatic backup logics to prevent software's original files
corruption.

Accent is made to flexibility and modularity by providing an open configuration logics
based on human-readable XML files and simple folders architecture witch can be easily
saved, deleted or altered.


Features
----------------------------------------------------------------------------------------
Open Mod Mananager currently implements the following key features:

- Flexible and modular XML and folder configuration logic.
- Multiple installation destinations per configuration context.
- Custom folders for packages (Mods) library and backup per installation destination.
- Support for both folders (legacy) Mods and advanced zipped Packages.
- Smart installation and backup mechanism allowing overlapped installed files.
- Packages installation dependencies mechanism (advanced packages).
- Backup data compressed as zip archives to save space (optional).
- Batch mechanism for automatic Package installation sequences.

Screenshots
----------------------------------------------------------------------------------------
![Open Mod Mananager Screenshot](snaps/screenshot.png)

Version history
----------------------------------------------------------------------------------------

0.9.2
 - Rewritten Package building algorithm.
 - Fixed Package "Save As" button never enabling.
 - Replace GPL text by credits in the "About" dialog.
 - Rewritten file/directory Access-Control check mechanisms.
 - Improved Unicode and non-ASCII characters support.
 - Fixed incorrect packages list refresh after move to trash.

0.9.1 (07/11/2020)
 - Fixed random string bug and crash caused by buffer overflow.
 - Fixed Context creation wizard not properly reseted after cancel by user.
 - Fixed missing application informations and icons within Windows Application list.
 - Algorithm to check file and folder access permissions slightly modified.

0.9.0 (07/08/2020)
 - First public BETA release
