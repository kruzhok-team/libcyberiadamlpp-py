#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The regionGeometry meta parameter test: set, saved, read back, removed
# 
#  Copyright (C) 2026 Alexey Fedoseev <aleksey@fedoseev.net>
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see https://www.gnu.org/licenses/
#  ----------------------------------------------------------------------------- 

import sys
import traceback
import CyberiadaML

try:
    d = CyberiadaML.LocalDocument()
    d.open(sys.argv[0] + "-input.graphml")
    print("read:", int(d.meta().regions_stored()))
    d.meta().set_regions_stored(True)
    print("set:", int(d.meta().regions_stored()))
    path = sys.argv[0] + "-saved.graphml"
    d.save_as(path, CyberiadaML.formatCyberiada10)
    saved = CyberiadaML.LocalDocument()
    saved.open(path)
    print("read back:", int(saved.meta().regions_stored()))
    saved.meta().set_regions_stored(False)
    print("removed:", int(saved.meta().regions_stored()))
except Exception:
    traceback.print_exc()
    sys.exit(1)
