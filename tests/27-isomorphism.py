#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  A simple Berloga Autoborder test
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
    d1 = CyberiadaML.LocalDocument()
    d1.open(sys.argv[0] + "-graph1.graphml")
    sm1 = d1.get_state_machines()[0]
    d2 = CyberiadaML.LocalDocument()
    d2.open(sys.argv[0] + "-graph2.graphml")
    sm2 = d2.get_state_machines()[0]
    d3 = CyberiadaML.LocalDocument()
    d3.open(sys.argv[0] + "-graph3.graphml")
    sm3 = d3.get_state_machines()[0]
    d4 = CyberiadaML.LocalDocument()
    d4.open(sys.argv[0] + "-graph4.graphml")
    sm4 = d4.get_state_machines()[0]
    d5 = CyberiadaML.LocalDocument()
    d5.open(sys.argv[0] + "-graph5.graphml")
    sm5 = d5.get_state_machines()[0]
    assert sm1.check_isomorphism(sm2) == CyberiadaML.smiIdentical    
    assert sm1.check_isomorphism(sm3) == CyberiadaML.smiIsomorphic

    new_initial = ''
    diff_nodes = []
    diff_nodes_flags = []
    assert sm4.check_isomorphism(sm5, True, False, new_initial, diff_nodes, diff_nodes_flags) == CyberiadaML.smiIsomorphic
    assert len(diff_nodes) == 6
    assert diff_nodes[2] == 'n0::n0::n0'
    assert len(diff_nodes_flags)
    assert diff_nodes_flags[3] | CyberiadaML.smiNodeDiffFlagTitle
    for f in diff_nodes_flags:
        assert f | CyberiadaML.smiNodeDiffFlagID
except CyberiadaML.Exception as e:
    sys.stderr.write('Unexpected CyberiadaML exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
