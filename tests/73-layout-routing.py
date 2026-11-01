#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The layout routing test: the orthogonal routes of the reconstruction, the
#  update and the arrange, the polylines the default
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
    o = CyberiadaML.LocalDocument()
    d.open(sys.argv[0] + "-input.graphml")
    o.open(sys.argv[0] + "-input.graphml")
    d.reconstruct_geometry(True)
    o.reconstruct_geometry(True, CyberiadaML.layoutRoutingPolyline)
    d.round_geometry()
    o.round_geometry()
    print("the polylines the default:", int(str(d) == str(o)))
    o.reconstruct_geometry(True, routing=CyberiadaML.layoutRoutingOrthogonal)
    o.round_geometry()
    print("the orthogonal routes differ:", int(str(d) != str(o)))
    print("check:", int(o.check_geometry()))
    o.update_geometry(True, CyberiadaML.layoutRoutingOrthogonal)
    print("the update check:", int(o.check_geometry()))
    o.arrange_geometry(True, CyberiadaML.layoutRoutingOrthogonal)
    o.round_geometry()
    print("the arrange check:", int(o.check_geometry()))
    print(o)
except Exception:
    traceback.print_exc()
    sys.exit(1)
