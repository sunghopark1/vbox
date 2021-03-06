################################################################
# Boilerplate text to be included by any DSC file using the
# Standard Libraries.
#
# The including DSC file must DEFINE the EMULATE macro if
# the application is to be run in an emulation environment.
#
#  Copyright (c) 2011, Intel Corporation. All rights reserved.<BR>
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution. The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
################################################################

##########
#  Socket Support Libraries
##########

[LibraryClasses.common]
  BsdSocketLib|StdLib/BsdSocketLib/BsdSocketLib.inf
  EfiSocketLib|StdLib/EfiSocketLib/EfiSocketLib.inf
  UseSocketDxe|StdLib/UseSocketDxe/UseSocketDxe.inf

[LibraryClasses.Common.UEFI_APPLICATION]
  #
  # C Standard Libraries
  #
  LibC|StdLib/LibC/LibC.inf
  LibCType|StdLib/LibC/Ctype/Ctype.inf
  LibLocale|StdLib/LibC/Locale/Locale.inf
  LibMath|StdLib/LibC/Math/Math.inf
  LibSignal|StdLib/LibC/Signal/Signal.inf
  LibStdio|StdLib/LibC/Stdio/Stdio.inf
  LibStdLib|StdLib/LibC/StdLib/StdLib.inf
  LibString|StdLib/LibC/String/String.inf
  LibTime|StdLib/LibC/Time/Time.inf
  LibUefi|StdLib/LibC/Uefi/Uefi.inf
  LibWchar|StdLib/LibC/Wchar/Wchar.inf

# Common Utilities for Networking Libraries
  LibNetUtil|StdLib/LibC/NetUtil/NetUtil.inf

# Additional libraries for POSIX functionality.
  LibErr|StdLib/PosixLib/Err/LibErr.inf
  LibGen|StdLib/PosixLib/Gen/LibGen.inf
  LibGlob|StdLib/PosixLib/Glob/LibGlob.inf
  LibStringlist|StdLib/PosixLib/Stringlist/LibStringlist.inf

# Libraries for device abstractions within the Standard C Library
# Applications should not directly access any functions defined in these libraries.
  LibGdtoa|StdLib/LibC/gdtoa/gdtoa.inf
  DevConsole|StdLib/LibC/Uefi/Devices/daConsole.inf
  DevShell|StdLib/LibC/Uefi/Devices/daShell.inf
  DevUtility|StdLib/LibC/Uefi/Devices/daUtility.inf

[LibraryClasses.ARM.UEFI_APPLICATION]
  NULL|ArmPkg/Library/CompilerIntrinsicsLib/CompilerIntrinsicsLib.inf

[Components]
# BaseLib and BaseMemoryLib need to be built with the /GL- switch when using the Microsoft
# tool chain.  This is required so that the library functions can be resolved during
# the second pass of the linker during Link-time-code-generation.
###
  MdePkg/Library/BaseLib/BaseLib.inf {
    <BuildOptions>
      MSFT:*_*_*_CC_FLAGS    = /X /Zc:wchar_t /GL-
  }

  MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf {
    <BuildOptions>
      MSFT:*_*_*_CC_FLAGS    = /X /Zc:wchar_t /GL-
  }

##########
#  Socket Layer
##########
  StdLib/SocketDxe/SocketDxe.inf


##############################################################################
#
# See the additional comments below if you plan to run applications under an
# emulation environment.
#

[BuildOptions]
!ifndef $(EMULATE)
  # These Build Options are used when building the Standard Libraries to be run
  # on real hardware.
  INTEL:*_*_*_CC_FLAGS      = /Qfreestanding
   MSFT:*_*_*_CC_FLAGS      = /X /Zc:wchar_t
    GCC:*_*_*_CC_FLAGS      = -nostdinc -nostdlib
    RVCT:*_*_*_CC_FLAGS      = --library_interface=none -J$(WORKSPACE)/StdLib/Include -J$(WORKSPACE)/StdLib/Include/Arm
  ARMGCC:*_*_*_CC_FLAGS      = -nostdinc -nostdlib -Wno-unknown-pragmas -Wno-unused -Wno-format-zero-length

!else
  # The Build Options, below, are only used when building the Standard Libraries
  # to be run under an emulation environment.
  # They disable optimization which facillitates debugging under the Emulation environment.
  INTEL:*_*_IA32_CC_FLAGS     = /Od
   MSFT:*_*_IA32_CC_FLAGS     = /Od
    GCC:*_*_IA32_CC_FLAGS     = -O0
    RVCT:*_*_*_CC_FLAGS      = --library_interface=none -J$(WORKSPACE)/StdLib/Include -J$(WORKSPACE)/StdLib/Include/Arm
  ARMGCC:*_*_*_CC_FLAGS      = -O0 -Wno-unknown-pragmas -Wno-unused -Wno-format-zero-length
!endif
