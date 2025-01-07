#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The two statemachines test
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
    d = CyberiadaML.Document()
    d.new_state_machine("SM1", CyberiadaML.Rect())
    try:
        # check id uniqueness
        d.new_state_machine("G0", "SM2", CyberiadaML.Rect())
    except CyberiadaML.ParametersException:
        pass
    d.new_state_machine("SM2", CyberiadaML.Rect(1, 2, 300, 40))
    print(d)
    CyberiadaML.LocalDocument(d, sys.argv[0] + ".graphml").save()
except CyberiadaML.Exception as e:
    sys.stderr.write('Unexpected CyberiadaML exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)

