#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The geometry arrange test: the seed order kept, the layout anew
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
    # the full layout puts n1 below the composite n0; drawn above it and small,
    # n1 stays above after the arrange, both laid out anew
    d = CyberiadaML.LocalDocument()
    d.open(sys.argv[0] + "-input.graphml")
    d.reconstruct_geometry(True)
    d.round_geometry()
    sm = d.get_state_machines()[0]

    def rect(element_id):
        # the rect is a reference into the element: its values are copied
        r = d.get_state_machines()[0].find_element_by_id(element_id).get_geometry_rect()
        return (r.x, r.y, r.width, r.height)

    p0, p1 = rect("n0"), rect("n1")
    print("the full layout: n1 below n0:", int(p1[1] > p0[1]))
    sm.find_element_by_id("n0").update_geometry(CyberiadaML.Rect(p0[0], p1[1], 10, 10))
    sm.find_element_by_id("n1").update_geometry(CyberiadaML.Rect(p1[0], p0[1], 10, 10))
    d.arrange_geometry(True)
    d.round_geometry()
    q0, q1 = rect("n0"), rect("n1")
    print("the arrange: n1 above n0:", int(q1[1] + q1[3] <= q0[1]))
    print("the sizes from the texts:", int(q1[2:] == p1[2:]))
    print("check:", int(d.check_geometry()))
    print(d)
except Exception:
    traceback.print_exc()
    sys.exit(1)
