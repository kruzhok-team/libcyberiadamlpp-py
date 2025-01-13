#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  A Cyberiada GraphML geometry test
# 
#  Copyright (C) 2025 Alexey Fedoseev <aleksey@fedoseev.net>
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
    d.open(sys.argv[0] + "-input.graphml", CyberiadaML.formatDetect, CyberiadaML.geometryFormatNone)
    print(d)
    d.open(sys.argv[0] + "-input.graphml", CyberiadaML.formatDetect, CyberiadaML.geometryFormatLegacyYED)
    print(d)
    d.open(sys.argv[0] + "-input.graphml", CyberiadaML.formatDetect, CyberiadaML.geometryFormatCyberiada10)
    print(d)
    d.open(sys.argv[0] + "-input.graphml", CyberiadaML.formatDetect, CyberiadaML.geometryFormatQt)
    d.round_geometry()
    print(d)
    d.save_as(sys.argv[0] + ".graphml", CyberiadaML.formatCyberiada10)
except CyberiadaML.Exception as e:
    sys.stderr.write('Unexpected CyberiadaML exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
