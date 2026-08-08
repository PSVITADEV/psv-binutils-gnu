
/* 
   Copyright (C) 2019 David "Davee" Morgan

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "defs.h"
#include "arm-tdep.h"
#include "osabi.h"

#include <string.h>

static bfd_boolean find_vitalink_section(bfd *abfd, asection *section, void *)
{
    return strncmp(section->name, ".vitalink", strlen(".vitalink")) == 0;
}

static void
arm_vita_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
    // enable single stepping for target
    set_gdbarch_software_single_step (gdbarch, arm_software_single_step);
}

static enum gdb_osabi
arm_vita_osabi_sniffer (bfd *abfd)
{
    // for vita we look for .vitalink. section
    if (bfd_sections_find_if(abfd, find_vitalink_section, NULL) != NULL)
        return GDB_OSABI_VITA;
    else
        return GDB_OSABI_UNKNOWN;
}

void
_initialize_arm_vita_tdep (void)
{
    gdbarch_register_osabi_sniffer (bfd_arch_arm, bfd_target_elf_flavour,
                                   arm_vita_osabi_sniffer);
    gdbarch_register_osabi (bfd_arch_arm, 0, GDB_OSABI_VITA,
                            arm_vita_init_abi);
}
