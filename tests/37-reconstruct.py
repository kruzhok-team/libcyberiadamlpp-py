#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  A geometry reconstruction test
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
    # the full reconstruction of a geometry-less document
    d = CyberiadaML.LocalDocument()
    d.open(sys.argv[0] + "-input.graphml")
    d.reconstruct_geometry(True)
    d.round_geometry()
    print(d)

    # the read-path fill-in: only the edges lack geometry
    p = CyberiadaML.LocalDocument()
    p.open("tests/23-cyb-autoborder.py-input.graphml", CyberiadaML.formatDetect,
           CyberiadaML.geometryFormatQt, True, True)
    p.round_geometry()
    print(p)

    # the metainformation node is not displayed (6.9): the reconstruction
    # leaves it and the comment edge it carries out of the geometry
    m = CyberiadaML.LocalDocument()
    m.open(sys.argv[0] + "-input2.graphml")
    m.reconstruct_geometry(True)
    m.round_geometry()
    meta = m.find_element_by_id("nMeta")
    assert meta and meta.get_type() == CyberiadaML.elementFormalComment
    assert not meta.has_geometry()
    assert m.find_element_by_id("n0").has_geometry()
    print(CyberiadaML.Document(m))
except CyberiadaML.Exception as e:
    sys.stderr.write('Unexpected CyberiadaML exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
