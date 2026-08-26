#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The point comment geometry test
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
    # the strict load rejects the comment with point geometry
    try:
        bad = CyberiadaML.LocalDocument()
        bad.open(sys.argv[0] + "-input.graphml")
        exit(1)
    except CyberiadaML.CybMLException:
        pass

    # the reconstruction mode repairs the malformed geometry
    d = CyberiadaML.LocalDocument()
    d.open(sys.argv[0] + "-input.graphml", CyberiadaML.formatDetect,
           CyberiadaML.geometryFormatQt, True)
    sm = d.get_state_machines()[0]
    note = sm.find_element_by_id("cX")
    assert note
    assert note.get_type() == CyberiadaML.elementComment
    assert note.has_geometry()
    assert note.get_geometry_rect().valid
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
